#include "symbol.h"

extern long IC, DC;

bool add_symbol(char *line, char *label, bool is_Code, bool is_Data, bool is_Entry, bool is_Extern)
{
    extern Symbol *head, *tail;
    Symbol *symNew = (Symbol *)malloc(sizeof(Symbol));
    Symbol *temp = head;
    char *labelname = (char *)malloc(sizeof(label));
    char *data = (char *)malloc(sizeof(line));
    strcpy(labelname, label);
    strcpy(data,line);
    if (!symNew || !labelname)
    {
        printf("Unable to allocate memory\n");
        return false;
    }
    symNew->name = labelname;
    symNew->is_Code = is_Code;
    symNew->is_Data = is_Data;
    symNew->is_Entry = is_Entry;
    symNew->is_Extern = is_Extern;
    symNew->data = data;
    symNew->next = NULL;

    if(is_Data)
    {
        symNew->address=DC;
        DC++;
    }
    else if(is_Code)
    {
        symNew->address=IC;
        IC++;
    }
    else
    {
        symNew->address=0;
    }
    

    if (head == NULL)
    {
        head = symNew;
        tail = symNew;
        return true;
    }

    while (temp != NULL)
    {
        if (strcmp(temp->name, symNew->name) == 0 && !is_Extern && !labelname)
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
        printf("data: %s ",head->data);
        printf("\n");
        head = head->next;
    }
}

int check_length(char *line)
{
    int length = 0;
    char *token = trim(strtok(NULL, ARGUMENT_SEPARATOR));
    while (token != NULL)
    {
        length++;
        token = trim(strtok(NULL, ARGUMENT_SEPARATOR));
    }

    return length;
}
