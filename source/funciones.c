
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


int touchingScreen() {
	touchPosition pos_pantalla;
	touchRead(&pos_pantalla);
	iprintf("\x1b[00;00H  NORMAL        ");
	iprintf("\x1b[00;10H %d %d", pos_pantalla.px, pos_pantalla.py);
  	if (pos_pantalla.px == 0 && pos_pantalla.py == 0) {
  		return 0;
  	}
  	else {
  		return 1;
  	}
}

int playButton() {
	touchPosition pos_pantalla;
	touchRead(&pos_pantalla);
	iprintf("\x1b[01;00H  PLAYYY  ");
	iprintf("\x1b[01;10H  %d %d ", pos_pantalla.px, pos_pantalla.py);
  	if (pos_pantalla.px > 75 && pos_pantalla.px < 205 &&
  		pos_pantalla.py > 40 && pos_pantalla.py < 95) {
  		return 1;
  	}
  	else {
  		return 0;
  	}
}

int instructionButton() {
	touchPosition pos_pantalla;
	touchRead(&pos_pantalla);
	iprintf("\x1b[02;00H  INSTRUCTION ");
  	if (pos_pantalla.px > 105 && pos_pantalla.px < 175 &&
  		pos_pantalla.py > 108 && pos_pantalla.py < 126) {
  		return 1;
  	}
  	else {
  		return 0;
  	}
}

void printInstructions() {
	iprintf("\x1b[01;00H    Welcome to StayAtHome-NDS  ");
 	iprintf("\x1b[03;00H           Instructions:       ");
 	iprintf("\x1b[05;00H    Press PLAY (touchscreen)   ");
	iprintf("\x1b[07;00H    Kill COVID-19 viruses with ");
	iprintf("\x1b[08;00H    the hidroalcoholic gel     ");
	iprintf("\x1b[09;00H    Press A to shot.           ");
	iprintf("\x1b[11;00H    Move the hidroalcoholic gel");
	iprintf("\x1b[12;00H    pressing UP and DOWN       ");
	iprintf("\x1b[14;00H           BE CAREFUL!!!       ");
	iprintf("\x1b[16;00H      If virus touches people  ");
	iprintf("\x1b[17;00H       they will be infected   ");
	iprintf("\x1b[20;00H    Developed by:              ");
	iprintf("\x1b[22;00H    Iyan A. Unai R. Aleina P.  ");
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

void initVarEstado() {
	Estado.initdone = false;
	Estado.instructdone = false;
	Estado.numVirus = 1;
}

void printGameScreen() {
	MostrarPersonas();
	MostrarSpray(Objetos.Spray.x, Objetos.Spray.y);
}

void initVarGameScreen() {

	Objetos.Spray.x = 28;
	Objetos.Spray.y = 50;
	Objetos.Spray.dir = 0;

	int i = 0;
	while (i < numVirusT) {
		Objetos.Virus[i].indice = i;
		Objetos.Virus[i].visible = false;
		Objetos.Virus[i].x = 250;
		Objetos.Virus[i].y = 0;
		i++;
	}	
}

void MostrarPersona(int indice, int x, int y) {
	MostrarP1Arriba(indice,x,y);
	MostrarP1Abajo (indice+1,x,y+16);
}

void MostrarPersonas() {
	MostrarPersona(11,10,5);
	MostrarPersona(13,10,40);
	MostrarPersona(15,10,75);
	MostrarPersona(17,10,110);
	MostrarPersona(19,10,145);
}

void updateSpray() {
	if (Objetos.Spray.dir == UP && Objetos.Spray.y > 3) {
		Objetos.Spray.y--;
	}
	else if (Objetos.Spray.dir == DOWN && Objetos.Spray.y < 160) {
		Objetos.Spray.y++;
	}
	MostrarSpray(Objetos.Spray.x, Objetos.Spray.y);
}

void spawnVirus(){
	int n = Estado.numVirus;
	Objetos.Virus[n].visible = true;
	Objetos.Virus[n].y = 10+rand()%(150 + 1 - 10);
	MostrarVirus(Objetos.Virus[n].indice, Objetos.Virus[n].x, Objetos.Virus[n].y);
	if (n < numVirusT-1) {
		Estado.numVirus++;
	}
	else {
		Estado.numVirus = 0;
	}
}

void updateVirus() {
	int i = 0;
	while (i < numVirusT) {
		if (Objetos.Virus[i].visible) {
			if (1+rand()%(5) == 1){
				if (1+rand()%(2) == 1 && Objetos.Virus[i].y < 150){
					Objetos.Virus[i].y += 2;
				}
				else if (1+rand()%(2) == 2 && Objetos.Virus[i].y > 10){
					Objetos.Virus[i].y -= 2;
				}
			}
			Objetos.Virus[i].x--;
			MostrarVirus(Objetos.Virus[i].indice, Objetos.Virus[i].x, Objetos.Virus[i].y);
		}
		i++;
	}
}








