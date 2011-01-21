CC = g++
CFLAGS = -c -Wall
SOURCES = main.cpp Graph.h Board.h Token.h Solver.h
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = fore-and-aft

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE)
