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
u16* gfxPersona;


/* Inicializar la memoria de Sprites. */
void initSpriteMem() {

	//int i;
	oamInit(&oamMain, SpriteMapping_1D_32, false);
	oamInit(&oamSub, SpriteMapping_1D_32, false);

	gfxSpray = oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxPersona = oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);

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
}


/* Dibujado de un Sprite de 16x16 pixels */

/* Debido al funcionamiento de los bancos de memoria, las primeras cuatro filas 
 * forman el cuadrante superior izquiero, las siguientes, el cuadrante superior 
 * derecho, las siguientes el cuadrante inferior izquierdo y las últimas cuatro
 * filas, el cuadrante inferior derecho, como se muestra al lado.
 */

u8 Spray[256] = 
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

u8 Persona[256] = 
{
	 0, 0, 0, 0,14,14,14,14, 0, 0, 0,14,14,14,14,14, 
	 0, 0,14,14,14,24,24,24, 0, 0,14,14,24, 3, 3,24, 
	 0, 0,14,14,24, 3, 6,24, 0, 0,14,14,24,24,24,24, 
	 0, 0,14,14,24,24,24, 6, 0, 0, 0,14,24,24,24,24, 
	14,14,14,14, 0, 0, 0, 0,14,14,14,14,14, 0, 0, 0, 
	24,24,24,14,14,14, 0, 0,24, 3, 3,24,14,14, 0, 0, 
	24, 3, 6,24,14,14, 0, 0,24,24,24,24,14,14, 0, 0, 
	 6,24,24,24,14,14, 0, 0,24,24,24,24,14, 0, 0, 0, 
	 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 
	 0, 0, 0, 0, 1,13,13,13, 0, 0, 0, 0, 1, 1, 1, 1, 
	 0, 0, 0, 0, 1, 1, 1,13, 0, 0, 0, 0, 1, 1, 1, 1, 
	 0, 0, 0, 0, 1,13,13,13, 0, 0, 0, 0, 1, 1, 1, 1, 
	 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 
	13,13, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 
	13,13,13, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 
	 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 
};


/* Para cada Sprite que se quiera llevar a pantalla hay que hacer una de estas funciones. */

void BorrarSpray (int indice, int x, int y) {
oamSet(&oamMain, 					//main graphics engine context
	indice,  						//oam index (0 to 127)  
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

void MostrarSpray (int indice, int x, int y){ 
oamSet(&oamMain, 					//main graphics engine context
	indice,  						//oam index (0 to 127)  
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

void BorrarPersona(int indice, int x, int y) {
oamSet(&oamMain, 					//main graphics engine context
	indice,  						//oam index (0 to 127)  
	x, y,    						//x and y pixle location of the sprite
	0,       						//priority, lower renders last (on top)
	0,       						//this is the palette index if multiple palettes or the alpha value if bmp sprite	
	SpriteSize_16x16,     
	SpriteColorFormat_256Color, 
	gfxPersona, //+16*16/2, 		//pointer to the loaded graphics
	-1,                  			//sprite rotation data  
	false,               			//double the size when rotating?
	true,							//hide the sprite?
	false, false, 					//vflip, hflip
	false							//apply mosaic
	); 
	oamUpdate(&oamMain); 
}

void MostrarPersona (int indice, int x, int y){ 
oamSet(&oamMain, 					//main graphics engine context
	indice,  						//oam index (0 to 127)  
	x, y,    						//x and y pixle location of the sprite
	0,       						//priority, lower renders last (on top)
	0,       						//this is the palette index if multiple palettes or the alpha value if bmp sprite	
	SpriteSize_16x16,     
	SpriteColorFormat_256Color, 
	gfxPersona, //+16*16/2, 		//pointer to the loaded graphics
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
		gfxSpray[i] = Spray[i*2] | (Spray[(i*2)+1]<<8);	
		gfxPersona[i] = Persona[i*2] | (Persona[(i*2)+1]<<8);				
	}
}



