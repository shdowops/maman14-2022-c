CC=gcc
CFLAGS=-Wall -ansi -pedantic
TARGET=assembler

assembler: main.c main.h
	$(CC) $(CFLAGS) main.c -o $(TARGET)

clean:
	rm $(TARGET)
