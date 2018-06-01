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
	
	//Mostrem finestra
	jocLib.show();
	// AFEGIR CODI: Definició del grafic del fons
	Sprite fons;
	fons.create("data/tauler.png");
	// AFEGIR CODI: Definició i inicialització de la matriu que representarà
	// les caselles al tauler
	Tauler t;
	Partida p;
	//t.inicialitza();
	p.inicialitza();
	
	// Variables d'ajuda per agafar posició ratolí

	int xMouse = 0;
	int yMouse = 0;
	/*
	int filaorigen = 0;
	int columnaorigen = 0;
	int filadesti = 0;
	int columnadesti = 0;
	int torn = 1;
	int clic = 0;
	bool missatge = false;
	*/

	/*
	do 
	{
		jocLib.processEvents();

		if (Mouse_getButLeft())
		{
			xMouse = Mouse_getX();
			yMouse = Mouse_getY();

			if (clic == 0)
			{
				if ((t.validaClick(xMouse, yMouse, filaorigen, columnaorigen) == true) && (t.checkOrigenValid(filaorigen, columnaorigen, torn) == true))
				{
					t.marcaCasella(filaorigen, columnaorigen, torn);
					clic++;
				}
			}
			else
			{
				if (clic == 1)
				{
					if (t.validaClick(xMouse, yMouse, filadesti, columnadesti) == true)
					{
						t.processaMoviment(filaorigen, columnaorigen, filadesti, columnadesti, torn);
						clic = 0;
					}
					else
					{
						clic = 0;
					}
				}
			}
		}
		*/
	do
	{
		jocLib.processEvents();

		if (Mouse_getButLeft())
		{
			xMouse = Mouse_getX();
			yMouse = Mouse_getY();
			//do {
				p.processaClick(xMouse, yMouse);

				//cout << p.getclic()<<endl;
			//} while (p.getclic() < 1);
				if (p.getclic() == 2)
				{
					p.ferMoviment();
					p.contador();
				}

			
			//p.setClick();
			p.canviaTorn();		
			
		}

		// Pintem fons i peces
		//t.dibuixa(torn, missatge);
		p.visualitza();
		
		// Actualitza la pantalla
		jocLib.update();
		// ***********************************************************************
		// Sortim del bucle si pressionem ESC
		// ***********************************************************************
	} while (!Keyboard_GetKeyTrg(KEYBOARD_ESCAPE) && (p.verificaFitxes() != false));


}
