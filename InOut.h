#ifndef INOUT_H
#define INOUT_H
#include <string.h>



char *read_line();
char *fread_line();

int readint(int *a);
char* readword(char* s, int* position);
int readPositive(int *a);
int* readArray(int n);
int* readArray(int n);
int FilenameIsValid(char* name);

void printArray(int* arr, int n);
void printArrayFloat(float* arr, int n);
void printText(char* text);
void printInteger(int a);


#endif