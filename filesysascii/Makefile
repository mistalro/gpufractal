TARGET  = libfilesysascii.a

BASEDIR = ..

TEXLIB  = texlib
TEXDIR  = $(BASEDIR)/$(TEXLIB)

INCLUDEDIR = -I$(TEXDIR) 
LIBDIR     = -L$(TEXDIR) 
LIBFILES   = -l$(TEXLIB) 

CXXFLAGS     = $(INCLUDEDIR) $(LIBDIR) -g -Wall -std=c++11

CXX = g++
AR  = ar

HEADERS = \
	basefilesystem.h \
	tokenentry.h \
	virtualfsascii.h \
	io_par.h \
	io_string.h \
	io_bool.h \
	io_boolarray.h \
	io_byte.h \
	io_bytearray.h \
	io_integer.h \
	io_intarray.h \
	io_short.h \
	io_shortarray.h \
	io_long.h \
	io_longarray.h \
	io_vec2i.h \
	io_vec3i.h \
	io_vec4i.h \
	io_float.h \
	io_floatarray.h \
	io_double.h \
	io_doublearray.h \
	io_vec2f.h \
	io_vec3f.h \
	io_vec4f.h \
	io_color3f.h \
	io_color4f.h \
	io_plane4f.h \
	fileiolib.h

SRC = \
	tokenentry.cpp \
	io_par.cpp \
	io_string.cpp \
	io_boolarray.cpp \
	io_bytearray.cpp \
	io_intarray.cpp \
	io_longarray.cpp \
	io_floatarray.cpp \
	io_doublearray.cpp \
	virtualfsascii.cpp \
	virtualfsglobal.cpp

OBJ = $(SRC:.cpp=.o)

# Automagically create set of file dependencies

# For recursive makefiles
#
# subsystem:
#        $(MAKE) -C subdir

all: $(OBJ) $(TARGET)

$(TARGET): $(OBJ)
	$(AR) -rv $(TARGET) $(OBJ)

clean1:
	$(RM) -f *.o *.out $(TARGET) core 

all1: $(TARGET)
