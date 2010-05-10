import os
pippo  = 'hadd /tmp/cerati/ntuple_conversion_CMSSW356_goodcoll7TeV.root '
pippo2 = 'hadd /tmp/cerati/ntuple_nuclint_CMSSW356_goodcoll7TeV.root '
pippo = pippo+' /tmp/cerati/tmp/ntuple_conversion_goodcoll7TeV_*_1.root'
pippo2 = pippo2+' /tmp/cerati/tmp/ntuple_nuclint_goodcoll7TeV_*_1.root'
os.system(pippo)
os.system(pippo2)
os.system('rfcp /tmp/cerati/ntuple_conversion_CMSSW356_goodcoll7TeV.root $CASTOR_HOME/MaterialNtuples/ntuple_conversion_CMSSW356_goodcoll7TeV_2010-05-03.root')
os.system('rfcp /tmp/cerati/ntuple_nuclint_CMSSW356_goodcoll7TeV.root $CASTOR_HOME/MaterialNtuples/ntuple_nuclint_CMSSW356_goodcoll7TeV_2010-05-03.root')
