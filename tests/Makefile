CC = g++
CFLAGS = -c -Wall -g3
SOURCES = AllTests.cpp SolverTests.cpp BoardTests.cpp GraphTests.cpp

OBJECTS = $(SOURCES:.cpp=.o)
OBJECTS_DIR = $(addprefix objs/, $(OBJECTS))
EXECUTABLE = fore-and-aft-tests

INCLUDE = ../include

CPPUTEST_HOME = ../lib/CppUTest
CPPFLAGS = -I$(CPPUTEST_HOME)/include -I$(INCLUDE)
LD_LIBRARIES = $(CPPUTEST_HOME)/lib/libCppUTest.a

all: $(INCLUDE) $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS_DIR) -o $@ $(LD_LIBRARIES)

.cpp.o:
	$(CC) $(CFLAGS) $(CPPFLAGS) $< -o objs/$@

clean:
	rm -rf *.o $(EXECUTABLE)

