/*--------------------------------------------------------------------------------------------------------------
									funciones.c
---------------------------------------------------------------------------------------------------------------*/
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


/*-----------------------------------------------------------------------------------------------------------
								FUNCIONES PANTALLA TACTIL
------------------------------------------------------------------------------------------------------------*/

// Esta función detecta si la pantalla ha sido tocada.
bool touchingScreen() {
	touchPosition pos_pantalla;
	touchRead(&pos_pantalla);
  	return pos_pantalla.px != 0 && pos_pantalla.py != 0;
}

// En esta función se detecta si la pantalla ha sido tocada, dentro del cuadro de Play.
bool playButton() {
	touchPosition pos_pantalla;
	touchRead(&pos_pantalla);
  	return pos_pantalla.px > 75 && pos_pantalla.px < 205 &&
  		pos_pantalla.py > 40 && pos_pantalla.py < 95;
}

// En esta función se detecta si la pantalla ha sido tocada, dentro del cuadro de instrucciones.
bool instructionButton() {
	touchPosition pos_pantalla;
	touchRead(&pos_pantalla);
  	return pos_pantalla.px > 105 && pos_pantalla.px < 175 &&
  		   pos_pantalla.py > 108 && pos_pantalla.py < 126;
}

/*-----------------------------------------------------------------------------------------------------------
								FUNCIONES BÁSICAS PANTALLA
------------------------------------------------------------------------------------------------------------*/

// Se escribe en pantalla un mensaje informativo sobre el funcionamiento del juego.
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

// Se escribe en pantalla un mensaje informativo sobre el juego y el estado de los puntos/segundos.
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

// Se muestran en pantalla el bote y las personas.
void printGameScreen() {
	MostrarPersonas();
	MostrarSpray(Objetos.Spray.x, Objetos.Spray.y);
}

// Esta función actualiza el número de segundos trascurridos durante el juego en pantalla.
void printSegs() {
	iprintf("\x1b[08;13H %d", Estado.segs0);
}

// Esta función calcula y actualiza el nivel de dificultad del juego, en función del tiempo trascurrido. 
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

// Esta función actualiza en pantalla el número de personas infectadas.
void printInfectados() {
	iprintf("\x1b[12;00H  Infectados: %d", Estado.infectedpeople);
}

// Esta función actualiza el número de viruses eliminados en pantalla.
void printVirusKilled() {
	iprintf("\x1b[14;23H %d", Estado.viruskilled);
}

// Esta función escribe en pantalla un mensaje cuando el juego se encuentra en pausa.
void printPausa() {
	consoleDemoInit();
	iprintf("\x1b[12;00H         --- PAUSA ---            ");
	iprintf("\x1b[14;00H   Pulsa START para continuar     ");
}

// Esta función escribe un mensaje en pantalla, en el momento que el juego se acaba.
void printRestart() {
	consoleDemoInit();
	iprintf("\x1b[10;00H      --- HAS PERDIDO ---         ");
	iprintf("\x1b[12;00H     Pulsa START para jugar       ");
	iprintf("\x1b[13;00H            de nuevo              ");

	iprintf("\x1b[15;00H       Pulsa SELECT para          ");
	iprintf("\x1b[16;00H       apagar la consola          ");
}

// Esta función "contruye" el sprite de una persona entera.
void MostrarPersona(int indice, int x, int y) {
	MostrarP1Arriba(indice,x,y);
	MostrarP1Abajo (indice+1,x,y+16);
}

// Esta función hace que se muestren en pantalla las personas.
void MostrarPersonas() {
	int i = 0;
	while (i < numPersonaT) {
		MostrarPersona(Objetos.Persona[i].indiceArriba, Objetos.Persona[i].x, Objetos.Persona[i].y);
		i++;
	}
}


/*-----------------------------------------------------------------------------------------------------------
								FUNCIONES INICIALIZACIÓN
------------------------------------------------------------------------------------------------------------*/

// Se inicializan los detalles del juego.
void initVarEstado() {
	Estado.dificultad = 1;
	Estado.initdone = false;
	Estado.instructdone = false;
	Estado.numVirus = 0;
	Estado.numGota = 0;
	Estado.infectedpeople = 0;
	Estado.viruskilled =  0;
	Estado.restartdone = false;
	Estado.canshot = true;
	Estado.segs0 = 0;
}

// En esta función se inicializan las variables del juego, las características y las coordenadas de los sprites.
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


/*-----------------------------------------------------------------------------------------------------------
								FUNCIONES PRINCIPALES
							  ACTUALIZACIÓN Y DETECCIÓN
------------------------------------------------------------------------------------------------------------*/

// Esta función hace que se actualice la posición del desinfectante.
void updateSpray() {
	if (Objetos.Spray.dir == UP && Objetos.Spray.y > 3) {
		Objetos.Spray.y = Objetos.Spray.y - 1;
	}
	else if (Objetos.Spray.dir == DOWN && Objetos.Spray.y < 160) {
		Objetos.Spray.y = Objetos.Spray.y + 1;
	}
	MostrarSpray(Objetos.Spray.x, Objetos.Spray.y);
}


// Esta función hace que se spawnee una gota.
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

// Esta función hace que se actualice en pantalla la posición de las gotas.
void updateDrop() {
	int i = 0;
	while (i < numGotaT) {
		if (Objetos.Gota[i].visible){
	       	Objetos.Gota[i].x = Objetos.Gota[i].x + 1;
	       	MostrarGota(Objetos.Gota[i].indice, Objetos.Gota[i].x, Objetos.Gota[i].y);
			if (Objetos.Gota[i].x > 240) {
				Objetos.Gota[i].visible = false;
				BorrarGota(Objetos.Gota[i].indice, Objetos.Gota[i].x, Objetos.Gota[i].y);
			}
		}
		i++;
	}
}

// Esta función hace que se spawnee un virus en una posición 'x' fija y en una 'y' aleatoria.
void spawnVirus(){
	int n = Estado.numVirus;
	Objetos.Virus[n].visible = true;
	Objetos.Virus[n].x = 250;
	Objetos.Virus[n].y = rand()% (170-10+1) + 5;
	MostrarVirus(Objetos.Virus[n].indice, Objetos.Virus[n].x, Objetos.Virus[n].y);
	if (n < numVirusT-1) {
		Estado.numVirus = Estado.numVirus + 1;
	}
	else {
		Estado.numVirus = 0;
	}
}

// Esta función hace que se actualice la posición de los viruses siguiendo una trayectoria definida por la dificultad.
void updateVirus() {
	int i = 0;
	if (Estado.dificultad == 1) {
		while (i < numVirusT) {
			if(Objetos.Virus[i].visible && Objetos.Virus[i].x < 5){
				Objetos.Virus[i].visible = false;
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
			if(Objetos.Virus[i].visible && Objetos.Virus[i].x < 5){
				Objetos.Virus[i].visible = false;
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
			if(Objetos.Virus[i].visible && Objetos.Virus[i].x < 5){
				Objetos.Virus[i].visible = false;
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

// Esta función hace que se dispare una gota controlando el tiempo de recarga.
void shot() {
	if (Estado.canshot) {
		spawnDrop();
		Estado.canshot = false;
	}
}

// Esta función verifica si un virus ha sido eliminado, es decir, si una gota ha llegado a tocar un virus.
void checkVirusKill() {
	int i = 0;
	int j = 0;
	while (i < numGotaT) {
		if (Objetos.Gota[i].visible) {
			while (j < numVirusT) {
				if (Objetos.Virus[j].visible &&
					Objetos.Gota[i].x <= Objetos.Virus[j].x && 
					Objetos.Virus[j].x <= Objetos.Gota[i].x+2 &&
					Objetos.Gota[i].y-10 <= Objetos.Virus[j].y &&
					Objetos.Virus[j].y <= Objetos.Gota[i].y+18) {

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

// Esta función detecta cuándo las personas se infectan, es decir, cuando un virus llega a la posición de una persona.
void detectInfection() {
	int i = 0;
	int j = 0;
	while (i < numVirusT) {
		if (Objetos.Virus[i].visible && Objetos.Virus[i].x < 10) {
			while (j < numPersonaT) {
				if (Objetos.Persona[j].infectado == false &&
					Objetos.Persona[j].y-3 <= Objetos.Virus[i].y &&
					Objetos.Virus[i].y <= Objetos.Persona[j].y + 32) {

						BorrarP1Arriba(Objetos.Persona[j].indiceArriba, Objetos.Persona[j].x, Objetos.Persona[j].y);
						BorrarP1Abajo(Objetos.Persona[j].indiceAbajo, Objetos.Persona[j].x, Objetos.Persona[j].y+16);
						MostrarP2Arriba(Objetos.Persona[j].indiceArriba, Objetos.Persona[j].x, Objetos.Persona[j].y);
						MostrarP2Abajo(Objetos.Persona[j].indiceAbajo, Objetos.Persona[j].x, Objetos.Persona[j].y+16);
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

// Esta función detecta cuándo se han infectado las 5 personas y el juego se da por finalizado.
void detectGameFinish() {
	if (Estado.infectedpeople == 5) {
		Estado.estado = RESTART;
	}
}




