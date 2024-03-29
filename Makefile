CC=gcc
CFLAGS=-Wall -ansi -pedantic -lm
TARGET=assembler
AMFILES=$(wildcard *.am)
OBFILES=$(wildcard *.ob)
EXTFILES=$(wildcard *.ext)
ENTFILES=$(wildcard *.ent)

assembler: main.c main.h preprocessor.c preprocessor.h firstpass.c firstpass.h secondpass.c secondpass.h global.h global.c error_handling.h error_handling.c symbol.c symbol.h
	$(CC) $(CFLAGS) main.c main.h preprocessor.c preprocessor.h firstpass.c firstpass.h secondpass.c secondpass.h global.h global.c error_handling.h error_handling.c symbol.c symbol.h -o $(TARGET)

clean:
	rm -f $(TARGET) $(AMFILES) $(OBFILES) $(EXTFILES) $(ENTFILES)
