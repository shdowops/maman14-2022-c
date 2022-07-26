#include "global.h"

bool isLabel(char *line)
{
  char *temp = (char *)malloc(sizeof(char) * strlen(line));
  strcpy(temp, line);
  temp = strtok(temp, ":");
  if (strcmp(line, temp) == 0)
    return false;

  return true;
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
  return (line[START_OF_LINE] == ';' || line == NULL) ? true : false;
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
  if(strstr(line, ENTRY))
    return true;
  return false;
}

bool isExtern(char *line)
{
  if(strstr(line,EXTERN))
    return true;
  return false;
}

bool isDataSymbol(char *line)
{
  if(strstr(line, DATA) || strstr(line, STRING) || strstr(line, STRUCT))
    return true;
  return false;
}




/**
 The method recieves an integer number and converts it into binary and returns the binary number as a String.
  input params:
  @num: the number that will be converted to binary.
  returns
  @res: the string which is the binary number.
*/

char convert_decimal_Binary(int num)
{
  
  int c, k;/*Initializing variables to find the correct binary digit*/
  char res;/* Initializing the String which will contain the binary number*/
  /*Initializing the charachters for creating the binary number*/
  char chOne ='1';
  char chZero = '0';
  
  int i=0;/*Counter for identifying if it is the first binary digit*/

  /*For loop to find the proper binary digit*/
  for (c = 31; c >= 0; c--)
  {
    /*Locating proper binary digit*/
    k = num >> c;
    /*Checking if first binary digit*/
    if(i=0)
    {
        /*Checking what is the proper binary digit*/
        if (k & 1)
        {
           res='1';
        }
        else
        {
           res='0';
        }
        
      i=1;/*Updating that first binary digit had been found*/
    }
    /*If this is not the first binary digit*/
    else
    {
      /*Checking what is the proper binary digit*/
      if (k & 1)
      {
        strncat(res, &chOne, 1);/*Adding the binary digit to the binary number*/
      }
      else
        {strncat(res, &chTwo, 1);/*Adding the binary digit to the binary number*/
      }
     }
  }/*End of for loop*/
  return res; /*Return the binary number*/
}



char chop_string(char str, int last, int first, int num)
{!!!!!!!!!!!!!!!
  char res[1];
  /*Checking if needing the characters at the end*/
  if(first=0)
  {

  }



}