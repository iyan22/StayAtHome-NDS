#include <nds.h>
#include <stdio.h>
#include <stdlib.h>	// srand, rand,...
#include <unistd.h>
#include <time.h>       // time 

// Esta función consulta si se ha tocado la pantalla tactil
extern int calculateInfectados();

extern bool playButton();
extern bool instructionButton();
extern bool touchingScreen();


extern void printInstructions();
extern void printBasicInfo();
extern void printInstructions();
extern void initVarEstado();
extern void printGameScreen();
extern void initVarGameScreen();
extern void MostrarPersonas();
extern void MostrarPersona(int indice, int x, int y);
extern void updateSpray();
extern void spawnVirus();
extern void updateVirus();
extern void spawnDrop();
extern void updateDrop();
extern void shot();
extern void calculateDifficulty(int segs);
extern void printInfectados();


