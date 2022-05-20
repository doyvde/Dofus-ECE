#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>


void allegro_install()
{
    allegro_init();
    install_keyboard();

    install_mouse();
    if(install_mouse() == -1){
        allegro_message("Erreur souris ! : %s", allegro_error);
        //return -1;
    }

    set_color_depth(desktop_color_depth());
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1280, 720, 0,0);

    if(set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1280, 720, 0,0) != 0){
        set_gfx_mode(GFX_TEXT, 0,0,0,0);
        allegro_message("Erreur graphique !\n%s\n", allegro_error);
        //return 1;
    }

    show_mouse(screen);
}


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














