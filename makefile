CC = g++
OPTFLAGS = -O3 -pthread -fno-strict-aliasing -D_GNU_SOURCE
COPTIONS = -DLINUX -D_FILE_OFFSET_BITS=64 -std=c++11 -Wall\
           -Wno-unused-function -Wno-unused-label -Wno-unused-variable\
           -Wno-parentheses -Wsequence-point

#Standard Libraries
STDLIBS = -lm

CFLAGS = $(COPTIONS)  $(OPTFLAGS)
LIBS = $(STDLIBS)

SOURCE = main.cc cube.cc
EXE = Cube

default:
	$(CC) $(CFLAGS) $(SOURCE) $(LIBS) -o $(EXE)
