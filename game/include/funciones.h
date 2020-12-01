#include <nds.h>
#include <stdio.h>
#include <stdlib.h>		// srand, rand,...
#include <unistd.h>
#include <time.h>       // time 


// Funciones pantalla táctil
extern bool playButton();
extern bool instructionButton();
extern bool touchingScreen();

// Funciones básicas pantalla
extern void printInstructions();
extern void printBasicInfo();
extern void printGameScreen();
extern void printInstructions();
extern void printSegs();
extern void calculateDifficulty();
extern void printInfectados();
extern void printVirusKilled();
extern void printPausa();
extern void printRestart();
extern void MostrarPersonas();
extern void MostrarPersona(int indice, int x, int y);
extern void limpiarPantalla();

// Funciones inicialización
extern void initVarEstado();
extern void initVarGameScreen();

//   Funciones principales
// actualización y detección
extern void updateSpray();
extern void spawnDrop();
extern void updateDrop();
extern void spawnVirus();
extern void updateVirus();
extern void shot();
extern void checkVirusKill();
extern void detectInfection();
extern void detectGameFinish();
