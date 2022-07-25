

#ifndef SYMBOL_H /*!!!!!!!!!!!!!*/
#define SYMBOL_H /*!!!!!!!!!!!!!*/
#include <symbolTable.h>
typedef bool *IsEqual(void *data, void *parameter);

typedef struct Symbol
{
    char *name;
    LinkedList *comm;
    char[4] address;   
} Symbol;


/**
 * Creates a new symbol
 */
Symbol *create_symbol(int ic);

/**
 * deletes a given symbol
 *
 */
void delete_symbol(Symbol *sym, SymbolTable symTable);

/**
 * adds a symbol
 * params:
 *  @symbol: The target symbol
 *  @data: The data to insert
 */


bool add_Command(Symbol *symbol, void *data);

/**Searches if the data already exists in the symbol*/
Symbol *search_symbol( SymbolTable *symbol_table, char *name, IsEqual is_equal);
#endif



/**The method return the address of the Symbol
 * input param:
 * @Symbol *sym: the symbol of which the address is needed
 * output:
 * The required address
*/
char *get_sym_address(Symbol *sym);