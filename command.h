
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
	{0, 1, 'R', "mov","",0},
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
	

    Symbol *create_CommandR(CommandDeclaration *str, int tyP, int val1)
{
	Symbol result = malloc(sizeof(Symbol));
	result->name = str;
	result->type = tyP;
	result->value = val1;
	return result;
}