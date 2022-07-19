
#include "symbolTable.h"
void *search_symbol_table(SymbolTable *symbol_table, void *data, IsEqual is_equal)
{

    int i;
    struct linked_list = symbol_table->linkedList;
    return search_linked_list(linked_list, data, is_equal);
}

bool add_value(SymbolTable *symbol_table, void *data)
{
    return add_value(symbol_table->linked_list, data);
}

void delete_Symbol_Table(SymbolTable *symbol_table)
{
    delete_linked_list(symbol_table->linked_list);
    free(symbol_table);
}

LinkedList *create_symbol_table()
{
    SymbolTable *resTable = malloc(sizeof(SymbolTable));
    LinkedList *result = malloc(sizeof(LinkedList));
    resTable->linked_list=result;
    result->size = 0;
    return resTable;
}