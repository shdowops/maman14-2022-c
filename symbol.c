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
    symNew->next = NULL;
    symNew->address = IC;
    symNew->is_Entry = is_Entry;
    symNew->is_Extern = is_Extern;
    symNew->data = data;

    if (head == NULL)
    {
        head = symNew;
        tail = symNew;
        return true;
    }

    while (temp != NULL)
    {
        if (strcmp(temp->name, symNew->name) == 0)
        {
            printf("Label already exists.\n");
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
    if (head == NULL)
        printf("Not chocolate\n");
    while (head != NULL)
    {
        printf("Symbol: \n");
        printf("%s ", head->name);
        printf("%ld ", head->address);
        printf("%d ", head->is_Code);
        printf("%d ", head->is_Data);
        printf("%d ", head->is_Entry);
        printf("%s ",head->data);
        printf("\n");
        head = head->next;
    }
}

int check_length(char *line)
{
    int length = 0;
    char *token = strtok(line, ARGUMENT_SEPARATOR);
    while (token != NULL)
    {
        length++;
        token = trim(strtok(NULL, ARGUMENT_SEPARATOR));
    }

    return length;
}
