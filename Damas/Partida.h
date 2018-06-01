#pragma once
#include "tauler.h"

class Partida
{
public:
	Partida();
	~Partida();
	
	void inicialitza();
	void visualitza();
	int getclic();
	void processaClick(int xMouse, int yMouse);
	void canviaTorn();
	int ferMoviment();
	void setClick();
	bool m_siguiente_turno;
	bool verificaFitxes();
	void contador();
	
   
private:
	Tauler m_obj;
	int m_torn_actual;
	int m_filaorigen;
	int m_columnaorigen;
	int m_filadesti;
	int m_columnadesti;
	int m_clic;
	bool m_missatge;
	int m_contadorblancas;
	int m_contadornegras;
	int m_captura;
	int m_contadordamasblancas;
	int m_contadordamasnegras;

};


