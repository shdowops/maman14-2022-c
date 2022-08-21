#include "symbol.h"

extern long IC, DC;

bool add_symbol(char *line, char *label, bool is_Code, bool is_Data, bool is_Entry, bool is_Extern)
{
    extern Symbol *head, *tail;
    Symbol *symNew = (Symbol *)malloc(sizeof(Symbol));
    Symbol *temp = head;
    char *labelname = (char *)malloc(strlen(label));
    char *data = (char *)malloc(strlen(line));
    strcpy(labelname, label);
    strcpy(data, line);
    if (!symNew || !labelname)
    {
        alertFileError(ER_MEMORY_ALLOCATION);
        return false;
    }
    symNew->name = labelname;
    symNew->is_Code = is_Code;
    symNew->is_Data = is_Data;
    symNew->is_Entry = is_Entry;
    symNew->is_Extern = is_Extern;
    symNew->data = data;
    symNew->next = NULL;

    /*Updating the address*/
    if (is_Data)
    {
        symNew->address = DC;
    }
    else if (is_Code)
    {
        symNew->address = IC;
        IC++;
    }
    else if (is_Entry || is_Extern)
    {
        symNew->address = -1;
    }
    else
    {
        symNew->address = IC;
        IC++;
    }

    if (head == NULL) /*First symbol in the list*/
    {
        head = symNew;
        tail = symNew;
        return true;
    }

    /*Searcing for location to add the new symbol*/
    while (temp != NULL)
    {
        if (strcmp(temp->name, symNew->name) == 0 && !is_Extern && strlen(labelname))
        {
            alertError(ER_LABEL_ALREADY_EXISTS);
            return false;
        }
        temp = temp->next;
    }
    /*Symbol not found, add to list */
    tail->next = symNew;
    tail = tail->next;
    return true;
}

Symbol *findsymbol(Symbol *head, long address)
{
    while (head != NULL)
    {
        if (head->address == address)
            return head;
        head = head->next;
    }
    return NULL;
}

Symbol *findname(Symbol *head, char *name)
{
    while (head != NULL)
    {
        if (strcmp(head->name, name) == 0)
            return head;
        head = head->next;
    }
    return NULL;
}

void update_entry_symbol(Symbol *head, char *text)
{
    while (head != NULL)
    {
        if (strcmp(head->name, text) == 0)
        {
            head->is_Entry = true;
            return;
        }
        head = head->next;
    }
}

void print_symbol(Symbol *head)
{
    while (head != NULL)
    {
        printf("name: %s ", head->name);
        printf("address: %ld ", head->address);
        printf("code: %d ", head->is_Code);
        printf("is_data: %d ", head->is_Data);
        printf("is_entry: %d ", head->is_Entry);
        printf("is_extern: %d ", head->is_Extern);
        printf("data: %s ", head->data);
        printf("binarydate: %s ", head->binarydata);
        printf("\n");
        head = head->next;
    }
}
