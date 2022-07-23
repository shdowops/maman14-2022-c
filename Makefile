CC=gcc
CFLAGS=-Wall -ansi -pedantic
TARGET=assembler
AMFILES=$(wildcard *.am)

assembler: main.c main.h preprocessor.c preprocessor.h linkedList.c linkedList.h firstpass.c firstpass.h secondpass.c secondpass.h global.h global.c
	$(CC) $(CFLAGS) main.c main.h preprocessor.c preprocessor.h linkedList.c linkedList.h firstpass.c firstpass.h secondpass.c secondpass.h global.h global.c -o $(TARGET)

clean:
	rm $(TARGET) $(AMFILES)
