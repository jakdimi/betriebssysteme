/*
 * leaking_program.c
 *
 * Author: Alexander Ploss <a.ploss@uni-muenster.de>
 *         Michel Steuwer <michel.steuwer@uni-muenster.de>
 */

#include "leaking_program.h"

// Verwendet monitoring_alloc.
#include "monitoring_alloc.h"

/* 
 * Funktion arbeitet auf übergebenem Speicherbereich und belegt dynamisch neuen
 * Speicher.
 */
char* leaking_function(char* first, char* last) {
  char *allocated = NULL;
  char *ptr = first;
  if(ptr) {
    while(ptr != last) {
      if(*ptr) {
        allocated = (char*) monitoring_alloc_malloc(
            (*ptr)*sizeof(char) );
      } 
      ++ptr;
    }
  }
  return allocated;
}


