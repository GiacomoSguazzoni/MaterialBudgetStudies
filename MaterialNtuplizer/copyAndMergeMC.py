import os
pippo  = 'hadd /tmp/cerati/ntuple_conversion_CMSSW356_minbias7TeV.root '
pippo1 = 'hadd /tmp/cerati/ntuple_conversion_CMSSW356_minbias7TeV_hit.root '
pippo2 = 'hadd /tmp/cerati/ntuple_nuclint_CMSSW356_minbias7TeV.root '
#undone = [10,13,19,26,29,30,32,38,43,44,47,49,58,62,66,69,72,75,78,80,84,86,88,91,93,95,100,106,111,112]
for i in range(1,114):
#    if i in undone: continue
    run = 1;
    if i==14: run =2
    if i==41: run =2
    if i==60: run =2
    os.system('stager_get -M /castor/cern.ch/user/c/cerati/Tmp/ntuple_conversion_minbias7TeV_'+str(i)+'_'+str(run)+'.root')
    os.system('stager_get -M /castor/cern.ch/user/c/cerati/Tmp/ntuple_conversion_minbias7TeV_hit_'+str(i)+'_'+str(run)+'.root')
    os.system('stager_get -M /castor/cern.ch/user/c/cerati/Tmp/ntuple_nuclint_minbias7TeV_'+str(i)+'_'+str(run)+'.root')
    pippo = pippo+' rfio:/castor/cern.ch/user/c/cerati/Tmp/ntuple_conversion_minbias7TeV_'+str(i)+'_'+str(run)+'.root'
    pippo1 = pippo1+' rfio:/castor/cern.ch/user/c/cerati/Tmp/ntuple_conversion_minbias7TeV_hit_'+str(i)+'_'+str(run)+'.root'
    pippo2 = pippo2+' rfio:/castor/cern.ch/user/c/cerati/Tmp/ntuple_nuclint_minbias7TeV_'+str(i)+'_'+str(run)+'.root'
#print pippo
os.system(pippo)
os.system(pippo1)
os.system(pippo2)
os.system('rfcp /tmp/cerati/ntuple_conversion_CMSSW356_minbias7TeV.root $CASTOR_HOME/MaterialNtuples/ntuple_conversion_CMSSW356_minbias7TeV_2010-05-10.root')
os.system('rfcp /tmp/cerati/ntuple_conversion_CMSSW356_minbias7TeV_hit.root $CASTOR_HOME/MaterialNtuples/ntuple_conversion_CMSSW356_minbias7TeV_hit_2010-05-10.root')
os.system('rfcp /tmp/cerati/ntuple_nuclint_CMSSW356_minbias7TeV.root $CASTOR_HOME/MaterialNtuples/ntuple_nuclint_CMSSW356_minbias7TeV_2010-05-10.root')
#os.system('rm /tmp/cerati/*.root')
#for i in range(1,204):
#    os.system('rfrm /castor/cern.ch/cms/store/caf/user/cerati/ntuple_conversion_CMSSW336p3_minbias900GeV_'+str(i)+'.root')
