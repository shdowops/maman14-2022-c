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

    if (is_Data)
    {
        symNew->address = DC;
        DC++;
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
    else /* not data, not code, not entry and not extern ---> regular command*/
    {
        symNew->address = IC;
        IC++;
    }

    if (head == NULL)
    {
        head = symNew;
        tail = symNew;
        return true;
    }

    while (temp != NULL)
    {
        if (strcmp(temp->name, symNew->name) == 0 && !is_Extern && strlen(labelname))
        {
            alertError(ER_LABEL_ALREADY_EXISTS);
            return false;
        }
        temp = temp->next;
    }
    tail->next = symNew;
    tail = tail->next;
    return true;
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
        printf("binarydate: %s ",head->binarydata);
        printf("\n");
        head = head->next;
    }
}
