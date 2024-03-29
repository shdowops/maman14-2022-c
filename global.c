#include "global.h"

/*Initiazling arrays of charachters for use of pre-defined language*/
char *Registers[NUM_OF_REGISTERS] = {"r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7"};
char *Keywords[NUM_OF_KEYWORDS] = {"mov", "cmp", "add", "sub", "not", "clr", "lea", "inc", "dec", "jmp", "bne", "get", "prn", "jsr", "rts", "hlt",
                                   ".data", ".string", ".extern", ".entry", ".struct"};
char *TwoOperandCmd[] = {"mov", "cmp", "add", "sub", "lea"};
char *SingleOperandCmd[] = {"not", "clr", "inc", "dec", "jmp", "bne", "get", "prn", "jsr"};
char *NoOperandCmd[] = {"rts", "hlt"};

/*Ready made array of opcodes based on language dfeinition*/
opcode opcodes[OPCODE_AMOUNT] = {
    {0, "mov", "0000"},
    {1, "cmp", "0001"},
    {2, "add", "0010"},
    {3, "sub", "0011"},
    {4, "not", "0100"},
    {5, "clr", "0101"},
    {6, "lea", "0110"},
    {7, "inc", "0111"},
    {8, "dec", "1000"},
    {9, "jmp", "1001"},
    {10, "bne", "1010"},
    {11, "get", "1011"},
    {12, "prn", "1100"},
    {13, "jsr", "1101"},
    {14, "rts", "1110"},
    {15, "hlt", "1111"}};

/*initializing global filename*/
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
  /*saving the label after it was approved*/
  if (labeltosave)
    strcpy(labeltosave, labeltocheck);
  return true;
}

bool isLabel(char *line, char *label)
{
  char *secondpart;
  char *temp = (char *)malloc(strlen(line));
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

  for (i = strlen(line) - 1; (isspace(line[i])); i--) /*skip right whitespaces*/
    ;
  line[i + 1] = '\0';
  return line;
}

bool isEntry(char *line)
{
  return strstr(line, ENTRY);
}

bool isExtern(char *line)
{
  return strstr(line, EXTERN);
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
    if (strcmp(line, Keywords[i]) == 0) /*checking if the line matching a keyword*/
      return true;
  return false;
}

bool isRegister(char *line)
{
  int i;
  for (i = 0; i < NUM_OF_REGISTERS; i++)
    if (strcmp(line, Registers[i]) == 0) /*checking if the current register matches the String*/
      return true;
  return false;
}

bool isStruct(char *line)
{
  char *token;
  char *temp = malloc(strlen(line));
  strcpy(temp, line);

  /*Dividing the line into parts according to struct syntax*/
  token = strtok(temp, SEPARATOR);
  token = strtok(NULL, SEPARATOR);
  if (!token)
  {
    free(temp);
    return false;
  }

  if (*token != STURCT_FIRST_ARG && *token != STRUCT_SECOND_ARG) /*Checking that struct is valid*/
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
  char *temp = malloc(strlen(line));
  strcpy(temp, line);
  /*Dividing the line into parts according to number syntax*/
  token = strtok(temp, NUMBERSTART);

  if (strcmp(token, temp) == 0) /*If number indicator does not exist*/
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

bool check_opcode(char *line, int *type, char **binarydata)
{
  char *token;
  line = strtok(line, ARGUMENT_SEPARATOR); /*get instruction */
  *binarydata = (char *)malloc(BINARY_LENGTH);
  memset(*binarydata, 0, BINARY_LENGTH);
  strcat(*binarydata, getopcode(line));     /*save instruction binary code */
  line = strtok(NULL, ARGUMENT_SEPARATOR);  /*get first argument */
  token = strtok(NULL, ARGUMENT_SEPARATOR); /*get second argument */
  if (*type == TWO_OPERANDS)                /*if command is of two operand type*/
  {
    if (!checkoperand(line, binarydata)) /*Check first operand*/
    {
      alertError(ER_SOURCE_OPERAND);
      return false;
    }
    if (!checkoperand(token, binarydata)) /*Check second operand and update binary text*/
    {
      alertError(ER_DESTINATION_OPERAND);
      return false;
    }
    if (isRegister(line) && isRegister(token)) /* if both operand register, remove line count */
      IC--;
  }
  else if (*type == ONE_OPERAND)
  {
    strcat(*binarydata, "00"); /*No source operand*/
    if (line && !checkoperand(line, binarydata))
    {
      alertError(ER_OPERANDS_OVERFLOW_IN_COMMAND);
      return false;
    }
  }
  else /* No operands command*/
  {
    if (line != NULL)
    {
      alertError(ER_OPERANDS_OVERFLOW_IN_COMMAND);
      return false;
    }
    strcat(*binarydata, "0000");
  }

  return true;
}

bool checkoperand(char *operand, char **binarydata)
{
  if (!operand) /*Checking if operand is not empty*/
    return false;

  if (isRegister(operand)) /*checking if the operand is a register*/
  {
    strcat(*binarydata, "11");
    IC++;
    return true;
  }
  if (isStruct(operand)) /*checking if the operand is a struct*/
  {
    strcat(*binarydata, "10");
    IC += 2;
    return true;
  }
  if (isNumber(operand)) /*checking if the operand is a number*/
  {
    strcat(*binarydata, "00");
    IC++;
    return true;
  }
  if (check_label(operand, NULL)) /*checking if the operand is a label*/
  {
    strcat(*binarydata, "01");
    IC++;
    return true;
  }
  /*If the operand type is not found until now, the operand that is being checked is not valid*/
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
  /*If the command is not found in pre defined language requirements*/
  alertError(ER_OPCODE_ILLEGAL);
  return false;
}

char *getopcode(char *line)
{
  int i;
  for (i = 0; i < OPCODE_AMOUNT; i++)
    if (strcmp(line, opcodes[i].name) == 0)
      break;

  return (opcodes[i].code);
}

bool checkNumbers(char *line, char **binarydata)
{
  int count = 0;
  long currentnumber = 0;
  char *tempbinarydata = (char *)malloc(BINARY_LENGTH);
  memset(tempbinarydata, 0, BINARY_LENGTH);
  /*checking if the numbers in the data are legal*/
  if (line[START_OF_LINE] == COMMA) /*Data begins with a comma*/
  {
    free(tempbinarydata);
    alertError(ER_DATA_BEGINS_WITH_COMMA);
    return false;
  }
  if (!isdigit(line[strlen(line) - 1])) /*Data ends without a number*/
  {
    free(tempbinarydata);
    alertError(ER_DATA_ENDS_WITHOUT_NUMBER);
    return false;
  }
  line = strtok(line, ARGUMENT_SEPARATOR);

  for (; line; line = strtok(NULL, ARGUMENT_SEPARATOR))
  {
    currentnumber = atol(line);
    /*checking number in range*/
    if (strstr(line, SEPARATOR) || currentnumber < MIN_NUMBER || currentnumber > MAX_NUMBER)
    {
      alertError(ER_NUM_OUT_OF_RANGE);
      return false;
    }
    strcat(tempbinarydata, convert_decimal_binary(currentnumber));
    strcat(tempbinarydata, "\n");
    tempbinarydata = (char *)realloc(tempbinarydata, strlen(tempbinarydata) + BINARY_LENGTH + 1);
    count++;
  }
  DC += count;
  *binarydata = tempbinarydata;
  return true;
}

bool checkString(char *line, char **binarydata)
{
  char *temp = strtok(line, STRUCT_STRING_START);
  if (strcmp(line, temp) == 0)
  {
    alertError(ER_STRING_WITHOUT_QUOTES);
    return false;
  }

  *binarydata = (char *)malloc(BINARY_LENGTH);
  memset(*binarydata, 0, BINARY_LENGTH);
  DC += strlen(temp) + 1;

  while (*temp != '\0')
  {
    /*translate charachter into binary*/
    strcat(*binarydata, convert_decimal_binary(*temp));
    strcat(*binarydata, "\n");
    *binarydata = (char *)realloc(*binarydata, (sizeof(char) * strlen(*binarydata)) + BINARY_LENGTH + 1);
    temp++;
  }
  *binarydata = (char *)realloc(*binarydata, (sizeof(char) * strlen(*binarydata)) + BINARY_LENGTH + 1);
  strcat(*binarydata, NULL_TERMINATION);
  return true;
}

bool checkStruct(char *line, char **binarydata)
{
  char *number, *text;
  char *temp = (char *)malloc(strlen(line));
  strcpy(temp, line);
  line = strtok(NULL, ARGUMENT_SEPARATOR); /*Get struct name */
  temp = strtok(temp, ARGUMENT_SEPARATOR); /*Get struct field */
  if (checkNumbers(temp, &number))
    if (checkString(line, &text))
    {
      *binarydata = (char *)malloc(strlen(number) + strlen(text));
      memset(*binarydata, 0, strlen(number) + strlen(text));
      strcat(*binarydata, number);
      strcat(*binarydata, text);
      return true;
    }

  alertError(ER_NON_VALID_STRUCT);
  return false;
}

char *convert_decimal_binary(long num)
{
  int currentbit, digit, i;
  char *result;
  i = 0;
  result = (char *)malloc(BINARY_LENGTH);

  if (result == NULL)
    alertError(ER_MEMORY_ALLOCATION);

  for (currentbit = BINARY_LENGTH - 2; currentbit >= 0; currentbit--)
  {
    digit = num >> currentbit;
    if (digit & 1)
      *(result + i) = 1 + '0';
    else
      *(result + i) = 0 + '0';
    i++;
  }
  strcat(result, ABSOLUTE);
  *(result + i) = '\0';
  return result;
}
