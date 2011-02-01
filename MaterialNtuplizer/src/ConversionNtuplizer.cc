// -*- C++ -*-
//
// Package:    ConversionNtuplizer
// Class:      ConversionNtuplizer
// 
/**\class ConversionNtuplizer ConversionNtuplizer.cc Tests/ConversionTest/src/ConversionNtuplizer.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Giuseppe Cerati
//         Created:  Wed Aug 19 15:39:10 CEST 2009
// $Id: ConversionNtuplizer.cc,v 1.13 2011/01/27 17:56:58 hlliu Exp $
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
//#include "FWCore/ParameterSet/interface/InputTag.h"
#include "FWCore/Utilities/interface/InputTag.h"

#include "DataFormats/EgammaCandidates/interface/Conversion.h"
#include "DataFormats/EgammaCandidates/interface/ConversionFwd.h"

#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

#include "DataFormats/GeometrySurface/interface/BoundCylinder.h"
#include "DataFormats/GeometrySurface/interface/BoundDisk.h"
#include "DataFormats/GeometrySurface/interface/SimpleCylinderBounds.h"
#include "DataFormats/GeometrySurface/interface/SimpleDiskBounds.h"
#include "Geometry/TrackerGeometryBuilder/interface/TrackerGeometry.h"
#include "Geometry/Records/interface/TrackerDigiGeometryRecord.h"
#include "Geometry/CommonDetUnit/interface/GeomDetUnit.h"
#include "DataFormats/GeometryVector/interface/GlobalPoint.h"
#include "TrackingTools/MaterialEffects/interface/PropagatorWithMaterial.h"
#include "TrackingTools/TrajectoryState/interface/TrajectoryStateTransform.h"
#include "TrackingTools/TrajectoryState/interface/TrajectoryStateOnSurface.h"

#include "TrackingTools/TransientTrack/interface/TransientTrackBuilder.h"
#include "TrackingTools/Records/interface/TransientTrackRecord.h"
#include "TrackingTools/TransientTrack/interface/TransientTrack.h"
#include "RecoVertex/VertexPrimitives/interface/TransientVertex.h"
#include "RecoVertex/KalmanVertexFit/interface/KalmanVertexFitter.h"
#include "RecoVertex/KinematicFit/interface/KinematicConstrainedVertexFitter.h"
#include "RecoVertex/KinematicFit/interface/ColinearityKinematicConstraint.h"
#include "RecoVertex/KinematicFitPrimitives/interface/KinematicParticleFactoryFromTransientTrack.h"
#include "SimTracker/Records/interface/TrackAssociatorRecord.h"

#include "RecoEgamma/EgammaMCTools/interface/PhotonMCTruthFinder.h"
#include "RecoEgamma/EgammaMCTools/interface/PhotonMCTruthFinder.h"
#include "RecoEgamma/EgammaMCTools/interface/PhotonMCTruth.h"
#include "RecoEgamma/EgammaMCTools/interface/ElectronMCTruth.h"
#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "SimDataFormats/Track/interface/SimTrack.h"
#include "SimDataFormats/Track/interface/SimTrackContainer.h"
#include "SimDataFormats/Vertex/interface/SimVertex.h"
#include "SimDataFormats/Vertex/interface/SimVertexContainer.h"

#include "SimTracker/Records/interface/TrackAssociatorRecord.h"
#include "SimTracker/TrackAssociation/interface/TrackAssociatorBase.h"
#include "DataFormats/Common/interface/RefToBaseVector.h"

#include "MagneticField/Engine/interface/MagneticField.h"
#include "Geometry/TrackerGeometryBuilder/interface/TrackerGeometry.h"
#include "Geometry/Records/interface/TrackerDigiGeometryRecord.h"
#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h" 
#include "TrackingTools/Records/interface/TrackingComponentsRecord.h" 
#include "TrackingTools/TrajectoryState/interface/TrajectoryStateOnSurface.h"
#include "TrackingTools/TrajectoryState/interface/TrajectoryStateTransform.h"
#include "Geometry/CommonDetUnit/interface/GeomDet.h"

#include "TrackingTools/PatternTools/interface/ClosestApproachInRPhi.h"
#include "TrackingTools/PatternTools/interface/TwoTrackMinimumDistance.h"
#include "CommonTools/Statistics/interface/ChiSquaredProbability.h"

#include <TH1F.h>
#include <TH2F.h>
#include <TFile.h>
#include <TTree.h>
//
// class decleration
//
#define ADDONS 1
typedef struct { 
  int run, event;
  int isAssoc;
  int q1, q2;
  float pt1, phi1, theta1;
  float pt2, phi2, theta2;
  float pt, phi, theta, x, y, z;
  float deltapt, deltaphi, deltatheta, deltax, deltay, deltaz;
#ifdef ADDONS
  float qseed1, ptseed1, phiseed1, thetaseed1, rseed1, zseed1;
  float qseed2, ptseed2, phiseed2, thetaseed2, rseed2, zseed2;
  //gc4hl
  float r_pt1, r_chi21, r_d01, r_theta1, r_phi1;//its associated reco tk properties
  float r_pt2, r_chi22, r_d02, r_theta2, r_phi2;
  int r_algo1, r_hits1, r_missHits1, r_before1;
  int r_algo2, r_hits2, r_missHits2, r_before2;
  float r_minapp, r_chi2prob;
#endif
} SIMTORECO;

typedef struct { 
  int run, event;
  int isAssoc;
  int q1, q2;
  int nHits1, nHits2;
  int algo1, algo2;
  float pt1, phi1, theta1, x1, y1, z1, chi21;
  float pt2, phi2, theta2, x2, y2, z2, chi22;
  float pt, phi, theta, x, y, z, chi2;
  float deltapt, deltaphi, deltatheta, deltax, deltay, deltaz;
  float minapp, d01, d02, dz1, dz2, iphi1, iphi2;
#ifdef ADDONS
  int refit;
  int missHits1, missHits2;//missed hits
  int npHits1, npHits2;//pixel hits
  int nsHits1, nsHits2;//strip stereo hits
  int beforeHits1, beforeHits2;//num of hits before vertex
  float r_pt1, r_phi1, r_theta1, r_d01;//refitted tracks
  float r_pt2, r_phi2, r_theta2, r_d02;
  float ipx1, ipy1, ipz1;//momentum at vertex
  float ipx2, ipy2, ipz2;
  float r_px1, r_py1, r_pz1;//momentum of refitted tracks
  float r_px2, r_py2, r_pz2;
  float r_pt, r_phi, r_theta;
  float vx, vy, vz;//primary vertex position
  float bsx, bsy, bsz;
  float mass;//photon invariant mass by conv->mass()
  float chi2prob;
#endif
} RECOTOSIM;


#ifdef ADDONS
typedef struct {
  int run, event;
  unsigned int lumi;
} EVT;
#endif

class ConversionNtuplizer : public edm::EDAnalyzer {
public:
  explicit ConversionNtuplizer(const edm::ParameterSet&);
  ~ConversionNtuplizer();
    
private:
  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
  
  TFile * file;
  std::string outfile;
  bool generalTkOnly;
  bool hitassoc;
  bool retracking;
  double minPhoPtForEffic;
  double maxPhoEtaForEffic;
  double maxPhoZForEffic;
  double maxPhoRForEffic;
  double minPhoPtForPurity;
  double maxPhoEtaForPurity;
  double maxPhoZForPurity;
  double maxPhoRForPurity;
  bool simulation;
  bool prints;
#ifdef ADDONS
  EVT evtbranch;
  TTree *ntupleEvt;
#endif
  SIMTORECO s2rbranch;
  RECOTOSIM r2sbranch;
  TTree *ntupleS2R,*ntupleR2S;
  TrajectoryStateTransform transformer;
  edm::ESHandle<TrackerGeometry> theG;
  edm::ESHandle<MagneticField> theMF;
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
ConversionNtuplizer::ConversionNtuplizer(const edm::ParameterSet& iConfig) :
  outfile(iConfig.getParameter<std::string>("outfile")),
  generalTkOnly(iConfig.getParameter<bool>("generalTkOnly")),
  hitassoc(iConfig.getParameter<bool>("hitassoc")),
  retracking(iConfig.getParameter<bool>("retracking")),
  minPhoPtForEffic(iConfig.getParameter<double>("minPhoPtForEffic")),
  maxPhoEtaForEffic(iConfig.getParameter<double>("maxPhoEtaForEffic")),
  maxPhoZForEffic(iConfig.getParameter<double>("maxPhoZForEffic")),
  maxPhoRForEffic(iConfig.getParameter<double>("maxPhoRForEffic")),
  minPhoPtForPurity(iConfig.getParameter<double>("minPhoPtForPurity")),
  maxPhoEtaForPurity(iConfig.getParameter<double>("maxPhoEtaForPurity")),
  maxPhoZForPurity(iConfig.getParameter<double>("maxPhoZForPurity")),
  maxPhoRForPurity(iConfig.getParameter<double>("maxPhoRForPurity")),
  simulation(iConfig.getParameter<bool>("simulation")), 
  prints(iConfig.getParameter<bool>("prints")) ,
#ifdef ADDONS
  ntupleEvt(0),
#endif
  ntupleS2R(0),ntupleR2S(0)
{ }


ConversionNtuplizer::~ConversionNtuplizer() { }

void ConversionNtuplizer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
  if (prints) std::cout << "new evt" << std::endl;

#ifdef ADDONS
  edm::EventID eventId = iEvent.id();
  int runNer = iEvent.run();
  int eventNumber = eventId.event();
  unsigned int lumi_block = eventId.luminosityBlock();

  evtbranch.run = runNer;
  evtbranch.event = eventNumber;
  evtbranch.lumi = lumi_block;

  ntupleEvt->Fill();
#endif

  edm::Handle<reco::VertexCollection> vertexHandle;
  reco::VertexCollection vertexCollection;
  iEvent.getByLabel("offlinePrimaryVertices", vertexHandle);
  if (!vertexHandle.isValid()) {
      edm::LogError("TrackerOnlyConversionProducer") << "Error! Can't get the product primary Vertex Collection "<< "\n";
  } else {
      vertexCollection = *(vertexHandle.product());
  }
  reco::Vertex the_pvtx;
  bool valid_pvtx = false;
  if (!vertexCollection.empty()){
      the_pvtx = *(vertexCollection.begin());
      //asking for one good vertex
      if (the_pvtx.isValid() && fabs(the_pvtx.position().z())<=15 && the_pvtx.position().Rho()<=2){
	  valid_pvtx = true;
      }
  }

#ifdef ADDONS
  //record the beam spot
  edm::Handle<reco::BeamSpot> bs;
  if (iEvent.getByLabel(edm::InputTag("offlineBeamSpot"),bs)){
      r2sbranch.bsx = bs->position().x();
      r2sbranch.bsy = bs->position().y();
      r2sbranch.bsy = bs->position().z();
  } else {
      r2sbranch.bsx = 0;
      r2sbranch.bsy = 0;
      r2sbranch.bsz = 0;
  }
#endif

  s2rbranch.run=iEvent.run();
  s2rbranch.event=iEvent.id().event();
  s2rbranch.q1 =0;
  s2rbranch.pt1 =0;
  s2rbranch.phi1 =0;
  s2rbranch.theta1 =0;
  s2rbranch.q2 =0;
  s2rbranch.pt2 =0;
  s2rbranch.phi2 =0;
  s2rbranch.theta2 =0;
  s2rbranch.pt =0;
  s2rbranch.phi =0;
  s2rbranch.theta =0;
  s2rbranch.x =0;
  s2rbranch.y =0;
  s2rbranch.z =0;
  s2rbranch.isAssoc =0;
  s2rbranch.deltapt =0;
  s2rbranch.deltaphi =0;
  s2rbranch.deltatheta =0;
  s2rbranch.deltax =0;
  s2rbranch.deltay =0;
  s2rbranch.deltaz =0;
#ifdef ADDONS
  s2rbranch.qseed1 =0;
  s2rbranch.qseed2 =0;
  s2rbranch.ptseed1 =0;
  s2rbranch.phiseed1 =0;
  s2rbranch.thetaseed1 =0;
  s2rbranch.rseed1 =0;
  s2rbranch.zseed1 =0;
  s2rbranch.ptseed2 =0;
  s2rbranch.phiseed2 =0;
  s2rbranch.thetaseed2 =0;
  s2rbranch.rseed2 =0;
  s2rbranch.zseed2 =0;
  s2rbranch.r_pt1 = 0;
  s2rbranch.r_phi1 = 0;
  s2rbranch.r_chi21 = 0;
  s2rbranch.r_d01 = 0;
  s2rbranch.r_theta1 = 0;
  s2rbranch.r_algo1 = 0;
  s2rbranch.r_hits1 = 0;
  s2rbranch.r_missHits1 = 0;
  s2rbranch.r_before1 = 0;
  s2rbranch.r_pt2 = 0;
  s2rbranch.r_phi2 = 0;
  s2rbranch.r_chi22 = 0;
  s2rbranch.r_d02 = 0;
  s2rbranch.r_theta2 = 0;
  s2rbranch.r_algo2 = 0;
  s2rbranch.r_hits2 = 0;
  s2rbranch.r_missHits2 = 0;
  s2rbranch.r_before2 = 0;
  s2rbranch.r_minapp = 0;
  s2rbranch.r_chi2prob = 0;
#endif

  r2sbranch.run=iEvent.run();
  r2sbranch.event=iEvent.id().event();
  r2sbranch.q1 =0;
  r2sbranch.nHits1 =0;
  r2sbranch.algo1 =0;
  r2sbranch.d01 =0;
  r2sbranch.dz1 =0;
  r2sbranch.pt1 =0;
  r2sbranch.phi1 =0;
  r2sbranch.iphi1 =0;
  r2sbranch.theta1 =0;
  r2sbranch.x1 =0;
  r2sbranch.y1 =0;
  r2sbranch.z1 =0;
  r2sbranch.chi21=0;
  r2sbranch.q2 =0;
  r2sbranch.nHits2 =0;
  r2sbranch.algo2 =0;
  r2sbranch.d02 =0;
  r2sbranch.dz2 =0;
  r2sbranch.pt2 =0;
  r2sbranch.phi2 =0;
  r2sbranch.iphi2 =0;
  r2sbranch.theta2 =0;
  r2sbranch.x2 =0;
  r2sbranch.y2 =0;
  r2sbranch.z2 =0;
  r2sbranch.chi22=0;
  r2sbranch.pt =0;
  r2sbranch.phi =0;
  r2sbranch.theta =0;
  r2sbranch.x =0;
  r2sbranch.y =0;
  r2sbranch.z =0;
  r2sbranch.chi2=0;
  r2sbranch.isAssoc =0;
  r2sbranch.deltapt =0;
  r2sbranch.deltaphi =0;
  r2sbranch.deltatheta =0;
  r2sbranch.deltax =0;
  r2sbranch.deltay =0;
  r2sbranch.deltaz =0;
  r2sbranch.minapp =0;

#ifdef ADDONS
  r2sbranch.npHits2 =0;
  r2sbranch.nsHits2 =0;
  r2sbranch.beforeHits2 =0;
  r2sbranch.missHits2 =0;
  r2sbranch.r_d02 =0;
  r2sbranch.r_pt2 =0;
  r2sbranch.r_phi2 =0;
  r2sbranch.r_theta2 =0;
  r2sbranch.r_px2 =0;
  r2sbranch.r_py2 =0;
  r2sbranch.r_pz2 =0;
  r2sbranch.ipx2 =0;
  r2sbranch.ipy2 =0;
  r2sbranch.ipz2 =0;
  r2sbranch.r_pt =0;
  r2sbranch.r_phi =0;
  r2sbranch.r_theta =0;
  r2sbranch.mass = -1.;
  r2sbranch.refit = 0;
  r2sbranch.npHits1 =0;
  r2sbranch.nsHits1 =0;
  r2sbranch.beforeHits1 =0;
  r2sbranch.missHits1 =0;
  r2sbranch.r_d01 =0;
  r2sbranch.r_pt1 =0;
  r2sbranch.r_phi1 =0;
  r2sbranch.r_theta1 =0;
  r2sbranch.r_px1 =0;
  r2sbranch.r_py1 =0;
  r2sbranch.r_pz1 =0;
  r2sbranch.ipx1 =0;
  r2sbranch.ipy1 =0;
  r2sbranch.ipz1 =0;
  //r2sbranch.sx =0;//its sim vertex
  //r2sbranch.sy =0;
  //r2sbranch.sz =0;
  if (valid_pvtx){
      r2sbranch.vx =the_pvtx.position().x();
      r2sbranch.vy =the_pvtx.position().y();
      r2sbranch.vz =the_pvtx.position().z();
  } else {
      r2sbranch.vx =0;
      r2sbranch.vy =0;
      r2sbranch.vz =0;
  }
#endif

  using namespace std;
  using namespace edm;
  using namespace reco;


  //get tracker geometry for hits positions
  edm::ESHandle<TrackerGeometry> tracker;
  iSetup.get<TrackerDigiGeometryRecord>().get(tracker);

  const TrackerGeometry* trackerGeom = tracker.product();

  edm::ESHandle<MagneticField> magFieldHandle;
  iSetup.get<IdealMagneticFieldRecord>().get( magFieldHandle );
  const MagneticField* magField = magFieldHandle.product();;

  PropagatorWithMaterial propag( anyDirection, 0.000511, magField );
  TrajectoryStateTransform transformer;

  //make conversion vertices
  Handle<ConversionCollection> pIn;
  iEvent.getByLabel("trackerOnlyConversions",pIn);
  ESHandle<TransientTrackBuilder> theB;
  iSetup.get<TransientTrackRecord>().get("TransientTrackBuilder",theB);

  ESHandle<TrackAssociatorBase> theAssociator;
  Handle<TrackingParticleCollection>  TPCollectionH ;
  if (simulation) {
    if (hitassoc) {
      iSetup.get<TrackAssociatorRecord>().get("TrackAssociatorByHits",theAssociator);
      iEvent.getByLabel("mergedtruth","MergedTrackTruth",TPCollectionH);
    }
  }

  iSetup.get<TrackerDigiGeometryRecord>().get(theG);
  iSetup.get<IdealMagneticFieldRecord>().get(theMF);  
  
  vector<PhotonMCTruth> mcPhotons;
  if (simulation) {
    //compute efficiency
    if (prints) std::cout << "get sim stuff" << endl;
    //get sim info
    std::vector<SimTrack> theSimTracks;
    std::vector<SimVertex> theSimVertices;
    Handle<SimTrackContainer> SimTk;
    Handle<SimVertexContainer> SimVtx;
    iEvent.getByLabel("g4SimHits",SimTk);
    iEvent.getByLabel("g4SimHits",SimVtx);
    PhotonMCTruthFinder*  thePhotonMCTruthFinder_ = new PhotonMCTruthFinder();
    theSimTracks.insert(theSimTracks.end(),SimTk->begin(),SimTk->end());
    theSimVertices.insert(theSimVertices.end(),SimVtx->begin(),SimVtx->end());
    mcPhotons=thePhotonMCTruthFinder_->find(theSimTracks,  theSimVertices);
    if (prints) std::cout << "loop over sim, size=" << mcPhotons.size() << endl;
    for (vector<PhotonMCTruth>::const_iterator iPho=mcPhotons.begin(); iPho !=mcPhotons.end(); ++iPho ) {
      std::vector<ElectronMCTruth> electrons = (*iPho).electrons();
      if ( (!(*iPho).isAConversion()) || electrons.size()!=2 ) continue;
      double mcPhoPt = (*iPho).fourMomentum().perp();
      double mcElecPt1 = electrons[0].fourMomentum().perp();
      double mcElecPt2 = electrons[1].fourMomentum().perp();
      //double mcPhoE = (*iPho).fourMomentum().e();
      double mcPhoEta = (*iPho).fourMomentum().eta();
      double mcPhoTheta = (*iPho).fourMomentum().theta();
      double mcPhoPhi = (*iPho).fourMomentum().phi();
      double mcPhoR = (*iPho).vertex().perp();
      double mcPhoZ = (*iPho).vertex().z();
      if (mcPhoPt<minPhoPtForEffic) continue;
      if (fabs(mcPhoEta)>maxPhoEtaForEffic) continue;
      if (fabs(mcPhoZ)>maxPhoZForEffic) continue;
      if (mcPhoR>maxPhoRForEffic) continue;
      if (prints) std::cout << "fill mc plots" << endl;

      s2rbranch.q1 = electrons[0].simTracks().charge();
      s2rbranch.pt1 = mcElecPt1;
      s2rbranch.phi1 =electrons[0].fourMomentum().phi();
      s2rbranch.theta1 =electrons[0].fourMomentum().theta();
      s2rbranch.q2 = electrons[1].simTracks().charge();
      s2rbranch.pt2 =mcElecPt2;
      s2rbranch.phi2 =electrons[1].fourMomentum().phi();
      s2rbranch.theta2 =electrons[1].fourMomentum().theta();
      s2rbranch.pt =mcPhoPt;
      s2rbranch.phi =mcPhoPhi;
      s2rbranch.theta = mcPhoTheta;
      s2rbranch.x =(*iPho).vertex().x();
      s2rbranch.y =(*iPho).vertex().y();
      s2rbranch.z =mcPhoZ;
      s2rbranch.isAssoc =0;
      s2rbranch.deltapt =0;
      s2rbranch.deltaphi =0;
      s2rbranch.deltatheta =0;
      s2rbranch.deltax = 0;
      s2rbranch.deltay = 0;
      s2rbranch.deltaz = 0;
#ifdef ADDONS
      s2rbranch.qseed1 =0;
      s2rbranch.qseed2 =0;
      s2rbranch.ptseed1 =0;
      s2rbranch.phiseed1 =0;
      s2rbranch.thetaseed1 =0;
      s2rbranch.rseed1 =0;
      s2rbranch.zseed1 =0;
      s2rbranch.ptseed2 =0;
      s2rbranch.phiseed2 =0;
      s2rbranch.thetaseed2 =0;
      s2rbranch.rseed2 =0;
      s2rbranch.zseed2 =0;
      s2rbranch.r_pt1 = 0;
      s2rbranch.r_phi1 = 0;
      s2rbranch.r_chi21 = 0;
      s2rbranch.r_d01 = 0;
      s2rbranch.r_theta1 = 0;
      s2rbranch.r_algo1 = 0;
      s2rbranch.r_hits1 = 0;
      s2rbranch.r_missHits1 = 0;
      s2rbranch.r_before1 = 0;
      s2rbranch.r_pt2 = 0;
      s2rbranch.r_phi2 = 0;
      s2rbranch.r_chi22 = 0;
      s2rbranch.r_d02 = 0;
      s2rbranch.r_theta2 = 0;
      s2rbranch.r_algo2 = 0;
      s2rbranch.r_hits2 = 0;
      s2rbranch.r_missHits2 = 0;
      s2rbranch.r_before2 = 0;
      s2rbranch.r_minapp = 0;
      s2rbranch.r_chi2prob = 0;
#endif

      //look for matching reco conversion
      if (prints) std::cout << "look for match" << endl;
      bool assoc = false;
      //bool cuts = false;
      RefVector<TrackingParticleCollection> tpc;
      if (prints) std::cout << "look for match.. again" << endl;
      if (hitassoc) { 
	tpc = RefVector<TrackingParticleCollection>(TPCollectionH.id());
	for (unsigned int j=0; j<TPCollectionH->size();j++) {
	  Ref<TrackingParticleCollection> tptest(TPCollectionH,j);
	  if (
	      ( (fabs(tptest->p4().x()-electrons[0].fourMomentum().x())<0.0001) &&
		(fabs(tptest->p4().y()-electrons[0].fourMomentum().y())<0.0001) &&
		(fabs(tptest->p4().z()-electrons[0].fourMomentum().z())<0.0001) ) ||
	      ( (fabs(tptest->p4().x()-electrons[1].fourMomentum().x())<0.0001) &&
		(fabs(tptest->p4().y()-electrons[1].fourMomentum().y())<0.0001) &&
		(fabs(tptest->p4().z()-electrons[1].fourMomentum().z())<0.0001) )
	      ) {
	    //std::cout << "pushing tp=" << tptest->p4() << " e0=" << electrons[0].fourMomentum() << " e1=" << electrons[1].fourMomentum() << endl;
	    tpc.push_back(tptest);
	  }
	}
      }
      double deltaR  = 999;
      double deltaZ  = 999;
      double deltaPt = 999;
      double deltaPhi = 999;
      double deltaTheta = 999;
      double deltaX = 999;
      double deltaY = 999;
#ifdef ADDONS
      double qSeed1 =999;
      double qSeed2 =999;
      double ptSeed1 =999;
      double phiSeed1 =999;
      double thetaSeed1 =999;
      double rSeed1 =999;
      double zSeed1 =999;
      double ptSeed2 =999;
      double phiSeed2 =999;
      double thetaSeed2 =999;
      double rSeed2 =999;
      double zSeed2 =999;
      int theAlgo1 = 999;
      int theAlgo2 = 999;
#endif

      for (ConversionCollection::const_iterator it = pIn->begin();it!=pIn->end();++it) {
	const Conversion& conv = (*it);

        if ( generalTkOnly ) {//only check with general tracks. High purity flag always ON (suggested by Nancy)
	  if (! ( conv.quality(reco::Conversion::generalTracksOnly)  && conv.quality(reco::Conversion::highPurity) ) ) continue;
	}
	else {
	  if (! ( conv.quality(reco::Conversion::arbitratedMerged) && conv.quality(reco::Conversion::highPurity))  ) continue;
	}

	if (conv.nTracks()!=2) continue;
	const Vertex& vtx = conv.conversionVertex();
	if (!(vtx.isValid())) continue;
	const edm::RefToBase<reco::Track> tk1 = conv.tracks().front();
	const edm::RefToBase<reco::Track> tk2 = conv.tracks().back();
	double recoPhoR = vtx.position().Rho();
	//math::XYZVector photonMom = tk1->momentum()+tk2->momentum();
	math::XYZVector photonMom = conv.refittedPairMomentum();
	double recoPhoPt = sqrt(photonMom.perp2());
	deltaX = (*iPho).vertex().x()-vtx.position().x();
	deltaY = (*iPho).vertex().y()-vtx.position().y();
	deltaZ = (*iPho).vertex().z()-vtx.position().z();
	deltaR  = recoPhoR-mcPhoR;
	deltaPt = recoPhoPt-mcPhoPt;
	deltaPhi = photonMom.phi()-mcPhoPhi;
	deltaTheta = photonMom.theta()-mcPhoTheta;
#ifdef ADDONS

	if (retracking){//if re-doing the tracking to test the dedicated tracking step. 
	    //NOTE retracking should be set to False if reading conversions out of box because trajectory is not stored in RECO
	    PTrajectoryStateOnDet state1 = tk1->seedRef()->startingState();
	    DetId detId1(state1.detId());
	    TrajectoryStateOnSurface tsos1 = transformer.transientState( state1, &(theG->idToDet(detId1)->surface()), theMF.product());
	    PTrajectoryStateOnDet state2 = tk2->seedRef()->startingState();
	    DetId detId2(state2.detId());
	    TrajectoryStateOnSurface tsos2 = transformer.transientState( state2, &(theG->idToDet(detId2)->surface()), theMF.product());
	    qSeed1 = state1.parameters().charge();
	    ptSeed1 = tsos1.globalMomentum().perp();
	    phiSeed1 = tsos1.globalMomentum().phi();
	    thetaSeed1 = tsos1.globalMomentum().theta();
	    rSeed1 = tsos1.globalPosition().perp();
	    zSeed1 = tsos1.globalPosition().z();
	    qSeed2 = state2.parameters().charge();
	    ptSeed2 = tsos2.globalMomentum().perp();
	    phiSeed2 = tsos2.globalMomentum().phi();
	    thetaSeed2 = tsos2.globalMomentum().theta();
	    rSeed2 = tsos2.globalPosition().perp();
	    zSeed2 = tsos2.globalPosition().z();
	}
 	theAlgo1 = tk1->algo();
	theAlgo2 = tk2->algo();
#endif
	if (hitassoc) {
	  RefToBase<Track> tfrb1(tk1);
	  RefToBase<Track> tfrb2(tk2);
	  RefToBaseVector<Track> tc1, tc2;
	  tc1.push_back(tfrb1);
	  tc2.push_back(tfrb2);
	  SimToRecoCollection q1 = theAssociator->associateSimToReco(tc1,tpc,&iEvent);
	  SimToRecoCollection q2 = theAssociator->associateSimToReco(tc2,tpc,&iEvent);
	  std::vector<std::pair<RefToBase<reco::Track>, double> > trackV1, trackV2;
	  int tp_1 = 0, tp_2 = 1;//the index of associated tp in tpc for two tracks

	  if (q1.find(tpc[0])!=q1.end()){
	      trackV1 = (std::vector<std::pair<RefToBase<reco::Track>, double> >) q1[tpc[0]];
	  } else if (q1.find(tpc[1])!=q1.end()){
	      trackV1 = (std::vector<std::pair<RefToBase<reco::Track>, double> >) q1[tpc[1]];
	      tp_1 = 1;
	  }
	  if (q2.find(tpc[1])!=q2.end()){
	      trackV2 = (std::vector<std::pair<RefToBase<reco::Track>, double> >) q2[tpc[1]];
	  } else if (q2.find(tpc[0])!=q2.end()){
	      trackV2 = (std::vector<std::pair<RefToBase<reco::Track>, double> >) q2[tpc[0]];
	      tp_2 = 0;
	  }
	  if (!(trackV1.size()&&trackV2.size()))
	      continue;

	  RefToBase<Track> tr1 = trackV1.front().first;
	  RefToBase<Track> tr2 = trackV2.front().first;
	  if (prints) std::cout << "sim converted photon with p=" << (*iPho).fourMomentum() << " (pt=" << (*iPho).fourMomentum().perp()
	      << ") associated to reco conversion with p=" << tr1->momentum()+tr2->momentum() << endl;
	  assoc = true;
	} else {
          bool associationCondition = false;
	  if (fabs(vtx.position().eta())<1.2) 
	    associationCondition =(fabs(deltaX)<5. && fabs(deltaY)<5. &&fabs(deltaZ)<5.);
	  else 
	    associationCondition =(fabs(deltaX)<10. && fabs(deltaY)<10. &&fabs(deltaZ)<10.);

          if ( ! associationCondition ) continue;
	  assoc = true;
	}
	if (prints) std::cout << "associated" << endl;
	s2rbranch.isAssoc =1;
	s2rbranch.deltapt =deltaPt;
	s2rbranch.deltaphi =deltaPhi;
	s2rbranch.deltatheta =deltaTheta;
	s2rbranch.deltax = deltaX;
	s2rbranch.deltay = deltaY;
	s2rbranch.deltaz = deltaZ;
#ifdef ADDONS
	s2rbranch.qseed1 = qSeed1;
	s2rbranch.ptseed1 = ptSeed1;
	s2rbranch.phiseed1 = phiSeed1;
	s2rbranch.thetaseed1 = thetaSeed1;
	s2rbranch.rseed1 = rSeed1;
	s2rbranch.zseed1 = zSeed1;
	s2rbranch.qseed2 = qSeed2;
	s2rbranch.ptseed2 = ptSeed2;
	s2rbranch.phiseed2 = phiSeed2;
	s2rbranch.thetaseed2 = thetaSeed2;
	s2rbranch.rseed2 = rSeed2;
	s2rbranch.zseed2 = zSeed2;
	s2rbranch.r_algo1 = theAlgo1;
	s2rbranch.r_algo2 = theAlgo2;

	//count hits before vertex
	int before_hit1 = 0, before_hit2 = 0;
	for (trackingRecHit_iterator hit = tk1->recHitsBegin(); hit != tk1->recHitsEnd(); ++hit){
	  if ((*hit)->isValid () && !(*hit)->geographicalId ().null ()){
	    LocalPoint local_pos(0, 0, 0);//for 336, it needs refit
	    GlobalPoint hit_pos = tracker->idToDet((*hit)->geographicalId())->surface().toGlobal(local_pos);
	    if ((hit_pos.perp()<recoPhoR) && fabs(hit_pos.z())<fabs(vtx.position().z())){
	      before_hit1 ++;
	    }
	  }
	}
	for (trackingRecHit_iterator hit = tk2->recHitsBegin(); hit != tk2->recHitsEnd(); ++hit){
	  if ((*hit)->isValid () && !(*hit)->geographicalId ().null ()){
	    LocalPoint local_pos(0, 0, 0);//for 336, it needs refit
	    GlobalPoint hit_pos = tracker->idToDet((*hit)->geographicalId())->surface().toGlobal(local_pos);
	    if ((hit_pos.perp()<recoPhoR) && fabs(hit_pos.z())<fabs(vtx.position().z())){
	      before_hit2 ++;
	    }
	  }
	}
	double iphi1 = tk1->innerMomentum().phi(), iphi2 = tk2->innerMomentum().phi();
	GlobalVector ip1(tk1->innerMomentum().x(), tk1->innerMomentum().y(), tk1->innerMomentum().z()),
	  ip2(tk2->innerMomentum().x(), tk2->innerMomentum().y(), tk2->innerMomentum().z());
	//take the phi from the vertex if it can propagate back to that position
	Surface::RotationType rot;
	ReferenceCountingPointer<BoundCylinder>  theBarrel_(new BoundCylinder( Surface::PositionType(0,0,0), rot,
									       SimpleCylinderBounds( recoPhoR-0.001, recoPhoR+0.001, -fabs(vtx.position().z()), fabs(vtx.position().z()))));
	ReferenceCountingPointer<BoundDisk>      theDisk_(
							  new BoundDisk( Surface::PositionType( 0, 0, vtx.position().z()), rot,
									 SimpleDiskBounds( 0, recoPhoR, -0.001, 0.001)));

	const TrajectoryStateOnSurface myTSOS1 = transformer.innerStateOnSurface(*tk1, *trackerGeom, magField);
	const TrajectoryStateOnSurface myTSOS2 = transformer.innerStateOnSurface(*tk2, *trackerGeom, magField);
	TrajectoryStateOnSurface  stateAtVtx1, stateAtVtx2;
	stateAtVtx1 = propag.propagate(myTSOS1, *theBarrel_);
	if (!stateAtVtx1.isValid() ) {
	  stateAtVtx1 = propag.propagate(myTSOS1, *theDisk_);
	}
	if (stateAtVtx1.isValid()){
	  iphi1 = stateAtVtx1.globalDirection().phi();
	  ip1 = stateAtVtx1.globalMomentum();
	}
	stateAtVtx2 = propag.propagate(myTSOS2, *theBarrel_);
	if (!stateAtVtx2.isValid() ) {
	  stateAtVtx2 = propag.propagate(myTSOS2, *theDisk_);
	}
	if (stateAtVtx2.isValid()){
	  iphi2 = stateAtVtx2.globalDirection().phi();
	  ip2 = stateAtVtx2.globalMomentum();
	}
	s2rbranch.r_pt1 = tk1->pt();
	s2rbranch.r_pt2 = tk2->pt();
	s2rbranch.r_theta1 = tk1->theta();
	s2rbranch.r_theta2 = tk2->theta();
	s2rbranch.r_hits1 = tk1->numberOfValidHits();
	s2rbranch.r_hits2 = tk2->numberOfValidHits();
	s2rbranch.r_chi21 = tk1->normalizedChi2();
	s2rbranch.r_chi22 = tk2->normalizedChi2();
	s2rbranch.r_missHits1 = tk1->lost();
	s2rbranch.r_missHits2 = tk2->lost();
	s2rbranch.r_before1 = before_hit1;
	s2rbranch.r_before2 = before_hit2;
	s2rbranch.r_phi1 = iphi1;
	s2rbranch.r_phi2 = iphi2;
	if (valid_pvtx){
	  s2rbranch.r_d01 = - tk1->dxy(the_pvtx.position());
	  s2rbranch.r_d02 = - tk2->dxy(the_pvtx.position());
	} else {
	  s2rbranch.r_d01 = tk1->d0();
	  s2rbranch.r_d02 = tk2->d0();
	}
	double chi2Prob = ChiSquaredProbability(vtx.chi2(), vtx.ndof());
	s2rbranch.r_chi2prob = chi2Prob;
	s2rbranch.r_minapp = conv.distOfMinimumApproach();
#endif

	break;
      }
      ntupleS2R->Fill();     
    }
  }
  
  //compute purity and plot residues
#ifdef ADDONS
  const static unsigned short PatternSize = 25;
  const static unsigned short HitSize = 11;
#endif
  for (ConversionCollection::const_iterator it = pIn->begin();it!=pIn->end();++it) {
    const Conversion& conv = (*it);

    if ( generalTkOnly ) {//only check with general tracks. High purity flag always ON (suggested by Nancy)
	if (! ( conv.quality(reco::Conversion::generalTracksOnly)  && conv.quality(reco::Conversion::highPurity) ) ) continue;
    } else {
	if (! (conv.quality(reco::Conversion::highPurity))  ) continue;
    }

    if (conv.nTracks()!=2) continue;
    const Vertex& vtx = conv.conversionVertex();
    if (!(vtx.isValid())) continue;

    edm::RefToBase<reco::Track> tk1 = conv.tracks().front();
    edm::RefToBase<reco::Track> tk2 = conv.tracks().back();     
    math::XYZVector photonMom = conv.refittedPairMomentum();
    double recoPhoPt = sqrt(photonMom.perp2());
    double recoPhoR = vtx.position().Rho();
    double chiSquaredVtx = vtx.chi2()/vtx.ndof();
    double chi2tk1=tk1->normalizedChi2();
    double chi2tk2=tk2->normalizedChi2();
    int hitstk1=tk1->numberOfValidHits();
    int hitstk2=tk2->numberOfValidHits();
    double deltaR  = 999;
    double deltaZ  = 999;
    double deltaPt = 999;
    double deltaPhi = 999;
    double deltaTheta = 999;
    double deltaX = 999;
    double deltaY = 999;

    //reco plots
    if (prints) std::cout << "fill reco plots" << endl;

    r2sbranch.q1 =tk1->charge();
    r2sbranch.nHits1 =hitstk1;
    r2sbranch.algo1 = tk1->algo();
    r2sbranch.pt1 =tk1->pt();
    r2sbranch.phi1 =tk1->phi();
    r2sbranch.theta1 =tk1->theta();
    r2sbranch.x1 =tk1->innerPosition().x();
    r2sbranch.y1 =tk1->innerPosition().y();
    r2sbranch.z1 =tk1->innerPosition().z();
    r2sbranch.chi21=chi2tk1;
    r2sbranch.q2 =tk2->charge();
    r2sbranch.nHits2 =hitstk2;
    r2sbranch.algo2 = tk2->algo();
    r2sbranch.pt2 =tk2->pt();
    r2sbranch.phi2 =tk2->phi();
    r2sbranch.theta2 =tk2->theta();
    r2sbranch.x2 =tk2->innerPosition().x();
    r2sbranch.y2 =tk2->innerPosition().y();
    r2sbranch.z2 =tk2->innerPosition().z();
    r2sbranch.chi22=chi2tk2;
    r2sbranch.pt =recoPhoPt;
    r2sbranch.phi =photonMom.phi();
    r2sbranch.theta =photonMom.theta();
    r2sbranch.x =vtx.position().x();
    r2sbranch.y =vtx.position().y();
    r2sbranch.z =vtx.position().z();
    r2sbranch.chi2=chiSquaredVtx;
    r2sbranch.minapp =conv.distOfMinimumApproach();

    if (valid_pvtx){
      r2sbranch.d01 = - tk1->dxy(the_pvtx.position());
      r2sbranch.d02 = - tk2->dxy(the_pvtx.position());
      r2sbranch.dz1 = - tk1->dz(the_pvtx.position());
      r2sbranch.dz2 = - tk2->dz(the_pvtx.position());
    } else {
      r2sbranch.d01 =tk1->d0();
      r2sbranch.d02 =tk2->d0();
      r2sbranch.dz1 =tk1->dz();
      r2sbranch.dz2 =tk2->dz();
    }

    double iphi1 = tk1->innerMomentum().phi(), iphi2 = tk2->innerMomentum().phi();
    GlobalVector ip1(tk1->innerMomentum().x(), tk1->innerMomentum().y(), tk1->innerMomentum().z()),
      ip2(tk2->innerMomentum().x(), tk2->innerMomentum().y(), tk2->innerMomentum().z());
    //take the phi from the vertex if it can propagate back to that position
    Surface::RotationType rot;
    ReferenceCountingPointer<BoundCylinder>  theBarrel_(new BoundCylinder( Surface::PositionType(0,0,0), rot,
									   SimpleCylinderBounds( recoPhoR-0.001, recoPhoR+0.001, 
												 -fabs(vtx.position().z()), 
												 fabs(vtx.position().z()))));
    ReferenceCountingPointer<BoundDisk>      theDisk_(
						      new BoundDisk( Surface::PositionType( 0, 0, vtx.position().z()), rot,
								     SimpleDiskBounds( 0, recoPhoR, -0.001, 0.001)));
    const TrajectoryStateOnSurface myTSOS1 = transformer.innerStateOnSurface(*tk1, *trackerGeom, magField);
    const TrajectoryStateOnSurface myTSOS2 = transformer.innerStateOnSurface(*tk2, *trackerGeom, magField);
    TrajectoryStateOnSurface  stateAtVtx1, stateAtVtx2;
    stateAtVtx1 = propag.propagate(myTSOS1, *theBarrel_);
    if (!stateAtVtx1.isValid() ) {
      stateAtVtx1 = propag.propagate(myTSOS1, *theDisk_);
    }
    if (stateAtVtx1.isValid()){
      iphi1 = stateAtVtx1.globalDirection().phi();
      ip1 = stateAtVtx1.globalMomentum();
    }
    stateAtVtx2 = propag.propagate(myTSOS2, *theBarrel_);
    if (!stateAtVtx2.isValid() ) {
      stateAtVtx2 = propag.propagate(myTSOS2, *theDisk_);
    }
    if (stateAtVtx2.isValid()){
      iphi2 = stateAtVtx2.globalDirection().phi();
      ip2 = stateAtVtx2.globalMomentum();
    }
    bool back_prop1 = (tk1->innerPosition().Rho()<recoPhoR) && fabs(tk1->innerPosition().z())<fabs(vtx.position().z());
    bool back_prop2 = (tk2->innerPosition().Rho()<recoPhoR) && fabs(tk2->innerPosition().z())<fabs(vtx.position().z());
    if (prints)
      std::cout<<" state validity "<<stateAtVtx1.isValid()<<" "<<stateAtVtx2.isValid()<<" eta "<<photonMom.eta()<<" bk1 "<<back_prop1<<" bk2 "<<back_prop2<<std::endl;

    r2sbranch.iphi1 =iphi1;
    r2sbranch.iphi2 =iphi2;

#ifdef ADDONS
    reco::Vertex the_vtx = conv.conversionVertex();
    vector<Track> refit_tracks;
    bool has_refit = false;
    if (the_vtx.isValid()){
      refit_tracks = the_vtx.refittedTracks();
      if (refit_tracks.size()==2){
	r2sbranch.refit = 1;
	has_refit = true;
      }
    }
    const TransientTrack ttk_l(*tk1, magField);
    const TransientTrack ttk_r(*tk2, magField);

    const HitPattern & pattern1 = tk1->hitPattern();
    const HitPattern & pattern2 = tk2->hitPattern();
    //valid pixel hits
    int np_hit1 = pattern1.numberOfValidPixelHits();
    int np_hit2 = pattern2.numberOfValidPixelHits();
    int ns_hit1 = 0, ns_hit2 = 0;
    for (int i=0; i<(PatternSize * 32) / HitSize; i++) {
      uint32_t pattern = pattern1.getHitPattern(i);
      if (pattern != 0) {//valid strip stereo hit
	if (pattern1.validHitFilter(pattern)) {
	  if (pattern1.stripHitFilter(pattern)){
	    if (pattern1.getSide(pattern)==1){
	      ns_hit1++;
	    }
	  }
	}
      }
    }
    for (int i=0; i<(PatternSize * 32) / HitSize; i++) {
      uint32_t pattern = pattern2.getHitPattern(i);
      if (pattern != 0) {//valid strip stereo hit
	if (pattern2.validHitFilter(pattern)) {
	  if (pattern2.stripHitFilter(pattern)){
	    if (pattern2.getSide(pattern)==1){
	      ns_hit2++;
	    }
	  }
	}
      }
    }

    double chi2Prob = ChiSquaredProbability(vtx.chi2(), vtx.ndof());
    //count hits before vertex
    int before_hit1 = 0, before_hit2 = 0;

    for (trackingRecHit_iterator hit = tk1->recHitsBegin(); hit != tk1->recHitsEnd(); ++hit){
      if ((*hit)->isValid () && !(*hit)->geographicalId ().null ()){
	LocalPoint local_pos(0, 0, 0);//for 336, it needs refit
	GlobalPoint hit_pos = tracker->idToDet((*hit)->geographicalId())->surface().toGlobal(local_pos);
	if ((hit_pos.perp()<recoPhoR) && fabs(hit_pos.z())<fabs(vtx.position().z())){
	  before_hit1 ++;
	}
      }
    }
    for (trackingRecHit_iterator hit = tk2->recHitsBegin(); hit != tk2->recHitsEnd(); ++hit){
      if ((*hit)->isValid () && !(*hit)->geographicalId ().null ()){
	LocalPoint local_pos(0, 0, 0);//for 336, it needs refit
	GlobalPoint hit_pos = tracker->idToDet((*hit)->geographicalId())->surface().toGlobal(local_pos);
	if ((hit_pos.perp()<recoPhoR) && fabs(hit_pos.z())<fabs(vtx.position().z())){
	  before_hit2 ++;
	}
      }
    }

    if (has_refit){
      Track& rtk1 = refit_tracks.front();
      Track& rtk2 = refit_tracks.back();
      math::XYZVector refit_photonMom = rtk1.momentum()+rtk2.momentum();
      double refit_recoPhoPt = sqrt(refit_photonMom.perp2());
      if (prints) std::cout<<"Refitted tracks "<<refit_tracks.size()<<" momentum "<< sqrt(refit_photonMom.perp2()) 
			   <<"  diff "<< sqrt(refit_photonMom.perp2())-sqrt(photonMom.perp2())<<std::endl;

      if (valid_pvtx){
	r2sbranch.r_d01 = - rtk1.dxy(the_pvtx.position());
	r2sbranch.r_d02 = - rtk2.dxy(the_pvtx.position());
      } else {
	r2sbranch.r_d01 =rtk1.d0();
	r2sbranch.r_d02 =rtk2.d0();
      }
      r2sbranch.r_pt1 =rtk1.pt();
      r2sbranch.r_phi1 =rtk1.phi();
      r2sbranch.r_theta1 =rtk1.theta();
      r2sbranch.r_px1 = rtk1.px();
      r2sbranch.r_py1 = rtk1.py();
      r2sbranch.r_pz1 = rtk1.pz();
      r2sbranch.r_pt2 =rtk2.pt();
      r2sbranch.r_phi2 =rtk2.phi();
      r2sbranch.r_theta2 =rtk2.theta();
      r2sbranch.r_px2 = rtk2.px();
      r2sbranch.r_py2 = rtk2.py();
      r2sbranch.r_pz2 = rtk2.pz();
      r2sbranch.r_pt =refit_recoPhoPt;
      r2sbranch.r_phi =refit_photonMom.phi();
      r2sbranch.r_theta =refit_photonMom.theta();
    }
    r2sbranch.beforeHits1 =before_hit1;
    r2sbranch.npHits1 =np_hit1;
    r2sbranch.nsHits1 =ns_hit1;
    r2sbranch.missHits1 = tk1->lost();;
    r2sbranch.ipx1 = ip1.x();
    r2sbranch.ipy1 = ip1.y();
    r2sbranch.ipz1 = ip1.z();
    r2sbranch.beforeHits2 =before_hit2;
    r2sbranch.npHits2 =np_hit2;
    r2sbranch.nsHits2 =ns_hit2;
    r2sbranch.missHits2 = tk2->lost();;
    r2sbranch.ipx2 = ip2.x();
    r2sbranch.ipy2 = ip2.y();
    r2sbranch.ipz2 = ip2.z();
    r2sbranch.chi2prob = chi2Prob;
    r2sbranch.mass = conv.pairInvariantMass();
#endif

    r2sbranch.isAssoc =0;
    r2sbranch.deltapt =0;
    r2sbranch.deltaphi =0;
    r2sbranch.deltatheta =0;
    r2sbranch.deltax =0;
    r2sbranch.deltay =0;
    r2sbranch.deltaz =0;

    bool associated = false;
    if (simulation) {
      double simPhoR(0), simPhoZ(0), simPhoEta(0), simPhoPt(0), simPhoPhi(0), simPhoTheta(0);
      if (prints) std::cout << "check assoc" << endl;
      if (hitassoc) {
	RefToBase<Track> tfrb1(tk1);
	RefToBase<Track> tfrb2(tk2);
	RefToBaseVector<Track> tc1, tc2;
	tc1.push_back(tfrb1);
	tc2.push_back(tfrb2);
	RefVector<TrackingParticleCollection> tpc(TPCollectionH.id());
	for (unsigned int j=0; j<TPCollectionH->size();j++) {
	  Ref<TrackingParticleCollection> tptest(TPCollectionH,j);
	  if (abs(tptest->pdgId())==11 && (tptest->parentVertex()->sourceTracks_end()-tptest->parentVertex()->sourceTracks_begin()==1) 
	      && (*tptest->parentVertex()->sourceTracks_begin())->pdgId()==22 ) {
	    double tmpSimPhoR = sqrt(tptest->parentVertex()->position().Perp2());
	    double tmpSimPhoZ = tptest->parentVertex()->position().z();
	    double tmpSimPhoEta = (*tptest->parentVertex()->sourceTracks_begin())->momentum().eta();
	    double tmpSimPhoPt = sqrt((*tptest->parentVertex()->sourceTracks_begin())->momentum().Perp2());
	    //double tmpSimPhoPhi = (*tptest->parentVertex()->sourceTracks_begin())->momentum().Phi();
	    //double tmpSimPhoTheta = (*tptest->parentVertex()->sourceTracks_begin())->momentum().Theta();
	    if (tmpSimPhoPt>minPhoPtForPurity && fabs(tmpSimPhoEta)<maxPhoEtaForPurity 
		&& tmpSimPhoR<maxPhoRForPurity && fabs(tmpSimPhoZ)<maxPhoZForPurity ) {
	      tpc.push_back(tptest);
	    }
	  }
	}
	if (tpc.size()>0) {
	  RecoToSimCollection p1 = theAssociator->associateRecoToSim(tc1,tpc,&iEvent);
	  RecoToSimCollection p2 = theAssociator->associateRecoToSim(tc2,tpc,&iEvent);
	  std::vector<std::pair<TrackingParticleRef, double> > tp1, tp2;
	  //std::vector<std::pair<TrackingParticleRef, double> > tp2 = p2[tfrb2];
	  if (p1.find(tfrb1) != p1.end()){
	      tp1 = p1[tfrb1];
	  }
	  if (p2.find(tfrb2) != p2.end()){
	      tp2 = p2[tfrb2];
	  }
	  if (tp1.size()&&tp2.size()) {
	      TrackingParticleRef tpr1 = tp1.front().first;
	      TrackingParticleRef tpr2 = tp2.front().first;
	      if (abs(tpr1->pdgId())==11&&abs(tpr2->pdgId())==11) {
		  if ( (tpr1->parentVertex()->sourceTracks_end()-tpr1->parentVertex()->sourceTracks_begin()==1) && 
			  (tpr2->parentVertex()->sourceTracks_end()-tpr2->parentVertex()->sourceTracks_begin()==1)) {
		      if (tpr1->parentVertex().key()==tpr2->parentVertex().key() && ((*tpr1->parentVertex()->sourceTracks_begin())->pdgId()==22)) {
			  simPhoR = sqrt(tpr1->parentVertex()->position().Perp2());
			  simPhoZ = tpr1->parentVertex()->position().z();
			  simPhoEta = (*tpr1->parentVertex()->sourceTracks_begin())->momentum().eta();
			  simPhoPt = sqrt((*tpr1->parentVertex()->sourceTracks_begin())->momentum().Perp2());
			  simPhoPhi = (*tpr1->parentVertex()->sourceTracks_begin())->momentum().Phi();
			  simPhoTheta = (*tpr1->parentVertex()->sourceTracks_begin())->momentum().Theta();
			  deltaX = tpr1->parentVertex()->position().x()-vtx.position().x();
			  deltaY = tpr1->parentVertex()->position().y()-vtx.position().y();
			  deltaZ = tpr1->parentVertex()->position().z()-vtx.position().z();
			  if (prints) std::cout << "reco converted photon with p=" << photonMom << " (pt=" << sqrt(photonMom.Perp2())
			      << ") associated to reco conversion with p=" << (*tpr1->parentVertex()->sourceTracks_begin())->momentum()
				  << " recoR=" << recoPhoR << " simR=" << simPhoR << endl;
			  //std::cout << "associated track1 to " << tpr1->pdgId() << " with p=" << tpr1->p4() << " with pT=" << tpr1->pt() << endl;
			  //std::cout << "associated track2 to " << tpr2->pdgId() << " with p=" << tpr2->p4() << " with pT=" << tpr2->pt() << endl;
			  associated = true;
		      }
		  }
	      }
	  }
	}
      } else {
	  vector<PhotonMCTruth>::const_iterator iPho;
	  for (iPho=mcPhotons.begin(); iPho !=mcPhotons.end(); ++iPho ) {
	      if (prints) std::cout << "in loop over mc photons" << endl;
	      simPhoR = (*iPho).vertex().perp();
	  simPhoZ = (*iPho).vertex().z();
	  simPhoEta = (*iPho).fourMomentum().eta();
	  simPhoPt = (*iPho).fourMomentum().perp();
	  simPhoPhi = (*iPho).fourMomentum().phi();
	  simPhoTheta = (*iPho).fourMomentum().theta();
	  if ( ((*iPho).isAConversion()) && simPhoPt>minPhoPtForPurity && fabs(simPhoEta)<maxPhoEtaForPurity 
	       && simPhoR<maxPhoRForPurity && fabs(simPhoZ)<maxPhoZForPurity ) {
	    deltaX = (*iPho).vertex().x()-vtx.position().x();
	    deltaY = (*iPho).vertex().y()-vtx.position().y();
	    deltaZ = (*iPho).vertex().z()-vtx.position().z();

	    bool associationCondition = false;
	    if (fabs(vtx.position().eta())<1.2) 
	      associationCondition =(fabs(deltaX)<5. && fabs(deltaY)<5. &&fabs(deltaZ)<5.);
	    else 
	      associationCondition =(fabs(deltaX)<10. && fabs(deltaY)<10. &&fabs(deltaZ)<10.);
	    
	    if ( associationCondition ) {
	      //if (prints) std::cout << "recV=" << vtx.position() << " simV=" << (*iPho).vertex() << " deltaR=" << vtx.position().perp()-(*iPho).vertex().perp() << " deltaPt=" << sqrt(photonMom.perp2())-(*iPho).fourMomentum().perp() << endl;
	      associated = true;
	      deltaR  = recoPhoR-simPhoR;
	      deltaPt = recoPhoPt-simPhoPt;
	      deltaPhi = photonMom.phi()-simPhoPhi;
	      deltaTheta = photonMom.theta()-simPhoTheta;
	      break;
	    }
	  }
	}
      }    
      if (associated) {
	if (prints) std::cout << "associated" << endl;
	//residue
	r2sbranch.isAssoc =1;
	r2sbranch.deltapt =deltaPt;
	r2sbranch.deltaphi =deltaPhi;
	r2sbranch.deltatheta =deltaTheta;
	r2sbranch.deltax = deltaX;
	r2sbranch.deltay = deltaY;
	r2sbranch.deltaz = deltaZ;
      }
    }
    ntupleR2S->Fill();    
    if (prints) std::cout << "end of loop" << endl;
  }  
  if (prints) std::cout << "end of event" << endl;
}


// ------------ method called once each job just before starting event loop  ------------
void 
ConversionNtuplizer::beginJob()
{
  file = new TFile(outfile.c_str(),"recreate");
  
  const bool oldAddDir = TH1::AddDirectoryStatus();
  TH1::AddDirectory(true);

#ifdef ADDONS
  ntupleEvt = new TTree("ntupleEvt", "evt");
  ntupleEvt->Branch("run", &(evtbranch.run),"run/I");
  ntupleEvt->Branch("event", &(evtbranch.event),"event/I");
  ntupleEvt->Branch("lumi", &(evtbranch.lumi),"lumi/I");
#endif

  ntupleS2R = new TTree("ntupleS2R","sim2reco");
  ntupleS2R->Branch("run",&(s2rbranch.run),"run/I");
  ntupleS2R->Branch("event",&(s2rbranch.event),"event/I");
  ntupleS2R->Branch("isAssoc",&(s2rbranch.isAssoc),"isAssoc/I");
  ntupleS2R->Branch("q1",&(s2rbranch.q1),"q1/I");
  ntupleS2R->Branch("pt1",&(s2rbranch.pt1),"pt1/F");
  ntupleS2R->Branch("phi1",&(s2rbranch.phi1),"phi1/F");
  ntupleS2R->Branch("theta1",&(s2rbranch.theta1),"theta1/F");
  ntupleS2R->Branch("q2",&(s2rbranch.q2),"q2/I");
  ntupleS2R->Branch("pt2",&(s2rbranch.pt2),"pt2/F");
  ntupleS2R->Branch("phi2",&(s2rbranch.phi2),"phi2/F");
  ntupleS2R->Branch("theta2",&(s2rbranch.theta2),"theta2/F");
  ntupleS2R->Branch("pt",&(s2rbranch.pt),"pt/F");
  ntupleS2R->Branch("phi",&(s2rbranch.phi),"phi/F");
  ntupleS2R->Branch("theta",&(s2rbranch.theta),"theta/F");
  ntupleS2R->Branch("x",&(s2rbranch.x),"x/F");
  ntupleS2R->Branch("y",&(s2rbranch.y),"y/F");
  ntupleS2R->Branch("z",&(s2rbranch.z),"z/F");
  ntupleS2R->Branch("deltapt",&(s2rbranch.deltapt),"deltapt/F");
  ntupleS2R->Branch("deltaphi",&(s2rbranch.deltaphi),"deltaphi/F");
  ntupleS2R->Branch("deltatheta",&(s2rbranch.deltatheta),"deltatheta/F");
  ntupleS2R->Branch("deltax",&(s2rbranch.deltax),"deltax/F");
  ntupleS2R->Branch("deltay",&(s2rbranch.deltay),"deltay/F");
  ntupleS2R->Branch("deltaz",&(s2rbranch.deltaz),"deltaz/F");
#ifdef ADDONS
  ntupleS2R->Branch("qseed1",&(s2rbranch.qseed1),"qseed1/F");
  ntupleS2R->Branch("ptseed1",&(s2rbranch.ptseed1),"ptseed1/F");
  ntupleS2R->Branch("phiseed1",&(s2rbranch.phiseed1),"phiseed1/F");
  ntupleS2R->Branch("thetaseed1",&(s2rbranch.thetaseed1),"thetaseed1/F");
  ntupleS2R->Branch("rseed1",&(s2rbranch.rseed1),"rseed1/F");
  ntupleS2R->Branch("zseed1",&(s2rbranch.zseed1),"zseed1/F");
  ntupleS2R->Branch("qseed2",&(s2rbranch.qseed2),"qseed2/F");
  ntupleS2R->Branch("ptseed2",&(s2rbranch.ptseed2),"ptseed2/F");
  ntupleS2R->Branch("phiseed2",&(s2rbranch.phiseed2),"phiseed2/F");
  ntupleS2R->Branch("thetaseed2",&(s2rbranch.thetaseed2),"thetaseed2/F");
  ntupleS2R->Branch("rseed2",&(s2rbranch.rseed2),"rseed2/F");
  ntupleS2R->Branch("zseed2",&(s2rbranch.zseed2),"zseed2/F");
  ntupleS2R->Branch("r_pt1",&(s2rbranch.r_pt1),"r_pt1/F");
  ntupleS2R->Branch("r_d01",&(s2rbranch.r_d01),"r_d01/F");
  ntupleS2R->Branch("r_theta1",&(s2rbranch.r_theta1),"r_theta1/F");
  ntupleS2R->Branch("r_phi1",&(s2rbranch.r_phi1),"r_phi1/F");
  ntupleS2R->Branch("r_chi21",&(s2rbranch.r_chi21),"r_chi21/F");
  ntupleS2R->Branch("r_algo1",&(s2rbranch.r_algo1),"r_algo1/I");
  ntupleS2R->Branch("r_hits1",&(s2rbranch.r_hits1),"r_hits1/I");
  ntupleS2R->Branch("r_before1",&(s2rbranch.r_before1),"r_before1/I");
  ntupleS2R->Branch("r_missHits1",&(s2rbranch.r_missHits1),"r_missHits1/I");
  ntupleS2R->Branch("r_pt2",&(s2rbranch.r_pt2),"r_pt2/F");
  ntupleS2R->Branch("r_d02",&(s2rbranch.r_d02),"r_d02/F");
  ntupleS2R->Branch("r_theta2",&(s2rbranch.r_theta2),"r_theta2/F");
  ntupleS2R->Branch("r_phi2",&(s2rbranch.r_phi2),"r_phi2/F");
  ntupleS2R->Branch("r_chi22",&(s2rbranch.r_chi22),"r_chi22/F");
  ntupleS2R->Branch("r_algo2",&(s2rbranch.r_algo2),"r_algo2/I");
  ntupleS2R->Branch("r_hits2",&(s2rbranch.r_hits2),"r_hits2/I");
  ntupleS2R->Branch("r_before2",&(s2rbranch.r_before2),"r_before2/I");
  ntupleS2R->Branch("r_missHits2",&(s2rbranch.r_missHits2),"r_missHits2/I");
  ntupleS2R->Branch("r_minapp",&(s2rbranch.r_minapp),"r_minapp/F");
  ntupleS2R->Branch("r_chi2prob",&(s2rbranch.r_chi2prob),"r_chi2prob/F");
#endif

  ntupleR2S = new TTree("ntupleR2S","reco2sim");
  ntupleR2S->Branch("run",&(r2sbranch.run),"run/I");
  ntupleR2S->Branch("event",&(r2sbranch.event),"event/I");
  ntupleR2S->Branch("isAssoc",&(r2sbranch.isAssoc),"isAssoc/I");
  ntupleR2S->Branch("q1",&(r2sbranch.q1),"q1/I");
  ntupleR2S->Branch("q2",&(r2sbranch.q2),"q2/I");
  ntupleR2S->Branch("nHits1",&(r2sbranch.nHits1),"nHits1/I");
  ntupleR2S->Branch("nHits2",&(r2sbranch.nHits2),"nHits2/I");
  ntupleR2S->Branch("algo1",&(r2sbranch.algo1),"algo1/I");
  ntupleR2S->Branch("algo2",&(r2sbranch.algo2),"algo2/I");
  ntupleR2S->Branch("d01",&(r2sbranch.d01),"d01/F");
  ntupleR2S->Branch("dz1",&(r2sbranch.dz1),"dz1/F");
  ntupleR2S->Branch("pt1",&(r2sbranch.pt1),"pt1/F");
  ntupleR2S->Branch("phi1",&(r2sbranch.phi1),"phi1/F");
  ntupleR2S->Branch("iphi1",&(r2sbranch.iphi1),"iphi1/F");
  ntupleR2S->Branch("theta1",&(r2sbranch.theta1),"theta1/F");
  ntupleR2S->Branch("x1",&(r2sbranch.x1),"x1/F");
  ntupleR2S->Branch("y1",&(r2sbranch.y1),"y1/F");
  ntupleR2S->Branch("z1",&(r2sbranch.z1),"z1/F");
  ntupleR2S->Branch("chi21",&(r2sbranch.chi21),"chi21/F");
  ntupleR2S->Branch("d02",&(r2sbranch.d02),"d02/F");
  ntupleR2S->Branch("dz2",&(r2sbranch.dz2),"dz2/F");
  ntupleR2S->Branch("pt2",&(r2sbranch.pt2),"pt2/F");
  ntupleR2S->Branch("phi2",&(r2sbranch.phi2),"phi2/F");
  ntupleR2S->Branch("iphi2",&(r2sbranch.iphi2),"iphi2/F");
  ntupleR2S->Branch("theta2",&(r2sbranch.theta2),"theta2/F");
  ntupleR2S->Branch("x2",&(r2sbranch.x2),"x2/F");
  ntupleR2S->Branch("y2",&(r2sbranch.y2),"y2/F");
  ntupleR2S->Branch("z2",&(r2sbranch.z2),"z2/F");
  ntupleR2S->Branch("chi22",&(r2sbranch.chi22),"chi22/F");
  ntupleR2S->Branch("pt",&(r2sbranch.pt),"pt/F");
  ntupleR2S->Branch("phi",&(r2sbranch.phi),"phi/F");
  ntupleR2S->Branch("theta",&(r2sbranch.theta),"theta/F");
  ntupleR2S->Branch("x",&(r2sbranch.x),"x/F");
  ntupleR2S->Branch("y",&(r2sbranch.y),"y/F");
  ntupleR2S->Branch("z",&(r2sbranch.z),"z/F");
  ntupleR2S->Branch("chi2",&(r2sbranch.chi2),"chi2/F");
  ntupleR2S->Branch("deltapt",&(r2sbranch.deltapt),"deltapt/F");
  ntupleR2S->Branch("deltaphi",&(r2sbranch.deltaphi),"deltaphi/F");
  ntupleR2S->Branch("deltatheta",&(r2sbranch.deltatheta),"deltatheta/F");
  ntupleR2S->Branch("deltax",&(r2sbranch.deltax),"deltax/F");
  ntupleR2S->Branch("deltay",&(r2sbranch.deltay),"deltay/F");
  ntupleR2S->Branch("deltaz",&(r2sbranch.deltaz),"deltaz/F");
  ntupleR2S->Branch("minapp",&(r2sbranch.minapp),"minapp/F");
#ifdef ADDONS
  ntupleR2S->Branch("beforeHits1",&(r2sbranch.beforeHits1),"beforeHits1/I");
  ntupleR2S->Branch("beforeHits2",&(r2sbranch.beforeHits2),"beforeHits2/I");
  ntupleR2S->Branch("npHits1",&(r2sbranch.npHits1),"npHits1/I");
  ntupleR2S->Branch("npHits2",&(r2sbranch.npHits2),"npHits2/I");
  ntupleR2S->Branch("nsHits1",&(r2sbranch.nsHits1),"nsHits1/I");
  ntupleR2S->Branch("nsHits2",&(r2sbranch.nsHits2),"nsHits2/I");
  ntupleR2S->Branch("missHits1",&(r2sbranch.missHits1),"missHits1/I");
  ntupleR2S->Branch("missHits2",&(r2sbranch.missHits2),"missHits2/I");
  ntupleR2S->Branch("refit",&(r2sbranch.refit),"refit/I");
  ntupleR2S->Branch("r_pt1",&(r2sbranch.r_pt1),"r_pt1/F");
  ntupleR2S->Branch("r_d01",&(r2sbranch.r_d01),"r_d01/F");
  ntupleR2S->Branch("r_phi1",&(r2sbranch.r_phi1),"r_phi1/F");
  ntupleR2S->Branch("r_theta1",&(r2sbranch.r_theta1),"r_theta1/F");
  ntupleR2S->Branch("ipx1",&(r2sbranch.ipx1),"ipx1/F");
  ntupleR2S->Branch("ipy1",&(r2sbranch.ipy1),"ipy1/F");
  ntupleR2S->Branch("ipz1",&(r2sbranch.ipz1),"ipz1/F");
  ntupleR2S->Branch("r_px1",&(r2sbranch.r_px1),"r_px1/F");
  ntupleR2S->Branch("r_py1",&(r2sbranch.r_py1),"r_py1/F");
  ntupleR2S->Branch("r_pz1",&(r2sbranch.r_pz1),"r_pz1/F");
  ntupleR2S->Branch("r_pt2",&(r2sbranch.r_pt2),"r_pt2/F");
  ntupleR2S->Branch("r_d02",&(r2sbranch.r_d02),"r_d02/F");
  ntupleR2S->Branch("r_phi2",&(r2sbranch.r_phi2),"r_phi2/F");
  ntupleR2S->Branch("r_theta2",&(r2sbranch.r_theta2),"r_theta2/F");
  ntupleR2S->Branch("ipx2",&(r2sbranch.ipx2),"ipx2/F");
  ntupleR2S->Branch("ipy2",&(r2sbranch.ipy2),"ipy2/F");
  ntupleR2S->Branch("ipz2",&(r2sbranch.ipz2),"ipz2/F");
  ntupleR2S->Branch("r_px2",&(r2sbranch.r_px2),"r_px2/F");
  ntupleR2S->Branch("r_py2",&(r2sbranch.r_py2),"r_py2/F");
  ntupleR2S->Branch("r_pz2",&(r2sbranch.r_pz2),"r_pz2/F");
  ntupleR2S->Branch("r_pt",&(r2sbranch.r_pt),"r_pt/F");
  ntupleR2S->Branch("r_phi",&(r2sbranch.r_phi),"r_phi/F");
  ntupleR2S->Branch("r_theta",&(r2sbranch.r_theta),"r_theta/F");
  ntupleR2S->Branch("vx",&(r2sbranch.vx),"vx/F");
  ntupleR2S->Branch("vy",&(r2sbranch.vy),"vy/F");
  ntupleR2S->Branch("vz",&(r2sbranch.vz),"vz/F");
  ntupleR2S->Branch("bsx",&(r2sbranch.bsx),"bsx/F");
  ntupleR2S->Branch("bsy",&(r2sbranch.bsy),"bsy/F");
  ntupleR2S->Branch("bsz",&(r2sbranch.bsz),"bsz/F");
  ntupleR2S->Branch("chi2prob",&(r2sbranch.chi2prob),"chi2prob/F");
  ntupleR2S->Branch("mass",&(r2sbranch.mass),"mass/F");
#endif

  TH1::AddDirectory(oldAddDir);
}

// ------------ method called once each job just after ending the event loop  ------------
void 
ConversionNtuplizer::endJob() {
  file->Write();
  file->Close();
}

//define this as a plug-in
DEFINE_FWK_MODULE(ConversionNtuplizer);
