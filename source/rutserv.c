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
  // Se escribe  0x1018 ya que utilizamos el TIMER0 y TIMER1, para eso tenemos que activar
  // el siguiente bit, asi revisaríamos que es lo que pasa en los dos.
	IE = 0x1018;
  // Se vuelven a habilitar todas las interrupciones    
	IME = 1;
}


void ProgramarRegistrosControl() { 

  // Registro de Control del Teclado
	TECLAS_CNT = 0x4080;

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
  //TIMER1_CNT = 0x00C2;

  // TIMERx_DAT 
  //   Indica a partir de qué valor tiene que empezar a contar (latch)
	TIMER0_DAT = 56798;
  //TIMER1_DAT = 39322;

}

void DefinirVectorInterrupciones() { // Rutinas de atención

  // Rutina de Atención al Teclado
	irqSet(IRQ_KEYS, IntTec);
  // Rutinas de Atención a los Temporizadores
	irqSet(IRQ_TIMER0, IntTemp0);
  //irqSet(IRQ_TIMER1, IntTemp1);
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



