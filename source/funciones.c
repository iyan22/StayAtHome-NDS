
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


bool touchingScreen() {
	touchPosition pos_pantalla;
	touchRead(&pos_pantalla);
  	return pos_pantalla.px != 0 && pos_pantalla.py != 0;
}

bool playButton() {
	touchPosition pos_pantalla;
	touchRead(&pos_pantalla);
  	return pos_pantalla.px > 75 && pos_pantalla.px < 205 &&
  		pos_pantalla.py > 40 && pos_pantalla.py < 95;
}

bool instructionButton() {
	touchPosition pos_pantalla;
	touchRead(&pos_pantalla);
  	return pos_pantalla.px > 105 && pos_pantalla.px < 175 &&
  		   pos_pantalla.py > 108 && pos_pantalla.py < 126;
}

void printInstructions() {
	iprintf("\x1b[01;00H   Welcome to StayAtHome-NDS  ");
 	iprintf("\x1b[03;00H          Instructions:       ");
 	iprintf("\x1b[05;00H   Press PLAY (touchscreen)   ");
	iprintf("\x1b[07;00H   Kill COVID-19 viruses with ");
	iprintf("\x1b[08;00H   the hidroalcoholic gel     ");
	iprintf("\x1b[09;00H   Press A to shot.           ");
	iprintf("\x1b[11;00H   Move the hidroalcoholic gel");
	iprintf("\x1b[12;00H   pressing UP and DOWN       ");
	iprintf("\x1b[14;00H          BE CAREFUL!!!       ");
	iprintf("\x1b[16;00H     If virus touches people  ");
	iprintf("\x1b[17;00H      they will be infected   ");
	iprintf("\x1b[20;00H   Developed by:              ");
	iprintf("\x1b[22;00H   Iyan A. Unai R. Aleina P.  ");
}

void printBasicInfo() {
	consoleDemoInit();
	iprintf("\x1b[01;00H  +--------------------------+ ");
 	iprintf("\x1b[02;00H  : EC                 19/20 : ");
 	iprintf("\x1b[03;00H  +--------------------------+ ");
	iprintf("\x1b[06;00H    Project StayAtHome - NDS   ");
	iprintf("\x1b[08;00H  Segundos:");
	iprintf("\x1b[14;00H  COVID-19 eliminados:");
	iprintf("\x1b[20;00H          Grupo 2A03           ");
	iprintf("\x1b[22;00H    Iyan A. Unai R. Aleina P.  ");
	printInfectados();
	calculateDifficulty();
}

void initVarEstado() {
	Estado.dificultad = 1;
	Estado.initdone = false;
	Estado.instructdone = false;
	Estado.numVirus = 0;
	Estado.numGota = 0;
	Estado.infectedpeople = 0;
	Estado.viruskilled =  0;
	Estado.restartdone = false;
}

void printGameScreen() {
	MostrarPersonas();
	MostrarSpray(Objetos.Spray.x, Objetos.Spray.y);
}

void initVarGameScreen() {

	Objetos.Spray.x = 28;
	Objetos.Spray.y = 85;
	Objetos.Spray.dir = 0;

	int i = 0;
	while (i < numVirusT) {
		Objetos.Virus[i].indice = i;
		Objetos.Virus[i].visible = false;
		Objetos.Virus[i].x = 250;
		Objetos.Virus[i].y = 0;
		i++;
	}

	i = 0;
	while (i < numGotaT) {
		Objetos.Gota[i].indice = 10 + i;
		Objetos.Gota[i].visible = false;
		Objetos.Gota[i].x = 0;
		Objetos.Gota[i].y = 0;
		i++;
	}

	i = 0;
	while (i < numPersonaT) {
		Objetos.Persona[i].indiceArriba = 20 + (i*2);
		Objetos.Persona[i].indiceAbajo = 20 + (i*2) +1;
		Objetos.Persona[i].infectado = false;
		Objetos.Persona[i].x = 10;
		Objetos.Persona[i].y = 5 + 35*i;
		i++;
	}
}

void MostrarPersona(int indice, int x, int y) {
	MostrarP1Arriba(indice,x,y);
	MostrarP1Abajo (indice+1,x,y+16);
}

void MostrarPersonas() {
	int i = 0;
	while (i < numPersonaT) {
		MostrarPersona(Objetos.Persona[i].indiceArriba, Objetos.Persona[i].x, Objetos.Persona[i].y);
		i++;
	}
}

void updateSpray() {
	if (Objetos.Spray.dir == UP && Objetos.Spray.y > 3) {
		Objetos.Spray.y = Objetos.Spray.y - 1;
	}
	else if (Objetos.Spray.dir == DOWN && Objetos.Spray.y < 160) {
		Objetos.Spray.y = Objetos.Spray.y + 1;
	}
	MostrarSpray(Objetos.Spray.x, Objetos.Spray.y);
}

void spawnVirus(){
	int n = Estado.numVirus;
	Objetos.Virus[n].visible = true;
	Objetos.Virus[n].x = 250;
	Objetos.Virus[n].y = rand()% (170-10+1) + 5;
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
	if (Estado.dificultad == 1) {
		while (i < numVirusT) {
			if(Objetos.Virus[i].x < 5){
				BorrarVirus(Objetos.Virus[i].indice, Objetos.Virus[i].x, Objetos.Virus[i].y);
			}
			else if (Objetos.Virus[i].visible){
	       		Objetos.Virus[i].x = Objetos.Virus[i].x - 1;
	        	MostrarVirus(Objetos.Virus[i].indice, Objetos.Virus[i].x, Objetos.Virus[i].y);
			}
			i++;
    	}
	}
	else if (Estado.dificultad >= 2) {
		while (i < numVirusT) {
			if(Objetos.Virus[i].x < 10){
				BorrarVirus(Objetos.Virus[i].indice, Objetos.Virus[i].x, Objetos.Virus[i].y);
			}
			else if (Objetos.Virus[i].visible) {
				if ( rand()%5 == 0 && Objetos.Virus[i].y < 170){
						Objetos.Virus[i].y = Objetos.Virus[i].y + 1;
					}
				else if ( rand()%5 == 0 && Objetos.Virus[i].y > 10){
						Objetos.Virus[i].y = Objetos.Virus[i].y - 1;
				}
				Objetos.Virus[i].x = Objetos.Virus[i].x - 1;
				MostrarVirus(Objetos.Virus[i].indice, Objetos.Virus[i].x, Objetos.Virus[i].y);
			}
			i++;
		}
	}
	else {
		while (i < numVirusT) {
			if(Objetos.Virus[i].x < 10){
				BorrarVirus(Objetos.Virus[i].indice, Objetos.Virus[i].x, Objetos.Virus[i].y);
			}
			else if (Objetos.Virus[i].visible) {
				if ( rand()%2 == 0 && Objetos.Virus[i].y < 170){
					Objetos.Virus[i].y = Objetos.Virus[i].y - 2;
				}
				else if ( rand()%2 == 0 && Objetos.Virus[i].y > 10){
					Objetos.Virus[i].y = Objetos.Virus[i].y + 2;
				}
				Objetos.Virus[i].x = Objetos.Virus[i].x - 1;
				MostrarVirus(Objetos.Virus[i].indice, Objetos.Virus[i].x, Objetos.Virus[i].y);
			}
			i++;
		}
	}
}

void spawnDrop() {
	int n = Estado.numGota;
	Objetos.Gota[n].visible = true;
	Objetos.Gota[n].x = Objetos.Spray.x + 16;
	Objetos.Gota[n].y = Objetos.Spray.y;
	MostrarGota(Objetos.Gota[n].indice, Objetos.Gota[n].x, Objetos.Gota[n].y);
	if (n < numGotaT-1) {
		Estado.numGota++;
	}
	else {
		Estado.numGota = 0;
	}
}

void updateDrop() {
	int i = 0;
	while (i < numGotaT) {
		if (Objetos.Gota[i].visible){
	       	Objetos.Gota[i].x = Objetos.Gota[i].x + 1;
	       	MostrarGota(Objetos.Gota[i].indice, Objetos.Gota[i].x, Objetos.Gota[i].y);
		}
		if (Objetos.Gota[i].x > 240) {
			Objetos.Gota[i].visible = false;
			BorrarGota(Objetos.Gota[i].indice, Objetos.Gota[i].x, Objetos.Gota[i].y);
		}
		i++;
   	}
}

void shot() {
	spawnDrop();
}

void calculateDifficulty() {
	if (Estado.segs0 < 60) {
		Estado.dificultad = 1;
		iprintf("\x1b[10;00H  Dificultad: Facil    ");
	}
	else if (Estado.segs0 < 120) {
		Estado.dificultad = 2;
		iprintf("\x1b[10;00H  Dificultad: Media    ");
	}
	else {
		Estado.dificultad = 3;
		iprintf("\x1b[10;00H  Dificultad: Dificil  ");
	}
}

void printInfectados() {
	iprintf("\x1b[12;00H  Infectados: %d", Estado.infectedpeople);
}

void printPausa() {
	consoleDemoInit();
	iprintf("\x1b[12;00H         --- PAUSA ---            ");
	iprintf("\x1b[14;00H   Pulsa START para continuar     ");
}



void checkVirusKill() {
	int i = 0;
	int j = 0;
	while (i < numGotaT) {
		if (Objetos.Gota[i].visible) {
			while (j < numVirusT) {
				if (Objetos.Virus[j].visible &&
					Objetos.Gota[i].x <= Objetos.Virus[j].x && 
					Objetos.Virus[j].x <= Objetos.Gota[i].x+5) {
						Objetos.Virus[j].visible = false;
						Objetos.Gota[i].visible = false;
						BorrarVirus(Objetos.Virus[j].indice, Objetos.Virus[j].x, Objetos.Virus[j].y);
						BorrarGota(Objetos.Gota[i].indice, Objetos.Gota[i].x, Objetos.Gota[i].y);
						Estado.viruskilled = Estado.viruskilled + 1;
				}
				j++;
			}
		}
		i++;
	}
}

void printVirusKilled() {
	iprintf("\x1b[14;23H %d", Estado.viruskilled);
}

void printSegs() {
	iprintf("\x1b[08;13H %d", Estado.segs0);
}

void detectInfection() {
	int i = 0;
	int j = 0;
	while (i < numVirusT) {
		if (Objetos.Virus[i].visible && Objetos.Virus[i].x < 10) {
			while (j < numPersonaT) {
				if (5+(35*j) <= Objetos.Virus[i].y && Objetos.Virus[i].y <= 5+(35*j)+35 && 
					!Objetos.Persona[j].infectado){
					BorrarP1Arriba(Objetos.Persona[j].indiceArriba, 10, 5+(35*j));
					BorrarP1Abajo(Objetos.Persona[j].indiceAbajo, 10, 5+(35*j)+16);
					MostrarP2Arriba(Objetos.Persona[j].indiceArriba, 10, 5+(35*j));
					MostrarP2Abajo(Objetos.Persona[j].indiceAbajo, 10, 5+(35*j)+16);
					BorrarVirus(Objetos.Virus[i].indice, Objetos.Virus[i].x, Objetos.Virus[i].y);
					Objetos.Persona[j].infectado = true;
					Objetos.Virus[i].visible = false;
					Estado.infectedpeople = Estado.infectedpeople + 1;
					printInfectados();
				}
				j++;
			}
		}
		i++;
	}
}

void printRestart() {
	consoleDemoInit();
	iprintf("\x1b[10;00H      --- HAS PERDIDO ---         ");
	iprintf("\x1b[12;00H     Pulsa START para jugar       ");
	iprintf("\x1b[13;00H            de nuevo              ");

	iprintf("\x1b[15;00H       Pulsa SELECT para          ");
	iprintf("\x1b[16;00H       apagar la consola          ");

}

void detectGameFinish() {
	if (Estado.infectedpeople == 5) {
		Estado.estado = RESTART;
	}
}




