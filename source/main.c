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
int nv = 1;


int xVi1 = 255;
int xVi2 = 255;
int xVi3 = 255;
int xVi4 = 255;
int xVi5 = 255;
int xVi6 = 255;

bool v1Visible = false;
bool v2Visible = false;
bool v3Visible = false;
bool v4Visible = false;
bool v5Visible = false;
bool v6Visible = false;

int random1 = 0;
int random2 = 0;
int random3 = 0;
int random4 = 0;
int random5 = 0;
int random6 = 0;

int initdone = 0;
int instructdone = 0;
touchPosition pos_pantalla;

tObjetos Objetos;

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

	
	while(1) {
		switch(estado){
			case INIT:
				// Hay que cambiarlo por playButton() y que funcione bien
				if (TeclaPulsada() == A) {
					//consoleDemoInit();
					estado = GAME;
				}
				// Hay que cambiarlo por instructionButton() y que funcione bien
				else if (instructdone == 0 && TeclaPulsada() == B) {
					//printInstructions();
					instructdone = 1;
				}
				break;
			case GAME:
				if (initdone == 0) {
					MostrarFondoTrafico();
					initVarGameScreen();
					printBasicInfo();
					printGameScreen();
					initdone = 1;
				}
				// Encuesta movimiento Spray
				switch(TeclaPulsada()) {
					case DOWN:
						Objetos.Spray.dir = DOWN;
						break;
					//default:
					//	speSp = false;
					//	break;
				}
				break;

		} // switch(estado)
 	} // while(1)
} // main()

 


