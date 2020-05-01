/*----------------------------------------------------------
			temporizadores.c
----------------------------------------------------------*/
// Añadir los includes que sean necesarios
#include "defines.h"
#include "sprites.h"
#include "funciones.h"
#include "fondos.h"
#include <nds.h>
#include <stdio.h>


// Rutina de atención a la interrupción del temporizador
// 60 ticks/seg
//	- cada tick actualizamos la posición del Spray
//	- cada 60 ticks sumamos un segundo
void IntTemp0() {
	static int tick0 = 0;
	tick0++;											// Sumamos 1 a tick0
	if (Estado.estado == GAME) {						// Si estamos en estado GAME
		updateSpray();									// Actualizamos posición Spray
		updateVirus();									// Actualizamos posición Viruses
		printVirusKilled();	
		detectInfection();
		detectGameFinish();						
	}
	if (tick0 == 60) {									// Cuando tenemos 60 tick0
		tick0 = 0;										// Restablecemos tick0
		if (Estado.estado == GAME) {					// Si estamos en estado GAME
			if (Estado.segs0 % 2 == 0){
				spawnVirus();							// Generamos virus
				calculateDifficulty();
			}
			Estado.segs0 = Estado.segs0 + 1;			// Sumamos 1 a segs0 (seg jugando)
			printSegs();	// Imprimimos en pantalla segs0
		}
	}
}

void IntTemp1() {
	static int tick1 = 0;
	tick1++;
	if (Estado.estado == GAME) {
		updateDrop();							// Actualizamos posición Gotas
		checkVirusKill();
	}
	if (tick1 == 1) {
		tick1 = 0;
	}
}










