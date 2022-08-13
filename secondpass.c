#include "secondpass.h"
extern long IC, DC;
extern Symbol *head, *tail;
void secondpass(char *filename)
{
    print_symbol(head);
    char line[MAX_LINE_LENGTH], *trimmedline, label[MAX_LABEL_LENGTH];
    bool is_error;
    /* int kind;*/
    bool no_error, is_data, is_code, is_entry, is_extern;
    FILE *processedfile = fopen(filename, "r");
    memset(label, 0, MAX_LABEL_LENGTH - 1); /*Reset the label to nothing*/

    if (processedfile == NULL) /*If file was not opened*/
    {
        alertFileError(ER_OPEN_FILE);
    }
    else /*File was opened*/
    {
        IC = 0;
        is_error = false;
        /*read next line from file*/
        while ((fgets(line, MAX_LINE_LENGTH, processedfile) != NULL))
        {
            trimmedline = trim(line);
            if (isEmptyLine(trimmedline) || isComment(trimmedline))
                continue;

            /* is label ?*/
            if (isLabel(trimmedline, label))
                /*skip to next field*/
                continue;

            /* is data? string? struct? extern? */
            if (isDataSymbol(trimmedline) || isExtern(trimmedline) || isStructDeclaration(trimmedline))
                continue;

            /* is entry */

            if (isEntry(trimmedline))
            {
                char *entry;
                is_data = is_code = is_entry = is_extern = false;
                entry = getEntry(trimmedline);
                if (entry == NULL)
                    alertError(ER_EMPTY_ENTREY);
                else
                {
                    is_entry = true;
                    no_error &= add_symbol(trimmedline, label, is_code, is_data, is_entry, is_extern); /* insert to symbol as code with IC value*/
                }
                continue;
            }

            /* finish encoding operands*/

            if (isEmptyLine(trimmedline) || isComment(trimmedline))
                continue;

            is label ? if (isLabel(trimmedline, label))

                           kind = 0;
            if (isCommand(trimmedline, &kind))
            {
                check instruction type if (kind != 0)
                {
                    char *tok;
                    char * strWord;
                    tok = strtok(trimmedline, LINE_SPACE);

                    if (kind == 1)
                    {
                        if (isRegister(tok))
                        {
                            int j;
                            char transRegister [] = {"0000","0001","0010","0011","0100","0101","0110","0111"}; 
                            for (j = 0; j < 8; j++)
                            {
                                if(tok==Registers[j])
                                {
                                    strWord==transRegister[j];
                                }
                            }
                                continue;
                        }
                        else
                        {
                            if (isLabel(tok))
                            {
                                bool notFound=true;
                                Symbol temp=head;
                                while(temp->next!=NULL)
                                {
                                    if(temp->name!='\0')
                                        {
                                            if(strcmp(tok,temp->name)==0)
                                            {
                                                strWord=convert_decimal_Binary(temp->address);
                                                notFound=false
                                            }
                                        }
                                    temp=temp->next;
                                }
                                if(notFound)
                                {
                                    alertError(ER_LABEL_IS_MISSING);
                                }

                                continue;
                            }
                            else
                            {
                                if (isdigit(line[strlen(tok) - 1]))
                                {
                                    strWord=convert_decimal_Binary(tok);
                                    continue;
                                }
                                
                            }
                        }
                    }
                    else
                    {
                        tok = strtok(line, ARGUMENT_SEPARATOR);
                    }
                }
            }
            continue;

            /* is data? string? struct? extern? */
            if (isDataSymbol(trimmedline) || isExtern(trimmedline) || isStruct(trimmedline))
                continue;
            /*IC = IC + L;*/
        }
    }
    /* end reading file */

    if (is_error)
        /*print error*/
        return;

    printf("filename:%s\n", filename);
    /* save files */
}

/*Translate to 32 bits*/
char *translated(char line[], char res [2])
{
    char first[5];
    char second[5];
    
    int i;
    int numOne;
    int numTwo;
    char language[] = {'!', '@', '#', '$', '%', '^', '&', '*', '<', '>', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v'};
    for (i = 0; i < 5; i++)
    {
        first[i] = line[i];
    }
    for (i = 0; i < 5; i++)
    {
        second[i] = line[i];
    }
    numOne = binary_converter(first);
    numTwo = binary_converter(second);
    res[0] = language[numOne];
    res[1] = language[numTwo];
    return res;
}

/*The method recieves a binary number in a string format and converts it into an integer*/
int binary_converter(char binary[])
{
    int length = 5;
    int decimal = 0;
    int position = 0;
    int index = length - 1;
    while (index >= 0)
    {
        decimal = decimal + (binary[index] - 48) * SQUARE(position);
        index--;
        position++;
    }
    return decimal;
}