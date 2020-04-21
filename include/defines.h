/*-------------------------------------
defines.h
-------------------------------------*/

#include <nds.h>
#include <stdio.h>

// Aquí se definen los registros del gestor de interrupciones
#define IME		(*(vuint16*)0x04000208) //Interrupt Master Enable - Habilita o deshabilita todas las interrupciones
#define IE		(*(vuint32*)0x04000210) //Interrupt Enable - Activa o desactiva las interrupciones una a una
#define IF		(*(vuint32*)0x04000214) //Interrupt Flag - Guarda las peticiones de interrupción

// Aquí se definen algunas funciones para el tratamiento de las interrupciones
#define EnableInts() 	IME=1 //Habilita todas las interrupciones
#define DisableInts() 	IME=0 //Deshabilita todas las interrupciones

// Aquí se definen los registros del teclado 
#define TECLAS_DAT	(*(vuint16*)0x4000130) //Registro de datos del teclado
#define TECLAS_CNT	(*(vuint16*)0x4000132) //Registro de control del teclado

// Aquí se definen los registros del temporizador
#define TIMER0_CNT   	(*(vuint16*)0x04000102) //Registro de control del temporizador
#define TIMER1_CNT   	(*(vuint16*)0x04000106) 
// El temporizador se activa poniendo un 1 en el 7º bit.
// El temporizador interrumpirá al desbordarse el contador, si hay un 1 en el 6º bit.
// Los dos bits de menos peso indican lo siguiente:
//		00 frecuencia 33554432 hz
//		01 frecuencia 33554432/64 hz
//		10 frecuencia 33554432/256 hz
//		11 frecuencia 33554432/1024 hz

#define TIMER0_DAT    (*(vuint16*)0x04000100) //Registro de datos del temporizador
#define TIMER1_DAT    (*(vuint16*)0x04000104) 
// Se utiliza para indicar a partir de qué valor tiene que empezar a contar

// Para no liarse con los números a cada teclas se le ha asignado un nombre

#define A			0 
#define B			1
#define SELECT		2 
#define START		3
#define LEFT		4 
#define RIGHT		5
#define UP			6 
#define DOWN		7
#define R			8 
#define L			9

// Asignar un nombre a cada estado
#define INIT 		0
#define GAME 		1
#define PAUSE 		2
#define RESTART 	3
#define END 		4


// Implement typedef



// Variables globales
extern int estado;
extern int tsegs;
extern int segs0;
extern int segs1;

extern int dirSp;
extern int speSp;
extern int ySp;


