#include "secondpass.h"
extern long IC, DC, linenumber;
extern Symbol *head, *tail;
extern char *Registers[NUM_OF_REGISTERS];
char res[2];
FILE *ent_fptr, *ext_fptr, *obj_fptr;
char *extfilename;

void secondpass(char *filename)
{
    int op_type;
    char line[MAX_LINE_LENGTH];
    char *firstoperand, *secondoperand, *trimmedline, *token, *binarydata , *noextension;
    bool no_error;
    FILE *processedfile = fopen(filename, "r");
    Symbol *toupdate;
    linenumber = 0;

    noextension = (char*)malloc(strlen(filename));
    strcpy(noextension,filename);
    noextension=strtok(noextension,SEPARATOR);

    extfilename = (char*)malloc(strlen(noextension)+MAX_EXT_LENGTH);
    extfilename = strcat(noextension,EXTERN_EXT);


    if (processedfile == NULL)
    {
        alertFileError(ER_OPEN_FILE);
        no_error = false;
    }
    else
    {
        IC = 100;
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
                        binarydata = toupdate->binarydata;
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
    {   
        remove(extfilename);
        return;
    }

    print_symbol(head);
    strtok(filename, SEPARATOR);
    obj_fptr = fopen(strcat(filename, OBJECT_EXT), "wb");
    save_files(ent_fptr, obj_fptr, filename);

    if (ent_fptr)
        fclose(ent_fptr);
    if (ext_fptr)
        fclose(ext_fptr);
    fclose(obj_fptr);
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
    getaddress = findname(head, operand);
    if (!getaddress)
    {
        IC++;
        alertError(ER_LABEL_NOT_DEFINED);
        return false;
    }
    binarydata = (char *)realloc(binarydata, strlen(binarydata) + BINARY_LENGTH + 1);
    strcat(binarydata, "\n");
    if (getaddress->address == -1)
    {
        if(!ext_fptr)
            ext_fptr = fopen(extfilename, "wb");

        strcat(binarydata, "00000000");
        strcat(binarydata, EXTERNAL);
        fputs(getaddress->name, ext_fptr);
        fputs("\t", ext_fptr);
        translated(convert_decimal_binary(IC), res);
        fputs(res, ext_fptr);
        fputs("\n", ext_fptr);
    }
    else
    {
        strcat(binarydata, (convert_decimal_binary(getaddress->address) + 2));
        strcat(binarydata, RELOCATABLE);
    }
    toupdate->binarydata = binarydata;
    IC++;
    return true;
}

void save_files(FILE *ent_fptr, FILE *obj_fptr, char *filename)
{
    char *binarydata;
    Symbol *temp = head;
    IC = 100;
    while (temp != NULL)
    {
        if (temp->binarydata)
        {
            binarydata = (char *)malloc(strlen(temp->binarydata));
            strcpy(binarydata, temp->binarydata);
            binarydata = strtok(binarydata, "\n");
            while (binarydata)
            {
                translated(convert_decimal_binary(IC),res);
                fputs(res, obj_fptr);
                fputs("\t",obj_fptr);
                translated(binarydata, res);
                fputs(res,obj_fptr);
                fputs("\n",obj_fptr);
                IC++;
                binarydata = strtok(NULL, "\n");
            }
            free(binarydata);
        }

        if (temp->is_Entry)
        {
            if (!ent_fptr)
                ent_fptr = fopen(strcat(strtok(filename, SEPARATOR), ENTRY_EXT), "wb");
            /*additions*/
            translated(convert_decimal_binary(temp->address), res); /*result of translation stored in res*/
            fputs(temp->name, ent_fptr);
            fputs("\t", ent_fptr);
            fputs(res, ent_fptr);
            fputs("\n", ent_fptr);
            temp = temp->next;
            continue;
        }
        temp = temp->next;
    }
}

char *translated(char line[], char *res)
{
    int i,j;
    int numOne;
    int numTwo;        
    char language[] = {'!', '@', '#', '$', '%', '^', '&', '*', '<',
                       '>', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
                       'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v'};
    char first[HALF_BINARY_LENGTH];
    char second[HALF_BINARY_LENGTH];
    memset(first,0,HALF_BINARY_LENGTH);
    memset(second,0,HALF_BINARY_LENGTH);

    
    for (i = 0; i < HALF_BINARY_LENGTH -1 ; i++) /*seperating first digit for base 32*/
    {
        first[i] = line[i];
    }
    j=i;
    for (i = 0; i < HALF_BINARY_LENGTH -1 ; i++, j++) /*seperating second digit for base 32*/
    {
        second[i] = line[j];
    }
    numOne = binary_converter(first);  /*identifying the value of first binary number*/
    numTwo = binary_converter(second); /*identifying the value of second binary number*/
    res[0] = language[numOne]; /*translating the value of the first digit into base 32*/
    res[1] = language[numTwo]; /*translating the value of the second digit into base 32*/
    return res;
}

/*The method recieves a binary number in a string format and converts it into an integer*/
int binary_converter(char binary[])
{
    int length;
    int decimal;
    int position;
    int index;

    length = HALF_BINARY_LENGTH -1 ;
    decimal = 0;
    position = 0;
    index = length - 1;
    /*The loop iterates as long as there is a binary number digit that has not been processed*/
    while (index >= 0)
    {
        decimal = decimal + (binary[index] - '0') * SQUARE(position); /*converts the decimal digit into equation*/
        index--;                                                     /*updates the iterator*/
        position++;                                                  /*updats the square level for the conversion of the binary number into decimal*/
    }
    return decimal;
}