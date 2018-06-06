// #include "stdafx.h"
#include "Partida.h"
#include "Tauler.h"
#include "Joc.h"


Partida::Partida()
{
}
Partida::~Partida()
{
}

void Partida:: inicialitza()
{
	m_obj.inicialitza();

	m_columnadesti = 0;
	m_columnaorigen = 0;
	m_filadesti = 0;
	m_filaorigen = 0;
	m_torn_actual = TORN_BLANC;
	m_missatge = false;
	m_clic = 0;
	m_siguiente_turno = false;
	m_contadorblancas = 12;
	m_contadornegras = 12;
	m_captura = 0;
}


void Partida::processaClick(int xMouse, int yMouse)
{

	//validaClick checkOrigenValid marcaCasella
	m_missatge = false;
		if (Mouse_getButLeft())
		{
			xMouse = Mouse_getX();
			yMouse = Mouse_getY();

			if (m_clic == 0)
			{
				if ((m_obj.validaClick(xMouse, yMouse, m_filaorigen, m_columnaorigen)) && (m_obj.checkOrigenValid(m_filaorigen, m_columnaorigen, m_torn_actual))==true)
				{
					m_obj.marcaCasella(m_filaorigen, m_columnaorigen, m_torn_actual);
					m_clic++;
				}
				else
				{
					m_clic = 0;
					m_missatge = true;
				}
			}
			else
			{
				if (m_clic == 1)
				{
					if (m_obj.validaClick(xMouse, yMouse, m_filadesti, m_columnadesti)==true)
					{
						m_clic++;
						m_siguiente_turno = true;
					}
					else
					{
						m_clic++;
					}
					
				}
				else {
					m_clic = 0;
					
				}
			}
		}
	}

int Partida::ferMoviment()
{
 	int x = 0;

	x = m_obj.processaMoviment(m_filaorigen, m_columnaorigen, m_filadesti, m_columnadesti, m_torn_actual);

	if (x == 1)
	{
		m_missatge = false;
	}
	else
	{
		if (x == 2)
		{
			m_missatge = false;
			m_captura = x;
		}
		else
		{
			if (x == 3)
			{
				m_missatge = false;
				m_captura = x;
			}
			else
			{
				if (x == 4)
				{
					m_missatge = false;
				}
				else
				{
					if (x == 5)
					{
						m_missatge = false;
						m_captura = x;
					}
					else
					{
						if (x == 6)
						{
							m_missatge = false;
							m_captura = x;
						}
						else
						{

							m_missatge = true;
							m_siguiente_turno = false;
							m_obj.desmCasella(m_filaorigen, m_columnaorigen, m_torn_actual);

						}

					}
				}
			}

		}
	}
	
	setClick();
	return x;
}

void Partida::canviaTorn()
{	
	if ((m_siguiente_turno == true ))
	{
		if (m_torn_actual == TORN_BLANC)
		{
			m_torn_actual = TORN_NEGRE;
			
		}
		else
		{
			m_torn_actual = TORN_BLANC;
			
		}
	}
	m_siguiente_turno = false;
}

void Partida::visualitza()
{
	m_obj.dibuixa(m_torn_actual, m_missatge);
}

int Partida::getclic()
{
	return m_clic;
}

void Partida::setClick() {
	m_clic = 0;
}