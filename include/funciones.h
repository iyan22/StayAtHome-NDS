#include <nds.h>
#include <stdio.h>
#include <stdlib.h>	// srand, rand,...
#include <unistd.h>
#include <time.h>       // time 

// Esta función consulta si se ha tocado la pantalla tactil
extern int playButton();
extern int instructionButton();
extern int touchingScreen();

extern void printInstructions();
extern void printBasicInfo();
extern void printGameScreen();
extern void initVarGameScreen();
extern void updateSpray();


