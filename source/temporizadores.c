/*----------------------------------------------------------
			temporizadores.c
----------------------------------------------------------*/
// Añadir los includes que sean necesarios
#include "defines.h"
#include "sprites.h"
#include <nds.h>
#include <stdio.h>


// Rutina de atención a la interrupción del temporizador
void IntTemp() {

	static int tick = 0;

	tick++;

}





