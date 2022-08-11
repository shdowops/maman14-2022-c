
#include "symbolTable.h"


bool add_value(SymbolTable *symbol_table, void *data)
{
    return add_value_linked(symbol_table->linked_list, data);
}

void delete_Symbol_Table(SymbolTable *symbol_table)
{
    delete_linked_list(symbol_table->linked_list);
    free(symbol_table);
}

SymbolTable *create_symbol_table()
{
    SymbolTable *resTable = malloc(sizeof(SymbolTable));
    LinkedList *result = malloc(sizeof(LinkedList));
    resTable->linked_list=result;
    result->size = 0;
    return resTable;
}