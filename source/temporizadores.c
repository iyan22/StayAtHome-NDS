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
	if (estado == GAME) {
		updateSpray();
	}
	if (tick0 == 60) {
		tick0 = 0;
		segs0++;
		iprintf("\x1b[12;13H %d", segs0);

		if (estado == INIT) {
			if 		(segs0%5==0) {MostrarInicio1();}
			else if (segs0%5==1) {MostrarInicio2();}
			else if (segs0%5==2) {MostrarInicio3();}
			else if (segs0%5==3) {MostrarInicio2();}
			else if (segs0%5==4) {MostrarInicio1();}
		}
	}
}

/*
void IntTemp1() {
	static int tick1 = 0;
	tick1++;
	
}
*/









