// Este procedimiento inicializa la tabla de interrupciones para que el gestor de interrupciones sepa
// qué rutina de atención tiene que ejecutar cuando le llega una petición de interrupción. Además es 
// aquí donde se configuran los registros de control de los periféricos.

extern void interrupciones();

extern void HabilitarInterrupciones();
extern void ProgramarRegistrosControl();
extern void DefinirVectorInterrupciones();
extern void InhibirInterrupciones();
