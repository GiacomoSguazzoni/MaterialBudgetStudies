import commands
import os

dir = "MCtmp"
os.system("mkdir /tmp/cerati/"+dir)
tmp = commands.getoutput("nsls Tmp/"+dir)
tmp2 = tmp.split()
for i in tmp2:
    os.system("stager_get -M $CASTOR_HOME/Tmp/"+dir+"/"+i)
for i in tmp2:
    os.system("rfcp $CASTOR_HOME/Tmp/"+dir+"/"+i+" /tmp/cerati/"+dir)
#os.system("hadd conv.root /tmp/cerati/*conv*.root")
#os.system("hadd nucl.root /tmp/cerati/*nucl*.root")
