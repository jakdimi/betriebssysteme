/*
 * monitoring_alloc.h
 *
 * Author: Alexander Ploss <a.ploss@uni-muenster.de>
 *         Michel Steuwer <michel.steuwer@uni-muenster.de>
 */

#ifndef MONITORING_MALLOC_H
#define MONITORING_MALLOC_H

#include "stdio.h"
#include "string.h"
#include "malloc.h"

#define MAX_ALLOCATIONS (32)
#define MAX_TOTAL_ALLOCATION_SIZE (1024)

/*
 * Die Struktur AllocatedMemoryBlock beinhaltet Informationen über einen
 * belegten Speicherblock.
 */
typedef struct {
  void *  frame;    // Zeiger auf den Begin des Speicherblocks
  size_t  size;     // Größe des belegten Speicherblocks
  size_t  ordinal;  // Laufende Nummer der Vergabe
} AllocatedMemoryBlock;


/* 
 * Initialisiert Speicherverwaltung. 
 *
 * Benötigte Datenstrukturen zur Verwendung in monitoring_alloc_malloc und
 * monitoring_alloc_free initialisieren.
 *
 */
void init_monitoring_alloc();

/* 
 * Beendet Speicherverwaltung und prüft Freigaben. 
 *
 * Wird nach Beendigung des Programms aufgerufen, um dynamische
 * Speicherverwaltung zu überprüfen.  
 * Datenstrukturen aufräumen, verbliebenen Speicher wieder freigeben.
 * Die Größe von nicht freigegebenen Speicher in Byte wird zurückgegeben.
 */
int shutdown_monitoring_alloc();

/* 
 * monitoring_alloc_malloc reserviert Speicherblock der Größe size und liefert
 * einen Zeiger auf den Beginn des Blocks zurück. Im Falle eines Fehler wird
 * ein NULL-Zeiger zurückgegeben.
 *
 * Verwenden Sie malloc um den Speicherblock anzulegen und verwalten Sie die
 * nötigen Informationen mittels der Struktur AllocatedMemoryBlock.
 */
void * monitoring_alloc_malloc( size_t size );

/* 
 * monitoring_alloc_free gibt den übergebenen Speicherblock wieder frei. 
 *
 * Prüfen Sie ob der Speicherblock mittels monitoring_alloc_malloc angelegt
 * wurde. Verwenden sie free um den Speicherbereich wieder freizugeben.
 * Tragen Sie die verwaltungsinformationen wieder aus (AllocatedMemoryBlock).
 * 
 */ 
void monitoring_alloc_free( void * );

#endif

