CC = g++
CFLAGS = -O3 -Wall -g -pthread

SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

.PHONY: all clean memcheck

all: snake 

snake: $(OBJECTS)
	$(CC) $^ $(CFLAGS) -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) snake $(OBJECTS)

memcheck:
	valgrind --leak-check=full --track-origins=yes --log-file=valgrind-out.txt ./snake
	cat valgrind-out.txt
	rm valgrind-out.txt
