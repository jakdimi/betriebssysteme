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
  for (int i = 0; i < MAX_ALLOCATIONS; i++) {
    allocated_blocks[i].frame = NULL;
    allocated_blocks[i].size = 0;
    allocated_blocks[i].ordinal = i;
  }
}

int shutdown_monitoring_alloc() {
  int leakingBytes = 0;
  int count = 0;

  for (int i = 0; i < MAX_ALLOCATIONS; i++) {
    if (allocated_blocks[i].frame) {
      count++;
      leakingBytes += allocated_blocks[i].size;
    }
  }

  printf("ERROR: Leaking %lu bytes in %d blocks!\n",
      (unsigned long)leakingBytes, count);
  return leakingBytes;
}

void *monitoring_alloc_malloc(size_t size) {
  void *allocated = NULL;

  for (int i = 0; i < MAX_ALLOCATIONS; i++) {
    if (!allocated_blocks[i].frame) {
      allocated_blocks[i].frame = malloc(size);
      allocated_blocks[i].size = size;
      allocated = allocated_blocks[i].frame;
      break;
    }
  }
  printf("allcoated %ld bites \n", size);
  printf("Allocated: %p\n", allocated);
  if(!allocated) {
    printf("ERROR: Block of size %lu could not be allocated!\n",
        (unsigned long)size);
  }
  return allocated;
}

void monitoring_alloc_free(void *ptr) {
  int found = 0;

  for (int i = 0; i < MAX_ALLOCATIONS; i++) {
    if (allocated_blocks[i].frame == ptr) {
      found++;
      free(ptr);
      allocated_blocks[i].frame = NULL;
      allocated_blocks[i].size = 0;
    }
  }

  if(!found) {
    printf("ERROR: Block %p not allocated!\n", ptr);
  }
}

