#pragma once

///////////////////////////////////////////////////////////////////////////
//Llibreria grafica
#include "lib/libreria.h"
///////////////////////////////////////////////////////////////////////////

#include <conio.h>      /* getch */ 
#include <stdio.h>      /* printf */
#include <time.h>       /* time */
#include <stdlib.h>

int aleatori(int min, int max, int pas);

void joc();
void joc(char x);
void getPosMatrix(int x, int y, int(&fila), int(&columna));

/*----- END --------------*/