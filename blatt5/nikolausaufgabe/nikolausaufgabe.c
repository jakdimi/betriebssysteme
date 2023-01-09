#include <stdio.h>
#include <stdlib.h> 

int main()
{
  FILE *fileptr;
  char c;
  char filename[] = "banner.txt";
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
    c = fgetc(fileptr);
  }
  
  fclose(fileptr);
  return 0;
}