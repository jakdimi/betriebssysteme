/*
 * leaking_program.h
 *
 * Author: Alexander Ploss <a.ploss@uni-muenster.de>
 *         Michel Steuwer <michel.steuwer@uni-muenster.de>
 */

#ifndef LEAKING_PROGRAM_H
#define LEAKING_PROGRAM_H

#include <stdlib.h>

/* 
 * Funktion die auf einem übergebenen Speicherbereich arbeitet. Diese Funktion
 * benutzt evtl. selbst dynamisch reservierten Speicher. 
 */
char* leaking_function(char* first, char* last);

#endif

