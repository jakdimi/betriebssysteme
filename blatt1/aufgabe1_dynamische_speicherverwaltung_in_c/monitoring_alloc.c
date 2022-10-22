/*
 * monitoring_alloc.c
 *
 * Author: Alexander Ploss <a.ploss@uni-muenster.de>
 *         Michel Steuwer <michel.steuwer@uni-muenster.de>
 *
 */

// Header einbinden.
#include "monitoring_alloc.h"

// Datenstrukturen verwendet von den monitoring_alloc Funktionen.
AllocatedMemoryBlock allocated_blocks[MAX_ALLOCATIONS];

// Schreiben Sie hier ihre Implementierung für Aufgabenteil a).

void init_monitoring_alloc() {
}

int shutdown_monitoring_alloc() {
  int leakingBytes = 0;

  printf("ERROR: Leaking %lu bytes in total!\n",
      (unsigned long)leakingBytes);
  return leakingBytes;
}

void *monitoring_alloc_malloc(size_t size) {
  void *allocated = NULL;

  if(!allocated) {
    printf("ERROR: Block of size %lu could not be allocated!\n",
        (unsigned long)size);
  }
  return allocated;
}

void monitoring_alloc_free(void *ptr) {
  int found = 0;

  if(!found) {
    printf("ERROR: Block %p not allocated!\n", ptr);
  }
}

