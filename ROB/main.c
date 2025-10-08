#include "HEADERS/funky.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

FILE* fptr = NULL;

int main(int argc, char* argv[]) {

  char* name = argv[2];
  
  if (argc < 2 || strcmp(argv[1], "--help") == 0) { 
    if (argc < 2) {printf("Error: Too few arguments.\n");} // if the only argument is ./ROB, then return Error
    fn_help(); // print help 
    return 1;
  }

  if (strcmp(argv[1], "-n") == 0 || strcmp(argv[1], "-new") == 0) {

    fptr = createFile_b(argv[2]);  // try to create the desired file 
    if (fptr == NULL) {
      printf("Error: Failed to create %s \n", name);  // return error if file failed to create
      return 102;
    }

    bool header_written = writeWavHeaders(name); // writes the header files to 'name'
    if (header_written == false) {
      printf("Failed to write the WAV header to %s \n", name);
      return 102;
    }
  }
  
  if (strcmp(argv[1], "-o") == 0 || strcmp(argv[1], "-open") == 0) {
    
    fptr = readFile_b(name);  // try to read the desired file
    if (fptr == NULL) {
      printf("Error: Failed to read %s \n", name);  // return error if failed to read the file
      printf("File likely does not exist");
      return 103;
    }
  }

  bool is_wav = checkFileType(name);
  if (!is_wav) {
    printf("Error: file is not of WAV format. \n");
    return 104;
  }

  if (strcmp(argv[1], "-n") == 0 || strcmp(argv[1], "-new") == 0) {
    audioFormat format;
    format.compression = 1; // no compression 
    
    format.chanels = getIntInput("How many audio chanels? (1 is Mono, 2 is stereo)\n");
    format.sampleRate = getIntInput("What is the sample rate?\n");
    format.bitsPerSample = getIntInput("How many bits per sample? (8 or 16 is recomended)\n");

    format.byteRate = format.sampleRate * format.chanels * format.bitsPerSample / 8; 
    format.blockAlign = format.chanels * format.bitsPerSample / 8;
 
    bool waf_succeed = writeAudioFormat(format, name);      // write data in 'format' to the file 
    if (false == waf_succeed) {
      printf("Error: failed to write the format to file\n");   // print and return if error
      return 102;
    }
  }

  //            TODO:
  //  Diffrent tags for notes, and diration
  //  EX: -A# -S 5

  fclose(fptr);   // close the file aftr use 
  return 0;
}
