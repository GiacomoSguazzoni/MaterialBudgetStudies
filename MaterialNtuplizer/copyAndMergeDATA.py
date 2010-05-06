import os
pippo  = 'hadd /tmp/cerati/ntuple_conversion_CMSSW356_goodcoll7TeV.root '
pippo2 = 'hadd /tmp/cerati/ntuple_nuclint_CMSSW356_goodcoll7TeV.root '
done = [11,15,18,1,20,21,24,28,31,34,35,37,38,43,44,45,46,48,49,4,54,58,5,60,61,62,65,66,67,68,69,6,70,71,72,74,75,7,80,81,82,83,84,85,86,9]
for i in range(1,87):
    if i not in done: continue
    os.system('stager_get -M /castor/cern.ch/user/c/cerati/Tmp/ntuple_conversion_goodcoll7TeV_'+str(i)+'_1.root')
    os.system('stager_get -M /castor/cern.ch/user/c/cerati/Tmp/ntuple_nuclint_goodcoll7TeV_'+str(i)+'_1.root')
    pippo = pippo+' rfio:/castor/cern.ch/user/c/cerati/Tmp/ntuple_conversion_goodcoll7TeV_'+str(i)+'_1.root'
    pippo2 = pippo2+' rfio:/castor/cern.ch/user/c/cerati/Tmp/ntuple_nuclint_goodcoll7TeV_'+str(i)+'_1.root'
#print pippo
os.system(pippo)
os.system(pippo2)
os.system('rfcp /tmp/cerati/ntuple_conversion_CMSSW356_goodcoll7TeV.root $CASTOR_HOME/MaterialNtuples/ntuple_conversion_CMSSW356_goodcoll7TeV_2010-05-03.root')
os.system('rfcp /tmp/cerati/ntuple_nuclint_CMSSW356_goodcoll7TeV.root $CASTOR_HOME/MaterialNtuples/ntuple_nuclint_CMSSW356_goodcoll7TeV_2010-05-03.root')
#os.system('rm /tmp/cerati/*.root')
#for i in range(1,204):
#    os.system('rfrm /castor/cern.ch/cms/store/caf/user/cerati/ntuple_conversion_CMSSW336p3_goodcoll900GeV_'+str(i)+'.root')

