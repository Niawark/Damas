// #include "stdafx.h"
#include "Tauler.h"
//#include "Moviment.h"
#include "Joc.h"

Tauler::Tauler()
{
}
Tauler::~Tauler()
{
}


void Tauler::inicialitza()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			m_tauler[i][j] = 0;
		}
	}

	for (int j = 1; j < 4; j += 2)
	{
		//m_tauler[0][j] = 2;
		//m_tauler[1][j - 1] = 2;
		m_tauler[2][j] = 222;

		m_tauler[5][j - 1] = 111;
		//m_tauler[6][j] = 1;
		//m_tauler[7][j - 1] = 1;
	}
	//lecturaMoviments();

	//sprites necessaris
	tablero.create("data/tauler.png");
	piezanegra.create("data/fitxa_negra.png");
	piezablanca.create("data/fitxa_blanca.png");
	piezablanca_sel.create("data/fitxa_blanca_sel.png");
	piezanegra_sel.create("data/fitxa_negra_sel.png");
	aviso.create("data/avis_error.png");
	piezablanca_dama.create("data/dama_blanca.png");
	piezanegra_dama.create("data/dama_negra.png");
	piezablanca_dama_sel.create("data/dama_blanca_sel.png");
	piezanegra_dama_sel.create("data/dama_negra_sel.png");
	turnoblanco.create("data/torn_blanc.png");
	turnonegro.create("data/torn_negre.png");
	win_white.create("data/ganan_white.png");
	win_black.create("data/ganan_black.png");

	m_caselladiagx = 0;
	m_caselladiagy = 0;
	m_fitxes_blanques = 2;
	//m_fitxes_blanques = 12;
	m_fitxes_negras = 2;
	//m_fitxes_negras = 12;

}


bool Tauler::validaClick(int x, int y, int &fila, int &columna)
{
	bool valida = false;

	if ((x >= INIPANTALLAX) && (y >= INIPANTALLAY))
	{
		columna = ((x - INIPANTALLAX) / MIDACASELLA);
		fila = ((y - INIPANTALLAY) / MIDACASELLA);
		columna = columna + 1;
		fila = fila + 1;
		valida = true;
	}
	else
	{
		columna = 0;
		fila = 0;
	}

	printf("Columna Fila %d %d \n", fila, columna);
	return valida;
}

bool Tauler::checkOrigenValid(int filaOrigen, int columnaOrigen, int torn)
{
	bool origenV = false;

	if ((m_tauler[filaOrigen - 1][columnaOrigen - 1] == 1) && (torn == TORN_BLANC))
	{
		origenV = true;
	}
	else
	{
		if ((m_tauler[filaOrigen - 1][columnaOrigen - 1] == 2) && (torn == TORN_NEGRE))
		{
			origenV = true;
		}
		else
		{
			if ((m_tauler[filaOrigen - 1][columnaOrigen - 1] == 111) && (torn == TORN_BLANC))
			{
				origenV = true;
			}
			else
			{
				if ((m_tauler[filaOrigen - 1][columnaOrigen - 1] == 222) && (torn == TORN_NEGRE))
				{
					origenV = true;
				}
			}
		}
	}
	return origenV;
}

void Tauler::marcaCasella(int fila, int columna, int torn)
{
	if ((m_tauler[fila - 1][columna - 1] == 2) && (torn == TORN_NEGRE))
	{
		m_tauler[fila - 1][columna - 1] = 0;
		m_tauler[fila - 1][columna - 1] = 22;
	}
	else
	{
		if ((m_tauler[fila - 1][columna - 1] == 1) && (torn == TORN_BLANC))
		{
			m_tauler[fila - 1][columna - 1] = 0;
			m_tauler[fila - 1][columna - 1] = 11;
		}
		else
		{
			if ((m_tauler[fila - 1][columna - 1] == 111) && (torn == TORN_BLANC))
			{
				m_tauler[fila - 1][columna - 1] = 0;
				m_tauler[fila - 1][columna - 1] = 1111;
			}
			else
			{
				if ((m_tauler[fila - 1][columna - 1] == 222) && (torn == TORN_NEGRE))
				{
					m_tauler[fila - 1][columna - 1] = 0;
					m_tauler[fila - 1][columna - 1] = 2222;
				}
			}
		}
	}
}

int Tauler::processaMoviment(int filaorigen, int columnaorigen, int filadesti, int columnadesti, int torn)
{
	bool move = false;
	int i = 0;
	int aux = 0;
	//////////////////////////////////////////////////////// MOVIMENT NORMAL
	if ((filadesti == filaorigen + 1) && ((columnadesti == columnaorigen - 1) || (columnadesti == columnaorigen + 1)) || (filadesti == filaorigen - 1) && ((columnadesti == columnaorigen - 1) || (columnadesti == columnaorigen + 1)))
	{
		move = movimentNormal(filaorigen, columnaorigen, filadesti, columnadesti, torn);
		if (move == true)
		{
			i = 1;
		}
	}

	//////////////////////////////////////////////////////CAPTURA
	if ((filadesti == filaorigen + 2) && ((columnadesti == columnaorigen - 2) || (columnadesti == columnaorigen + 2)) || (filadesti == filaorigen - 2) && ((columnadesti == columnaorigen - 2) || (columnadesti == columnaorigen + 2)))
	{
		move = movimentCaptura(filaorigen, columnaorigen, filadesti, columnadesti, torn);

		if ((move == true) && (torn == TORN_NEGRE))
		{
			i = 2;//capturablanca
		}
		else
		{
			if ((move == true) && (torn == TORN_BLANC))
			{
				i = 3;//capturanegra
			}
		}
	}
	//////////////////////////////////////////////////////MOVIMENT DAMA

	if ((m_tauler[filaorigen - 1][columnaorigen - 1] == 1111 || m_tauler[filaorigen - 1][columnaorigen - 1] == 2222) && (DiagonalDama(filaorigen, columnaorigen, filadesti, columnadesti, torn) == true))
	{
		aux = IdentificaMovimentDama(filaorigen, columnaorigen, filadesti, columnadesti, torn);
		//////////////////////////////////////////////////////MOVIMENT DAMA NORMAL
		if (aux % 2 != 0)
		{
			move = movimentNormalDama(filaorigen, columnaorigen, filadesti, columnadesti, torn);

			if (move == true)
			{
				i = 4;
				m_caselladiagx = 0;
				m_caselladiagy = 0;
			}
		}
		else
		{
			//////////////////////////////////////////////////////MOVIMENT DAMA CAPTURA
			if (aux % 2 == 0)
			{
				move = movimentCapturaDama(filaorigen, columnaorigen, filadesti, columnadesti, torn);

				if ((move == true) && (torn == TORN_NEGRE))
				{
					i = 5;//capturadamablanca
					m_caselladiagx = 0;
					m_caselladiagy = 0;
				}
				else
				{
					if ((move == true) && (torn == TORN_BLANC))
					{
						i = 6;//capturadamanegra
						m_caselladiagx = 0;
						m_caselladiagy = 0;
					}
				}
			}
		}
	}

	/////////////////////////////////////////////////////
	return i;
}

void Tauler::dibuixa(int torn, bool missatge)
{
	tablero.draw(0, 0);


	if (torn == TORN_BLANC)
	{
		turnoblanco.draw(POSICIO_TORN_X, POSICIO_TORN_Y);
	}
	else
	{
		if (torn == TORN_NEGRE)
		{
			turnonegro.draw(POSICIO_TORN_X, POSICIO_TORN_Y);
		}

	}

	if (missatge == true)
	{
		aviso.draw(POSICIO_AVIS_X, POSICIO_AVIS_Y);
	}


	int fila = INIPANTALLAX;
	int columna = INIPANTALLAY;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (m_tauler[i][j] == 1)
			{
				piezablanca.draw(j*MIDACASELLA + INIPANTALLAX, i*MIDACASELLA + INIPANTALLAY);
			}
			else
			{
				if (m_tauler[i][j] == 2)
				{
					piezanegra.draw(j*MIDACASELLA + INIPANTALLAX, i*MIDACASELLA + INIPANTALLAY);
				}
				else
				{
					if (m_tauler[i][j] == 11)
					{
						piezablanca_sel.draw(j*MIDACASELLA + INIPANTALLAX, i*MIDACASELLA + INIPANTALLAY);
					}
					else
					{
						if (m_tauler[i][j] == 22)
						{
							piezanegra_sel.draw(j*MIDACASELLA + INIPANTALLAX, i*MIDACASELLA + INIPANTALLAY);
						}
						else
						{
							if (m_tauler[i][j] == 111)
							{
								piezablanca_dama.draw(j*MIDACASELLA + INIPANTALLAX, i*MIDACASELLA + INIPANTALLAY);
							}
							else
							{
								if (m_tauler[i][j] == 222)
								{
									piezanegra_dama.draw(j*MIDACASELLA + INIPANTALLAX, i*MIDACASELLA + INIPANTALLAY);
								}
								else
								{
									if (m_tauler[i][j] == 1111)
									{
										piezablanca_dama_sel.draw(j*MIDACASELLA + INIPANTALLAX, i*MIDACASELLA + INIPANTALLAY);
									}
									else
									{
										if (m_tauler[i][j] == 2222)
										{
											piezanegra_dama_sel.draw(j*MIDACASELLA + INIPANTALLAX, i*MIDACASELLA + INIPANTALLAY);
										}
									}
								}
							}
						}
					}
				}
			}
			columna += MIDACASELLA;
		}
		fila += MIDACASELLA;
		columna = INIPANTALLAY;
	}
}

void Tauler::desmCasella(int fila, int columna, int torn)
{
	if ((m_tauler[fila - 1][columna - 1] == 22) && (torn == TORN_NEGRE))
	{
		m_tauler[fila - 1][columna - 1] = 0;
		m_tauler[fila - 1][columna - 1] = 2;
	}
	else
	{
		if ((m_tauler[fila - 1][columna - 1] == 11) && (torn == TORN_BLANC))
		{
			m_tauler[fila - 1][columna - 1] = 0;
			m_tauler[fila - 1][columna - 1] = 1;
		}
		else
		{
			if ((m_tauler[fila - 1][columna - 1] == 2222) && (torn == TORN_NEGRE))
			{
				m_tauler[fila - 1][columna - 1] = 0;
				m_tauler[fila - 1][columna - 1] = 222;
			}
			else
			{
				if ((m_tauler[fila - 1][columna - 1] == 1111) && (torn == TORN_BLANC))
				{
					m_tauler[fila - 1][columna - 1] = 0;
					m_tauler[fila - 1][columna - 1] = 111;
				}
			}
		}
	}
}

bool Tauler::movimentNormal(int filaorigen, int columnaorigen, int filadesti, int columnadesti, int torn)
{
	bool move = false;

	if (m_tauler[filaorigen - 1][columnaorigen - 1] == 11)
	{
		if (((filadesti == filaorigen - 1) && (columnadesti == columnaorigen + 1) && (m_tauler[filadesti - 1][columnadesti - 1]) == 0) || ((filadesti == filaorigen - 1) && (columnadesti == columnaorigen - 1) && (m_tauler[filadesti - 1][columnadesti - 1]) == 0))
		{
			move = true;
		}
	}
	else
	{

		if (m_tauler[filaorigen - 1][columnaorigen - 1] == 22)
		{
			if (((filadesti == filaorigen + 1) && (columnadesti == columnaorigen + 1) && (m_tauler[filadesti - 1][columnadesti - 1]) == 0) || ((filadesti == filaorigen + 1) && (columnadesti == columnaorigen - 1) && (m_tauler[filadesti - 1][columnadesti - 1]) == 0))
			{
				move = true;
			}
		}
	}

	if (move == true)
	{
		if (torn == TORN_BLANC)
		{
			if (filadesti - 1 == 0)
			{
				m_tauler[filaorigen - 1][columnaorigen - 1] = 0;
				m_tauler[filadesti - 1][columnadesti - 1] = 111;

			}
			else
			{
				m_tauler[filaorigen - 1][columnaorigen - 1] = 0;
				m_tauler[filadesti - 1][columnadesti - 1] = 1;
			}
		}
		else
		{
			if (torn == TORN_NEGRE)
			{
				if (filadesti - 1 == 7)
				{
					m_tauler[filaorigen - 1][columnaorigen - 1] = 0;
					m_tauler[filadesti - 1][columnadesti - 1] = 222;
				}
				else
				{
					m_tauler[filaorigen - 1][columnaorigen - 1] = 0;
					m_tauler[filadesti - 1][columnadesti - 1] = 2;
				}

			}
		}

		columnaorigen = 0;
		columnadesti = 0;
		filaorigen = 0;
		filadesti = 0;
	}
	return move;
}

bool Tauler::movimentCaptura(int filaorigen, int columnaorigen, int filadesti, int columnadesti, int torn)
{

	bool move = false;
	int direccio = 0;
	////direccio=1 DRETA  i  direccio=-1 ESQUERRA

	if (m_tauler[filaorigen - 1][columnaorigen - 1] == 11)
	{
		if (((filadesti == filaorigen - 2) && (columnadesti == columnaorigen + 2) && (m_tauler[filadesti - 1][columnadesti - 1]) == 0) && (m_tauler[filaorigen - 2][columnaorigen] != torn) && (m_tauler[filaorigen - 2][columnaorigen] != 111) && (m_tauler[filaorigen - 2][columnaorigen] != 0))
		{
			move = true;
			direccio = 1;
		}
		else
		{
			if (((filadesti == filaorigen - 2) && (columnadesti == columnaorigen - 2) && (m_tauler[filadesti - 1][columnadesti - 1]) == 0) && (m_tauler[filaorigen - 2][columnaorigen - 2] != torn) && (m_tauler[filaorigen - 2][columnaorigen - 2] != 111) && (m_tauler[filaorigen - 2][columnaorigen - 2] != 0))
			{
				move = true;
				direccio = -1;
			}
		}
	}
	else
	{
		if (m_tauler[filaorigen - 1][columnaorigen - 1] == 22)
		{
			if (((filadesti == filaorigen + 2) && (columnadesti == columnaorigen + 2) && (m_tauler[filadesti - 1][columnadesti - 1]) == 0) && (m_tauler[filaorigen][columnaorigen] != torn) && (m_tauler[filaorigen][columnaorigen] != 222) && (m_tauler[filaorigen][columnaorigen] != 0))
			{
				move = true;
				direccio = 1;
			}
			else
			{
				if (((filadesti == filaorigen + 2) && (columnadesti == columnaorigen - 2) && (m_tauler[filadesti - 1][columnadesti - 1]) == 0) && (m_tauler[filaorigen][columnaorigen - 2] != torn) && (m_tauler[filaorigen][columnaorigen - 2] != 222) && (m_tauler[filaorigen][columnaorigen - 2] != 0))
				{
					move = true;
					direccio = -1;
				}
			}
		}
	}

	if (move == true)
	{
		if (torn == TORN_BLANC)
		{
			if (filadesti - 1 == 0)
			{
				if (direccio == 1)//convertir
				{
					m_tauler[filaorigen - 1][columnaorigen - 1] = 0;
					m_tauler[filaorigen - 2][columnaorigen] = 0;
					m_tauler[filadesti - 1][columnadesti - 1] = 111;
				}
				else
				{
					m_tauler[filaorigen - 1][columnaorigen - 1] = 0;
					m_tauler[filaorigen - 2][columnaorigen - 2] = 0;
					m_tauler[filadesti - 1][columnadesti - 1] = 111;
				}
			}
			else
			{
				m_fitxes_negras--;
				if (direccio == 1)
				{
					m_tauler[filaorigen - 1][columnaorigen - 1] = 0;
					m_tauler[filaorigen - 2][columnaorigen] = 0;
					m_tauler[filadesti - 1][columnadesti - 1] = 1;
				}
				else
				{
					m_tauler[filaorigen - 1][columnaorigen - 1] = 0;
					m_tauler[filaorigen - 2][columnaorigen - 2] = 0;
					m_tauler[filadesti - 1][columnadesti - 1] = 1;
				}
			}
		}
		else
		{
			if (torn == TORN_NEGRE)
			{
				if (filadesti - 1 == 7)//convertir
				{
					if (direccio == 1)
					{
						m_tauler[filaorigen - 1][columnaorigen - 1] = 0;
						m_tauler[filaorigen][columnaorigen] = 0;
						m_tauler[filadesti - 1][columnadesti - 1] = 222;
					}
					else
					{
						m_tauler[filaorigen - 1][columnaorigen - 1] = 0;
						m_tauler[filaorigen][columnaorigen - 2] = 0;
						m_tauler[filadesti - 1][columnadesti - 1] = 222;
					}
				}
				else
				{
					m_fitxes_blanques--;
					if (direccio == 1)
					{
						m_tauler[filaorigen - 1][columnaorigen - 1] = 0;
						m_tauler[filaorigen][columnaorigen] = 0;
						m_tauler[filadesti - 1][columnadesti - 1] = 2;
					}
					else
					{
						m_tauler[filaorigen - 1][columnaorigen - 1] = 0;
						m_tauler[filaorigen][columnaorigen - 2] = 0;
						m_tauler[filadesti - 1][columnadesti - 1] = 2;
					}
				}

			}
		}

		columnaorigen = 0;
		columnadesti = 0;
		filaorigen = 0;
		filadesti = 0;
	}
	return move;
}

bool Tauler::movimentNormalDama(int filaorigen, int columnaorigen, int filadesti, int columnadesti, int torn)
{
	bool move = false;
	if (torn == TORN_NEGRE)
	{
		m_tauler[filaorigen - 1][columnaorigen - 1] = 0;
		m_tauler[filadesti - 1][columnadesti - 1] = 222;
		move = true;
	}
	else
	{
		m_tauler[filaorigen - 1][columnaorigen - 1] = 0;
		m_tauler[filadesti - 1][columnadesti - 1] = 111;
		move = true;
	}

	if (move == true)
	{
		columnaorigen = 0;
		columnadesti = 0;
		filaorigen = 0;
		filadesti = 0;
	}
	return move;
}

bool Tauler::movimentCapturaDama(int filaorigen, int columnaorigen, int filadesti, int columnadesti, int torn)
{
	bool move = false;
	if (torn == TORN_NEGRE)
	{
		m_fitxes_blanques--;
		m_tauler[filaorigen - 1][columnaorigen - 1] = 0;
		m_tauler[m_caselladiagx][m_caselladiagy] = 0;
		m_tauler[filadesti - 1][columnadesti - 1] = 222;
		move = true;
	}
	else
	{
		m_fitxes_negras--;
		m_tauler[filaorigen - 1][columnaorigen - 1] = 0;
		m_tauler[m_caselladiagx][m_caselladiagy] = 0;
		m_tauler[filadesti - 1][columnadesti - 1] = 111;
		move = true;
	}

	if (move == true)
	{
		columnaorigen = 0;
		columnadesti = 0;
		filaorigen = 0;
		filadesti = 0;
	}
	return move;
}

int Tauler::IdentificaMovimentDama(int filaorigen, int columnaorigen, int filadesti, int columnadesti, int torn)
{
	int x = 0;
	bool valid = false;
	bool desti_par = (filadesti - 1 + columnadesti - 1) % 2 == 0;
	bool origen_par = (filaorigen - 1 + columnaorigen - 1) % 2 == 0;

	if (m_tauler[filadesti - 1][columnadesti - 1] == 0)
	{
		if (filaorigen - 1 > filadesti - 1)
		{//arriba
			if (columnadesti - 1 < columnaorigen - 1)
			{
				//izquierda
				if (m_tauler[filadesti][columnadesti] == 0)
				{
					if ((!origen_par && !desti_par) || (origen_par && desti_par))
					{
						x = 1;
					}
				}

				else if ((m_tauler[filadesti][columnadesti] / 111) != torn)
				{
					if ((!origen_par && !desti_par) || (origen_par && desti_par))
					{
						x = 2;
					}
				}
			}
			else {
				//derecha
				if (m_tauler[filadesti][columnadesti - 2] == 0)
				{
					if ((!origen_par && !desti_par) || (origen_par && desti_par))
					{
						x = 5;
					}
				}
				else if ((m_tauler[filadesti][columnadesti - 2] / 111) != torn)
				{	
					if ((!origen_par && !desti_par) || (origen_par && desti_par))
						{
						x =		6;
					}
				}	
			}
		}	
		else  //abajo
		{	
			if (columnadesti - 1 < columnaorigen - 1)
			{	
				//izquierda
				if ((!origen_par && !desti_par) || (origen_par && desti_par)) {
					if (m_tauler[filadesti - 2][columnadesti] == 0 || (m_tauler[filadesti - 2][columnadesti] / 1111) == torn)
					{
						x = 3;
						
					}
					else if ((m_tauler[filadesti - 2][columnadesti] / 111) != torn)
					{
						x = 4;
					}
				}
			}	
			else
			{//derecha
				if (m_tauler[filadesti - 2][columnadesti - 2] == 0)
				{	
					if ((!origen_par && !desti_par) || (origen_par && desti_par))
					{
						x =	7;
					}	
				}	
				else if ((m_tauler[filadesti - 2][columnadesti - 2] / 111) != torn)
					{
					if ((!origen_par && !desti_par) || (origen_par && desti_par))
					{	
					x = 8;
					}
				}
			}
		}
	}
	return x;
}

bool Tauler::DiagonalDama(int filaorigen, int columnaorigen, int filadesti, int columnadesti, int torn)
{
	int aux = 0;
	int cont = 0;
	bool diagonalvalida = false;
	int i;
	int j;


	aux = IdentificaMovimentDama(filaorigen, columnaorigen, filadesti, columnadesti, torn);
	if ((aux == 1 && (filadesti - 1 == filaorigen - 2) && (columnadesti - 1 == columnaorigen)) || (aux == 3 && (filadesti - 1 == filaorigen) && (columnadesti - 1 == columnaorigen)) || (aux == 5 && (filadesti - 1 == filaorigen - 2) && (columnadesti - 1 == columnaorigen)) || (aux == 7 && (filadesti - 1 == filaorigen) && (columnadesti - 1 == columnaorigen)))
	{
		////comprovar
	}
	else
	{
		if (aux == 1 || aux == 2)//arriba izq
		{
			for (i = filaorigen - 2, j = columnaorigen - 2; i > filadesti - 1; i--, j--)
			{
				if (m_tauler[i][j] != 0)
				{
					cont++;
					m_caselladiagx = i;
					m_caselladiagy = j;
				}
			}
		}

		if (aux == 3 || aux == 4)//abajo izq
		{
			for (i = filaorigen,j = columnaorigen - 2; i< filadesti - 1; i++, j--)
			{	
				if (m_tauler[i][j] != 0)
				{
					cont++;
					m_caselladiagx = i;
					m_caselladiagy = j;
				}
			}			
		}

		if (aux == 5 || aux == 6)//arriba derecha
		{
			for (i = filaorigen -2, j = columnaorigen; i >= filadesti - 1; i--, j++)
			{
				if (m_tauler[i][j] != 0)
				{
					cont++;
					m_caselladiagx = i;
					m_caselladiagy = j;
				}
			}
		}

		if (aux == 7 || aux == 8)//abajo derecha
		{
			for (i = filaorigen,j = columnaorigen; i < filadesti - 1; i++, j++)
			{
				if (m_tauler[i][j] != 0)
				{
					cont++;
					m_caselladiagx = i;
					m_caselladiagy = j;
				}
			}
		}
	}


	////////////////////////////////////////////////////////normal

	if (aux == 1 || aux == 3 || aux == 5 || aux == 7 || aux == 2 || aux == 4 || aux == 6 || aux == 8)
	{
		if (cont == 0)
		{
			diagonalvalida = true;
		}
	}

	////////////////////////////////////////////////////////captura
	if (aux == 2 || aux == 4 || aux == 6 || aux == 8)
	{
		if (cont == 1 && (m_tauler[m_caselladiagx][m_caselladiagy]/111) != torn)
		{
			diagonalvalida = true;
		}
	}

	return diagonalvalida;
}

int Tauler::lecturaMoviments()
{
	int nMov;
	std::ifstream fitxer;
	// Variable per guardar el nom del fitxer
	std::string nomFitxer = "data/MatriuMoviments.txt";
	fitxer.open(nomFitxer);
	if (fitxer.is_open())
	{
		int fo, co, fd, cd;
		fitxer >> nMov;
		mov = new Moviment[nMov];
		//fitxer >> numero;
		for (int i = 0; i < nMov; i++) {
			fitxer >> fo >> co >> fd >> cd;
			mov[i].inicialitza(fo, co, fd, cd);
		}
		fitxer.close();
	}
	return nMov;
}

void Tauler::iniciautoMoviments(int i, int torn)
{

	int filaorigen = mov[i].get_filaorigen();
	int columnaorigen = mov[i].get_columnaorigen();

	int filadesti = mov[i].get_filadesti();
	int columnadesti = mov[i].get_columnadesti();

	if (checkOrigenValid(filaorigen, columnaorigen, torn) == true)
	{
		processaMoviment(filaorigen, columnaorigen, filadesti, columnadesti, torn);
	}

}
