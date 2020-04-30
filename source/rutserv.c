/*-------------------------------------
 rutserv.c
-------------------------------------*/
// Añadir los includes que sean necesarios
#include <nds.h>
#include <stdio.h>
#include "teclado.h"
#include "defines.h"
#include "temporizadores.h"

// Este procedimiento inicializa la tabla de interrupciones para que el gestor de interrupciones sepa
// qué rutina de atención tiene que ejecutar cuando le llega una petición de interrupción. 
// Además es aquí donde se configuran los registros de control de los periféricos.

void HabilitarInterrupciones() { // En el Controlador de Interrupciones

  // Primero se inhiben todas las interrupciones
	IME = 0;
  // Escribir un 1 en el bit correspondiente 
  // Se escribe  0x1038 ya que utilizamos el TIMER0, TIMER1 y TIMER2 para eso tenemos que activar
  // los bits 3, 4 y 5 respectivamente, de esta forma revisaríamos que es lo que pasa en los tres.
	//IE = 0x1038;
  IE = 0x1028;
  // Se vuelven a habilitar todas las interrupciones    
	IME = 1;
}


void ProgramarRegistrosControl() { 

  // Registro de Control del Teclado
	TECLAS_CNT = 0x4049; // Tecla A, START y UP 

  // TIMERx_CNT   
  //   El temporizador se activa poniendo un 1 en el 7º bit.
  //   El temporizador interrumpirá al desbordarse el contador, 
  //      si hay un 1 en el 6º bit.
  //   Los dos bits de menos peso indican lo siguiente:
  //      00 frecuencia 33554432 hz
  //      01 frecuencia 33554432/64 hz
  //      10 frecuencia 33554432/256 hz
  //      11 frecuencia 33554432/1024 hz
	TIMER0_CNT = 0x00C1;
  TIMER1_CNT = 0x00C3;
  TIMER2_CNT = 0x00C1;

  // TIMERx_DAT 
  //   Indica a partir de qué valor tiene que empezar a contar (latch)
	TIMER0_DAT = 56798;
  TIMER1_DAT = 49152;
  TIMER2_DAT = 60293;

}

// Rutinas de atención
void DefinirVectorInterrupciones() {
  // Rutina de Atención al Teclado
	irqSet(IRQ_KEYS, IntTec);
  // Rutinas de Atención a los Temporizadores
	irqSet(IRQ_TIMER0, IntTemp0);
  //irqSet(IRQ_TIMER1, IntTemp1);
  irqSet(IRQ_TIMER2, IntTemp2);
}

void InhibirInterrupciones() { // En el Controlador de Interrupciones

  // Primero se inhiben todas las interrupciones
	IME = 0;
  // Escribir un 0 en el bit correspondiente 
	IE = 0x0000;
  // Se vuelven a habilitar todas las interrupciones
	IME = 1;
}


void interrupciones() {
  HabilitarInterrupciones();
  ProgramarRegistrosControl();
  DefinirVectorInterrupciones();
}



