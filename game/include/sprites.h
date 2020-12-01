extern u16* gfxSpray;
extern u16* gfxGota;
extern u16* gfxP1Arriba;
extern u16* gfxP1Abajo;
extern u16* gfxVirus;

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

extern void MostrarSpray(int x, int y);
extern void BorrarSpray(int x, int y);
extern void MostrarGota(int indice, int x, int y);
extern void BorrarGota(int indice, int x, int y);

extern void MostrarP1Arriba(int indice, int x, int y);
extern void BorrarP1Arriba(int indice, int x, int y);
extern void MostrarP1Abajo(int indice, int x, int y);
extern void BorrarP1Abajo(int indice, int x, int y);
extern void MostrarP2Arriba(int indice, int x, int y);
extern void BorrarP2Arriba(int indice, int x, int y);
extern void MostrarP2Abajo(int indice, int x, int y);
extern void BorrarP2Abajo(int indice, int x, int y);

extern void MostrarVirus(int indice, int x, int y);
extern void BorrarVirus(int indice, int x, int y);








