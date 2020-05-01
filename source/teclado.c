/*-------------------------------------
 teclado.c
-------------------------------------*/

// Añadir los includes que sean necesarios
#include <nds.h>
#include <stdio.h>
#include "defines.h"
#include "sprites.h"
#include "funciones.h"


// Esta funcion tiene que devolver el valor de la tecla pulsada
int  TeclaPulsada() {
	if 	   ((TECLAS_DAT & 0x0001)==0)	 return A;
	else if((TECLAS_DAT & 0x0002)==0)return B;
	else if((TECLAS_DAT & 0x0004)==0)return SELECT;
	else if((TECLAS_DAT & 0x0008)==0)return START;
	else if((TECLAS_DAT & 0x0010)==0)return LEFT;
	else if((TECLAS_DAT & 0x0020)==0)return RIGHT;
	else if((TECLAS_DAT & 0x0040)==0)return UP;
	else if((TECLAS_DAT & 0x0080)==0)return DOWN;
	else if((TECLAS_DAT & 0x0100)==0)return R;
	else if((TECLAS_DAT & 0x0200)==0)return L;
	else return -1;
}


// Rutina de atencion a la interrupcion del teclado
void IntTec() {
	switch(Estado.estado) {
		case GAME:
			switch(TeclaPulsada()) {
				case A:
					shot();
					break;
				case UP:
					Objetos.Spray.dir = UP;
					break;
				case START:
					Estado.estado = PAUSE;
					printPausa();
					break;
			}
			break;
		case PAUSE:
			switch(TeclaPulsada()) {
				case START:
					Estado.estado = GAME;
					printBasicInfo();
					break;
			}
			break;
			
	}

}



