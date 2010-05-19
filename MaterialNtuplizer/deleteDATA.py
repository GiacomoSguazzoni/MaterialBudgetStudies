import os

#for i in range(1,102):
#os.system('rfrm /castor/cern.ch/cms/store/caf/user/cerati/ntuple_conversion_CMSSW358p3_data900GeV_Dec19th_'+str(i)+'.root')

#for i in range(1,204):
#        os.system('rfrm /castor/cern.ch/user/c/cerati/Tmp/ntuple_conversion_CMSSW358p3_minbias900GeV_'+str(i)+'_1.root')
        
for i in range(1,87):
    os.system('rfrm /castor/cern.ch/user/c/cerati/Tmp/ntuple_conversion_goodcoll7TeV_'+str(i)+'_1.root')
    os.system('rfrm /castor/cern.ch/user/c/cerati/Tmp/ntuple_nuclint_goodcoll7TeV_'+str(i)+'_1.root')


