// -*- C++ -*-
//
// Package:    NuclIntNtuplizer
// Class:      NuclIntNtuplizer
// 
/**\class NuclIntNtuplizer NuclIntNtuplizer.cc Tests/NuclIntTest/src/NuclIntNtuplizer.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Giuseppe Cerati
//         Created:  Wed Aug 19 15:39:10 CEST 2009
// $Id: NuclIntNtuplizer.cc,v 1.3 2010/05/06 16:05:35 cerati Exp $
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ParameterSet/interface/InputTag.h"

#include "DataFormats/ParticleFlowReco/interface/PFDisplacedVertex.h"
#include "DataFormats/ParticleFlowReco/interface/PFDisplacedVertexFwd.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

#include "SimTracker/Records/interface/TrackAssociatorRecord.h"
#include "SimDataFormats/TrackingAnalysis/interface/TrackingVertexContainer.h"

#include "SimTracker/Records/interface/TrackAssociatorRecord.h"
#include "SimTracker/TrackAssociation/interface/TrackAssociatorBase.h"
#include "DataFormats/Common/interface/RefToBaseVector.h"

#include <TH1F.h>
#include <TH2F.h>
#include <TFile.h>
#include <TTree.h>

typedef struct { 
  int run, event;
  int isAssoc;
  float pt, phi, theta;
  float ptOut, phiOut, thetaOut, mOut;
  int nOut;
  bool isTherePrimaryTrack, isThereMergedTrack;
  bool isNucl, isNuclLoose, isNuclKink;
  bool isK0, isLambda, isLambdaBar, isKplusLoose, isKminusLoose;
  bool isLooper, isConvLoose, isFake;
  float x, y, z;
  float deltapt, deltaphi, deltatheta, deltax, deltay, deltaz;
} SIMTORECO;

typedef struct { 
  int run, event;
  int isAssoc;
  float pt, phi, theta;
  float ptOut, phiOut, thetaOut, mOut, angle;
  int nOut, nOutTkStep67Good, nOutTkStep67Poor;
  bool isTherePrimaryTrack, isThereMergedTrack;
  bool isNucl, isNuclLoose, isNuclKink;
  bool isK0, isLambda, isLambdaBar, isKplusLoose, isKminusLoose;
  bool isLooper, isConvLoose, isFake;
  float x, y, z;
  float deltapt, deltaphi, deltatheta, deltax, deltay, deltaz, 
    deltapt_InSim_OutRec, deltaphi_InSim_OutRec, deltatheta_InSim_OutRec;
  std::vector<float> tkPt,tkEta,tkDxy,tkDz,tkRho;
  std::vector<int> tkHits,tkAlgo,tkOuter;
  std::vector<bool> tkPrimary, tkSecondary;

} RECOTOSIM;

class NuclIntNtuplizer : public edm::EDAnalyzer {
public:
  explicit NuclIntNtuplizer(const edm::ParameterSet&);
  ~NuclIntNtuplizer();
    
private:
  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
  bool isNuclInt(const TrackingVertex&) const;  

  TFile * file;
  std::string outfile;
  bool hitassoc;
  bool simulation;
  bool prints;
  SIMTORECO s2rbranch;
  RECOTOSIM r2sbranch;
  TTree *ntupleS2R,*ntupleR2S;
};

NuclIntNtuplizer::NuclIntNtuplizer(const edm::ParameterSet& iConfig) :
  outfile(iConfig.getParameter<std::string>("outfile")),
  hitassoc(iConfig.getParameter<bool>("hitassoc")),
  simulation(iConfig.getParameter<bool>("simulation")), 
  prints(iConfig.getParameter<bool>("prints")) ,
  ntupleS2R(0),ntupleR2S(0)
{ }


NuclIntNtuplizer::~NuclIntNtuplizer() { }

void NuclIntNtuplizer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
  using namespace std;

  if (prints) cout << "new evt" << endl;

  s2rbranch.run=iEvent.run();
  s2rbranch.event=iEvent.id().event();
  s2rbranch.isAssoc =0;
  s2rbranch.pt =0;
  s2rbranch.phi =0;
  s2rbranch.theta =0;
  s2rbranch.ptOut =0;
  s2rbranch.phiOut =0;
  s2rbranch.thetaOut =0;
  s2rbranch.mOut =0;
  s2rbranch.nOut =0;
  s2rbranch.x =0;
  s2rbranch.y =0;
  s2rbranch.z =0;
  s2rbranch.deltapt =0;
  s2rbranch.deltaphi =0;
  s2rbranch.deltatheta =0;
  s2rbranch.deltax =0;
  s2rbranch.deltay =0;
  s2rbranch.deltaz =0;
  s2rbranch.isNucl =0;
  s2rbranch.isNuclLoose =0;
  s2rbranch.isNuclKink =0;

  s2rbranch.isK0 =0;
  s2rbranch.isLambda =0;
  s2rbranch.isLambdaBar =0;
  s2rbranch.isKplusLoose =0;
  s2rbranch.isKminusLoose  =0;
  s2rbranch.isConvLoose =0;
  s2rbranch.isLooper =0;
  s2rbranch.isFake =0;

  s2rbranch.isTherePrimaryTrack = 0;
  s2rbranch.isThereMergedTrack = 0;


  r2sbranch.run=iEvent.run();
  r2sbranch.event=iEvent.id().event();
  r2sbranch.isAssoc =0;
  r2sbranch.pt =0;
  r2sbranch.phi =0;
  r2sbranch.theta =0;
  r2sbranch.ptOut =0;
  r2sbranch.phiOut =0;
  r2sbranch.thetaOut =0;
  r2sbranch.mOut =0;
  r2sbranch.nOutTkStep67Good =0;
  r2sbranch.nOutTkStep67Poor =0;

  r2sbranch.angle =0;
  r2sbranch.nOut =0;
  r2sbranch.x =0;
  r2sbranch.y =0;
  r2sbranch.z =0;
  r2sbranch.deltapt =0;
  r2sbranch.deltaphi =0;
  r2sbranch.deltatheta =0;
  r2sbranch.deltapt_InSim_OutRec = 0;
  r2sbranch.deltaphi_InSim_OutRec = 0;
  r2sbranch.deltatheta_InSim_OutRec = 0;
  r2sbranch.deltax =0;
  r2sbranch.deltay =0;
  r2sbranch.deltaz =0;
  r2sbranch.isNucl =0;
  r2sbranch.isNuclLoose =0;
  r2sbranch.isNuclKink =0;


  r2sbranch.isK0 =0;
  r2sbranch.isLambda =0;
  r2sbranch.isLambdaBar =0;
  r2sbranch.isKplusLoose =0;
  r2sbranch.isKminusLoose  =0;
  r2sbranch.isConvLoose =0;
  s2rbranch.isLooper =0;
  r2sbranch.isFake =0;

  r2sbranch.isTherePrimaryTrack = 0;
  r2sbranch.isThereMergedTrack = 0;

  using namespace std;
  using namespace edm;
  using namespace reco;

  //make conversion vertices
  Handle<PFDisplacedVertexCollection> pIn;
  iEvent.getByLabel("particleFlowDisplacedVertex",pIn);

  edm::Handle<reco::VertexCollection> vertexHandle;
  iEvent.getByLabel("offlinePrimaryVertices", vertexHandle);
  reco::Vertex the_pvtx;
  bool valid_pvtx = false;
  if (!vertexHandle->empty()){
      the_pvtx = *(vertexHandle->begin());
      valid_pvtx = true;
  }

  Handle<TrackingVertexCollection> SimVtx;
  if (simulation) {
    if (prints) cout << "get sim stuff" << endl;
    //get sim info
    iEvent.getByLabel("mergedtruth","MergedTrackTruth",SimVtx);
    if (hitassoc) {
      //iSetup.get<TrackAssociatorRecord>().get("TrackAssociatorByHits",theAssociator);
      //iEvent.getByLabel("mergedtruth","MergedTrackTruth",TPCollectionH);
    }
  }

  if (simulation) {
    //compute efficiency
    if (prints) cout << "loop over sim vtx, size=" << SimVtx->size() << endl;
    for (vector<TrackingVertex>::const_iterator iVtx=SimVtx->begin(); iVtx !=SimVtx->end(); ++iVtx ) {

      //check if it is nucl int
      if (iVtx->nSourceTracks()<1) continue; 
      if (isNuclInt(*iVtx)==false) continue;

      if (prints) cout << "fill mc" << endl;
      math::XYZVectorD momIncSim = (*iVtx->sourceTracks_begin())->momentum();
      math::XYZTLorentzVectorD momOutSim(0,0,0,0);
      double nTrackingParticles = 0;
      for (TrackingParticleRefVector::iterator tpOut=iVtx->daughterTracks_begin(); tpOut!=iVtx->daughterTracks_end(); ++tpOut) {
	momOutSim += (*tpOut)->p4();
	nTrackingParticles++;
      }

      s2rbranch.x =iVtx->position().x();
      s2rbranch.y =iVtx->position().y();
      s2rbranch.z =iVtx->position().z();
      s2rbranch.pt = sqrt(momIncSim.Perp2());
      s2rbranch.phi = momIncSim.Phi();
      s2rbranch.theta = momIncSim.Theta();
      s2rbranch.ptOut = sqrt(momOutSim.Perp2());
      s2rbranch.phiOut = momOutSim.Phi();
      s2rbranch.thetaOut = momOutSim.Theta();
      s2rbranch.mOut = momOutSim.mass();
      s2rbranch.nOut = nTrackingParticles;

      s2rbranch.isAssoc = 0;
      s2rbranch.deltapt = 0;
      s2rbranch.deltaphi = 0;
      s2rbranch.deltatheta = 0;
      s2rbranch.deltax = 0;
      s2rbranch.deltay = 0;
      s2rbranch.deltaz = 0;
      s2rbranch.isNucl =0;
      s2rbranch.isNuclLoose =0;
      s2rbranch.isNuclKink =0;

      s2rbranch.isK0 =0;
      s2rbranch.isLambda =0;
      s2rbranch.isLambdaBar =0;
      s2rbranch.isKplusLoose =0;
      s2rbranch.isKminusLoose  =0;
      s2rbranch.isConvLoose =0;
      s2rbranch.isLooper =0;
      s2rbranch.isFake =0;

      r2sbranch.tkPt = std::vector<float>();
      r2sbranch.tkEta = std::vector<float>();
      r2sbranch.tkDxy = std::vector<float>();
      r2sbranch.tkDz = std::vector<float>();
      r2sbranch.tkRho = std::vector<float>();
      r2sbranch.tkHits = std::vector<int>();
      r2sbranch.tkAlgo = std::vector<int>();
      r2sbranch.tkOuter = std::vector<int>();
      r2sbranch.tkPrimary = std::vector<bool>();
      r2sbranch.tkSecondary = std::vector<bool>();

      //look for matching reco conversion
      if (prints) cout << "look for match" << endl;

      double deltaR  = 999;
      double deltaZ  = 999;
      double deltaPt = 999;
      double deltaPhi = 999;
      double deltaTheta = 999;
      double deltaX = 999;
      double deltaY = 999;

      for (PFDisplacedVertexCollection::const_iterator rni=pIn->begin();rni!=pIn->end();++rni) {
	if (prints) cout << "got vtx" << endl;

	if (rni->isFake()) continue;

	const math::XYZTLorentzVector momIncRec = rni->primaryMomentum("PI", false, 0.0);
	const math::XYZTLorentzVector momOutRec = rni->secondaryMomentum("PI", true, 0.0);

 	deltaPt = sqrt(momIncSim.Perp2())-sqrt(momIncRec.Perp2());
 	deltaPhi = momIncSim.Phi()-momIncRec.Phi();
 	deltaTheta = momIncSim.Theta()-momIncRec.Theta();
	deltaX = iVtx->position().x()-rni->position().x();
	deltaY = iVtx->position().y()-rni->position().y();
	deltaZ = iVtx->position().z()-rni->position().z();
	deltaR  = sqrt(iVtx->position().perp2())-sqrt(rni->position().perp2());

	bool assoc = false;
	if (hitassoc) {
	} else {
	  if (fabs(deltaX)>2. || fabs(deltaY)>2. || fabs(deltaZ)>2.) continue;
	  assoc = true;
	}
	if (prints) cout << "associated" << endl;

 	s2rbranch.isAssoc = 1;
	s2rbranch.deltapt = deltaPt;
	s2rbranch.deltaphi = deltaPhi;
	s2rbranch.deltatheta = deltaTheta;
	s2rbranch.deltax = deltaX;
	s2rbranch.deltay = deltaY;
	s2rbranch.deltaz = deltaZ;
	s2rbranch.isNucl = rni->isNucl();
	s2rbranch.isNuclLoose = rni->isNucl_Loose();
	s2rbranch.isNuclKink = rni->isNucl_Kink();

	s2rbranch.isK0 = rni->isK0();
	s2rbranch.isLambda = rni->isLambda();
	s2rbranch.isLambdaBar = rni->isLambdaBar();
	s2rbranch.isKplusLoose = rni->isKplus_Loose();
	s2rbranch.isKminusLoose = rni->isKminus_Loose();
	s2rbranch.isConvLoose = rni->isConv_Loose();
	s2rbranch.isLooper = rni->isLooper();
	s2rbranch.isFake = rni->isFake();

	s2rbranch.isTherePrimaryTrack = rni->isTherePrimaryTracks();
	s2rbranch.isThereMergedTrack = rni->isThereMergedTracks();

	break;
      }
      ntupleS2R->Fill();     
    }
  }
  
  //compute purity and plot residues
  if (prints) cout << "loop on reco, size=" << pIn->size() << endl;
  for (PFDisplacedVertexCollection::const_iterator rni=pIn->begin();rni!=pIn->end();++rni) {

    if (rni->isFake()) continue;

    const math::XYZTLorentzVector momIncRec = rni->primaryMomentum("PI", false, 0.0);
    const math::XYZTLorentzVector momOutRec = rni->secondaryMomentum("PI", true, 0.0);
    math::XYZVector p = momOutRec.Vect();
    math::XYZVector dir(rni->position().x(), rni->position().y(), rni->position().z()); 
    math::XYZVector pvtx(the_pvtx.x(), the_pvtx.y(), the_pvtx.z());
    dir = dir - pvtx;
    double angle = acos(p.Dot(dir)/sqrt(p.Mag2()*dir.Mag2()))/TMath::Pi()*180.0;

    if(prints) cout<<"nuclear interaction at R="<<sqrt(rni->position().Perp2())<<" pt="<<sqrt(momIncRec.Perp2())<<endl;

    if (prints) cout << "fill reco" << endl;

    r2sbranch.x =rni->position().x();
    r2sbranch.y =rni->position().y();
    r2sbranch.z =rni->position().z();
    r2sbranch.pt = sqrt(momIncRec.Perp2());
    r2sbranch.phi = momIncRec.Phi();
    r2sbranch.theta = momIncRec.Theta();
    r2sbranch.ptOut = sqrt(momOutRec.Perp2());
    r2sbranch.phiOut = momOutRec.Phi();
    r2sbranch.thetaOut = momOutRec.Theta();
    r2sbranch.mOut = momOutRec.mass();
    r2sbranch.angle = angle;

    r2sbranch.isTherePrimaryTrack = rni->isTherePrimaryTracks();
    r2sbranch.isThereMergedTrack = rni->isThereMergedTracks();

    r2sbranch.isNucl = rni->isNucl();
    r2sbranch.isNuclLoose = rni->isNucl_Loose();
    r2sbranch.isNuclKink = rni->isNucl_Kink();

    r2sbranch.isK0 = rni->isK0();
    r2sbranch.isLambda = rni->isLambda();
    r2sbranch.isLambdaBar = rni->isLambdaBar();
    r2sbranch.isKplusLoose = rni->isKplus_Loose();
    r2sbranch.isKminusLoose = rni->isKminus_Loose();
    r2sbranch.isConvLoose = rni->isConv_Loose();
    r2sbranch.isLooper = rni->isLooper();
    r2sbranch.isFake = rni->isFake();

    r2sbranch.tkPt = std::vector<float>();
    r2sbranch.tkEta = std::vector<float>();
    r2sbranch.tkDxy = std::vector<float>();
    r2sbranch.tkDz = std::vector<float>();
    r2sbranch.tkRho = std::vector<float>();
    r2sbranch.tkHits = std::vector<int>();
    r2sbranch.tkAlgo = std::vector<int>();
    r2sbranch.tkOuter = std::vector<int>();
    r2sbranch.tkPrimary = std::vector<bool>();
    r2sbranch.tkSecondary = std::vector<bool>();
    int tkStep67Good = 0;
    int tkStep67Poor = 0;

    for (Vertex::trackRef_iterator tk=rni->tracks_begin();tk!=rni->tracks_end();++tk) {
      r2sbranch.tkPt.push_back((*tk)->pt());
      r2sbranch.tkEta.push_back((*tk)->eta());
      r2sbranch.tkDxy.push_back((*tk)->dxy(the_pvtx.position()));
      r2sbranch.tkDz.push_back((*tk)->dz(the_pvtx.position()));
      r2sbranch.tkRho.push_back((*tk)->innerPosition().Rho());
      r2sbranch.tkHits.push_back((*tk)->numberOfValidHits());
      r2sbranch.tkAlgo.push_back((*tk)->algo());
      r2sbranch.tkOuter.push_back((*tk)->trackerExpectedHitsOuter().numberOfHits());
      r2sbranch.tkPrimary.push_back(rni->isPrimaryTrack(*tk));
      r2sbranch.tkSecondary.push_back(rni->isSecondaryTrack(*tk));

      if ((*tk)->algo() - 5 > 5) {

	bool isGood67Tk = fabs((*tk)->eta()) < 1.5 
	  && (*tk)->pt() < 5 
	  && (*tk)->trackerExpectedHitsOuter().numberOfHits() < 8;

	if ( isGood67Tk ) tkStep67Good++;
	else tkStep67Poor++;
	
      }

    }

    r2sbranch.nOut = rni->nSecondaryTracks();
    r2sbranch.nOutTkStep67Good =  tkStep67Good;
    r2sbranch.nOutTkStep67Poor =  tkStep67Poor;

    r2sbranch.isAssoc = 0;
    r2sbranch.deltapt = 0;
    r2sbranch.deltaphi = 0;
    r2sbranch.deltatheta = 0;
    r2sbranch.deltapt_InSim_OutRec = 0;
    r2sbranch.deltaphi_InSim_OutRec = 0;
    r2sbranch.deltatheta_InSim_OutRec = 0;
    r2sbranch.deltax = 0;
    r2sbranch.deltay = 0;
    r2sbranch.deltaz = 0;

    double deltaR  = 999;
    double deltaZ  = 999;
    double deltaPt = 999;
    double deltaPhi = 999;
    double deltaTheta = 999;
    double deltaX = 999;
    double deltaY = 999;
    double deltaPt_InSim_OutRec = 999;
    double deltaPhi_InSim_OutRec = 999;
    double deltaTheta_InSim_OutRec = 999;

    bool associated = false;
    if (simulation) {
      if (prints) cout << "check assoc" << endl;
     
      for (vector<TrackingVertex>::const_iterator iVtx=SimVtx->begin(); iVtx !=SimVtx->end(); ++iVtx ) {
	//check if it is nucl int
	if (iVtx->nSourceTracks()<1) continue; 
	if (isNuclInt(*iVtx)==false) continue;

	math::XYZVectorD momIncSim = (*iVtx->sourceTracks_begin())->momentum();
	math::XYZTLorentzVectorD momOutSim(0,0,0,0);
	for (TrackingParticleRefVector::iterator tpOut=iVtx->daughterTracks_begin(); tpOut!=iVtx->daughterTracks_end(); ++tpOut) {
	  momOutSim += (*tpOut)->p4();
	}

	deltaX = iVtx->position().x()-rni->position().x();
	deltaY = iVtx->position().y()-rni->position().y();
	deltaZ = iVtx->position().z()-rni->position().z();
	deltaR  = sqrt(iVtx->position().perp2())-sqrt(rni->position().perp2());

 	deltaPt = sqrt(momIncSim.Perp2())-sqrt(momIncRec.Perp2());
 	deltaPhi = momIncSim.Phi()-momIncRec.Phi();
 	deltaTheta = momIncSim.Theta()-momIncRec.Theta();

	deltaPt_InSim_OutRec = sqrt(momIncSim.Perp2())-sqrt(momOutRec.Perp2());
	deltaPhi_InSim_OutRec = momIncSim.Phi()-momOutRec.Phi();
	deltaTheta_InSim_OutRec = momIncSim.Theta()-momOutRec.Theta();

	if (hitassoc) {
	} else {
	  if (fabs(deltaX)<2. && fabs(deltaY)<2. && fabs(deltaZ)<2.) {
	    associated = true;
	    break;
	  }
	}
      }

      if (associated) {
	if (prints) cout << "associated" << endl;
	r2sbranch.isAssoc =1;
	r2sbranch.deltapt =deltaPt;
	r2sbranch.deltaphi =deltaPhi;
	r2sbranch.deltatheta =deltaTheta;
	r2sbranch.deltax = deltaX;
	r2sbranch.deltay = deltaY;
	r2sbranch.deltaz = deltaZ;
	r2sbranch.deltapt_InSim_OutRec = deltaPt_InSim_OutRec;
	r2sbranch.deltaphi_InSim_OutRec = deltaPhi_InSim_OutRec;
	r2sbranch.deltatheta_InSim_OutRec = deltaTheta_InSim_OutRec;

      }
    }
    ntupleR2S->Fill();    
    if (prints) cout << "end of loop" << endl;
  }  
  
  if (prints) cout << "end of event" << endl;
}

  
// ------------ method called once each job just before starting event loop  ------------
void NuclIntNtuplizer::beginJob() {
  file = new TFile(outfile.c_str(),"recreate");
  
  const bool oldAddDir = TH1::AddDirectoryStatus();
  TH1::AddDirectory(true);

  ntupleS2R = new TTree("ntupleS2R","sim2reco");
  ntupleS2R->Branch("run",&(s2rbranch.run),"run/I");
  ntupleS2R->Branch("event",&(s2rbranch.event),"event/I");
  ntupleS2R->Branch("isAssoc",&(s2rbranch.isAssoc),"isAssoc/I");
  ntupleS2R->Branch("pt",&(s2rbranch.pt),"pt/F");
  ntupleS2R->Branch("phi",&(s2rbranch.phi),"phi/F");
  ntupleS2R->Branch("theta",&(s2rbranch.theta),"theta/F");
  ntupleS2R->Branch("ptOut",&(s2rbranch.ptOut),"ptOut/F");
  ntupleS2R->Branch("phiOut",&(s2rbranch.phiOut),"phiOut/F");
  ntupleS2R->Branch("thetaOut",&(s2rbranch.thetaOut),"thetaOut/F");
  ntupleS2R->Branch("mOut",&(s2rbranch.mOut),"mOut/F");
  ntupleS2R->Branch("nOut",&(s2rbranch.nOut),"nOut/I");
  ntupleS2R->Branch("x",&(s2rbranch.x),"x/F");
  ntupleS2R->Branch("y",&(s2rbranch.y),"y/F");
  ntupleS2R->Branch("z",&(s2rbranch.z),"z/F");
  ntupleS2R->Branch("deltapt",&(s2rbranch.deltapt),"deltapt/F");
  ntupleS2R->Branch("deltaphi",&(s2rbranch.deltaphi),"deltaphi/F");
  ntupleS2R->Branch("deltatheta",&(s2rbranch.deltatheta),"deltatheta/F");
  ntupleS2R->Branch("deltax",&(s2rbranch.deltax),"deltax/F");
  ntupleS2R->Branch("deltay",&(s2rbranch.deltay),"deltay/F");
  ntupleS2R->Branch("deltaz",&(s2rbranch.deltaz),"deltaz/F");
  ntupleS2R->Branch("isTherePrimaryTrack",&(s2rbranch.isTherePrimaryTrack),"isTherePrimaryTrack/B");
  ntupleS2R->Branch("isThereMergedTrack",&(s2rbranch.isThereMergedTrack),"isThereMergedTrack/B");
  ntupleS2R->Branch("isNucl",&(s2rbranch.isNucl),"isNucl/B");
  ntupleS2R->Branch("isNuclLoose",&(s2rbranch.isNuclLoose),"isNuclLoose/B");
  ntupleS2R->Branch("isNuclKink",&(s2rbranch.isNuclKink),"isNuclKink/B");
  ntupleS2R->Branch("isFake",&(s2rbranch.isFake),"isFake/B");
  ntupleS2R->Branch("isK0",&(s2rbranch.isK0),"isK0/B");
  ntupleS2R->Branch("isLambda",&(s2rbranch.isLambda),"isLambda/B");
  ntupleS2R->Branch("isLambdaBar",&(s2rbranch.isLambdaBar),"isLambdaBar/B");
  ntupleS2R->Branch("isKminusLoose",&(s2rbranch.isKminusLoose),"isKminusLoose/B");
  ntupleS2R->Branch("isKplusLoose",&(s2rbranch.isKplusLoose),"isKplusLoose/B");
  ntupleS2R->Branch("isLooper",&(s2rbranch.isLooper),"isLooper/B");
  ntupleS2R->Branch("isConvLoose",&(s2rbranch.isConvLoose),"isConvLoose/B");

  ntupleR2S = new TTree("ntupleR2S","reco2sim");
  ntupleR2S->Branch("run",&(r2sbranch.run),"run/I");
  ntupleR2S->Branch("event",&(r2sbranch.event),"event/I");
  ntupleR2S->Branch("isAssoc",&(r2sbranch.isAssoc),"isAssoc/I");
  ntupleR2S->Branch("pt",&(r2sbranch.pt),"pt/F");
  ntupleR2S->Branch("phi",&(r2sbranch.phi),"phi/F");
  ntupleR2S->Branch("theta",&(r2sbranch.theta),"theta/F");
  ntupleR2S->Branch("ptOut",&(r2sbranch.ptOut),"ptOut/F");
  ntupleR2S->Branch("phiOut",&(r2sbranch.phiOut),"phiOut/F");
  ntupleR2S->Branch("thetaOut",&(r2sbranch.thetaOut),"thetaOut/F");
  ntupleR2S->Branch("mOut",&(r2sbranch.mOut),"mOut/F");
  ntupleR2S->Branch("angle",&(r2sbranch.angle),"angle/F");

  ntupleR2S->Branch("nOut",&(r2sbranch.nOut),"nOut/I");
  ntupleR2S->Branch("nOutTkStep67Good", &(r2sbranch.nOutTkStep67Good),"nOutTkStep67Good/I");
  ntupleR2S->Branch("nOutTkStep67Poor", &(r2sbranch.nOutTkStep67Poor),"nOutTkStep67Poor/I");



  ntupleR2S->Branch("x",&(r2sbranch.x),"x/F");
  ntupleR2S->Branch("y",&(r2sbranch.y),"y/F");
  ntupleR2S->Branch("z",&(r2sbranch.z),"z/F");
  ntupleR2S->Branch("deltapt",&(r2sbranch.deltapt),"deltapt/F");
  ntupleR2S->Branch("deltaphi",&(r2sbranch.deltaphi),"deltaphi/F");
  ntupleR2S->Branch("deltatheta",&(r2sbranch.deltatheta),"deltatheta/F");
  ntupleR2S->Branch("deltapt_InSim_OutRec",&(r2sbranch.deltapt_InSim_OutRec),"deltapt_InSim_OutRec/F");
  ntupleR2S->Branch("deltaphi_InSim_OutRec",&(r2sbranch.deltaphi_InSim_OutRec),"deltaphi_InSim_OutRec/F");
  ntupleR2S->Branch("deltatheta_InSim_OutRec",&(r2sbranch.deltatheta_InSim_OutRec),"deltatheta_InSim_OutRec/F");
  ntupleR2S->Branch("deltax",&(r2sbranch.deltax),"deltax/F");
  ntupleR2S->Branch("deltay",&(r2sbranch.deltay),"deltay/F");
  ntupleR2S->Branch("deltaz",&(r2sbranch.deltaz),"deltaz/F");
  ntupleR2S->Branch("isTherePrimaryTrack",&(r2sbranch.isTherePrimaryTrack),"isTherePrimaryTrack/B");
  ntupleR2S->Branch("isThereMergedTrack",&(r2sbranch.isThereMergedTrack),"isThereMergedTrack/B");
  ntupleR2S->Branch("isNucl",&(r2sbranch.isNucl),"isNucl/B");
  ntupleR2S->Branch("isNuclLoose",&(r2sbranch.isNuclLoose),"isNuclLoose/B");
  ntupleR2S->Branch("isNuclKink",&(r2sbranch.isNuclKink),"isNuclKink/B");
  ntupleR2S->Branch("isFake",&(r2sbranch.isFake),"isFake/B");
  ntupleR2S->Branch("isK0",&(r2sbranch.isK0),"isK0/B");
  ntupleR2S->Branch("isLambda",&(r2sbranch.isLambda),"isLambda/B");
  ntupleR2S->Branch("isLambdaBar",&(r2sbranch.isLambdaBar),"isLambdaBar/B");
  ntupleR2S->Branch("isKminusLoose",&(r2sbranch.isKminusLoose),"isKminusLoose/B");
  ntupleR2S->Branch("isKplusLoose",&(r2sbranch.isKplusLoose),"isKplusLoose/B");
  ntupleR2S->Branch("isLooper",&(r2sbranch.isLooper),"isLooper/B");
  ntupleR2S->Branch("isConvLoose",&(r2sbranch.isConvLoose),"isConvLoose/B");

  ntupleR2S->Branch("tkPt",&(r2sbranch.tkPt));
  ntupleR2S->Branch("tkEta",&(r2sbranch.tkEta));
  ntupleR2S->Branch("tkDxy",&(r2sbranch.tkDxy));
  ntupleR2S->Branch("tkDz",&(r2sbranch.tkDz));
  ntupleR2S->Branch("tkRho",&(r2sbranch.tkRho));
  ntupleR2S->Branch("tkHits",&(r2sbranch.tkHits));
  ntupleR2S->Branch("tkAlgo",&(r2sbranch.tkAlgo));
  ntupleR2S->Branch("tkOuter",&(r2sbranch.tkOuter));
  ntupleR2S->Branch("tkPrimary",&(r2sbranch.tkPrimary));
  ntupleR2S->Branch("tkSecondary",&(r2sbranch.tkSecondary));
  
  TH1::AddDirectory(oldAddDir);
}

// ------------ method called once each job just after ending the event loop  ------------
void 
NuclIntNtuplizer::endJob() {
  file->Write();
  file->Close();
}

bool NuclIntNtuplizer::isNuclInt(const TrackingVertex& v ) const {
  using namespace std;
  
  if (v.position().rho() > 45 || fabs(v.position().z())> 150 ||  v.position().rho() < 2) return false;
  
  //FIXME
  //TLorentzVector momentum_in = momentum(v, PFDisplacedVertex::T_TO_VERTEX);
  //TLorentzVector momentum_out = momentum(v, PFDisplacedVertex::T_FROM_VERTEX);
  //int nCharged = 0;
  
  bool bK0s = false;
  bool bLambda = false;
  bool bGamma = false;

  for (TrackingVertex::tp_iterator simMother = v.sourceTracks_begin();simMother != v.sourceTracks_end();++simMother){
    if ((**simMother).pdgId() == 11 || (**simMother).pdgId() == -11) return false; 
    bGamma = ((**simMother).pdgId() == 22);
    bK0s = ((**simMother).pdgId() == 310 || (**simMother).pdgId() == -310);
    bLambda = ((**simMother).pdgId() == 3122 || (**simMother).pdgId() == -3122);
  }

  vector<int> pdgIds;
  for (TrackingVertex::tp_iterator simDaughter = v.daughterTracks_begin();simDaughter != v.daughterTracks_end();++simDaughter){
    //FIXME
    //if (selector_(**simDaughter)){
    //  nCharged ++;
    //}
    pdgIds.push_back((**simDaughter).pdgId());        
  }

  //FIXME
  //if (nCharged < 2) return false;
  //if (momentum_out.Pt() < 0.2) return false;

  // V0 decays
  bool bK0sDecay = bK0s && v.nDaughterTracks() == 2 && ((pdgIds[0]==211&&pdgIds[1]==-211)||(pdgIds[0]==-211&&pdgIds[1]==211));
  if (bK0sDecay) return false;

  bool bLambdaDecay = bLambda &&  v.nDaughterTracks() == 2 && ((pdgIds[0] == -211 && pdgIds[1] == 2212)|| 
      (pdgIds[0] == 2212 && pdgIds[1] == -211)||(pdgIds[0] == 211 && pdgIds[1] == -2212)||(pdgIds[0] == -2212 && pdgIds[1] == 211));
  if (bLambdaDecay) return false;

  bool bConvers = bGamma;
  if (bConvers) return false;

  return true;
}

//define this as a plug-in
DEFINE_FWK_MODULE(NuclIntNtuplizer);




/*


  Handle<SimToRecoCollection> hSimToReco;
  Handle<RecoToSimCollection> hRecoToSim;

  iEvent.getByLabel(simToRecoLabel_, hSimToReco);
  iEvent.getByLabel(recoToSimLabel_, hRecoToSim);

  SimToRecoCollection simToReco = *(hSimToReco.product());
  RecoToSimCollection recoToSim = *(hRecoToSim.product());


  
  VertexCollection* ptrVertex = new VertexCollection();
  const PFDisplacedVertexCollection displacedVertexColl = *(displacedVertices.product());

  for (PFDisplacedVertexCollection::size_type i=0; i<displacedVertexColl.size(); i++){

    ptrVertex->push_back((Vertex) displacedVertexColl[i]);
    

  }

  Handle<VertexCollection> vertices(ptrVertex, displacedVertices.provenance());




  VertexRecoToSimCollection r2s = 
    theVertexAssociator->associateRecoToSim(vertices, VPCollection,
					    iEvent, recoToSim);

  VertexSimToRecoCollection s2r = 
    theVertexAssociator->associateSimToReco(vertices, VPCollection,
					    iEvent, simToReco);

*/
