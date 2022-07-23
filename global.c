#include "global.h"

char *checklabel(char *label)
{
  if (strlen(label) > MAX_LABLE_LENGTH)
    /*Add error*/
    return NULL;

  /* if(ilegalLabelName())
       Add error
       return NULL;*/
  return NULL;
}

char *isLabel(char *line)
{
  char *temp = (char *)malloc(sizeof(char) * strlen(line));
  strcpy(temp, line);
  temp = strtok(temp, ":");
  if (strcmp(line, temp) == 0)
    return false;
  if((temp = strtok(NULL,":")) != NULL )
    /*Add error for double : in label.*/

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