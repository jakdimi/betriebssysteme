#include <stdio.h>
#include <stdlib.h> 
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

int printSteffen()
{
  FILE *fileptr;
  char c;
  char filename[] = "banner.txt";
  int delay = 50;
  fileptr = fopen(filename, "r");
  if (fileptr == NULL)
  {
    printf("Cannot open file \n");
    exit(0);
  }
  // Read contents from file
  c = fgetc(fileptr);
  while (c != EOF)
  {
    printf ("%c", c);
    #ifdef _WIN32
    Sleep(delay);
    #else
    usleep(delay);
    #endif
    c = fgetc(fileptr);
  }
  
  fclose(fileptr);
  return 0;
}

int main()
{
  while(1)
  {
    printSteffen();
  }
}
