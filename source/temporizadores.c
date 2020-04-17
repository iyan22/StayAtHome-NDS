/*----------------------------------------------------------
			temporizadores.c
----------------------------------------------------------*/
// Añadir los includes que sean necesarios
#include "defines.h"
#include "sprites.h"
#include <nds.h>
#include <stdio.h>


// Rutina de atención a la interrupción del temporizador
void IntTemp0() {
	static int tick0 = 0;
	tick0++;
	if (tick0 == 60) {
		tick0 = 0;
		segs0++;
		iprintf("\x1b[12;13H %d", segs0);
	}
}

// Rutina de atención a la interrupción del temporizador
void IntTemp1() {

	static int tick1 = 0;
	tick1++;
	if (tick1 == 1) {
		tick1 = 0;
		segs1++;
		iprintf("\x1b[14;13H %d", segs1);
	}
}






