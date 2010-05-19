import commands
import os

dir = "GoodCollSkim2"
os.system("mkdir /tmp/cerati/"+dir)
tmp = commands.getoutput("nsls Tmp/"+dir)
tmp2 = tmp.split()
for i in tmp2:
    os.system("stager_get -M $CASTOR_HOME/Tmp/"+dir+"/"+i)
for i in tmp2:
    os.system("rfcp $CASTOR_HOME/Tmp/"+dir+"/"+i+" /tmp/cerati/"+dir)
