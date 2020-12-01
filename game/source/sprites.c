/*---------------------------------------------------------------------------------
Este código se ha implementado basándose en el ejemplo "Simple sprite demo" de 
dovoto y otro de Jaeden Amero
---------------------------------------------------------------------------------*/

#include <nds.h>			//librería desarrollada para la nds
#include <stdio.h>			//librería estandar de c que define las funciones estandar de entrada y salida
#include <stdlib.h>			//librería estandar de c para hacer reservas de memoria y conversión de números
#include <unistd.h>			//librería para asegurar la compatibilidad entre sistemas operativos
#include "sprites.h"
#include "defines.h"


u16* gfxSpray;
u16* gfxGota;
u16* gfxP1Arriba;
u16* gfxP1Abajo;
u16* gfxP2Arriba;
u16* gfxP2Abajo;
u16* gfxVirus;



/* Inicializar la memoria de Sprites. */
void initSpriteMem() {

	//int i;
	oamInit(&oamMain, SpriteMapping_1D_32, false);
	oamInit(&oamSub, SpriteMapping_1D_32, false);

	gfxSpray = oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxGota = oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxP1Arriba = oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxP1Abajo = oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxP2Arriba = oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxP2Abajo = oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxVirus = oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);

}



/* Dentro de esta función hay que definir el color con el que se mostrará cada uno de los 256 
 * colores posibles en la pantalla principal. El 0 es transparente y los no definidos son negros.
 */
void establecerPaletaPrincipal() {
                                         // 0: TRANSPARENTE
   SPRITE_PALETTE[1]  = RGB15(31,0,0);   // 1 ROJO:           	RGB24={FF,00,00} los pixels con valor 1 aparecen en rojo
   SPRITE_PALETTE[2]  = RGB15(31,31,0);  // 2 AMARILLO:       	RGB24={FF,FF,00}
   SPRITE_PALETTE[3]  = RGB15(31,31,31); // 3 BLANCO:         	RGB24={FF,FF,FF}
   SPRITE_PALETTE[4]  = RGB15(0,31,0);   // 4 VERDE:          	RGB24={00,FF,00}
   SPRITE_PALETTE[5]  = RGB15(0,0,31);   // 5 AZUL:           	RGB24={00,00,FF}
   SPRITE_PALETTE[6]  = RGB15(0,0,0);    // 6 NEGRO:          	RGB24={00,00,00}
   SPRITE_PALETTE[7]  = RGB15(0,31,31);  // 7 CYAN:           	RGB24={00,FF,FF}
   SPRITE_PALETTE[8]  = RGB15(31,0,31);  // 8 MAGENTA:        	RGB24={FF,00,FF}
   SPRITE_PALETTE[9]  = RGB15(16,16,16); // 9 GRIS:           	RGB24={80,80,80}
   SPRITE_PALETTE[10] = RGB15(25,25,25); // 10 GRIS CLARO:     	RGB24={D0,D0,D0}
   SPRITE_PALETTE[11] = RGB15(8,8,8);    // 11 GRIS OSCURO:    	RGB24={40,40,40}
   SPRITE_PALETTE[12] = RGB15(31,19,0);  // 12 NARANJA:        	RGB24={FF,99,00}
   SPRITE_PALETTE[13] = RGB15(27,3,0);   // 13 ROJO v2			(actualizado)
   SPRITE_PALETTE[14] = RGB15(12,9,8);   // 14 MARRON 			(actualizado)
   SPRITE_PALETTE[15] = RGB15(16,0,16);  // 15 MORADO:         	RGB24={80,00,80}
   SPRITE_PALETTE[16] = RGB15(25,19,31); // 16 LILA:           	RGB24={CC,99,FF}
   SPRITE_PALETTE[17] = RGB15(31,19,25); // 17 ROSA:           	RGB24={FF,99,CC}
   SPRITE_PALETTE[18] = RGB15(0,18,29);  // 18 AZUL CLARO		(actualizado)
   SPRITE_PALETTE[19] = RGB15(0,0,16);   // 19 AZUL MARINO:    	RGB24={00,00,80}
   SPRITE_PALETTE[20] = RGB15(0,16,16);  // 20 VERDE AZULADO:  	RGB24={00,80,80}
   SPRITE_PALETTE[21] = RGB15(0,12,0);   // 21 VERDE OSCURO:   	RGB24={00,66,00}
   SPRITE_PALETTE[22] = RGB15(16,16,0);  // 22 VERDE OLIVA:    	RGB24={80,80,00}
   SPRITE_PALETTE[23] = RGB15(19,31,19); // 23 VERDE CLARO:    	RGB24={99,FF,99}
   SPRITE_PALETTE[24] = RGB15(31,27,25); // 24 CARNE/PIEL 		(actualizado)
   SPRITE_PALETTE[25] = RGB15(22,27,16); // 25 VERDE (SICK) 	(actualizado)
}


/* Dibujado de un Sprite de 16x16 pixels */

/* Debido al funcionamiento de los bancos de memoria, las primeras cuatro filas 
 * forman el cuadrante superior izquiero, las siguientes, el cuadrante superior 
 * derecho, las siguientes el cuadrante inferior izquierdo y las últimas cuatro
 * filas, el cuadrante inferior derecho, como se muestra al lado.
 */

u8 SprayM[256] = 
{
	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 6, 6, 6, 6, 6, 6, 
	 6,18,18,18,18,18,18,18, 6,18,18,18,18, 3, 3, 3, 
	 6,18,18,18,18, 3, 6, 3, 6,18,18,18,18, 3, 3, 3, 
	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 0, 0, 0, 0, 0, 0, 
	18, 6, 6, 0, 0, 0, 0, 0,18,18, 6, 6, 0, 0, 0, 0, 
	18,18,18, 6, 6, 6, 6, 6,18,18,18, 6, 3, 3, 3, 6, 
	 6,18,18,18,18, 3, 6, 3, 6,18,18,18,18, 3, 6, 3, 
	 6,18,18,18,18, 3, 3, 3, 6,18,18,18,18,18,18,18, 
	 6, 6, 6, 6, 6, 6, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 
	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	18,18,18, 6, 3, 3, 3, 6,18,18,18, 6, 6, 6, 6, 6, 
	18,18, 6, 6, 0, 0, 0, 0,18, 6, 6, 0, 0, 0, 0, 0, 
	 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
};

u8 GotaM[256] = 
{
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	 0, 0, 0, 0, 0,18,18,18, 0, 0, 0, 0,18,18,18,18, 
	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	 0, 0, 0, 0, 0, 0, 0, 0,18, 0, 0, 0, 0, 0, 0, 0, 
	 0, 0, 0, 0,18,18,18,18, 0, 0, 0, 0,18,18,18,18, 
	 0, 0, 0, 0, 0,18,18,18, 0, 0, 0, 0, 0, 0, 0, 0, 
	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	18,18,18, 0, 0, 0, 0, 0,18, 0, 0, 0, 0, 0, 0, 0, 
	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

u8 P1ArribaM[256] = 
{
	 0, 0, 0, 0, 0, 0, 6, 6, 0, 0, 0, 0, 0, 6,14,14, 
	 0, 0, 0, 0, 6,14,14,14, 0, 0, 0, 0, 6,14,14,24, 
	 0, 0, 0, 0, 6,14,14,24, 0, 0, 0, 0, 6,24,14,24, 
	 0, 0, 0, 0, 6,24,24,24, 0, 0, 0, 0, 0, 6,24,24, 
	 6, 6, 6, 0, 0, 0, 0, 0,14,14,14, 6, 0, 0, 0, 0, 
	14,14,14,14, 6, 0, 0, 0,24,24,24,24, 6, 0, 0, 0, 
	24,24,24,24, 6, 0, 0, 0,14,24,14,24, 6, 0, 0, 0, 
	24,24,24,24, 6, 0, 0, 0,22,22,24,24, 6, 0, 0, 0, 
	 0, 0, 0, 0, 0, 6, 6,24, 0, 0, 0, 0, 6, 6, 6, 6, 
	 0, 0, 6, 6, 6,13, 1, 6, 0, 0, 6,13,13,13,13,13, 
	 0, 0, 6,13,13,13,13,13, 0, 0, 6,13,13, 6,13,13, 
	 0, 0, 6,13,13, 6,13,13, 0, 0, 6, 1, 1, 6,13,13, 
	24,24,24, 6, 0, 0, 0, 0, 6, 6, 6, 0, 0, 0, 0, 0, 
	 1,13, 6, 0, 0, 0, 0, 0,13,13, 6, 0, 0, 0, 0, 0, 
	13,13, 6, 0, 0, 0, 0, 0,13,13, 6, 0, 0, 0, 0, 0, 
	13,13, 6, 0, 0, 0, 0, 0,13,13, 6, 0, 0, 0, 0, 0,  
};

u8 P1AbajoM[256] = 
{
	 0, 0, 6,24,24, 6,13,13, 0, 0, 6,24,24, 6,13,13, 
	 0, 0, 6,24,24, 6,13,13, 0, 0, 6,24,24, 6,13,13, 
	 0, 0, 6,24,24, 6, 1, 1, 0, 0, 0, 6, 6,19,19, 6, 
	 0, 0, 0, 0, 6,19,19, 6, 0, 0, 0, 0, 6,19,19, 6, 
	13,13, 6, 0, 0, 0, 0, 0,13,13, 6, 0, 0, 0, 0, 0, 
	13,13, 6, 0, 0, 0, 0, 0, 1, 1, 6, 0, 0, 0, 0, 0, 
	19,19, 6, 0, 0, 0, 0, 0,19,19, 6, 0, 0, 0, 0, 0, 
	19,19, 6, 0, 0, 0, 0, 0,19,19, 6, 0, 0, 0, 0, 0, 
	 0, 0, 0, 0, 6,19,19, 6, 0, 0, 0, 0, 6,19,19, 6, 
	 0, 0, 0, 0, 6,19,19, 6, 0, 0, 0, 0, 6,19,19, 6, 
	 0, 0, 0, 0, 6,19,19, 6, 0, 0, 0, 0, 6, 6, 6, 6, 
	 0, 0, 0, 0, 6, 3, 3, 3, 0, 0, 0, 0, 6, 6, 6, 6, 
	19,19, 6, 0, 0, 0, 0, 0,19,19, 6, 0, 0, 0, 0, 0, 
	19,19, 6, 0, 0, 0, 0, 0,19,19, 6, 0, 0, 0, 0, 0, 
	19,19, 6, 0, 0, 0, 0, 0, 6, 6, 6, 6, 6, 0, 0, 0, 
	 6, 3, 3, 3, 6, 0, 0, 0, 6, 6, 6, 6, 6, 0, 0, 0,  
};

u8 P2ArribaM[256] =
{
	0, 0, 0, 0, 0, 0, 6, 6, 0, 0, 0, 0, 0, 6,14,14, 
	0, 0, 0, 0, 6,14,14,14, 0, 0, 0, 0, 6,14,14,25, 
	0, 0, 0, 0, 6,14,14,25, 0, 0, 0, 0, 6,25,14,25, 
	0, 0, 0, 0, 6,25,25,25, 0, 0, 0, 0, 0, 6,25,25, 
	6, 6, 6, 0, 0, 0, 0, 0,14,14,14, 6, 0, 0, 0, 0, 
	14,14,14,14, 6, 0, 0, 0,25,25,25,25, 6, 0, 0, 0, 
	25,25,25,25, 6, 0, 0, 0,14,25,14,25, 6, 0, 0, 0, 
	25,25,25,25, 6, 0, 0, 0,22,22,25,25, 6, 0, 0, 0, 
	0, 0, 0, 0, 0, 6, 6,25, 0, 0, 0, 0, 6, 6, 6, 6, 
	0, 0, 6, 6, 6,13, 1, 6, 0, 0, 6,13,13,13,13,13, 
	0, 0, 6,13,13,13,13,13, 0, 0, 6,13,13, 6,13,13, 
	0, 0, 6,13,13, 6,13,13, 0, 0, 6, 1, 1, 6,13,13, 
	25,25,25, 6, 0, 0, 0, 0, 6, 6, 6, 0, 0, 0, 0, 0, 
	1,13, 6, 0, 0, 0, 0, 0,13,13, 6, 0, 0, 0, 0, 0, 
	13,13, 6, 0, 0, 0, 0, 0,13,13, 6, 0, 0, 0, 0, 0, 
	13,13, 6, 0, 0, 0, 0, 0,13,13, 6, 0, 0, 0, 0, 0, 
};

u8 P2AbajoM[256] = 
{
	 0, 0, 6,25,25, 6,13,13, 0, 0, 6,25,25, 6,13,13, 
	 0, 0, 6,25,25, 6,13,13, 0, 0, 6,25,25, 6,13,13, 
	 0, 0, 6,25,25, 6, 1, 1, 0, 0, 0, 6, 6,19,19, 6, 
	 0, 0, 0, 0, 6,19,19, 6, 0, 0, 0, 0, 6,19,19, 6, 
	13,13, 6, 0, 0, 0, 0, 0,13,13, 6, 0, 0, 0, 0, 0, 
	13,13, 6, 0, 0, 0, 0, 0, 1, 1, 6, 0, 0, 0, 0, 0, 
	19,19, 6, 0, 0, 0, 0, 0,19,19, 6, 0, 0, 0, 0, 0, 
	19,19, 6, 0, 0, 0, 0, 0,19,19, 6, 0, 0, 0, 0, 0, 
	 0, 0, 0, 0, 6,19,19, 6, 0, 0, 0, 0, 6,19,19, 6, 
	 0, 0, 0, 0, 6,19,19, 6, 0, 0, 0, 0, 6,19,19, 6, 
	 0, 0, 0, 0, 6,19,19, 6, 0, 0, 0, 0, 6, 6, 6, 6, 
	 0, 0, 0, 0, 6, 3, 3, 3, 0, 0, 0, 0, 6, 6, 6, 6, 
	19,19, 6, 0, 0, 0, 0, 0,19,19, 6, 0, 0, 0, 0, 0, 
	19,19, 6, 0, 0, 0, 0, 0,19,19, 6, 0, 0, 0, 0, 0, 
	19,19, 6, 0, 0, 0, 0, 0, 6, 6, 6, 6, 6, 0, 0, 0, 
	 6, 3, 3, 3, 6, 0, 0, 0, 6, 6, 6, 6, 6, 0, 0, 0,  
};

u8 VirusM[256] = 
{
	 0, 0, 0, 0, 1,20, 0, 0, 0, 0, 0, 0, 0,23,20, 0, 
	 0, 0, 0, 0, 0,20,23, 0, 0, 0, 1, 0, 0,20, 4, 4, 
	 0, 1,20, 0, 4,23, 4,20, 0,23,20,20, 4, 4, 4, 4, 
	 0, 0, 0, 4, 4,20, 4,23, 0, 0, 0, 4,23, 4, 4, 4,
	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  
	 0, 0, 0,20,23, 1, 0, 0, 0, 0, 0,20, 0, 0, 0, 0,  
	 4, 4,20,23, 0, 0, 0, 0,23, 4,18,20,23, 0, 0, 0,  
	20, 4,23,23, 0, 0, 0, 0, 4, 4, 4, 4, 0, 0, 0, 0,  
	 0,20,20,20, 4, 4,20, 4, 0, 1, 0, 0, 4,23, 4,23,  
	 0, 0, 0, 0, 4,20, 4, 4, 0, 0, 0, 0,23, 0, 0, 0,  
	 0, 0,23,23,20, 0, 0, 0, 0, 0, 1,20, 0, 0, 0, 0,  
 	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  
	23, 4,23,20,20,23, 0, 0, 4,20, 4, 0, 0,20, 1, 0,  
 	 4, 4, 0, 0, 0, 0, 0, 0, 0,20, 0, 0, 0, 0, 0, 0,  
 	 0,23,20, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,  
 	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  
};

/* Para cada Sprite que se quiera llevar a pantalla hay que hacer una de estas funciones. */

void BorrarSpray (int x, int y) {
oamSet(&oamMain, 					//main graphics engine context
	127,  							//oam index (0 to 127)  
	x, y,    						//x and y pixle location of the sprite
	0,       						//priority, lower renders last (on top)
	0,       						//this is the palette index if multiple palettes or the alpha value if bmp sprite	
	SpriteSize_16x16,     
	SpriteColorFormat_256Color, 
	gfxSpray, //+16*16/2, 			//pointer to the loaded graphics
	-1,                  			//sprite rotation data  
	false,               			//double the size when rotating?
	true,							//hide the sprite?
	false, false, 					//vflip, hflip
	false							//apply mosaic
	); 
	oamUpdate(&oamMain); 
}

void MostrarSpray (int x, int y){ 
oamSet(&oamMain, 					//main graphics engine context
	127,  							//oam index (0 to 127)  
	x, y,    						//x and y pixle location of the sprite
	0,       						//priority, lower renders last (on top)
	0,       						//this is the palette index if multiple palettes or the alpha value if bmp sprite	
	SpriteSize_16x16,     
	SpriteColorFormat_256Color, 
	gfxSpray, //+16*16/2, 			//pointer to the loaded graphics
	-1,                  			//sprite rotation data  
	false,               			//double the size when rotating?
	false,							//hide the sprite?
	false, false, 					//vflip, hflip
	false							//apply mosaic
	); 
	oamUpdate(&oamMain);  
}

void BorrarGota (int indice, int x, int y) {
oamSet(&oamMain, 					//main graphics engine context
	indice,  						//oam index (0 to 127)  
	x, y,    						//x and y pixle location of the sprite
	0,       						//priority, lower renders last (on top)
	0,       						//this is the palette index if multiple palettes or the alpha value if bmp sprite	
	SpriteSize_16x16,     
	SpriteColorFormat_256Color, 
	gfxGota, //+16*16/2, 			//pointer to the loaded graphics
	-1,                  			//sprite rotation data  
	false,               			//double the size when rotating?
	true,							//hide the sprite?
	false, false, 					//vflip, hflip
	false							//apply mosaic
	); 
	oamUpdate(&oamMain); 
}

void MostrarGota (int indice, int x, int y){ 
oamSet(&oamMain, 					//main graphics engine context
	indice,  						//oam index (0 to 127)  
	x, y,    						//x and y pixle location of the sprite
	0,       						//priority, lower renders last (on top)
	0,       						//this is the palette index if multiple palettes or the alpha value if bmp sprite	
	SpriteSize_16x16,     
	SpriteColorFormat_256Color, 
	gfxGota, //+16*16/2, 			//pointer to the loaded graphics
	-1,                  			//sprite rotation data  
	false,               			//double the size when rotating?
	false,							//hide the sprite?
	false, false, 					//vflip, hflip
	false							//apply mosaic
	); 
	oamUpdate(&oamMain);  
}

void BorrarP1Arriba(int indice, int x, int y) {
oamSet(&oamMain, 					//main graphics engine context
	indice,  						//oam index (0 to 127)  
	x, y,    						//x and y pixle location of the sprite
	0,       						//priority, lower renders last (on top)
	0,       						//this is the palette index if multiple palettes or the alpha value if bmp sprite	
	SpriteSize_16x16,     
	SpriteColorFormat_256Color, 
	gfxP1Arriba, //+16*16/2, 		//pointer to the loaded graphics
	-1,                  			//sprite rotation data  
	false,               			//double the size when rotating?
	true,							//hide the sprite?
	false, false, 					//vflip, hflip
	false							//apply mosaic
	); 
	oamUpdate(&oamMain); 
}

void MostrarP1Arriba (int indice, int x, int y){ 
oamSet(&oamMain, 					//main graphics engine context
	indice,  						//oam index (0 to 127)  
	x, y,    						//x and y pixle location of the sprite
	0,       						//priority, lower renders last (on top)
	0,       						//this is the palette index if multiple palettes or the alpha value if bmp sprite	
	SpriteSize_16x16,     
	SpriteColorFormat_256Color, 
	gfxP1Arriba, //+16*16/2, 		//pointer to the loaded graphics
	-1,                  			//sprite rotation data  
	false,               			//double the size when rotating?
	false,							//hide the sprite?
	false, false, 					//vflip, hflip
	false							//apply mosaic
	); 
	oamUpdate(&oamMain);  
}

void BorrarP1Abajo(int indice, int x, int y) {
oamSet(&oamMain, 					//main graphics engine context
	indice,  						//oam index (0 to 127)  
	x, y,    						//x and y pixle location of the sprite
	0,       						//priority, lower renders last (on top)
	0,       						//this is the palette index if multiple palettes or the alpha value if bmp sprite	
	SpriteSize_16x16,     
	SpriteColorFormat_256Color, 
	gfxP1Abajo, //+16*16/2, 		//pointer to the loaded graphics
	-1,                  			//sprite rotation data  
	false,               			//double the size when rotating?
	true,							//hide the sprite?
	false, false, 					//vflip, hflip
	false							//apply mosaic
	); 
	oamUpdate(&oamMain); 
}

void MostrarP1Abajo (int indice, int x, int y){ 
oamSet(&oamMain, 					//main graphics engine context
	indice,  						//oam index (0 to 127)  
	x, y,    						//x and y pixle location of the sprite
	0,       						//priority, lower renders last (on top)
	0,       						//this is the palette index if multiple palettes or the alpha value if bmp sprite	
	SpriteSize_16x16,     
	SpriteColorFormat_256Color, 
	gfxP1Abajo, //+16*16/2, 		//pointer to the loaded graphics
	-1,                  			//sprite rotation data  
	false,               			//double the size when rotating?
	false,							//hide the sprite?
	false, false, 					//vflip, hflip
	false							//apply mosaic
	); 
	oamUpdate(&oamMain);  
}

void BorrarP2Arriba(int indice, int x, int y) {
oamSet(&oamMain, 					//main graphics engine context
	indice,  						//oam index (0 to 127)  
	x, y,    						//x and y pixle location of the sprite
	0,       						//priority, lower renders last (on top)
	0,       						//this is the palette index if multiple palettes or the alpha value if bmp sprite	
	SpriteSize_16x16,     
	SpriteColorFormat_256Color, 
	gfxP2Arriba, //+16*16/2, 	//pointer to the loaded graphics
	-1,                  			//sprite rotation data  
	false,               			//double the size when rotating?
	true,							//hide the sprite?
	false, false, 					//vflip, hflip
	false							//apply mosaic
	); 
	oamUpdate(&oamMain); 
}

void MostrarP2Arriba (int indice, int x, int y){ 
oamSet(&oamMain, 					//main graphics engine context
	indice,  						//oam index (0 to 127)  
	x, y,    						//x and y pixle location of the sprite
	0,       						//priority, lower renders last (on top)
	0,       						//this is the palette index if multiple palettes or the alpha value if bmp sprite	
	SpriteSize_16x16,     
	SpriteColorFormat_256Color, 
	gfxP2Arriba, //+16*16/2, 	//pointer to the loaded graphics
	-1,                  			//sprite rotation data  
	false,               			//double the size when rotating?
	false,							//hide the sprite?
	false, false, 					//vflip, hflip
	false							//apply mosaic
	); 
	oamUpdate(&oamMain);  
}

void BorrarP2Abajo(int indice, int x, int y) {
oamSet(&oamMain, 					//main graphics engine context
	indice,  						//oam index (0 to 127)  
	x, y,    						//x and y pixle location of the sprite
	0,       						//priority, lower renders last (on top)
	0,       						//this is the palette index if multiple palettes or the alpha value if bmp sprite	
	SpriteSize_16x16,     
	SpriteColorFormat_256Color, 
	gfxP2Abajo, //+16*16/2, 	//pointer to the loaded graphics
	-1,                  			//sprite rotation data  
	false,               			//double the size when rotating?
	true,							//hide the sprite?
	false, false, 					//vflip, hflip
	false							//apply mosaic
	); 
	oamUpdate(&oamMain); 
}

void MostrarP2Abajo (int indice, int x, int y){ 
oamSet(&oamMain, 					//main graphics engine context
	indice,  						//oam index (0 to 127)  
	x, y,    						//x and y pixle location of the sprite
	0,       						//priority, lower renders last (on top)
	0,       						//this is the palette index if multiple palettes or the alpha value if bmp sprite	
	SpriteSize_16x16,     
	SpriteColorFormat_256Color, 
	gfxP2Abajo, //+16*16/2, 	//pointer to the loaded graphics
	-1,                  			//sprite rotation data  
	false,               			//double the size when rotating?
	false,							//hide the sprite?
	false, false, 					//vflip, hflip
	false							//apply mosaic
	); 
	oamUpdate(&oamMain);  
}


void BorrarVirus (int indice, int x, int y) {
oamSet(&oamMain, 					//main graphics engine context
	indice,  						//oam index (0 to 127)  
	x, y,    						//x and y pixle location of the sprite
	0,       						//priority, lower renders last (on top)
	0,       						//this is the palette index if multiple palettes or the alpha value if bmp sprite	
	SpriteSize_16x16,     
	SpriteColorFormat_256Color, 
	gfxVirus, //+16*16/2, 			//pointer to the loaded graphics
	-1,                  			//sprite rotation data  
	false,               			//double the size when rotating?
	true,							//hide the sprite?
	false, false, 					//vflip, hflip
	false							//apply mosaic
	); 
	oamUpdate(&oamMain); 
}

void MostrarVirus (int indice, int x, int y){ 
oamSet(&oamMain, 					//main graphics engine context
	indice,  						//oam index (0 to 127)  
	x, y,    						//x and y pixle location of the sprite
	0,       						//priority, lower renders last (on top)
	0,       						//this is the palette index if multiple palettes or the alpha value if bmp sprite	
	SpriteSize_16x16,     
	SpriteColorFormat_256Color, 
	gfxVirus, //+16*16/2, 			//pointer to the loaded graphics
	-1,                  			//sprite rotation data  
	false,               			//double the size when rotating?
	false,							//hide the sprite?
	false, false, 					//vflip, hflip
	false							//apply mosaic
	); 
	oamUpdate(&oamMain);  
}


void guardarSpritesEnMemoria(){ 
	
	int i;
	//para sprites de 16*16
	for(i = 0; i < 16 * 16 / 2; i++) {				
		gfxSpray[i] = SprayM[i*2] | (SprayM[(i*2)+1]<<8);
		gfxGota[i] = GotaM[i*2] | (GotaM[(i*2)+1]<<8);
		gfxP1Arriba[i] = P1ArribaM[i*2] | (P1ArribaM[(i*2)+1]<<8);	
		gfxP1Abajo[i] = P1AbajoM[i*2] | (P1AbajoM[(i*2)+1]<<8);	
		gfxP2Arriba[i] = P2ArribaM[i*2] | (P2ArribaM[(i*2)+1]<<8);	
		gfxP2Abajo[i] = P2AbajoM[i*2] | (P2AbajoM[(i*2)+1]<<8);	
		gfxVirus[i] = VirusM[i*2] | (VirusM[(i*2)+1]<<8);			
	}
}



