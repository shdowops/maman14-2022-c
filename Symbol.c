#include "Symbol.h"




/** 
The method finds a Symbol and returns it. If it cannot locate it, it returns NULL
input param:
@symbol_table: The list of symbols where we are performing the search.
@name: the string representing the symbol name we are searching for 
returns:
@current->data: representing the symbol that we were searching for in the event we found it
@NULL: if we did not find it 
*/
void *search_symbol( SymbolTable *symbol_table, char *name);
{

    /*Initializing variable for loop*/
    int i;
    /*Creating a symbol so we can check all the symbols in the list*/
    struct Symbol *current = symbol_table->linked_list->start->data;
    /*for loop for the search*/
    for (i = 0; i < linked_list->size; i++)
    {
        /*Comparing if the names of the symbol match*/
        if (strcmp(current->data->name,name)=0)
            /*if we found the symbol, returns the symbol*/
            return current->data;
    }
    /*In the event that we did not find the symbol it returns null*/
    return NULL;
}



/**
 * deletes a given symbol
 *input:
 *  @sym: the SYmbol that needs to be deleted
 *  @sym_table: symbol list to which the symbol will be added
 */
void delete_symbol(Symbol *sym, SymbolTable *sym_table);
{
    return deleteNode(symTable->linked_list, sym);
    
}

/**
 *
 * The Method creates a new symbol based on the params that it recieves.
 * Input
 * @ic: the instruction count which will become the address of the Symbol
 * @name: the name of the Symbol
 * return:
 * pointer to newly created Symbol
 */
Symbol *create_symbol(int ic, char *name)
{


    /*Creating the new Symbol*/

    Symbol *symNew = malloc(sizeof(Symbol));
    /*Converting the instruction count to a binary number*/
    char[32] binNum=convert_decimal_Binary(ic);
    /*Converting the long address to small address*/
    symNew->ic= chop_string_for_address(binNum);
   /*copy the label name into the Symbol Name*/
    strcpy(sym->name,name);
    /*adding the Symbol to it's list*/
    return add_value(symbol_table, symNew);
    return 1;
}


/**
 * adds a command
 * params:
 *  @symbol: The target symbol
 *  @data: The data to insert
 */
{
    add_value(symbol->comm,data);
}




/**The method returns the address of the Symbol
 * input params:
 * @sym: the symbol of which the address is needed
 * output:
 * The required address
*/
char *get_sym_address(Symbol *sym)
{
    return sym->address;

}

