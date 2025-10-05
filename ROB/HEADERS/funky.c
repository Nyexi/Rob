#include "funky.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// Displays the diffrent commands 
// And overall how to use the program
void fn_help(void) {

  printf("Creating a new file.\n");
  printf("./ROB -n name.wav\n");
  printf("\n");
  printf("Open file\n");
  printf("./ROB -o name.wav\n");

}


//              TODO:   
//  finish the checkFileType function
bool checkFileType(char* name) {
  
  bool is_wave = false;

  FILE* fptr = readFile_b(name);  // read the bytes of the file
  if (fptr == NULL) {
    return false;
  }

  unsigned char buff[12]; // set a buffer to hold the first 12 byes of the file
  size_t bread= fread(buff, 1, sizeof(buff), fptr);
  if (bread < sizeof(buff)) {
    return false;         // if bytes read is smaller than the buffer, return false, as there is no file header
  }

  if (buff[0] == 0x52 && buff[1] == 0x49 && buff[2] == 0x46 && buff[3] == 0x46) {
    is_wave = true;       // check if the first bytes say RIFF
  } else {return false;}  // return false if is not RIFF 

  if (buff[8] == 0x57 && buff[9] == 0x41 && buff[10] == 0x56 && buff[11] == 0x45) { 
    is_wave = true;       // check if the first bytes say WAVE 
  } else {return false;}  // return false if is not WAVE 

  return is_wave;
}

// creates a file 
FILE* createFile(char* name) {

  FILE* fptr = NULL;  // init a File pointer 
  
  fptr = fopen(name, "r");
  if (fptr != NULL) {
    printf("Error: File '%s' alredy exists.\n", name);
    fptr = NULL;  // if FILE 'name; alredy exists,
    return fptr;  // NULL set fptr to NULL and return
  }
    
  fptr = fopen(name, "w");
  if (fptr == NULL)
  {
    printf("Error: Failed to create and open %s", name);
    return fptr; // if fptr is NULL return error
  } 

  return fptr;  //if no errors, return pointer to file
}

// creates a file, and opens in binary mode
FILE* createFile_b(char* name) {

  FILE* fptr = NULL;  // init a File pointer 
  
  fptr = fopen(name, "rb");
  if (fptr != NULL) {
    printf("Error: File '%s' alredy exists.\n", name);
    fptr = NULL;  // if FILE 'name; alredy exists,
    return fptr;  // NULL set fptr to NULL and return
  }
    
  fptr = fopen(name, "wb");
  if (fptr == NULL)
  {
    printf("Error: Failed to create and open %s", name);
    return fptr; // if fptr is NULL return error
  } 

  return fptr;  //if no errors, return pointer to file
}

FILE* readFile(char* name) {
  FILE* fptr = NULL;

  fptr = fopen(name, "r");
  if (fptr == NULL) {
    printf("Error: File '%s' does not exist.\n", name);
    return fptr;  // NULL set fptr to NULL and return
  }
  return fptr;
}

FILE* readFile_b(char* name) {
  FILE* fptr = NULL;

  fptr = fopen(name, "rb");
  if (fptr == NULL) {
    printf("Error: File '%s' does not exist.\n", name);
    return fptr;  // NULL set fptr to NULL and return
  }
  return fptr;
}
