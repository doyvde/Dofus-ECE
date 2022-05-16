#include <stdio.h>
#include <stdlib.h>

/**************************************************************************
DECOR TILEMAP: Ce programme construit un decor à l'écran
               en utilisant des éléments graphiques standardisés
               à partir d'une matrice 2D décrivant le terrain
               Un personnage simple (sans animation) se déplace dessus

               A chaque numéro de tuile est associé un type :
               0 : RAS   1 : Obstacle   2 : Eau
               Ces données sont dans le tableau typeTuiles.
               Ceci permet de prendre en compte le type de
               tuile dans les déplacements et de détecter
               l'environnement du personnage.

               Touches flèches pour diriger le personnage
               Touche espace pour montrer les types sur le terrain
**************************************************************************/

#include <allegro.h>
#include "mabiblio.h"



/******************************************/
/* PROGRAMME PRINCIPAL                    */
/* initialisation puis boucle de jeu      */
/******************************************/

int main()
{
    Joueur Joueures[4];//
    t_acteur *acteur1;    // Un acteur (à créer)
    t_acteur *acteur2;    // Un acteur (à créer)
    t_acteur *acteur3;    // Un acteur (à créer)
    t_acteur *acteur4;    // Un acteur (à créer)
    BITMAP *page;// BITMAP buffer d'affichage

    // Lancer allegro et le mode graphique
    allegro_init();
    install_keyboard();
    install_mouse();

    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,800,650,0,0)!=0)
    {
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }



    // CREATION DU BUFFER D'AFFICHAGE à la taille de l'écran
    page=create_bitmap(SCREEN_W,SCREEN_H);
    clear_bitmap(page);

    // pour voir le pointeur de la souris
    show_mouse(screen);

    // Charger le fichier avec les tuiles
    tableTuiles=load_bitmap_check("tableTuiles.bmp");

    // Allocation et initialisation des paramètres de l'acteur :
    acteur1 = (t_acteur *)malloc(1*sizeof(t_acteur));
    // Pour la position : multiples de l'unité de déplacement...
    acteur1->x = 32;     acteur1->y = 200;
    acteur1->img = load_bitmap_check("sprite.bmp");

    // Allocation et initialisation des paramètres de l'acteur :
    acteur2 = (t_acteur *)malloc(1*sizeof(t_acteur));
    // Pour la position : multiples de l'unité de déplacement...
    acteur2->x = 470;     acteur2->y = 45;
    acteur2->img = load_bitmap_check("sprite.bmp");

    // Allocation et initialisation des paramètres de l'acteur :
    acteur3 = (t_acteur *)malloc(1*sizeof(t_acteur));
    // Pour la position : multiples de l'unité de déplacement...
    acteur3->x = 760;     acteur3->y = 420;
    acteur3->img = load_bitmap_check("sprite.bmp");

    // Allocation et initialisation des paramètres de l'acteur :
    acteur4 = (t_acteur *)malloc(1*sizeof(t_acteur));
    // Pour la position : multiples de l'unité de déplacement...
    acteur4->x = 295;     acteur4->y = 530;
    acteur4->img = load_bitmap_check("sprite.bmp");



    // Boucle de jeu (rien pour l'instant)
    while (!key[KEY_ESC])
    {

       // Bord console utilisateur
        rect(page,0,0,800,650,makecol(0,255,0 ));
        rect(page,1,1,799,649,makecol(0,255,0 ));
        rect(page,2,2,798,648,makecol(0,255,0 ));
        rect(page,3,3,797,647,makecol(0,255,0 ));


        /*// Dessiner le terrain
        dessineTerrain(page, terrain);

        //( mouse_b&1 && mouse_x<=40 && mouse_x>=390 && mouse_y<=20 && mouse_y>=20)

        // Gérer déplacements en prenant en compte les obstacles

        if ((    key[KEY_RIGHT] && !typeTerrain(acteur1,4,0,1) )||(    ( mouse_b&1 && mouse_x<=435 && mouse_x>=410 && mouse_y<=610 && mouse_y>=598) && !typeTerrain(acteur1,4,0,1) ))//droite
            acteur1->x+=4;

        if ((    key[KEY_LEFT] && !typeTerrain(acteur1,-4,0,1) )||(    ( mouse_b&1 && mouse_x<=390 && mouse_x>=365 && mouse_y<=610 && mouse_y>=598) && !typeTerrain(acteur1,-4,0,1) ))//gauche
           acteur1->x-=4;

        if ((    key[KEY_DOWN] && !typeTerrain(acteur1,0,4,1) )||(    ( mouse_b&1 && mouse_x<=410 && mouse_x>=390 && mouse_y<=620 && mouse_y>=610) && !typeTerrain(acteur1,0,4,1) ))//bas
           acteur1->y+=4;

        if ((    key[KEY_UP] && !typeTerrain(acteur1,0,-4,1) )||(    ( mouse_b&1 && mouse_x<=410 && mouse_x>=390 && mouse_y<=598 && mouse_y>=588) && !typeTerrain(acteur1,0,-4,1) ))//haut
           acteur1->y-=4;



        // Détecter interactions avec des éléments spéciaux
        if ( typeTerrain(acteur1,0,0,2) ) // dans l'eau ?
            textprintf_centre_ex(page,font,400,565,makecol(255,255,255),0," NAGE ");
        else
            textprintf_centre_ex(page,font,400,565,makecol(255,255,255),0,"MARCHE");



        // Infos joueur
        textprintf_ex(page,font,5,580,makecol(255,0,0),makecol(0,255,0),"Joueur 1:");
        textprintf_ex(page,font,5,600,makecol(255,0,0),makecol(0,255,0),"PV:|||||||||||||||||||||||||||||");
        textprintf_ex(page,font,5,620,makecol(255,0,0),makecol(0,255,0),"PM:|||");


        // Commande

        // bouton hauts
        rectfill(page,390,588,410,598,makecol(0,128,0 ));
        textprintf_centre_ex(page,font,400,590,makecol(255,255,255),0,"^");
        //( mouse_b&1 && mouse_x<=410 && mouse_x>=390 && mouse_y<=598 && mouse_y>=588)

        // bouton bas
        rectfill(page,390,610,410,620,makecol(0,128,0 ));
        textprintf_centre_ex(page,font,400,612,makecol(255,255,255),0,"V");
        //( mouse_b&1 && mouse_x<=410 && mouse_x>=390 && mouse_y<=610 && mouse_y>=620)

        // bouton gauche
        rectfill(page,365,598,390,610,makecol(0,128,0 ));
        textprintf_centre_ex(page,font,375,600,makecol(255,255,255),0,"<");
        //( mouse_b&1 && mouse_x<=390 && mouse_x>=365 && mouse_y<=610 && mouse_y>=598)

        // bouton droit
        rectfill(page,410,598,435,610,makecol(0,128,0 ));
        textprintf_centre_ex(page,font,425,600,makecol(255,255,255),0,">");
        //( mouse_b&1 && mouse_x<=435 && mouse_x>=410 && mouse_y<=610 && mouse_y>=598)

        // bouton attaque corps à corps
        rectfill(page,330,625,370,642,makecol(255,0,0 ));
        textprintf_centre_ex(page,font,350,630,makecol(255,255,255),0,"Arme");
        //( mouse_b&1 && mouse_x<=370 && mouse_x>=330 && mouse_y<=642 && mouse_y>=625)

        // bouton attaque à distance
        rectfill(page,430,625,470,642,makecol(0,0,255));
        textprintf_centre_ex(page,font,450,630,makecol(255,255,255),0,"Sort");
        //( mouse_b&1 && mouse_x<=470 && mouse_x>=430 && mouse_y<=642 && mouse_y>=625)

        // Infos ennemi
        textprintf_right_ex(page,font,600,580,makecol(255,0,0),makecol(0,255,0),"Ennemi :");
        textprintf_right_ex(page,font,792,600,makecol(255,0,0),makecol(0,255,0),"PV:|||||||||||||||||||||||||||||");

        // Bord console utilisateur
        rect(page,0,560,800,650,makecol(0,255,0 ));
        rect(page,1,561,799,649,makecol(0,255,0 ));
        rect(page,2,562,798,648,makecol(0,255,0 ));
        rect(page,3,563,797,647,makecol(0,255,0 ));

        // Info curseur
        textprintf_ex(page,font,690,635,makecol(0,255,0),makecol(0,0,0),"x=%4d y=%4d",mouse_x,mouse_y);

        // Afficher personnage (positionner par rapport à ses jambes)
        draw_sprite(page, acteur1->img, acteur1->x - acteur1->img->w/2, acteur1->y - acteur1->img->h + 8);

        // Afficher personnage (positionner par rapport à ses jambes)
        draw_sprite(page, acteur2->img, acteur2->x - acteur2->img->w/2, acteur2->y - acteur2->img->h + 8);

        // Afficher personnage (positionner par rapport à ses jambes)
        draw_sprite(page, acteur3->img, acteur3->x - acteur3->img->w/2, acteur3->y - acteur3->img->h + 8);

        // Afficher personnage (positionner par rapport à ses jambes)
        draw_sprite(page, acteur4->img, acteur4->x - acteur4->img->w/2, acteur4->y - acteur4->img->h + 8);*/

        // Affichage du buffer mis a jour a l'ecran
        blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);

        // On fait une petite pause
        rest(15);

    }

    return 0;
}
END_OF_MAIN();
