#include "firstpass.h"
extern int IC, DC;

void firstpass(char *filename)
{
    IC = DC = 0;
    /*read next line from file*/
        /*it is label?*/
            /*flag that it is a label*/

        /*check if .data? .string? .struct? */
            /*if label flaged*/
                /*insert to symbol list with data flag with DC value (if exist error)*/
                /*continue */

        /*if .extern? .entry? */
            /* if extern*/
                /*insert to symbol list*/

        /* if flag is label */
            /*Insert to symbol list as IC error if already exist*/
            /* check instruction, if not exist, add error.
            /*check operands and count them*/
            /*build binary code of the instruction*/
            /* IC --> IC +L */

    /* Finished reading the file*/                



    /*if got errors
        , stop.
    
    update symbol list data adding the right IC*/
    /*Start second pass*/
    
}