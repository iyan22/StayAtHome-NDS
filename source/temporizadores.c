/*----------------------------------------------------------
			temporizadores.c
----------------------------------------------------------*/
// Añadir los includes que sean necesarios
#include "defines.h"
#include "sprites.h"
#include "funciones.h"
#include <nds.h>
#include <stdio.h>


// Rutina de atención a la interrupción del temporizador
// 60 ticks/seg
//	- cada tick actualizamos la posición del Spray
//	- cada 60 ticks sumamos un segundo
void IntTemp0() {
	static int tick0 = 0;
	tick0++;										// Sumamos 1 a tick0
	if (estado == GAME) {							// Si estamos en estado GAME
		updateSpray();								// Actualizamos posición Spray 60 veces/seg
	}
	if (tick0 == 60) {								// Cuando tenemos 60 tick0
		tick0 = 0;									// Restablecemos tick0
		if (estado == GAME) {						// Si estamos en estado GAME
			spawnVirus();							// Generamos virus
			segs0++;								// Sumamos 1 a segs0 (seg jugando)
			iprintf("\x1b[12;13H %d", segs0);		// Imprimimos en pantalla
		}
	}
}

// Rutina de atención a la interrupción del temporizador
// 2 ticks/seg
//	- cada tick actualizamos fondo en inicio
//  - cada medio seg cambia fondo en INIT para generar animación
void IntTemp1() {
	static int tick1 = 0;
	tick1++;										// Sumamos 1 a tick1
	if (tick1 == 1) {								// Si tick = 1
		if (estado == INIT) {						// Y estado INIT
				MostrarInicio1();					// Fondo Incio1
		}
	}
	else {											// Sino
		if (estado == INIT) {						// Si estado INIT
			MostrarInicio2();						// Fondo Inicio2
			tick1 = 0;								// Restablecemos tick1
		}
	}
}










