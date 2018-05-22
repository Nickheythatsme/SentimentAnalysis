#Nicholas Grout
.PHONY: clean
CC=g++
CFLAGS= -pthread -std=c++14
 
OBJS= main.o
TARGET= queue

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $^ $(CFLAGS) -o $@

main.o: main.cpp worker.h worker.cpp queue.h queue.cpp
	$(CC) $< $(CFLAGS) -c -o $@


clean:
	rm -f *.o $(TARGET)
