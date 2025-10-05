#ifndef FUNKY_H
#define FUNKY_H


#include <stdbool.h>  // for bool values
#include <stdio.h>    // include to define FILE type
                    

/*prints the commands*/
void fn_help(void);  


/* Returns a FILE pointer to file named 'name'
 * name is the name of the file,it is assumed
 * that the file extention is included in the name 
 * Returns NULL if the file named 'name' alredy exists
 * the _b funct is to open in binary mode*/
FILE* createFile(char* name);
FILE* createFile_b(char* name);


/* Returns a FILE pointer to file named 'name'
 * name is the name of the file,it is assumed
 * that the file extention is included in the name 
 * Returns NULL if the file named 'name' does not exist
 * the _b funct is to open in binary mode */
FILE* readFile(char* name);
FILE* readFile_b(char* name);


/* takes the name, opens the file in read mode
 * then reads the first 16 bytes to confirm if 
 * the file is WAV, Returns false if not or if error
 * Returns true if it is a WAV file */
bool checkFileType(char* name);


/* Writes the requierd bytes to the file named
 * name, to make it's header a WAV file */
bool writeWavHeaders(char* name);



#endif
