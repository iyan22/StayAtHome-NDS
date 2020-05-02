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

	initVarEstado();
	MostrarFondoInicio();

	while(1) {
		// Al entrar a la pausa se desactivavan las teclas por encuesta, esta 
		// instrucción lo soluciona.
		iprintf("\x1b[00;00H ");
		switch(Estado.estado){
			case INIT:
				if (playButton() == true) {
					consoleDemoInit();
					Estado.estado = GAME;
				}
				else if (Estado.instructdone == false && instructionButton() == true) {
					printInstructions();
					Estado.instructdone = true;
				}
				break;

			case GAME:
				if (Estado.initdone == false) {
					interrupciones();
					MostrarFondoTrafico();
					initVarGameScreen();
					printBasicInfo();
					printGameScreen();
					Estado.initdone = true;
					Estado.restartdone = false;
				} // if (!Estado.initdone)

				// Encuesta movimiento Spray
				// Revisar funcionamiento con PAUSA
				if (TeclaPulsada() == DOWN) {
					Objetos.Spray.dir = DOWN;
				} // if (TeclaPulsada() == DOWN) 
				break;
				
			case PAUSE:
				break;

			case RESTART:
				if (Estado.restartdone == false) {
					printRestart();
					interrupciones();
					Estado.restartdone = true;
				}
				break;

			case END:
				consoleDemoInit();
				powerOff(POWER_ALL_2D);
				break;

		} // switch(estado)
 	} // while(1)
} // main()

 


