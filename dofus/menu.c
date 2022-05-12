#include <stdio.h>
#include <stdlib.h>
#include "menu.h"


void chargerTableauBitmaps(int nombreBitmap, BITMAP* tab[nombreBitmap], char nomTypeBitmap[20])
{
    char nom[21];
    char charI;

    for(int i=0; i<nombreBitmap; i++){
        strcpy(nom, nomTypeBitmap); //je copie le nom du fichier bmp dans une nouvelle chaîne
        charI = i + '0' ;
        strncat(nom, &charI, 1);       //j'ajoute un nombre à la fin du nom pour sélectionner le bon fichier
        strcat(nom, ".bmp");           //j'ajoute ensuite l'extension
        tab[i] = load_bitmap(nom, NULL); // finalement je charge la bitmap dans mon tableau
    }
}


void afficherBoutonsVerticaux(BITMAP* bmp, int nombreBoutons, BITMAP* menuSprite[nombreBoutons], int x)
{
    int segmentBmp = bmp->h / nombreBoutons;    //je divise la hauteur du buffer par le nombre de boutons pour segmenter l'écran en parts égales

    draw_sprite(bmp, menuSprite[0], x, 2);  //je dessine le premier sprite

    for(int i=1; i<nombreBoutons; i++){
        draw_sprite(bmp, menuSprite[i], x, segmentBmp*i -5);        //je dessine les autres sprite

    }

}


/*
if(mouse_x > pos_XstartButton && mouse_x < (pos_XstartButton + startButtonMagenta->w) && mouse_y > pos_YstartButton && mouse_y < (pos_YstartButton + startButtonMagenta->h) ){
            //void rectfill(BITMAP *bmp, int x1, int y1, int x2, int y2, int color);
            //rectfill(buffer, pos_XstartButton, pos_YstartButton, pos_XstartButton + startButtonMagenta->w, pos_YstartButton + startButtonMagenta->h, makecol(0,0,0));

            draw_sprite(buffer, startButtonWhite, pos_XstartButton, pos_YstartButton);
        }
        else{
            //rectfill(buffer, pos_XstartButton, pos_YstartButton, pos_XstartButton + startButtonMagenta->w, pos_YstartButton + startButtonMagenta->h, makecol(0,0,0));
            draw_sprite(buffer, startButtonMagenta, pos_XstartButton , pos_YstartButton );
        }
*/

