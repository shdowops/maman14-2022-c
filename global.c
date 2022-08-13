#include "global.h"



char *Keywords[NUM_OF_KEYWORDS] = {"mov", "cmp", "add", "sub", "not", "clr", "lea", "inc", "dec", "jmp", "bne", "get", "prn", "jsr", "rts", "hlt",
                                   ".data", ".string", ".extern", ".entry", ".struct"};
char *TwoOperandCmd[] = {"mov", "cmp", "add", "sub", "lea"};
char *SingleOperandCmd[] = {"not", "clr", "inc", "dec", "jmp", "bne", "get", "prn", "jsr"};
char *NoOperandCmd[] = {"rts", "hlt"};
opcode opcodes[OPCODE_AMOUNT] = {
{ 0		,	"mov"	,"0000"	,	TWO_OPERANDS },
{ 1		,	"cmp"	,"0001"	,	TWO_OPERANDS },
{ 2		,	"add"	,"0010",	TWO_OPERANDS },
{ 3		,	"sub"	,"0011"	,	TWO_OPERANDS },
{ 4		,	"not"	,"0100"	,	ONE_OPERAND },
{ 5		,	"clr"	,"0101"	,	ONE_OPERAND },
{ 6		,	"lea"	,"0110"	,	ONE_OPERAND },
{ 7		,	"inc"	,"0111"	,	ONE_OPERAND },
{ 8		,	"dec"	,"1000"	,	ONE_OPERAND },
{ 9		,	"jmp"	,"1001"	,	ONE_OPERAND },
{ 10	,	"bne"	,"1010"	,	ONE_OPERAND },
{ 11	,	"get"	,"1011"	,	ONE_OPERAND },
{ 12	,	"prn"	,"1100"	,	ONE_OPERAND },
{ 13	,	"jsr"	,"1101"	,	ONE_OPERAND },
{ 14	,	"rts"	,"1110"	,	NO_OPERANDS },
{ 15	,	"hlt"	,"1111"	,	NO_OPERANDS }
};

char *filename;

bool check_label(char *labeltocheck, char *labeltosave)
{
  char *temp = labeltocheck;
  /*Label not starting with alpha numeric character*/
  if (!isalpha(temp[0]))
  {
    alertError(ER_LABEL_NOT_FIRST_ALPHA);
    return false;
  }

  /*Label is longer than 30 characters*/
  if (strlen(temp) > MAX_LABEL_LENGTH)
  {
    alertError(ER_LABEL_TOO_LONG);
    return false;
  }

  /*Label is a keyword or register*/
  if (isKeyword(temp) || isRegister(temp))
  {
    alertError(ER_LABEL_NAME_ILLEGAL);
    return false;
  }

  /*Label contains space before colon sign*/
  if (isspace(temp[strlen(temp) - 1]))
  {
    alertError(ER_LABEL_SPACE);
    return false;
  }

  /*Label is not alphanumeric*/
  while (*(temp + 1) != '\0')
  {
    if (!isalnum(*temp))
    {
      alertError(ER_LABEL_ALPHA);
      return false;
    }
    temp++;
  }
  if (labeltosave)
    strcpy(labeltosave, labeltocheck);
  return true;
}

bool isLabel(char *line, char *label)
{
  char *secondpart;
  char *temp = (char *)malloc(sizeof(char) * strlen(line));
  strcpy(temp, line);
  temp = strtok(temp, LABELMARK);
  if (strcmp(line, temp) == 0) /*No label found*/
    return false;
  secondpart = trim(strtok(NULL, LABELMARK));
  strcpy(line, secondpart);
  return check_label(temp, label);
}

bool isEmptyLine(char *line)
{
  char *temp = line;
  while (*temp)
  {
    if (!isspace(*temp))
      return false;
    temp++;
  }
  return true;
}

bool isComment(char *line)
{
  return (line[START_OF_LINE] == COMMENT || line == NULL) ? true : false;
}

char *trim(char *line)
{
  int i;

  while (isspace(*line)) /*skip left whitespaces*/
    line++;
  /*skip right whitespaces*/
  for (i = strlen(line) - 1; (isspace(line[i])); i--)
    ;
  line[i + 1] = '\0';
  return line;
}

bool isEntry(char *line)
{
  if (strstr(line, ENTRY))
    return true;
  return false;
}

bool isExtern(char *line)
{
  if (strstr(line, EXTERN))
    return true;
  return false;
}

bool isDataSymbol(char *line)
{
  return (isDataDeclaration(line) || isStringDeclaration(line) || isStructDeclaration(line));
}

bool isDataDeclaration(char *line)
{
  return strstr(line, DATA);
}

bool isStringDeclaration(char *line)
{
  return strstr(line, STRING);
}

bool isStructDeclaration(char *line)
{
  return strstr(line, STRUCT);
}

bool isKeyword(char *line)
{
  int i;
  for (i = 0; i < NUM_OF_KEYWORDS; i++)
    if (strcmp(line, Keywords[i]) == 0)
      return true;
  return false;
}

bool isRegister(char *line)
{
  int i;
  for (i = 0; i < NUM_OF_REGISTERS; i++)
    if (strcmp(line, Registers[i]) == 0)
      return true;
  return false;
}

bool isStruct(char *line)
{
  char *token;
  char *temp = malloc(sizeof(line));
  strcpy(temp, line);
  token = strtok(temp, SEPARATOR);
  token = strtok(NULL, SEPARATOR);
  if (!token)
  {
    free(temp);
    return false;
  }

  if (*token != STURCT_FIRST_ARG && *token != STRUCT_SECOND_ARG)
  {
    free(temp);
    alertError(ER_OUT_OF_BOUND_STRUCT);
    return false;
  }
  free(temp);
  return true;
}

bool isNumber(char *line)
{
  char *token;
  char *temp = malloc(sizeof(line));
  strcpy(temp, line);
  token = strtok(temp, NUMBERSTART);
  if (strcmp(token, temp) == 0)
  {
    free(temp);
    return false;
  }
  free(temp);
  return true;
}

char *getEntry(char *entryline)
{
  char *token = strtok(entryline, LINE_SPACE);
  token = strtok(NULL, LINE_SPACE);
  return token;
}

bool check_opcode(char *line, int *type, char *binarydata)
{
  char *token;
  line = strtok(line, ARGUMENT_SEPARATOR); /*get instruction */
  strcat(binarydata, getopcode(line));
  printf("bindata=%s\n",binarydata);
  line = strtok(NULL, ARGUMENT_SEPARATOR);  /*get first argument */
  token = strtok(NULL, ARGUMENT_SEPARATOR); /*get second argument */
  if (*type == TWO_OPERANDS)
  {
    if (!checkoperand(line)) /*Check first operand*/
    {
      alertError(ER_SOURCE_OPERAND);
      return false;
    }
    if (!checkoperand(token)) /*Check second operand*/
    {
      alertError(ER_DESTINATION_OPERAND);
      return false;
    }
    if (isRegister(line) && isRegister(token))
      IC--;
  }
  else if (*type == ONE_OPERAND)
  {
    line = strtok(NULL, LINE_SPACE);
    if (line != NULL && !checkoperand(line))
    {
      alertError(ER_OPERANDS_OVERFLOW_IN_COMMAND);
      return false;
    }
    IC++;
  }
  else if (line != NULL) /* No operands command*/
  {
    alertError(ER_OPERANDS_OVERFLOW_IN_COMMAND);
    return false;
  }
  return true;
}

bool checkoperand(char *operand)
{
  if (!operand)
  {
    alertError(ER_SOURCE_OPERAND);
    return false;
  }
  if (isRegister(operand))
  {
    IC++;
    return true;
  }
  if (isStruct(operand))
  {
    IC += 2;
    return true;
  }
  if (isNumber(operand))
  {
    IC++;
    return true;
  }
  if (check_label(operand, NULL))
  {
    IC++;
    return true;
  }
  alertError(NOT_VALID_OPERAND);
  return false;
}

bool isCommand(char *line, int *type)
{
  int i;

  /*Checking if command is type 2 operand*/
  for (i = 0; i < 5; i++)
    if (strcmp(line, TwoOperandCmd[i]) == 0)
    {
      *type = TWO_OPERANDS;
      return true;
    }

  /*Checking if command is type 1 operand*/
  for (i = 0; i < 9; i++)
    if (strcmp(line, SingleOperandCmd[i]) == 0)
    {
      *type = ONE_OPERAND;
      return true;
    }

  /*Checking if command is type 0 operand*/
  for (i = 0; i < 2; i++)
    if (strcmp(line, NoOperandCmd[i]) == 0)
    {
      *type = NO_OPERANDS;
      return true;
    }

  alertError(ER_OPCODE_ILLEGAL);
  return false;
}

/*Assisting function for the isCommand Method.
 *This method checks how many operands there are in the line
 */

char *getopcode(char *line)
{
  int i;
  for(i=0;i<OPCODE_AMOUNT;i++)
    if(strcmp(line, opcodes[i].name )==0)
      break;
  
  return(opcodes[i].code);
}

int numOfTokens(char *tok)
{
  int count = 0;
  /* walk through other tokens */
  while (tok != NULL)
  {
    count++;
    tok = strtok(NULL, ARGUMENT_SEPARATOR);
  }
  return count;
}

bool checkNumbers(char *line)
{
  int count = 0;
  if (line[START_OF_LINE] == COMMA)
  {
    alertError(ER_DATA_BEGINS_WITH_COMMA);
    return false;
  }
  if (!isdigit(line[strlen(line) - 1]))
  {
    alertError(ER_DATA_ENDS_WITHOUT_NUMBER);
    return false;
  }
  line = strtok(line, ARGUMENT_SEPARATOR);
  while ((line = strtok(NULL, ARGUMENT_SEPARATOR)))
    count++;

  DC += count;
  return true;
}

bool checkString(char *line)
{
  char *temp = strtok(line, "\"");
  if (strcmp(line, temp) == 0)
  {
    alertError(ER_STRING_WITHOUT_QUOTES);
    return false;
  }

  DC += strlen(line) - 1;
  return true;
}

bool checkStruct(char *line)
{
  line = strtok(NULL, ARGUMENT_SEPARATOR);
  DC += strlen(line);
  return true;
}

/**
 The method recieves an integer number and converts it into binary and returns the binary number as a String.
  input params:
  @num: the number that will be converted to binary.
  returns
  @res: the string which is the binary number.
*/

char *convert_decimal_Binary(long num)
{

  long c, k;         /*Initializing variables to find the correct binary digit*/
  char *res, chTwo; /*Initializing the String which will contain the binary number*/

  /*Initializing the charachters for creating the binary number*/
  char chOne = '1';
  int i = 0; /*Counter for identifying if it is the first binary digit*/
  res = NULL;

  /*For loop to find the proper binary digit*/
  for (c = 31; c >= 0; c--)
  {
    /*Locating proper binary digit*/
    k = num >> c;
    /*Checking if first binary digit*/
    if (i == 0)
    {
      /*Checking what is the proper binary digit*/
      if (k & 1)
      {
        strcpy(res,"1");
      }
      else
      {
        strcpy(res,"0");
      }

      i = 1; /*Updating that first binary digit had been found*/
    }
    /*If this is not the first binary digit*/
    else
    {
      /*Checking what is the proper binary digit*/
      if (k & 1)
      {
        strncat(res, &chOne, 1); /*Adding the binary digit to the binary number*/
      }
      else
      {
        strncat(res, &chTwo, 1); /*Adding the binary digit to the binary number*/
      }
    }
  }           /*End of for loop*/
  return res; /*Return the binary number*/
}

/** The method will recieve a string representing all digits for the bin number and will return according
to memory location.
input param:
@str: the original number in binary form
returns:
@res: the string representing the "chopped" location in the memory


char *chop_string_for_address(char str[])
{
  char res[5]; Initializing the returned string
  creating the string
  res[0] = str[28];
  res[1] = str[29];
  res[2] = str[30];
  res[3] = str[31];
  res[4] = '\0';
  return res; return the desired address
}*/
