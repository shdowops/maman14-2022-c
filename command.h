
#include <Symbol.h>




typedef struct CommandDeclaration
{
	char *opcode;
	char *source;
	char *destination;
	char *command_type; 
	char *name_trans;
	char *data;
} CommandDeclaration;

CommandDeclaration commands[] = {
	/*
	A=
	R=
	E=
	*/
	{0, 1, "00", "mov","",0},
	{1, 2, 'R', "cmp","",0},
	{2, 3, 'R', "add","",0},
	{3, 4, 'R', "sub","",0},
	{4, -1, 'I', "not","",0},
	{5, 5, 'R', "clr","",0},
	{6, 1, 'R', "lea","",0},
	{7, -1, 'I', "inc","",0},
	{8, 2, 'R', "dec","",0},
	{9, 3, 'R', "jmp","",0},
	{10, -1, 'I', "bne","",0},
	{11, -1, 'I', "get","",0},
	{12, -1, 'I', "prn","",0},
	{13, -1, 'I', "jsr","",0},
	{14, -1, 'I', "rts","",0},
	{15, -1, 'I', "hlt","",0}
	
CommandDeclaration *create_declare(char *str);

Node create_Command(Symbol sym, char *str);