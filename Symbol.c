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

bool add_Name(Symbol *sym, char *name)
{
    sym->name=name;
    return 1;
}

int delete_Symbol(Symbol *sym, SymbolTable symTable)
{
    return deleteNode(symTable->linked_list, sym);
    
}

Symbol *create_Symbol(SymbolTable *symbol_table, int ic)
{
    /*

    convert IC to binary

    Symbol->ic= result of binary transformation.
    
    
    */
    Symbol *symNew = malloc(sizeof(Symbol));
    return add_value(symbol_table, symNew);
    return 1;
}

void add_Command(Symbol *symbol, void *data)
{
    add_value(symbol->comm,data);
}




/**The method return the address of the Symbol
 * input param:
 * @Symbol *sym: the symbol of which the address is needed
 * output:
 * The required address
*/
char *get_sym_address(Symbol *sym)
{
    return sym->address;

}