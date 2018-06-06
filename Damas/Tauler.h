#pragma once
#include "lib/libreria.h"
#include "Moviment.h"
#include <fstream>

using namespace std;

const int MIDATAULER = 8;

//========================================================================
// Mida Pantalla
const int MIDAX = 624;
const int MIDAY = 680;

//========================================================================
// Inici del taulell respecte la cantonada superior esquerre
const int INIPANTALLAX = 0;
const int INIPANTALLAY = 58;

//========================================================================
// Fi del taulell respecte la cantonada inferior dreta
const int FIPANTALLAX = 624;
const int FIPANTALLAY = 680;

// Tamany d'una casella del tauler
const int MIDACASELLA = 78;

// Coordenades de pantalla on mostrar el jugador del torn actual
const int POSICIO_TORN_X = 120;
const int POSICIO_TORN_Y = 10;

// Coordenades de pantalla on mostrar el missatge d'av?s de moviment invalid
const int POSICIO_AVIS_X = 250;
const int POSICIO_AVIS_Y = 10;

// Constants per especificar el jugador del torn actual
const int TORN_BLANC = 1;
const int TORN_NEGRE = 2;

// Constants per codificar el tipus de fitxa que hi ha a cada posicio del tauler
const int FITXA_BLANCA = 1;
const int FITXA_NEGRA = 2;
const int FITXA_BLANCA_SEL = 11;
const int FITXA_NEGRA_SEL = 22;
const int FITXA_BLANCA_DAMA = 111;
const int FITXA_NEGRA_DAMA = 222;
const int FITXA_BLANCA_DAMA_SEL = 1111;
const int FITXA_NEGRA_DAMA_SEL = 2222;

class Tauler
{
public:
	Tauler();
	~Tauler();
	void inicialitza();
	void dibuixa(int torn, bool missatge);
	bool validaClick(int x, int y, int &fila, int &columna);
	int processaMoviment(int filaorigen, int columnaorigen, int filadesti, int columnadesti, int torn);
	bool movimentNormal(int filaorigen, int columnaorigen, int filadesti, int columnadesti,int torn);
	bool movimentCaptura(int filaorigen, int columnaorigen, int filadesti, int columnadesti, int torn);
	bool movimentNormalDama(int filaorigen, int columnaorigen, int filadesti, int columnadesti, int torn);
	bool movimentCapturaDama(int filaorigen, int columnaorigen, int filadesti, int columnadesti, int torn);
	void marcaCasella(int fila, int columna, int torn);
	bool checkOrigenValid(int filaOrigen, int columnaOrigen, int torn);
	void desmCasella(int fila, int columna,int torn);
	int IdentificaMovimentDama(int filaorigen, int columnaorigen, int filadesti, int columnadesti, int torn);
	bool DiagonalDama(int filaorigen, int columnaorigen, int filadesti, int columnadesti, int torn);
	int lecturaMoviments();
	void iniciautoMoviments(int i, int torn);
	int get_m_fitxes_blanques() { return m_fitxes_blanques; }
	int get_m_fitxes_negras() { return m_fitxes_negras; }
	bool end_game(), guanyador();
	Sprite win_white, win_black, frame1;
	void return_to_menu();

private:

	Moviment *mov;
	int m_tauler[8][8];
	int m_caselladiagx;
	int m_caselladiagy;
	int m_fitxes_blanques;
	int m_fitxes_negras;
	int Mov;
	Sprite tablero;
	Sprite piezablanca;
	Sprite piezanegra;
	Sprite piezablanca_sel;
	Sprite piezanegra_sel;
	Sprite piezablanca_dama;
	Sprite piezanegra_dama;
	Sprite piezablanca_dama_sel;
	Sprite piezanegra_dama_sel;
	Sprite turnoblanco;
	Sprite turnonegro;
	Sprite aviso;
};
