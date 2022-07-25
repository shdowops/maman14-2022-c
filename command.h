#include "Symbol.h"

typedef struct CommandDeclaration
{
	/*Typ represents What command group is it 
   1{lea, sub, add, cmp, mov}
   2{not, clr, inc, dec, jmp, bne, get, prn, jsr}
   3{rts,hlt}
   
   */
   int typ; 
   
   char[5] opcode;
	char[3] source;
	char[3]destination;
	char[4] command_name;
	char[3] are;
} CommandDeclaration;

CommandDeclaration commands[] = {

/*0*/	{1,"0000", "", "", "mov","00"}
/*1*/	{1,"0001", "", "",  "cmp", "00"},
/*2*/	{1,"0010", "", "",  "add", "00"},
/*3*/	{1,"0011", "", "",  "sub", "00"},
/*4*/	{2,"0100", "00", "",  "not", "00"},
/*5*/	{2,"0101", "00", "",  "clr", "00"},
/*6*/	{1,"0110", "", "",  "lea", "00"},
/*7*/	{2,"0111", "00", "",  "inc", "00"},
/*8*/	{2,"1000", "00", "",  "dec", "00"},
/*9*/	{2,"1001", "00", "",  "jmp", "00"},
/*10*/	{2,"1010", "00", "",  "bne", "00"},
/*11*/	{2,"1011", "00", "",  "get", "00"},
/*12*/	{2,"1100", "00", "",  "prn", "00"},
/*13*/	{2,"1101", "00", "",  "jsr", "00"},
/*14*/	{3,"1110", "00", "00",  "rts", "00"},
/*15*/	{3,"1111", "00", "00",  "hlt", "00" };

}



/*
    The function recieves a string which is the name of  the command,
    and creates a copy of that command type and returns it.
    Input params:
 *  @str: string which is the name of  the command
*/
CommandDeclaration *create_declare(char *str)
{}


/*
    The method recieves a Symbol, to which the command will be added, 
    and a string representing the type of command.
    The method creates a new command-declaration based on the specific command type.
    The method adds the new command-delaration to the proper Symbol.
    Input params:
 *@*sym:  the Symbol to which the command will be added
 *@str: string which is the name of  the command

*/
   create_command(Symbol *sym, char *str)
   {}


   /*
    The method recieves a string that represents the address of the source of data
    for the command-declaration. The method makes a copy of that address and then
    places it in the address location in the commaned-declartion structure 
    Input params:
 *@ char *src:  the string representing the address of the source to be placed in the command-declaration
 *@ CommandDeclaration *comm_decs: the command-declaration to which the address will be added

*/
void add_src(char *src,  CommandDeclaration *comm_dec )
{}

/*
    The method recieves a string that represents the address of the destination of data
    for the command-declaration. The method makes a copy of that address and then
    places it in the proper address location in the commaned-declartion structure .
    Input params:
 *@ char *dest:  the string representing the address of the destination to be placed in the command-declaration
 *@ CommandDeclaration *comm_decs: the command-declaration to which the address will be added

*/
void add_dest(char *dest,  CommandDeclaration *comm_dec )
{
	Symbol *sym= malloc(sizeof(Symbol))
	search_symbol(Symbol *symbol, SymbolTable *symbol_table, char *name, IsEqual is_equal)
}
