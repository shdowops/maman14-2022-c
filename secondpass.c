#include "secondpass.h"
extern long IC, DC, linenumber;
extern Symbol *head, *tail;
extern char *Registers[NUM_OF_REGISTERS];
int binary_converter(char binary[]);
void secondpass(char *filename)
{
    int op_type;
    char line[MAX_LINE_LENGTH];
    char *firstoperand, *secondoperand, *trimmedline, *token, *binarydata;
    bool no_error;
    FILE *ent_fptr, *ext_fptr, *obj_fptr;
    FILE *processedfile = fopen(filename, "r");
    Symbol *toupdate;
    linenumber = 0;
    ent_fptr = ext_fptr = obj_fptr = NULL;

    if (processedfile == NULL) /*If file was not opened*/
    {
        alertFileError(ER_OPEN_FILE);
    }
    else /*File was opened*/
    {
        IC = 0;
        no_error = true;
        /*read next line from file*/
        while ((fgets(line, MAX_LINE_LENGTH, processedfile) != NULL))
        {
            ++linenumber;
            trimmedline = trim(line);
            token = (char *)malloc(strlen(trimmedline));
            strcpy(token, trimmedline);
            if (isEmptyLine(trimmedline) || isComment(trimmedline))
                continue;

            /* is label ?*/
            if (isLabel(trimmedline, NULL))
            {
                token = strtok(token, ARGUMENT_SEPARATOR);
                token = strtok(NULL, ARGUMENT_SEPARATOR);
            }
            else
                token = strtok(token, ARGUMENT_SEPARATOR);

            /* is data? string? struct? extern? */
            if (isDataSymbol(trimmedline) || isExtern(trimmedline) || isStructDeclaration(trimmedline))
                continue;

            /* is entry */
            if (isEntry(trimmedline))
            {
                char *entry;
                entry = getEntry(trimmedline);
                if (entry == NULL)
                {
                    alertError(ER_EMPTY_ENTREY);
                    no_error = false;
                }
                else
                    update_entry_symbol(head, entry);
                continue;
            }
            /* finish encoding operands*/
            isCommand(token, &op_type);                       /*Get command type */
            token = strtok(NULL, ARGUMENT_SEPARATOR);         /*get first operand of the insturction */
            toupdate = findsymbol(head, IC);                  /*Find the symbol to be updated by IC */
            IC++;                                             /*Move IC by one for the command */
            firstoperand = token;                             /*Get first operand */
            secondoperand = strtok(NULL, ARGUMENT_SEPARATOR); /*Get second operand*/
            binarydata = toupdate->binarydata;

            /*Check operands by command type*/
            if (op_type == TWO_OPERANDS)
            {
                if (isRegister(firstoperand))
                {
                    strcat(binarydata, "\n");
                    no_error &= operand_to_binary(firstoperand, toupdate);
                    if (isRegister(secondoperand))
                    {
                        IC--;
                        no_error &= operand_to_binary(secondoperand, toupdate);
                        strcat(binarydata, ABSOLUTE);
                        continue;
                    }
                    else
                        strcat(binarydata, "000000");
                }
                if (!isRegister(firstoperand))
                    no_error &= operand_to_binary(firstoperand, toupdate);

                binarydata = toupdate->binarydata; /*get updated binary data after first operand*/

                if (isRegister(secondoperand))
                {
                    strcat(binarydata, "\n0000");
                    no_error &= operand_to_binary(secondoperand, toupdate);
                    strcat(binarydata, ABSOLUTE);
                    continue;
                }
                no_error &= operand_to_binary(secondoperand, toupdate);
            }
            else if (op_type == ONE_OPERAND)
                no_error &= operand_to_binary(firstoperand, toupdate);
            else
                continue;
        }
    }

    /* end reading file */

    if (!no_error)
        return;

    print_symbol(head);
    strtok(filename, SEPARATOR);
    obj_fptr = fopen(strcat(filename, OBJECT_EXT), "wb");
    /*save_files(ent_fptr, ext_fptr, obj_fptr, filename);

    if(ent_fptr)
        fclose(ent_fptr);
    if(ext_fptr)
        fclose(ext_fptr);
    fclose(obj_fptr); */
}

bool operand_to_binary(char *operand, Symbol *toupdate)
{
    Symbol *structaddress, *getaddress;
    char *binarydata = toupdate->binarydata;
    if (isRegister(operand)) /* check if operand is register */
    {
        binarydata = realloc(binarydata, strlen(binarydata) + BINARY_LENGTH + 1);
        strcat(binarydata, (convert_decimal_binary(operand[1] - '0') + 6));
        toupdate->binarydata = binarydata;
        IC++;
        return true;
    }

    if (isStruct(operand)) /* check if operand is struct */
    {
        IC += 2;
        operand = strtok(operand, SEPARATOR);
        structaddress = findname(head, operand);
        if (!structaddress)
        {

            alertError(ER_NO_STRUCT_DECLARED);
            return false;
        }
        /*Add Struct address*/
        binarydata = (char *)realloc(binarydata, strlen(binarydata) + BINARY_LENGTH + 1);
        strcat(binarydata, "\n");
        strcat(binarydata, (convert_decimal_binary(structaddress->address) + 2));
        strcat(binarydata, RELOCATABLE);

        /*Add struct field*/
        operand = strtok(NULL, SEPARATOR);
        binarydata = (char *)realloc(binarydata, strlen(binarydata) + BINARY_LENGTH + 1);
        strcat(binarydata, "\n");
        strcat(binarydata, (convert_decimal_binary(atol(operand)) + 2));
        strcat(binarydata, ABSOLUTE);
        toupdate->binarydata = binarydata;
        return true;
    }

    if (isNumber(operand)) /* check if operand is a number */
    {
        operand = strtok(operand, NUMBERSTART);
        binarydata = (char *)realloc(binarydata, strlen(binarydata) + BINARY_LENGTH + 1);
        strcat(binarydata, "\n");
        strcat(binarydata, (convert_decimal_binary(atol(operand)) + 2));
        strcat(binarydata, ABSOLUTE);
        toupdate->binarydata = binarydata;
        IC++;
        return true;
    }

    /*Check if valid label and exists*/
    IC++;
    getaddress = findname(head, operand);
    if (!getaddress)
    {
        alertError(ER_LABEL_NOT_DEFINED);
        return false;
    }
    binarydata = (char *)realloc(binarydata, strlen(binarydata) + BINARY_LENGTH + 1);
    strcat(binarydata, "\n");
    if (getaddress->address == -1)
    {
        strcat(binarydata, "00000000");
        strcat(binarydata, EXTERNAL);
    }
    else
    {
        strcat(binarydata, (convert_decimal_binary(getaddress->address) + 2));
        strcat(binarydata, RELOCATABLE);
    }
    toupdate->binarydata = binarydata;
    return true;
}

void save_files(FILE *ent_fptr, FILE *ext_fptr, FILE *obj_fptr, char *filename)
{
    Symbol *temp = head;
    while (temp != NULL)
    {
        if (temp->binarydata)
        {
            char res[2];
            printf("translated = %s\n", translated(temp->binarydata, res));
        }

        if (temp->is_Entry)
        {
            if (!ent_fptr)
                ent_fptr = fopen(strcat(strtok(filename, SEPARATOR), ENTRY_EXT), "wb");

            /*Need to convert the address to base 32 */
            long textsize = strlen(temp->name) + 15;
            char *completeline = (char *)malloc(textsize);
            memset(completeline, 0, textsize);
            fputs(temp->name, ent_fptr);
            fputs("\t", ent_fptr);
            fputs("!!", ent_fptr);
            fputs("\n", ent_fptr);
            temp = temp->next;
            continue;
        }

        /*if (temp->is_Extern)
        {
            if (!ext_fptr)
                ext_fptr = fopen(strcat(strtok(filename, SEPARATOR), EXTERN_EXT), "wb");
            fputs(temp->data, ext_fptr);
            fputs("\t", ext_fptr);
            fputs("\n", ext_fptr);
        }*/
        temp = temp->next;
    }
}

/*Translate to 32 bits*/
char *translated(char line[], char *res)
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
    printf("numone=%d , numtwo:%d \n", numOne, numTwo);
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
        printf("binary[index]: %c\n", binary[index]);
        decimal = decimal + (binary[index] - 48) * SQUARE(position);
        index--;
        position++;
    }
    decimal = (decimal) / 2;
    return decimal;
}