TARGET  = texlib.a

TEXLIB=../texlib

INCLUDEDIR =  -I$(MATHSLIB) -I$(TEXLIB)
LIBDIR  =  -L$(MATHSLIB) -L$(TEXLIB)
LIBFILES   = -lGL -lGLU -lglut -lrt
LIBS = $(TEXLIB)/$(TEXLIB).a
CXXFLAGS     = $(INCLUDEDIR) $(LIBDIR) -g -Wall -std=c++11

CXX = g++
AR  = ar

HEADERS = \
	color3tp.h \
	colormap.h \
	fileutils.h \
	templatelist.h \
	texcolor.h \
	texedit.h \
	texlib.h \
	textga.h \
	textiff.h \
	texture.h \
	texturelib.h

SRC = \
	color4f.cpp \
	colormap.cpp \
	fileutils.cpp \
	texbmp.cpp \
	texedit.cpp \
	texfileio.cpp \
	texfiles.cpp \
	texflip.cpp \
	texmode.cpp \
	texprocess.cpp \
	texswap.cpp \
	textga.cpp \
	textiff.cpp \
	texture.cpp

OBJ = $(SRC:.cpp=.o)

# Automagically create set of file dependencies

# For recursive makefiles
#
# subsystem:
#        $(MAKE) -C subdir

all: $(OBJ) $(TARGET)

all1: $(OBJ) $(TARGET)

#%.o : %.cpp
#       g++ $(CXXFLAGS) -g $(<) -o $(@)

$(TARGET): $(OBJ) $(HEADERS)
	$(RM) -f $(TARGET)
	$(AR) cr $(TARGET) $(OBJ)
	ranlib $(TARGET) 

clean1:
	$(RM) -f *.o *.out $(TARGET) core 
