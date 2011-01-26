CC = g++
CFLAGS = -c -Wall
SOURCES = AllTests.cpp BoardTests.cpp SolverTests.cpp

OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = fore-and-aft-tests

CPPUTEST_HOME = ../lib/CppUTest
CPPFLAGS = -I$(CPPUTEST_HOME)/include
LD_LIBRARIES = $(CPPUTEST_HOME)/lib/libCppUTest.a

all: $(INCLUDE) $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LD_LIBRARIES)

.cpp.o:
	$(CC) $(CFLAGS) $(CPPFLAGS) $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE)

