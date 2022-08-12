

#ifndef SYMBOL_H /*!!!!!!!!!!!!!*/
#define SYMBOL_H /*!!!!!!!!!!!!!*/
#include "global.h"

typedef struct Symbol
{
    char *name;
    long address;
    bool is_Code;
    bool is_Data;
    bool is_Entry;
    bool is_Extern;
    void *data;
    char **binarydata;
    struct Symbol *next;
} Symbol;

Symbol *head;

/**
 * 
 * @param 
 * return:
 * pointer to newly created Symbol
 */

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
bool add_symbol(char* line, char* label, bool is_Code, bool is_Data, bool is_Entry, bool is_Extern);


/**
 * Print the symbol list
 * 
 */
void print_symbol(Symbol *head);


/**
 * @brief 
 * 
 * @param line Trimmed line after command, data, struct or string.
 * @return int length of the command
 */
int check_length(char * line);

#endif