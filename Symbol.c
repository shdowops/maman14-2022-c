#include "Symbol.h"
void *search_symbol( SymbolTable *symbol_table, char *name, IsEqual is_equal);
{

    int i;
    struct Symbol *current = symbol_table->linked_list->start->data;
    for (i = 0; i < linked_list->size; i++)
    {
        if (is_equal(current->data, sym))
            return current->data;
    }
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
 * Not FInished!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 * The Method creates a new symbol based on the params that it recieves.
 * Input
 * @ic: the instruction count which will become the address of the Symbol
 * @name: the name of the Symbol
 * return:
 * pointer to newly created Symbol
 */
Symbol *create_symbol(int ic, char *name)
{


    
    Symbol *symNew = malloc(sizeof(Symbol));
    /*

    convert IC to binary !!!! We need to crate method of transform in to binary!!!!!!!!!!!!!!!!!!!!!!!!!!!

    Symbol->ic= result of binary transformation;
    
    
    */
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

