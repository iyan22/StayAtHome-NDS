/*----------------------------------------------------------------------------------------------------------
			Este código se ha implementado basándose en el ejemplo "Simple sprite demo" de 
										dovoto y otro de Jaeden Amero
-----------------------------------------------------------------------------------------------------------*/

#include <nds.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>       	// time 

#include "fondos.h"
#include "sprites.h"
#include "defines.h"
#include "rutserv.h"
#include "teclado.h"
#include "temporizadores.h"
#include "funciones.h"

/*----------------------------------------------------------------------------------------------------------
 											Variables globales
-----------------------------------------------------------------------------------------------------------*/

int estado;

int segs0 = 0;
int segs1 = 0;
bool speSp = false;
int dirSp = 0;
int ySp = 50;

int main() {


	//  Poner en marcha el motor gráfico 2D.
    powerOn(POWER_ALL_2D);

   	// Establecer la pantalla inferior como principal, inicializar el sistema gráfico
    // y configurar el sistema de fondos.
    lcdMainOnBottom();
    initVideo();
    initFondos();

	// Inicializar memoria de sprites y guardar en ella los sprites 
	initSpriteMem();
	guardarSpritesEnMemoria();

	// Establecer las paletas para los sprites 
	establecerPaletaPrincipal();

	// Para poder imprimir en pantalla (hacer trazas) 
	consoleDemoInit();
	
 	// Para inicializar el generador de números aleatorios en función de una semilla,
	// en este caso time(NULL). 
	// srand() sólo se suele activar una vez por ejecución y no devuelve ningún valor 
	srand (time(NULL));

	
	interrupciones();


	printBasicInfo();
	printGameScreen();

	
	while(1) {



		switch(estado){
			case INIT:
				if(TeclaPulsada() == A) {
					estado = GAME;
				}


				break;

			case GAME:
				MostrarFondoTrafico();
				// Encuesta movimiento Spray
				switch(TeclaPulsada()) {
					case UP:
						dirSp = UP;
						speSp = true;
						break;

					case DOWN:
						dirSp = DOWN;
						speSp = true;
						break;
					default:
						speSp = false;
						break;
				}
				break;

		}
 	}

}

 


