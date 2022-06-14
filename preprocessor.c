#include "preprocessor.h"

/* Preprocessor for macros */
void preprocessor(FILE *codefile, char *filename)
{
    FILE *processedfile;
    char line[MAX_LINE_LENGTH];
    char *found, *name, *macro, *token;

    Macro *newMacro = NULL, *macroToApply = NULL, *head = NULL;
    int macroflag = 0, macrolines = 1, firstmacro = 1;
    processedfile = fopen(strcat(strtok(filename, SEPARATOR), ".am"), "w");
    macro = (char *)malloc(MAX_LINE_LENGTH);

    /* searching file for macros and saving a processed file*/
    while ((fgets(line, MAX_LINE_LENGTH, codefile) != NULL))
    {
        if (!macroflag)
        {
            found = strstr(line, MACROSTART);

            if (!found)
            {
                if ((macroToApply = isMacro(line, head)))
                    fputs(macroToApply->macro, processedfile);
                else
                    fputs(line, processedfile);
            }
            else
            {
                macroflag = 1;
                strtok(line, " ");
                token = strtok(NULL, " "); /*Move to the macro name*/
                if (token == NULL)
                {
                    /*Add error message for empty macro declaration*/
                    continue;
                }
                newMacro = (Macro *)malloc(sizeof(Macro));
                name = (char *)malloc(sizeof(token));
                strcpy(name, token);
                newMacro->name = name;
                if (firstmacro)
                {
                    head = newMacro;
                    firstmacro = 0;
                }
                else
                    addToMacroList(newMacro, head);
            }
        }
        else
        {
            found = strstr(line, MACROEND);
            if (!found)
            {
                macro = (char *)realloc(macro, MAX_LINE_LENGTH * macrolines);
                strcat(macro, line);
                macrolines++;
            }
            else
            {
                macroflag = 0;
                newMacro->macro = macro;
                newMacro->next = NULL;
                macrolines = 1;
            }
        }
    }
    fclose(processedfile);
    freeMacros(head);
}

Macro *isMacro(char *str, Macro *head)
{
    while (head)
    {
        if (strcmp(str, head->name) == 0)
            return head;
        head = head->next;
    }
    return NULL;
}

void addToMacroList(Macro *newMacro, Macro *head)
{
    while (head->next!=NULL)
        head = head->next;

    head->next = newMacro;
}

void freeMacros(Macro *head)
{
    if(!head)
        return;
    if(head->next)
        freeMacros(head->next);

    free(head);
    
}