#include "firstpass.h"

extern int IC, DC;

void firstpass(char *filename)
{
    char line[MAX_LINE_LENGTH], *trimmedline;
    bool is_label, is_error;
    FILE *processedfile = fopen(filename, "r");
    IC = DC = 0;
    is_label = is_error = false;
    /*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
    SymbolTable labelTable=create_symbol_table();    /*Create Label Table*/
    SymbolTable dataTable= create_symbol_table(); /*Create Data Table*/
    Symbol label;/*Creating a label*/
    Command newCom;/*Creating a command*/
    /*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/

    /*read next line from file*/
    if (processedfile == NULL)
    {
        /* Add error unable to open file*/
        printf("Unable to open file %s\n", filename);
        return;
    }
    
    while ((fgets(line, MAX_LINE_LENGTH, processedfile) != NULL))
    {
        trimmedline = trim(line);
        if (isEmptyLine(trimmedline) || isComment(trimmedline))
            continue;

        /*it is label? */
        is_label = isLabel(trimmedline);

        /*check if .data? .string? .struct? */
        if (isDataSymbol(trimmedline))
            if (is_label)
            {
                printf("Data Symbol + lable\n");
                /*insert tavit as data label with value of DC*/
                /*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
                label= create_symbol(DC,trimmedline);/*creating a new data Symbol*/
                add_value(dataTable,dataSym);/*Adding a new data Symbol to the data table*/
            /*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/

                /*determine symboltype encode the memory*/
                /*update DC */
                continue;
            }

        /*if .extern? .entry? */
        if (isEntry(trimmedline) || isExtern(trimmedline))
            if (isExtern(trimmedline))
            {
                printf("It is extern!\n");
                /*add external symbols (one or more) to symbol list without a value*/
                continue;
            }

        /* if flag is label */
        if (is_label)
        {
            printf("Inside label\n");
            /* insert to symbol as code with IC value*/
            /*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
            /*Creating a new label*/
            label=create_symbol(IC,trimmedline);
            /*Adding label to label table*/
            addvalue(labelTable,label);
            /*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/


            IC++;
        }

        /* check instruction, if not exist, add error. */
        /*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
        newCom=create_command(label, trimmedline);/*Creating the command and adding to labels*/
        /*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/

        /*check operands and count them*/
        /*build binary code of the instruction*/
        /* IC --> IC +L */
    }
    /* Finished reading the file*/

    if (is_error)
        /* print errors */
        return;

    /* update symbol list data adding the right IC
        while(headptr != NULL)
        {
            headptr->dc+=IC;
            headptr=headptr->next;
        }
    */
    /*Start second pass*/
    fclose(processedfile);
    secondpass(filename);
}