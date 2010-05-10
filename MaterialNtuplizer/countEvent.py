import os
#os.system('grep passed DATADec19/res/CMSSW_*.stdout >& nEvtData.log')
#file = open('nEvtData.log','r')
os.system('grep passed MC/res/CMSSW_*.stdout >& nEvtMC.log')
file = open('nEvtMC.log','r')
tot=0;
pas=0;
rej=0;
for line in file.readlines():
    #print line
    words = line.split()
    #print words
    tot=tot+int(words[4])
    pas=pas+int(words[7])
    rej=rej+int(words[10])
print "total="+str(tot)
print "passed="+str(pas)
print "rejected="+str(rej)
print "efficiency="+str(float(pas)/float(tot))
