

#ifndef SYMBOL_H /*!!!!!!!!!!!!!*/
#define SYMBOL_H /*!!!!!!!!!!!!!*/
#include <stdio.h>
#include <stdlib.h>
#include <linkedList.h>
#include <symbolTable.h>
typedef bool *IsEqual(void *data, void *parameter);

typedef struct Symbol
{
    char *name;
    LinkedList *comm;
} Symbol;


/**
 * Creates a new symbol
 */
Symbol *create_symbol();

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


bool add_value(Symbol *symbol, void *data);

/**Searches if the data already exists in the symbol*/
void *search_symbol(SymbolTable *symbol_table, Symbol *symbol, char *name, IsEqual is_equal);
#endif
