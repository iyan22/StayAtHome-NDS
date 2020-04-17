
#include <nds.h>
#include <stdio.h>
#include <stdlib.h>	// srand, rand,...
#include <unistd.h>
#include <time.h>       // time 

#include "fondos.h"
#include "sprites.h"
#include "defines.h"
#include "rutserv.h"
#include "teclado.h"
#include "temporizadores.h"
/*--------------------------------------------------------------------------------------------------------------
							Funciones auxiliares
---------------------------------------------------------------------------------------------------------------*/

int tactilTocada() {
	touchPosition pos_pantalla;
	touchRead(&pos_pantalla);
  	return !(pos_pantalla.px==0 && pos_pantalla.py==0);
}

void printBasicInfo() {
	consoleDemoInit();
	iprintf("\x1b[01;00H  +--------------------------+ ");
 	iprintf("\x1b[02;00H  : EC                 19/20 : ");
 	iprintf("\x1b[03;00H  +--------------------------+ ");
	iprintf("\x1b[10;00H    Project StayAtHome - NDS   ");
	iprintf("\x1b[12;00H  Segundos:");
	iprintf("\x1b[20;00H          Grupo 2A03           ");
	iprintf("\x1b[22;00H    Iyan A. Unai R. Aleina P.  ");
}

void initGameScren() {
	MostrarP1Arriba(1,10,5);
	MostrarP1Abajo (2,10,21);
	MostrarP1Arriba(3,10,40);
	MostrarP1Abajo (4,10,56);
	MostrarP1Arriba(5,10,75);
	MostrarP1Abajo (6,10,91);
	MostrarP1Arriba(7,10,110);
	MostrarP1Abajo (8,10,126);
	MostrarP1Arriba(9,10,145);
	MostrarP1Abajo (10,10,161);
	MostrarSpray(20,30,50);
	MostrarGota(21,45,50);
}


