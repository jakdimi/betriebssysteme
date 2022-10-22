/*
 * main.c
 *
 * Author: Alexander Ploss <a.ploss@uni-muenster.de>
 *         Michel Steuwer <michel.steuwer@uni-muenster.de>
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>

// Verwendet monitoring_alloc.
#include "monitoring_alloc.h"

// Verwendet leaking_function.
#include "leaking_program.h"


// Hauptprogramm. Hier: Keine Argumente für Programm.
int main(void) {
  int error;
  // Ungültige Zeiger sollten immer auf NULL gesetzt werden.
  char *answer    = NULL;
  char *foo       = NULL;
  char *bar       = NULL;
  char *allocated = NULL;

  // Um die monitoring_alloc Funktionalität zu nutzen, muss man zunächst die
  // Bibliothek mit der init Funktion initialisieren.
  init_monitoring_alloc();


  // Nachfolgend steht ein Programmteil der die dynamische Speicherverwaltung
  // der monitoring_alloc Bibliothek nutzt.
  // Durch die Verwendung der monitoring_alloc_malloc und monitoring_alloc_free
  // Funktionen kann die dynamische Speicherbelegung auf Fehler untersucht
  // werden.

  // Speicher dynamisch anlegen.
  foo = (char*) monitoring_alloc_malloc(23);
  bar = (char*) monitoring_alloc_malloc(5);
  bar[0] = 11; bar[1] = 22; bar[2] = 33; bar[3] = 44; bar[4] = 55;

  allocated = leaking_function(foo, foo+23);

  // Nicht mehr benötigten Speicher wieder freigeben.
  // Zeiger wird dadurch ungültig, sollte also auf NULL gesetzt werden.
  if(allocated) { 
      monitoring_alloc_free(allocated);
      allocated = NULL;
  }

  allocated = leaking_function(bar, bar+5);
  if(allocated) { 
      monitoring_alloc_free(allocated);
      allocated = NULL;
  }

  if(bar) { 
      monitoring_alloc_free(bar);
      bar = NULL;
  }

  allocated = leaking_function(foo, foo+23);
  if(allocated) { 
      monitoring_alloc_free(allocated);
      allocated = NULL;
  }

  answer = (char*) monitoring_alloc_malloc(42);
  allocated = leaking_function(answer, answer+42);
  if(allocated) { 
      monitoring_alloc_free(allocated);
      allocated = NULL;
  }
  if(answer) { 
      monitoring_alloc_free(answer);
      answer = NULL;
  }

  // Nach Beendigung des eigentlichen Programms wird die shutdown Funktion der
  // Bibliothek aufgerufen. Diese räumt die Datenstrukturen der Bibliothek auf
  // und überprüft die Verwendung der Speicherverwaltung auf Fehler.
  error = shutdown_monitoring_alloc();

  return error;
}

