
/*Table to place all the labels so we can easily manage them built on linked list structure*/



#ifndef SYMBOL_TABLE_H /*!!!!!!!!!!!!!*/
#define SYMBOL_TABLE_H /*!!!!!!!!!!!!!*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <linkedList.h>


typedef struct SymbolTable;
{
    linkedList *linked_list;
} Node;


/**
 * Creates a Symbol Table
 */
symbolTable *create_symbol_table();

/**
 * deletes a given Symbol Table
 *
 */
void delete_Symbol_Table(SymbolTable *symbol_table);

/**
 * adds a new value to the Symbol Table
 * params:
 *  @symbol_table: The target Symbol Table
 *  @data: The data to insert
 */
bool add_value(SymbolTable *symbol_table, void *data);
