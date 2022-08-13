#ifndef FIRSTPASS_H
#define FIRSTPASS_H
#include "global.h"
#include "secondpass.h"
#include <stdbool.h>
/*
Description: Run the first pass on the expanded file
*/

/**
 * @brief Run the firstpass on the expanded file.
 * 
 * @param filename The filename + extension to be opened.
 */
void firstpass(char *filename);

/**
 * @brief Updated the data address number
 * 
 * @param head The beginning of the Symbol list.
 */
void updateData(Symbol *head);

#endif