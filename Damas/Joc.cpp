#include "Joc.h"
#include "Tauler.h"
#include "Partida.h"
#include <iostream>
using namespace std;
void getPosMatrix(int x, int y, int(&fila), int(&columna))
{
	if ((x >= INIPANTALLAX) && (y >= INIPANTALLAY))
	{
		columna = ((x - INIPANTALLAX) / MIDACASELLA);
		fila = ((y - INIPANTALLAY) / MIDACASELLA);
		columna = columna + 1;
		fila = fila + 1;
	}
	else
	{
		columna = 0;
		fila = 0;
	}
	printf("Columna Fila %d %d \n", fila, columna);
}

void joc(char x)
{
	Partida p;
	switch (x)
	{
	case '1':
		joc();
		break;
	case '2':
		break;
	case '3':
		p.fer_moviments();
		break;
	case '4':
	!Keyboard_GetKeyTrg(KEYBOARD_ESCAPE);
	break;
	}

}

void Pintartaulell(int tauler[8][8])
{
	Sprite pecablanca;
	Sprite pecanegra;
	int fila = INIPANTALLAX;
	int columna = INIPANTALLAY;
	
	pecanegra.create("data/fitxa_negra.png");
	pecablanca.create("data/fitxa_blanca.png");
	
	for (int i=0; i < 8; i++)
	{
		for (int j=0; j < 8; j++)
		{
			if (tauler[i][j] == 1)
			{
				pecablanca.draw(j*MIDACASELLA+INIPANTALLAX, i*MIDACASELLA+INIPANTALLAY);
			}
			else
			{
				if (tauler[i][j] == 2)
				{
					pecanegra.draw(j*MIDACASELLA + INIPANTALLAX, i*MIDACASELLA + INIPANTALLAY);
				}
			}
			columna += MIDACASELLA;
		}
		fila += MIDACASELLA;
		columna = INIPANTALLAY;
	}

}
//-----------------------------------------
// joc: porta el control de tot el joc
//-----------------------------------------
void joc()
{
	// ********************************************
	// Inicialització de la part gràfica del joc
	// *******************************************
	//Inicialitza Part grafica
	Screen jocLib(MIDAX, MIDAY);
	Partida p;
	
	// AFEGIR CODI: Definició del grafic del fons
	Sprite fons;
	fons.create("data/tauler.png");

	//Mostrem finestra
	jocLib.show();
	
	
	// AFEGIR CODI: inicialització de la partida
	p.inicialitza();
	
	// Variables d'ajuda per agafar posició ratolí

	int xMouse = 0;
	int yMouse = 0;
	do
	{
		jocLib.processEvents();

		if (Mouse_getButLeft())
		{
			xMouse = Mouse_getX();
			yMouse = Mouse_getY();
		
			p.processaClick(xMouse, yMouse);

			if (p.getclic() == 2)
			{
				p.ferMoviment();
			}		
			p.canviaTorn();
		}

		p.visualitza();
		
		// Actualitza la pantalla
		jocLib.update();
		// ***********************************************************************
		// Sortim del bucle si pressionem ESC
		// ***********************************************************************
	} while (!Keyboard_GetKeyTrg(KEYBOARD_ESCAPE));
}
