#include "funky.h"
#include <ctype.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/* This struct holds the audio format information 
 * For more information please look at --
 * http://soundfile.sapp.org/doc/WaveFormat/
 * i found it very usfull. --Nyexi */


/* Displays the diffrent commands 
 * And overall how to use the program */
void fn_help(void) {

  printf("Creating a new file.\n");
  printf("./ROB -n name.wav\n");
  printf("\n");
  printf("Open file\n");
  printf("./ROB -o name.wav\n");

}

/* My dumbass tryed to pass sizeof(arr) as the second argument
 * in fwrite(). I spent an hour trying to figure out the problem(?)
 * i'm tired, please inore the inconsitency here.. --Nyexi :3 */
bool writeWavHeaders(char* name) {
  
  FILE* fptr = fopen(name, "w"); // open file in Write mode to replace any junk with RIFF
  if (fptr == NULL) {
    return false;                // return early if there is no file
  }

  uint8_t riff[4] = {0x52, 0x49, 0x46, 0x46};     // the first chunck
  size_t riff_writen = fwrite(riff, 1, 4, fptr);  // Write RIFF to the first chunk
  if (riff_writen != sizeof(riff)) {
    printf("Error: failed to write RIFF in writeWavHeaders\n");   // if the bytes writen != the num of bytes we want to write, return
    return  false;
  }
  
  fclose(fptr); fptr = NULL;
  fptr = fopen(name, "ab");  // change the file mode to append, to add the rest
  if (fptr == NULL) {
    return false;           // return early if there is no file
  }
  
  uint32_t temp_chunkSize = UINT32_MAX;
  size_t chunkSize_writen = fwrite(&temp_chunkSize, 1, sizeof(uint32_t), fptr);   // Write a temp valuse to the chunkSize
  if (chunkSize_writen != sizeof(uint32_t)) {
    printf("Error: failed to write the chunkSize in writeWavHeaders\n");  // if the bytes writen != the num of bytes we want to write, return
    return false;
  } 

  uint8_t wave[4] = {0x57, 0x41, 0x56, 0x45};     // the first chunck
  size_t wave_writen = fwrite(wave, 1, 4, fptr);  // Write WAVE the third chunk
  if (wave_writen != sizeof(wave)) {
    printf("Error: failed to write WAVE in writeWavHeaders\n");  // if the bytes writen != the num of bytes we want to write, return
    return  false;
  }

  char fmt[4] = {'f', 'm', 't', ' '};                       // the first chunck
  size_t fmt_writen = fwrite(fmt, 1, sizeof(fmt), fptr);    // Write fmt the forth chunk
  if (fmt_writen != sizeof(fmt)) {
    printf("Error: failed to write fmt in writeWavHeaders\n");  // if the bytes writen != the num of bytes we want to write, return
    return  false;
  }
  
  fclose(fptr);
  return true;
}

bool checkFileType(char* name) {
  
  bool is_wave = false;

  FILE* fptr = readFile_b(name);  // read the bytes of the file
  if (fptr == NULL) {
    printf("FAILED ON FILE CHECK\n");
    return false;
  }

  unsigned char buff[16]; // set a buffer to hold the first 12 byes of the file
  size_t bread = fread(buff, 1 ,sizeof(buff) ,fptr);
  if (bread < sizeof(buff)) {
    printf("FAILED ON BUFFER CHECK %zu \n", bread);
    return false;         // if bytes read is smaller than the buffer, return false, as there is no file header
  }

  if (buff[0] == 0x52 && buff[1] == 0x49 && buff[2] == 0x46 && buff[3] == 0x46) {
    is_wave = true;       // check if the bytes say RIFF
  } else {
    printf("FAILED ON RIFF CHECK\n");
    return false;         // return false if is not RIFF 
  } 

  if (buff[8] == 0x57 && buff[9] == 0x41 && buff[10] == 0x56 && buff[11] == 0x45) { 
    is_wave = true;       // check if the bytes say WAVE 
  } else {
    printf("FAILED ON WAVE CHECK\n");
    return false;         // return false if is not WAVE 
  }

  if (buff[12] == 0x66 && buff[13] == 0x6D && buff[14] == 0x74) {
    is_wave = true;       // check if the bytes say fmt 
  } else {
    printf("FAILED ON fmt CHECK\n");
    return false;         // return false if is not fmt 
  }

  fclose(fptr);
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

/* Taks the audioFormat struct, and the name
 * of the file to opern, and writes the 
 * data to the file. return true on sucsessfull
 * completion, and false on failure */
bool writeAudioFormat(audioFormat fmt, char* fname) {
  
  FILE* fptr = fopen(fname, "ab");  // open the file 'fname' to append mode
  if (fptr == NULL) {
    printf("Error: failed to open the file\n");
    return false;                   // error handling if file open fails
  }
  
  uint32_t subChunk = 16; 
  size_t wn_sizeChunk = fwrite(&subChunk, 1, sizeof(uint32_t), fptr);   // write 16 to Subchunk1 Size
  if (wn_sizeChunk < sizeof(uint32_t)){
    printf("Error: Failed on Subchunk1\n");   // if bytes writen is less then disired amount return error
    return false;
  }

  size_t wn_compLevel = fwrite(&fmt.compression, 1, sizeof(uint16_t), fptr);  // write the compression level
  if (wn_compLevel < sizeof(uint16_t)) {
    printf("Error: Failed on compression level\n");   // if bytes writen is less then disired amount return error
    return false;
  }

  size_t wn_chanals = fwrite(&fmt.chanels, 1, sizeof(uint16_t), fptr);  // write the chanels 
  if (wn_chanals < sizeof(uint16_t)) {
    printf("Error: Failed on chanels \n");   // if bytes writen is less then disired amount return error
    return false;
  }
  size_t wn_sampleRate= fwrite(&fmt.sampleRate, 1, sizeof(uint32_t), fptr);  // write the chanels 
  if (wn_sampleRate < sizeof(uint32_t)) {
    printf("Error: Failed on sampleRate\n");   // if bytes writen is less then disired amount return error
    return false;
  } 

  size_t wn_byteRate = fwrite(&fmt.byteRate, 1, sizeof(uint32_t), fptr);  // write the byterate 
  if (wn_byteRate < sizeof(uint32_t)) {
    printf("Error: Failed on byteRate\n");   // if bytes writen is less then disired amount return error
    return false;
  }
  
  size_t wn_blockAlign = fwrite(&fmt.blockAlign, 1, sizeof(uint16_t), fptr);  // write the blockAlign 
  if (wn_blockAlign < sizeof(uint16_t)) {
    printf("Error: Failed on sampleRate\n");   // if bytes writen is less then disired amount return error
    return false;
  }
  size_t wn_BitsPerSample = fwrite(&fmt.bitsPerSample, 1, sizeof(uint16_t), fptr);  // write the bitsPerSample 
  if (wn_BitsPerSample< sizeof(uint16_t)) {
    printf("Error: Failed on sampleRate\n");   // if bytes writen is less then disired amount return error
    return false;
  }

  fclose(fptr);   // free the file pointer before exit
  return true;
}

/* gets input when not char 
 * i'm too lazy to do better input
 * validation at the moment. --Nyexi */
int getIntInput(char msg[]) {
  int n = 0;
  while (n == 0) {
    printf("%s", msg);  // print the message
    scanf("%d", &n);  // store the input in n
  }

  return n;
}

