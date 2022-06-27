CC = g++
CFLAGS = -O3 -Wall -g -pthread

SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

.PHONY: all clean

all: snake 

snake: $(OBJECTS)
	$(CC) $^ $(CFLAGS) -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) snake $(OBJECTS)
