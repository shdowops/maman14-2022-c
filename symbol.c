#include "symbol.h"

extern long IC, DC;

bool add_symbol(char *line, char *label, bool is_Code, bool is_Data, bool is_Entry, bool is_Extern)
{
    extern Symbol *head;
    Symbol *symNew = malloc(sizeof(Symbol));
    Symbol *temp = head;
    char *cpline = malloc(sizeof(line));
    strcpy(cpline, line);
    symNew->name = cpline;
    symNew->next = NULL;
    symNew->address = IC;
    symNew->is_Code = is_Code;
    symNew->is_Data = is_Data;
    symNew->is_Entry = is_Entry;
    symNew->is_Extern = is_Extern;

    if (head == NULL)
    {
        head = symNew;
        return true;
    }

    while (temp->next != NULL)
    {
        if (strcmp(temp->name, symNew->name))
        {
            printf("same name!\n");
            /*add_error();*/
            return false;
        }
        temp = temp->next;
    }
    temp->next = symNew;
    return true;
}


int check_length(char * line)
{
    int length = 0;
    char * token = strtok(line,ARGUMENT_SEPARATOR);
    while(token != NULL)
    {
        length++;
        token = trim(strtok(NULL,ARGUMENT_SEPARATOR));
    }

    return length;
}


void print_symbol(Symbol *head)
{
    while (head != NULL)
    {
        printf("Symbol: \n");
        printf("%s\n", head->name);
        printf("%ld\n", head->address);
        printf("%d\n", head->is_Code);
        printf("%d\n", head->is_Data);
        printf("%d\n", head->is_Entry);
        head = head->next;
    }
}
