#include <nds.h>
#include <stdio.h>
#include <stdlib.h>	// srand, rand,...
#include <unistd.h>
#include <time.h>       // time 

#include "defines.h"
#include "fondos.h"
#include "sprites.h"
#include "rutserv.h"
#include "teclado.h"
#include "temporizadores.h"

// Esta función consulta si se ha tocado la pantalla tactil
extern int tactilTocada();

extern void printBasicInfo();
extern void initGameScreen();
