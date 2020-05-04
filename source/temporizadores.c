/*---------------------------------------------------------------------------------------------------
											temporizadores.c
---------------------------------------------------------------------------------------------------*/


// Añadir los includes que vayan a ser utilizados o sean necesarios
#include "defines.h"
#include "sprites.h"
#include "funciones.h"
#include "fondos.h"
#include <nds.h>
#include <stdio.h>


/*
Rutina de atención a la interrupción del temporizador TIMER0
60 ticks/seg
 - cada tick:
 	+ actualizamos Spray
 	+ actualizamos Virus
 	+ imprimimos virus muertos totales
 	+ detectamos infeccion
 	+ detectamos posible final del juego
 - cada 60 ticks:
 	+ restablecemos tick0
 	+ sumamos 1 seg
 	+ imprimimos segs
 	+ cada 2 segs:
 		* Spawneamos Virus
 		* Recalculamos dificultad
*/
void IntTemp0() {
	static int tick0 = 0;
	tick0++;											// Sumamos 1 tick0
	if (Estado.estado == GAME) {						// Si estamos en estado GAME
		updateSpray();									// Actualizamos posición Spray
		updateVirus();									// Actualizamos posición Viruses
		printVirusKilled();								// Imprimimos virus muertos totales
		detectInfection();								// Detectamos si se infecta persona
		detectGameFinish();								// Detectamos final del juego
		if (tick0 == 30) {
		Estado.canshot = true;
		}		
	}
	if (tick0 == 60) {									// Cuando tenemos 60 tick0
		tick0 = 0;										// Restablecemos tick0
		Estado.canshot = true;
		if (Estado.estado == GAME) {					// Si estamos en estado GAME
			calculateDifficulty();						// Recalculamos dificultad
			if (Estado.dificultad == 1 ||
			    Estado.dificultad == 3	) {
				if (Estado.segs0 % 2 == 0){					// Cada 2 segs
					spawnVirus();							// Generamos virus
				}
			} else {
				if (Estado.segs0 % 1 == 0){					// Cada 2 segs
					spawnVirus();							// Generamos virus
				}
			}
			Estado.segs0 = Estado.segs0 + 1;			// Sumamos 1 a segs0 (seg jugando)
			printSegs();								// Imprimimos en pantalla segs0
		}
	}
}

/*
Rutina de atención a la interrupción del temporizador TIMER1
100 ticks/seg
 - cada tick:
 	+ actualizamos Gota
 	+ revisar impacto Gota con Virus
*/
void IntTemp1() {
	static int tick1 = 0;
	tick1++;											// Sumamos 1 a tick1
	if (Estado.estado == GAME) {						// Si estamos en GAME
		updateDrop();									// Actualizamos posición Gotas
		checkVirusKill();								// Revisamos si Gota toca Virus
	}
	if (tick1 == 1) {									// Si tick1		
		tick1 = 0;										// Restablecemos tick1
	}
}










