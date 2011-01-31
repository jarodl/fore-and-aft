CC = g++
SOURCES = src/main.cpp
INCLUDE = include/
CFLAGS = -c -Wall -I$(INCLUDE) -g3

OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = fore-and-aft

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf src/*.o $(EXECUTABLE)
