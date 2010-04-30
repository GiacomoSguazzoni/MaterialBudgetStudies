import os
pippo  = 'hadd /tmp/cerati/ntuple_conversion_CMSSW356_goodcoll7TeV.root '
pippo2 = 'hadd /tmp/cerati/ntuple_nuclint_CMSSW356_goodcoll7TeV.root '
for i in range(1,27):
    #if i==14: continue
    #if i==26: continue
    #if i==29: continue
    os.system('stager_get -M /castor/cern.ch/user/c/cerati/Tmp/ntuple_conversion_goodcoll7TeV_'+str(i)+'_1.root')
    os.system('stager_get -M /castor/cern.ch/user/c/cerati/Tmp/ntuple_nuclint_goodcoll7TeV_'+str(i)+'_1.root')
    pippo = pippo+' rfio:/castor/cern.ch/user/c/cerati/Tmp/ntuple_conversion_goodcoll7TeV_'+str(i)+'_1.root'
    pippo2 = pippo2+' rfio:/castor/cern.ch/user/c/cerati/Tmp/ntuple_nuclint_goodcoll7TeV_'+str(i)+'_1.root'
#print pippo
os.system(pippo)
os.system(pippo2)
os.system('rfcp /tmp/cerati/ntuple_conversion_CMSSW356_goodcoll7TeV.root $CASTOR_HOME/ConversionNtuples/ntuple_conversion_CMSSW356_goodcoll7TeV.root')
os.system('rfcp /tmp/cerati/ntuple_nuclint_CMSSW356_goodcoll7TeV.root $CASTOR_HOME/ConversionNtuples/ntuple_nuclint_CMSSW356_goodcoll7TeV.root')
#os.system('rm /tmp/cerati/*.root')
#for i in range(1,204):
#    os.system('rfrm /castor/cern.ch/cms/store/caf/user/cerati/ntuple_conversion_CMSSW336p3_goodcoll900GeV_'+str(i)+'.root')
