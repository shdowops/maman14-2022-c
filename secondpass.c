#include "secondpass.h"
extern long IC, DC, linenumber;
extern Symbol *head, *tail;
extern char *Registers[NUM_OF_REGISTERS];

FILE *ent_fptr, *ext_fptr, *obj_fptr;

void secondpass(char *filename)
{
    int op_type;
    char line[MAX_LINE_LENGTH];
    char *firstoperand, *secondoperand, *trimmedline, *token, *binarydata;
    bool no_error;
    FILE *processedfile = fopen(filename, "r");
    Symbol *toupdate;
    linenumber = 0;
    ent_fptr = ext_fptr = obj_fptr = NULL;

    if (processedfile == NULL)
    {
        alertFileError(ER_OPEN_FILE);
        no_error = false;
    }
    else
    {
        IC = 0;
        no_error = true;
        while ((fgets(line, MAX_LINE_LENGTH, processedfile) != NULL)) /*read next line from file*/
        {
            ++linenumber;
            trimmedline = trim(line);
            token = (char *)malloc(strlen(trimmedline));
            strcpy(token, trimmedline);
            if (isEmptyLine(trimmedline) || isComment(trimmedline)) /*checking if the line is empty*/
                continue;

            /* If it is a label*/
            if (isLabel(trimmedline, NULL))
            {
                /*Proceed to the next operand*/
                token = strtok(token, ARGUMENT_SEPARATOR);
                token = strtok(NULL, ARGUMENT_SEPARATOR);
            }
            else
                token = strtok(token, ARGUMENT_SEPARATOR);

            /* if is a .data .struct .extern */
            if (isDataSymbol(trimmedline) || isExtern(trimmedline) || isStructDeclaration(trimmedline))
                continue;

            /* is entry */
            if (isEntry(trimmedline))
            {
                char *entry;
                entry = getEntry(trimmedline);
                if (entry == NULL)
                {
                    alertError(ER_EMPTY_ENTRY);
                    no_error = false;
                }
                else
                    update_entry_symbol(head, entry);
                continue;
            }
            /* finish encoding operands*/
            isCommand(token, &op_type);                       /*Get command type with op_type */
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
                        strcat(binarydata, "000000"); /*finish register incoding if it is a single register */
                }
                if (!isRegister(firstoperand))
                    no_error &= operand_to_binary(firstoperand, toupdate);

                binarydata = toupdate->binarydata; /*get updated binary data after first operand*/

                if (isRegister(secondoperand))
                {
                    strcat(binarydata, "\n0000"); /*Set source operand as 0000*/
                    no_error &= operand_to_binary(secondoperand, toupdate);
                    strcat(binarydata, ABSOLUTE);
                    continue;
                }
                /*if the second operand is not a register*/
                no_error &= operand_to_binary(secondoperand, toupdate);
            }
            else if (op_type == ONE_OPERAND)
                no_error &= operand_to_binary(firstoperand, toupdate);
            else
                continue;
        }
    }
    /* done reading file */

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

    if (isStruct(operand)) /* check if operand is a struct */
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

        /*Add struct field address*/
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
    char res[2];
    Symbol *temp = head;
    while (temp != NULL)
    {
        if (temp->binarydata)
        {
            printf("translated binary data= %s\n", translated(temp->binarydata, res));
            /*additions*/
            /*
            fputs(res, obj_fptr);

            */
        }

        if (temp->is_Entry)
        {
            if (!ent_fptr)
                ent_fptr = fopen(strcat(strtok(filename, SEPARATOR), ENTRY_EXT), "wb");
            /*additions*/
            translated(convert_decimal_binary(temp->address), res); /*result of translation stored in res*/
            printf("translated entry address= %s\n", translated(temp->binarydata, res));
            long textsize = strlen(temp->name) + 15;
            char *completeline = (char *)malloc(textsize);
            memset(completeline, 0, textsize);
            fputs(temp->name, ent_fptr);
            fputs("\t", ent_fptr);
            fputs(res, ent_fptr);
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
            printf("translated extern address= %s\n", translated(temp->binarydata, res));
            fputs("\t", ext_fptr);
            fputs(res, ext_fptr);
            fputs("\n", ext_fptr);
        }*/
        temp = temp->next;
    }
}

/*Translate to 32 bits*/
char *translated(char line[], char *res)
{
    /*Variable declaration*/
    char first[5];
    char second[5];

    int i;
    int numOne;
    int numTwo;
    /*Array representing the alphabet for our 32 base language*/
    char language[] = {'!', '@', '#', '$', '%', '^', '&', '*', '<', '>', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v'};
    for (i = 0; i < 5; i++) /*seperating first digit for base 32*/
    {
        first[i] = line[i];
    }
    for (i = 0; i < 5; i++) /*seperating second digit for base 32*/
    {
        second[i] = line[i];
    }
    numOne = binary_converter(first);  /*identifying the value of first binary number*/
    numTwo = binary_converter(second); /*identifying the value of second binary number*/
    printf("numone=%d , numtwo:%d \n", numOne, numTwo);
    res[0] = language[numOne]; /*translating the value of the first digit into base 32*/
    res[1] = language[numTwo]; /*translating the value of the second digit into base 32*/
    return res;
}

/*The method recieves a binary number in a string format and converts it into an integer*/
int binary_converter(char binary[])
{
    /*Variable Declarations*/
    int length;
    int decimal;
    int position;
    int index;

    /*Initializng Variables*/
    length = 5;
    decimal = 0;
    position = 0;
    index = length - 1;
    /*The loop iterates as long as there is a binary number digit that has not been processed*/
    while (index >= 0)
    {
        printf("binary[index]: %c\n", binary[index]);
        decimal = decimal + (binary[index] - 48) * SQUARE(position); /*converts the decimal digit into equation*/
        index--;                                                     /*updates the iterator*/
        position++;                                                  /*updats the square level for the conversion of the binary number into decimal*/
    }
    decimal = (decimal) / 2;
    return decimal;
}