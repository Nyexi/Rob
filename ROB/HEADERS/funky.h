#ifndef FUNKY_H
#define FUNKY_H


#include <stdbool.h>  // for bool values
#include <stdio.h>    // include to define FILE type
#include <stdint.h>   // for specific bit with ints
                    
/* This struct holds the audio format information 
 * For more information please look at --
 * http://soundfile.sapp.org/doc/WaveFormat/
 * i found it very usfull. --Nyexi */
typedef struct {
  uint16_t compression;             // valuse other than 1 mean some sort of compression
  uint16_t chanels;         // number of audio chanels, 1 mono, 2 stereo--
  uint32_t sampleRate;      // think of this like quality, kinda...
  uint32_t byteRate;        // SampleRate * NumChannels * BitsPerSample/8
  uint16_t bitsPerSample;   // 8 bits = 8, 16 bits = 16, etc.
  uint16_t blockAlign;      // NumChannels * BitsPerSample / 8
} audioFormat ;

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

/* Writes the data stored in the audioFormat struct
 * to the file specified by 'fname'
 * Returns false if failed at some point 
 * and Returns true if it succeded */
bool writeAudioFormat(audioFormat fmt, char* fname);

/* Take a message from the user
 * prints it, and loops until 
 * input does not contain a char.
 * TODO: make input validation better..*/
int getIntInput(char msg[]);

#endif
