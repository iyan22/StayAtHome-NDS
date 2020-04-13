extern u16* gfxBola;
extern u16* gfxRaqueta;

/* Inicializar la memoria de Sprites. */
extern void initSpriteMem();

/* Dentro de esta función hay que definir el color con el que se mostrará cada uno de los 256 
 * colores posibles en la pantalla principal. El 0 es transparente y los no definidos son negros.
 */
extern void establecerPaletaPrincipal();

/* Dentro de esta función hay que definir el color con el que se mostrará cada uno de los 256 
 * colores posibles en la pantalla secundaria. El 0 es transparente y los no definidos son negros.
 */
extern void establecerPaletaSecundaria();

/* Para guardar los sprites en memoria y luego poder usarlos. */

extern void guardarSpritesEnMemoria();

/* Funciones específicas para manejar los sprites. */

extern void MostrarRombo(int indice, int x, int y);
extern void BorrarRombo(int indice, int x, int y);

extern void MostrarRomboGrande(int x, int y);
extern void BorrarRomboGrande(int x, int y);







