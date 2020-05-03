/*----------------------------------------------------------------------------------------------------------------------
												defines.h
----------------------------------------------------------------------------------------------------------------------*/

#include <nds.h>
#include <stdio.h>

// Aquí se definen los registros del gestor de interrupciones
#define IME		(*(vuint16*)0x04000208) // Interrupt Master Enable - Habilita o deshabilita todas las interrupciones
#define IE		(*(vuint32*)0x04000210) // Interrupt Enable - Activa o desactiva las interrupciones una a una
#define IF		(*(vuint32*)0x04000214) // Interrupt Flag - Guarda las peticiones de interrupción

// Aquí se definen algunas funciones para el tratamiento de las interrupciones
#define EnableInts() 	IME = 1 // Habilita todas las interrupciones
#define DisableInts() 	IME = 0 // Deshabilita todas las interrupciones

// Aquí se definen los registros del teclado 
#define TECLAS_DAT	(*(vuint16*)0x4000130) // Registro de datos del teclado
#define TECLAS_CNT	(*(vuint16*)0x4000132) // Registro de control del teclado

// Aquí se definen los registros del temporizador
#define TIMER0_CNT   	(*(vuint16*)0x04000102) // Registro de control del temporizador TIMER0
#define TIMER1_CNT   	(*(vuint16*)0x04000106) // Registro de control del temporizador TIMER1

#define TIMER0_DAT    (*(vuint16*)0x04000100) // Registro de datos del temporizador TIMER0
#define TIMER1_DAT    (*(vuint16*)0x04000104) // Registro de datos del temporizador TIMER1

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

// Constante
#define numVirusT 		6
#define numGotaT 		8
#define numPersonaT		5	


// Typedefs
typedef struct {
   int x;
   int y;
   int dir;
} tSpray;

typedef struct {
	int x;
	int y;
	int indice;
	bool visible;
} tGota;

typedef struct {
	int x;
	int y;
	int indice;
	bool visible;
} tVirus;

typedef struct {
	int x;
	int y;
	int indiceArriba;
	int indiceAbajo;
	bool infectado;
} tPersona;

typedef struct {
	tSpray Spray;
	tVirus Virus[numVirusT];
	tGota Gota[numGotaT];
	tPersona Persona[numPersonaT];
} tObjetos;

typedef struct {
	int estado;
	int segs0;
	int numVirus;
	int numGota;
	int dificultad;
	int viruskilled;
	int infectedpeople;
	bool canshot;
	bool initdone;
	bool instructdone;
	bool restartdone;
} tEstado;

// Variables globales
extern tObjetos Objetos;
extern tEstado Estado;




