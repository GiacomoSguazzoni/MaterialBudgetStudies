#!/usr/bin/env python

import os, sys

from optparse import OptionParser
parser = OptionParser(usage="usage: %prog crabdir")
#parser.add_option("-o", "--opt", var1="value1", var2="value2")

(options, args) = parser.parse_args()
if len(args) != 1: 
    parser.print_usage()
    sys.exit(2)
    
def countevts(dir):
    os.system('grep passed '+str(dir)+'/res/CMSSW_*.stdout >& nEvt.log')
    file = open('nEvt.log','r')
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
    os.system('rm nEvt.log')

countevts(args[0])
