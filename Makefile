CC = g++
SOURCES = src/main.cpp
INCLUDE = include/
CFLAGS = -c -Wall -I$(INCLUDE)
#GLEW_INCLUDE = /opt/local/include
#GLEW_LIB = /opt/local/lib
#OPENGL = -framework GLUT -framework OpenGL -L$(GLEW_LIB) -lGLEW

OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = fore-and-aft

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ #$(OPENGL)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf src/*.o $(EXECUTABLE)
