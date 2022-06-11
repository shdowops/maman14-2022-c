CC=gcc
CFLAGS=-Wall -ansi -pedantic
TARGET=assembler
AMFILES=$(wildcard *.am)

assembler: main.c main.h preprocessor.c preprocessor.h linkedList.c linkedList.h
	$(CC) $(CFLAGS) main.c main.h preprocessor.c preprocessor.h linkedList.c linkedList.h -o $(TARGET)

clean:
	rm $(TARGET) $(AMFILES)
