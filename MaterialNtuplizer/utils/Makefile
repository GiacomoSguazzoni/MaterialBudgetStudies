CC          = g++
CCFLAGS     = -g -Wall -m64 -O3
#SOURCEDIR   =
#INCDIR      =
#SOURCES     =
#INCFLAGS    = -I $(INCDIR)
ROOTFLAGS   = `root-config --cflags --glibs` -lMinuit

all: $(SOURCEDIR) $(INCDIR) QueryMatNtuple.cc
	$(CC) $(CCFLAGS) -o QueryMatNtuple $(ROOTFLAGS) $(INCFLAGS) $(SOURCES) QueryMatNtuple.cc

clean:
	rm -rf QueryMatNtuple QueryMatNtuple.dSYM
