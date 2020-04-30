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
	}
	if (tick0 == 60) {									// Cuando tenemos 60 tick0
		tick0 = 0;										// Restablecemos tick0
		if (Estado.estado == GAME) {					// Si estamos en estado GAME
			if (Estado.segs0 % 7 == 0){
				spawnVirus();							// Generamos virus
				calculateDifficulty();
				printInfectados();
			}
			Estado.segs0++;								// Sumamos 1 a segs0 (seg jugando)
			iprintf("\x1b[10;13H %d", Estado.segs0);	// Imprimimos en pantalla segs0
		}
	}
}

void IntTemp1() {
	static int tick1 = 0;
	tick1++;
	if (Estado.estado == GAME) {
		updateDrop();							// Actualizamos posición Gotas	
	}
	if (tick1 == 1) {
		tick1 = 0;
	}
}










