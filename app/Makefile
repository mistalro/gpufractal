TARGET=compute
BASE=..
TEXLIB=texlib
FILESYSCOMMON=filesyscommon
FILESYSASCII=filesysascii
INCLUDEDIR = -I../../mathslib -I$(BASE)/$(TEXLIB) -I$(BASE)/$(FILESYSCOMMON) -I$(BASE)/$(FILESYSASCII)
LIBDIR  =  -L$(BASE)/$(TEXLIB) -L$(BASE)/$(FILESYSASCII) -L$(BASE)/$(FILESYSCOMMON)
LIBFILES = -ldl -lGL -lGLU -lrt -lX11 -l$(FILESYSASCII) -l$(FILESYSCOMMON) -lpthread
LIBS= $(BASE)/$(TEXLIB)/$(TEXLIB).a 
CXXFLAGS     = $(INCLUDEDIR) $(LIBDIR) -g -Wall -std=c++11 
SUBDIRS = $(BASE)/$(TEXLIB) $(BASE)/$(FILESYSCOMMON) $(BASE)/$(FILESYSASCII)
CXX = g++
AR  = ar

HEADERS = \
	netnode.h \
	netnodeentryio.h \
	netnodeentrylistio.h \
	glx.h \
	computeformats.h \
	cputimer.h \
	fractparams.h \
	fractparamsio.h \
	fractparamslist.h \
	fractparamslistio.h \
	fractals.h \
	fractplayer.h \
	fractsystem.h \
	fractwindow.h

SRC = \
	netnode.cpp \
	netnodeentryio.cpp \
	netnodeentrylistio.cpp \
	fractnet.cpp \
	cputimer.cpp \
	glx.cpp \
	fractwindow.cpp \
	fractparams.cpp \
	fractparamsio.cpp \
	fractparamslistio.cpp \
	fractcompute.cpp \
	fractsystem.cpp \
	fractserver.cpp \
	fractclient.cpp \
	main.cpp 

OBJ = $(SRC:.cpp=.o)

# Automagically create set of file dependencies

# For recursive makefiles
#
# subsystem:
#        $(MAKE) -C subdir

#%.o : %.cpp
#       g++ $(CXXFLAGS) -g $(<) -o $(@)

$(TARGET): all link1

clean: $(SUBDIRS)
	for i in $(SUBDIRS); do (cd $${i}; $(MAKE) $@1); done; 
	rm $(OBJ) $(TARGET)

all:
	for i in $(SUBDIRS); do (cd $${i}; $(MAKE) $@1); done 

link1: $(OBJ) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ) $(LIBS) $(LIBFILES) $(LIBDIR)

clean1 :
	$(RM) -f *.o *.out $(TARGET) core 

.cpp.o:
	$(CC) $(CXXFLAGS) $< -c -o $@ 
