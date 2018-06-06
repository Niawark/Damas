//Definicio necesaria per poder incloure la llibreria i que trobi el main
#define SDL_MAIN_HANDLED

#include <windows.h>
#include "Joc.h" //Aquest inclou llibreria grafica
#include <conio.h>      /* getch */ 


//Arguments necesaris per poder incloure la llibreria i que trobi el main
void main(int argc, char* argv[])
{
	//Instruccions necesaries per poder incloure la llibreria i que trobi el main
	SDL_SetMainReady();
	SDL_Init(SDL_INIT_VIDEO);
	///////////////////////////////////////////////////////////////////////////

	char opcio;
	do {
		printf("1.Partida normal\n");
		printf("2.Guardar partida\n");
		printf("3.Cargar partida\n");
		printf("4.Sortir\n");
		opcio = _getch();
	} while ((opcio < '1') || (opcio > '4'));
	if (opcio != '4')
		joc(opcio);

	//Instruccio necesaria per poder incloure la llibreria i que trobi el main
	SDL_Quit();
	_getch;
	///////////////////////////////////////////////////////////////////////////

}
