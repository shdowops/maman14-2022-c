#include "command.h"


CommandDeclaration *create_declare(char *str)
{
    int i;
    i = 0;
    CommandDeclaration *comm_decla = malloc(sizeof(CommandDeclaration));
    /*
    make loop to find proper data to insert to node
		make the array that is called data*/
	

    for(i;i<=14;i++)
    {
        /*finding the exact name of the command in the array*/
        if(commands[i][3])
            break;
        /*else alert there is a problem*/

    }


	

comm_decla-> opcode=commands[i][0];
comm_decla->source=commands[i][1];
comm_decla->destination=commands[i][2];
comm_decla->command_type=commands[i][3];
comm_decla->name_trans=commands[i][4];
comm_decla->data=commands[i][5];

}


    Node create_command(Symbol *sym, char *str)
{
	
	 CommandDeclaration *comm_decla = malloc(sizeof(CommandDeclaration));
     comm_decla= create_declare(str);
	add_Command(sym, comm_decla);
	

}