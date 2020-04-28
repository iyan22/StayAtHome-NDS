
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
	MostrarPersona(1,10,5);
	MostrarPersona(3,10,40);
	MostrarPersona(5,10,75);
	MostrarPersona(7,10,110);
	MostrarPersona(9,10,145);
	MostrarSpray(Objetos.Spray.x, Objetos.Spray.y);
}

void initVarGameScreen() {

	Objetos.Spray.x = 28;
	Objetos.Spray.y = 50;
	Objetos.Spray.dir = 0;

	Objetos.Virus1.indice = 11;
	Objetos.Virus2.indice = 12;
	Objetos.Virus3.indice = 13;
	Objetos.Virus4.indice = 14;
	Objetos.Virus5.indice = 15;
	Objetos.Virus6.indice = 16;

	Objetos.Virus1.x = 250;
	Objetos.Virus2.x = 250;
	Objetos.Virus3.x = 250;
	Objetos.Virus4.x = 250;
	Objetos.Virus5.x = 250;
	Objetos.Virus6.x = 250;

	Objetos.Virus1.y = 0;
	Objetos.Virus2.y = 0;
	Objetos.Virus3.y = 0;
	Objetos.Virus4.y = 0;
	Objetos.Virus5.y = 0;
	Objetos.Virus6.y = 0;

	Objetos.Virus1.visible = false;
	Objetos.Virus2.visible = false;
	Objetos.Virus3.visible = false;
	Objetos.Virus4.visible = false;
	Objetos.Virus5.visible = false;
	Objetos.Virus6.visible = false;

}

void MostrarPersona(int indice, int x, int y) {
	MostrarP1Arriba(indice,x,y);
	MostrarP1Abajo (indice+1,x,y+16);
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
	switch(Estado.numVirus){
		case 1:
			Objetos.Virus1.visible = true;
			Objetos.Virus1.y = 10+rand()%(150 + 1 - 10);
			MostrarVirus(Objetos.Virus1.indice, Objetos.Virus1.x, Objetos.Virus1.y);
			Estado.numVirus++;
			break;
		case 2:
			Objetos.Virus2.visible = true;
			Objetos.Virus2.y = 10+rand()%(150 + 1 - 10);
			MostrarVirus(Objetos.Virus2.indice, Objetos.Virus2.x, Objetos.Virus2.y);
			Estado.numVirus++;
			break;
		case 3:
			Objetos.Virus3.visible = true;
			Objetos.Virus3.y = 10+rand()%(150 + 1 - 10);
			MostrarVirus(Objetos.Virus3.indice, Objetos.Virus3.x, Objetos.Virus3.y);
			Estado.numVirus++;
			break;
		case 4:
			Objetos.Virus4.visible = true;
			Objetos.Virus4.y = 10+rand()%(150 + 1 - 10);
			MostrarVirus(Objetos.Virus4.indice, Objetos.Virus4.x, Objetos.Virus4.y);
			Estado.numVirus++;
			break;
		case 5:
			Objetos.Virus5.visible = true;
			Objetos.Virus5.y = 10+rand()%(150 + 1 - 10);
			MostrarVirus(Objetos.Virus5.indice, Objetos.Virus5.x, Objetos.Virus5.y);
			Estado.numVirus++;
			break;
		case 6:
			Objetos.Virus6.visible = true;
			Objetos.Virus6.y = 10+rand()%(150 + 1 - 10);
			MostrarVirus(Objetos.Virus6.indice, Objetos.Virus6.x, Objetos.Virus6.y);
			Estado.numVirus = 1;
			break;
	}
}

void updateVirus(){
	if (Objetos.Virus1.visible){
		if (1+rand()%(5) == 1){
			if (1+rand()%(2) == 1 && Objetos.Virus1.y < 150){
				Objetos.Virus1.y += 2;
			}else if (1+rand()%(2) == 2 && Objetos.Virus1.y > 10){
				Objetos.Virus1.y -= 2;
			}
		}
		Objetos.Virus1.x--;
		MostrarVirus(Objetos.Virus1.indice, Objetos.Virus1.x, Objetos.Virus1.y);
	}
	if (Objetos.Virus2.visible){
		if (1+rand()%(5) == 1){
			if (1+rand()%(2) == 1 && Objetos.Virus2.y < 150){
				Objetos.Virus2.y += 2;
			}else if (1+rand()%(2) == 2 && Objetos.Virus2.y > 10){
				Objetos.Virus2.y -= 2;
			}
		}
		Objetos.Virus2.x--;
		MostrarVirus(Objetos.Virus2.indice, Objetos.Virus2.x, Objetos.Virus2.y);
	}
	if (Objetos.Virus3.visible){
		if (1+rand()%(5) == 1){
			if (1+rand()%(2) == 1 && Objetos.Virus3.y < 150){
				Objetos.Virus3.y += 2;
			}else if (1+rand()%(2) == 2 && Objetos.Virus3.y > 10){
				Objetos.Virus3.y -= 2;
			}
		}
		Objetos.Virus3.x--;
		MostrarVirus(Objetos.Virus3.indice, Objetos.Virus3.x, Objetos.Virus3.y);
	}
	if (Objetos.Virus4.visible){
		if (1+rand()%(5) == 1){
			if (1+rand()%(2) == 1 && Objetos.Virus4.y < 150){
				Objetos.Virus4.y += 2;
			}else if (1+rand()%(2) == 2 && Objetos.Virus4.y > 10){
				Objetos.Virus4.y -= 2;
			}
		}
		Objetos.Virus4.x--;
		MostrarVirus(Objetos.Virus4.indice, Objetos.Virus4.x, Objetos.Virus4.y);
	}
	if (Objetos.Virus5.visible){
		if (1+rand()%(5) == 1){
			if (1+rand()%(2) == 1 && Objetos.Virus5.y < 150){
				Objetos.Virus5.y += 2;
			}else if (1+rand()%(2) == 2 && Objetos.Virus5.y > 10){
				Objetos.Virus5.y -= 2;
			}
		}
		Objetos.Virus5.x--;
		MostrarVirus(Objetos.Virus5.indice, Objetos.Virus5.x, Objetos.Virus5.y);
	}
	if (Objetos.Virus6.visible){
		if (1+rand()%(5) == 1){
			if (1+rand()%(2) == 1 && Objetos.Virus6.y < 150){
				Objetos.Virus6.y += 2;
			}else if (1+rand()%(2) == 2 && Objetos.Virus6.y > 10){
				Objetos.Virus6.y -= 2;
			}
		}
		Objetos.Virus6.x--;
		MostrarVirus(Objetos.Virus6.indice, Objetos.Virus6.x, Objetos.Virus6.y);
	}

}







