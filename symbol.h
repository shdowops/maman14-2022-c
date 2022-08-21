
#ifndef SYMBOL_H
#define SYMBOL_H

#include "global.h"

/*Defining a structure Symbol to handle the input of the file and to sort the types*/
typedef struct Symbol
{
    char *name;
    long address;
    bool is_Code;
    bool is_Data;
    bool is_Entry;
    bool is_Extern;
    char *data;
    char *binarydata;
    struct Symbol *next;
} Symbol;

Symbol *head, *tail;

/**
 * @brief The Method creates a new symbol based on the params that it recieves.
 *
 * @param head The beginning of the list
 * @param line The line to examine
 * @param IC  The current instruction count
 * @param is_Code True if it is command false otherwise
 * @param is_Data True if it is data alse otherwise
 * @param is_Entry True if it is extern false otherwise
 * @param is_Label True if line starts with a label
 * @return true if symbol succesfully added to the table.
 * @return false when an error occured.
 */
bool add_symbol(char *line, char *label, bool is_Code, bool is_Data, bool is_Entry, bool is_Extern);

/**
 * @brief Finds a symbol by address
 *
 * @param head - The beginning of the list
 * @param address - The starting address of the symbol.
 * @return Symbol* if found otherwise NULL.
 */
Symbol *findsymbol(Symbol *head, long address);

/**
 * @brief Finds a symbol by name
 *
 * @param head - The beginning of the list
 * @param name - The symbol to find
 * @return Symbol* if found otherwise NULL.
 */
Symbol *findname(Symbol *head, char *name);

/**
 * @brief Update symbol as entry
 *
 * @param head - The beginning of the list
 * @param name - The name of the symbol
 */
void update_entry_symbol(Symbol *head, char *name);

/**
 * @brief free symbols
 *
 * @param head - The beginning of the list
 */
void freeSymbols(Symbol *head);

#endif