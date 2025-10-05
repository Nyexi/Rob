#include "HEADERS/funky.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

FILE* fptr = NULL;

int main(int argc, char* argv[]) {
  

  if (argc < 2 || strcmp(argv[1], "--help") == 0) { 
    if (argc < 2) {printf("Error: Too few arguments.\n");} // if the only argument is ./ROB, then return Error
    fn_help(); // print help 
    return 1;
  }

  if (strcmp(argv[1], "-n") == 0 || strcmp(argv[1], "-new") == 0) {

    fptr = createFile_b(argv[2]);  // try to create the desired file 
    if (fptr == NULL) {
      printf("Error: Faild to create %s \n", argv[2]);  // return error if file failed to create
      return 102;
    }
  }
  
  if (strcmp(argv[1], "-o") == 0 || strcmp(argv[1], "-open") == 0) {
    
    fptr = readFile_b(argv[2]);  // try to read the desired file
    if (fptr == NULL) {
      printf("Error: Faild to read %s \n", argv[2]);  // return error if failed to read the file
      printf("File likely does not exist");
      return 103;
    }
  }

  // TODO:
  //Add funct to write bytes to file

  int wave = 0;

  scanf("%x", &wave);


  fclose(fptr);   // close the file aftr use 
  return 0;
}
