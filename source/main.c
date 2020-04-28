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

tObjetos Objetos;
tEstado Estado;

touchPosition pos_pantalla;


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
	initVarEstado();

	
	while(1) {
		switch(Estado.estado){
			case INIT:
				// Hay que cambiarlo por playButton() y que funcione bien
				if (TeclaPulsada() == A) {
					consoleDemoInit();
					Estado.estado = GAME;
				}
				// Hay que cambiarlo por instructionButton() y que funcione bien
				else if (!Estado.instructdone && TeclaPulsada() == B) {
					printInstructions();
					Estado.instructdone = true;
				}
				break;
			case GAME:
				if (!Estado.initdone) {
					MostrarFondoTrafico();
					initVarGameScreen();
					printBasicInfo();
					printGameScreen();
					Estado.initdone = true;
				}
				// Encuesta movimiento Spray
				switch(TeclaPulsada()) {
					case DOWN:
						Objetos.Spray.dir = DOWN;
						break;
				}
				break;

		} // switch(estado)
 	} // while(1)
} // main()

 


