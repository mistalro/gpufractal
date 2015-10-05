TARGET   = libfilesyscommon.a

BASEDIR = ..

TEXLIB  = texlib
TEXDIR  = $(BASEDIR)/$(TEXLIB)

CXX =  g++
AR = ar

LIBDIR = -L../filesysascii \
	-L../filesysbinary \
	-L$(TEXDIR)

INCLUDEDIR = \
	-I../filesysascii \
	-I../filesysbinary \
	-I../filesyscommon \
	-I$(TEXDIR)

LIBFILES = \
	-lfilesysascii \
	-lfilesysbinary \
	-ltexlib
	
HEADERS	= \
	autoflow.h \
	fileentryio.h \
	fileentrylistio.h \

SRC = \
	filesysentryio.cpp \
	filesysentrylistio.cpp \
	filesysentrylist.cpp \
	filesystoken.cpp

CXXFLAGS = $(INCLUDEDIR) $(LIBDIR) -g

OBJ = $(SRC:.cpp=.o)

all: $(OBJ) $(TARGET)

all1: $(OBJ) $(TARGET)

$(OBJ) : $(SRC)

$(TARGET): $(OBJ)
	$(AR) -rv $(TARGET) $(OBJ)

clean1:
	$(RM) -f *.o *.out $(TARGET) core 
