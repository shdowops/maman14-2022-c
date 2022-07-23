#include "Symbol.h"
typedef struct CommandDeclaration
{
	int opcode;
	int source;
	int destination;
	char command_type;
	char *command_name;
	char *data;
	int value;
} CommandDeclaration;

CommandDeclaration commands[] = {
	{0, 1, 0, 'R', "mov", "", 0},
	{1, 2, 0, 'R', "cmp", "", 0},
	{2, 3, 0, 'R', "add", "", 0},
	{3, 4, 0, 'R', "sub", "", 0},
	{4, -1, 0, 'I', "not", "", 0},
	{5, 5, 0, 'R', "clr", "", 0},
	{6, 1, 0, 'R', "lea", "", 0},
	{7, -1, 0, 'I', "inc", "", 0},
	{8, 2, 0, 'R', "dec", "", 0},
	{9, 3, 0, 'R', "jmp", "", 0},
	{10, -1, 0, 'I', "bne", "", 0},
	{11, -1, 0, 'I', "get", "", 0},
	{12, -1, 0, 'I', "prn", "", 0},
	{13, -1, 0, 'I', "jsr", "", 0},
	{14, -1, 0, 'I', "rts", "", 0},
	{15, -1, 0, 'I', "hlt", "", 0}};

Symbol *create_CommandR(CommandDeclaration *str, int tyP, int val1)
{
	Symbol *result = (Symbol *)malloc(sizeof(Symbol));
	result->name = str;
	result->command = tyP;
	result->value = val1;
	return result;
}