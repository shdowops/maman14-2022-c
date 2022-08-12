CC=gcc
CFLAGS=-Wall -ansi -pedantic
TARGET=assembler
AMFILES=$(wildcard *.am)

assembler: main.c main.h preprocessor.c preprocessor.h firstpass.c firstpass.h secondpass.c secondpass.h global.h global.c error_handling.h error_handling.c symbol.c symbol.h
	$(CC) $(CFLAGS) main.c main.h preprocessor.c preprocessor.h firstpass.c firstpass.h secondpass.c secondpass.h global.h global.c error_handling.h error_handling.c symbol.c symbol.h -o $(TARGET)

clean:
	rm $(TARGET) $(AMFILES)
