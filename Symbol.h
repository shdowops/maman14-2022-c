

#ifndef SYMBOL_H /*!!!!!!!!!!!!!*/
#define SYMBOL_H /*!!!!!!!!!!!!!*/
#include <symbolTable.h>

typedef struct Symbol
{
    char *name;
    LinkedList *comm;
    char[4] address;   
} Symbol;


/**
 * The Method creates a new symbol based on the params that it recieves.
 * Input
 * @ic: the instruction count which will become the address of the Symbol
 * @name: the name of the Symbol
 * return:
 * pointer to newly created Symbol
 */
Symbol *create_symbol(int ic, char *name);

/**
 * deletes a given symbol
 *input:
 *  @sym: the SYmbol that needs to be deleted
 *  @sym_table: symbol list to which the symbol will be added
 */
void delete_symbol(Symbol *sym, SymbolTable *sym_table);

/**
 * adds a command
 * params:
 *  @symbol: The target symbol
 *  @data: The data to insert
 */
bool add_command(Symbol *symbol, void *data);

/**Searches if the data already exists in the symbol*/
Symbol *search_symbol( SymbolTable *symbol_table, char *name, IsEqual is_equal);
#endif



/**The method return the address of the Symbol
 * input params:
 * @sym: the symbol of which the address is needed
 * output:
 * The required address
*/
char *get_sym_address(Symbol *sym);