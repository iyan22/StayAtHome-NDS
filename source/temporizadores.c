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
	tick0++;
	updateSpray();
	if (tick0 == 60) {
		tick0 = 0;
		segs0++;
		iprintf("\x1b[12;13H %d", segs0);
	}
}

/*
void IntTemp1() {
	static int tick1 = 0;
	tick1++;
	if (tick1 == 1) {
		tick1 = 0;
		segs1++;
		iprintf("\x1b[12;15H %d", segs1);
	}
}
*/








