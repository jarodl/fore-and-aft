CC = g++
CFLAGS = -c -Wall
SOURCES = src/*
INCLUDE = include/*

OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = fore-and-aft

all: $(INCLUDE) $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE)
