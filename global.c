#include "global.h"

char * checklabel(char * label)
{
    if(strlen(label)> MAX_LABLE_LENGTH)
        /*Add error*/
        return NULL;
    
    if(ilegalLabelName())
        /*Add error*/
        return NULL;

}


char *isLabel(char *line)
{
    char *temp = strok(line, ":");
    if(temp != NULL)
        return checklabel(temp);

    return NULL;
}

bool isEmptyLine(const char *line)
{
  while (*line) {
    if (!isspace(*line))
      return false;
    line++;
  }
  return true;
}

bool isComment(const char *line)
{
    return line[0] == ';' ? true : false;
}
