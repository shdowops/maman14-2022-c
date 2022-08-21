#ifndef SECONDPASS_H
#define SECONDPASS_H
#define SQUARE(x) ((x) * (x))
#include <stdio.h>

#include "global.h"
void secondpass(char *filename);
#endif

/**
 * @brief The method recieves a binary number in a string format and converts it into an integer
 * @param binary a binary number in the formation of a string
 * @return an integer that is a decimal number equal to the original binary number
 */
int binary_converter(char binary[]);

/**
 * @brief The method saves the base32 output to the required files
 * @param ent_fptr - Pointer to entry file
 * @param ext_fptr - Pointer to external file
 * @param obj_fptr - Pointer to object file
 * @param filename - The filename
 */
void save_files(FILE *ent_fptr, FILE *ext_fptr, FILE *obj_fptr, char *filename);

/** The method recieves 2 binary numbers in a string format and converts it into a base 32
 * @param line 2 binary numbers in the formation of a string
 * @param res result storage
 * @return a base 32 number represented with 2 digits
 */
char *translated(char line[], char *res);

/**
 * @brief The method recieves an operand and translates it accordingly into binary language
 * @param firstoperand the operand to translate into binary
 * @param toupdate the symbol that will be updated in the method
 * @return true translation is succesfull false translation is unsuccesfull
 */
bool operand_to_binary(char *firstoperand, Symbol *toupdate);