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
