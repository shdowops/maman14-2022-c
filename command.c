#include "command.h"

/*
    The function recieves a string which is the name of  the command,
    and creates a copy of that command type and returns it.
    Input params:
 *  @str: string which is the name of  the command
*/
CommandDeclaration *create_declare(char *str)
{
    int i; /*creating counter for loop*/
    CommandDeclaration *comm_dec; /*command declartion that will be returned*/
    i = 0;/*initializing counter*/

    /* loop to locate from our array 'commands' that has the list of all
    the types of commands. We will make a copy of the proper command type    */
    for(i;i<=14;i++)
    {
        /*finding the exact name of the command in the array.
            then making a copy fo the proper paramaters for the newly created command declaration.
            Return the new command declaration
        */
        if(commands[i][3])
            {
                /*Copying the proper params of the command type*/
                strcpy(comm_dec->opcode,commands[i][0]);
                strcpy(comm_dec->source,commands[i][1]);
	            strcpy(comm_dec->destination,commands[i][2]);
        	    strcpy(comm_dec->command_name,commands[i][3]);
        	    strcpy(comm_dec->are,commands[i][4]);
                /*returning the copied version of the command type*/
                return comm_dec;

            }
        
        

    }
    /*If the command type wasn't found, we will reach thiswe will make an alert */
    fprintf(stderr, "\n Error: command %s is not a command according to requirements. \n",str);
    /*return the null command declaration*/
	return NULL;
}





/*
    The method recieves a Symbol, to which the command will be added, 
    and a string representing the type of command.
    The method creates a new command-declaration based on the specific command type.
    The method adds the new command-delaration to the proper Symbol.
    Input params:
 *@*sym:  the Symbol to which the command will be added
 *@str: string which is the name of  the command

*/
 void  create_command(Symbol *sym, char *str)
{
	/*intialize a new command-declaration*/
	 CommandDeclaration *comm_dec = malloc(sizeof(CommandDeclaration));
     /*make a copy of the proper command declaration*/
     comm_dec= create_declare(str);
     /*add the new command declaraion to the proper symbol*/
	add_Command(sym, comm_decla);
	return 1;

}

/*
    The method recieves a string that represents the address of the source of data
    for the command-declaration. The method makes a copy of that address and then
    places it in the proper address location in the commaned-declartion structure 
    Input params:
 *@ char *src:  the string representing the address of the source to be placed in the command-declaration
 *@ CommandDeclaration *comm_decs: the command-declaration to which the address will be added

*/
void add_src(char *src,  CommandDeclaration *comm_dec )
{
    strcpy(comm_dec->source,src);
    return 1;

}


/*
    The method recieves a string that represents the address of the destination of data
    for the command-declaration. The method makes a copy of that address and then
    places it in the proper address location in the commaned-declartion structure .
    Input params:

 *@ char *dest:  the string representing the address of the destination to be placed in the command-declaration
 *@ CommandDeclaration *comm_dec: the command-declaration to which the address will be added

*/
void add_dest(char *dest,  CommandDeclaration *comm_dec )
{
    strcpy(comm_dec->source,dest);
    return 1;

}

/*
    The method recieves a command, a source Symbol and adestination Symbol.
    The method locates the address of each symbol and inserts them into the
    proper locations within the command-declaration.
    Input params:
 *@ SymbolTable sym_tab: the symbol table from where we will find the symbols.
 *@ CommandDeclaration *comm_dec: the command-declaration to which the addresses will be added
 *@ char *src:  the string representing the Symbol of who's address is the source to be placed in the command-declaration
 *@ char *dest:  the string representing the Symbol of who's address is the destination to be placed in the command-declaration
 
*/
void add_command_values(SymbolTable *sym_tab, CommandDeclaration *comm_dec, char *src, char *dest)
{
    /*
        Checking Symbol is not of type 3. Type 3 reuqires no source or destination address
    */
    if(comm_dec->typ!=3)
    {
        /*
            Initializing the destination Symbol
            since both type of commands (1 and 2) reuqire a destination address
        
        */
        Symbol *sym_dest;
        /*creating an is equal pointer*/
        IsEqual *is_equal=NULL;
        
        /*Locating the source Symbol*/
        Symbol *sym_dest = search_symbol(sym_tab, dest, is_equal);
        add_src(get_sym_address(Symbol),  CommandDeclaration *comm_dec );

            if(comm_dec->typ!=3)
             
             {
                /*
                Initializing the source Symbol
                 since command type 1 reuqires a source address
                  */
                Symbol *sym_src;
                is_equal=NULL;
                /*Locating the source Symbol*/
                Symbol *sym_src = search_symbol(sym_tab, src, is_equal);
                sym_src=add_src(get_sym_address(Symbol),  CommandDeclaration *comm_dec )
             }

    }

}
