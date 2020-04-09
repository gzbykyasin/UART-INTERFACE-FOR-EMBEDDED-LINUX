CC = gcc
CFLAGS = -O2 -Wall

all: main
main: main.o uartInterface.o 
	$(CC) $(CFLAGS) -o main main.o uartInterface.o
main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp
uartInterface.o: uartInterface.cpp uartInterface.h
	$(CC) $(CFLAGS) -c uartInterface.cpp
clean:
	$(RM) *.o*~ main