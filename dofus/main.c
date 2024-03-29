#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/**************************************************************************
DECOR TILEMAP: Ce programme construit un decor � l'�cran
               en utilisant des �l�ments graphiques standardis�s
               � partir d'une matrice 2D d�crivant le terrain
               Un personnage simple (sans animation) se d�place dessus

               A chaque num�ro de tuile est associ� un type :
               0 : RAS   1 : Obstacle   2 : Eau
               Ces donn�es sont dans le tableau typeTuiles.
               Ceci permet de prendre en compte le type de
               tuile dans les d�placements et de d�tecter
               l'environnement du personnage.

               Touches fl�ches pour diriger le personnage
               Touche espace pour montrer les types sur le terrain
**************************************************************************/

#include <allegro.h>
#include <stdbool.h>
#include <winalleg.h>
#include "mabiblio.h"



/******************************************/
/* PROGRAMME PRINCIPAL                    */
/* initialisation puis boucle de jeu      */
/******************************************/

int main()
{
    //Joueur Joueures[4];//
    /*t_acteur *acteur1;    // Un acteur (� cr�er)
    t_acteur *acteur2;    // Un acteur (� cr�er)
    t_acteur *acteur3;    // Un acteur (� cr�er)
    t_acteur *acteur4;    // Un acteur (� cr�er)*/
    //BITMAP *page;// BITMAP buffer d'affichage
    t_coords tabChemin[10];
    int findetous=0,fin=0,fin1=0,fin2=0,fin3=0,nbjoueur=0,nbfinal=0,nbenvie=0,aurevoir=0;
    int i=0,j=0;
    int ennemi=0;


    // Lancer allegro et le mode graphique
    allegro_init();
    install_keyboard();
    install_mouse();

    srand(time(NULL));

    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,800,700,0,0)!=0)
    {
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }



    // CREATION DU BUFFER D'AFFICHAGE � la taille de l'�cran
    page=create_bitmap(SCREEN_W,SCREEN_H);
    clear_bitmap(page);

    // pour voir le pointeur de la souris
    show_mouse(screen);

    // Charger le fichier avec les tuiles
    tableTuiles=load_bitmap_check("tableTuiles.bmp");

    // Allocation et initialisation des param�tres de l'acteur :
    acteur1 = (t_acteur *)malloc(1*sizeof(t_acteur));
    // Pour la position : multiples de l'unit� de d�placement...
    acteur1->x = 24;     acteur1->y = 200;
    //((acteur4->x)<=(acteur1->x+100)) && ((acteur4->x)>=(acteur1->x-100)) && ((acteur4->y)<=(acteur1->y+100)) && ((acteur4->y)>=(acteur1->y-100))) // creer un rectangle de detction autour du personnaage
    //((acteur2->x)<=(acteur1->x+100)) && ((acteur2->x)>=(acteur1->x-100)) && ((acteur2->y)<=(acteur1->y+100)) && ((acteur2->y)>=(acteur1->y-100))) // creer un rectangle de detction autour du personnaage
    //((acteur3->x)<=(acteur1->x+100)) && ((acteur3->x)>=(acteur1->x-100)) && ((acteur3->y)<=(acteur1->y+100)) && ((acteur3->y)>=(acteur1->y-100))) // creer un rectangle de detction autour du personnaage
    //acteur1->img = load_bitmap_check("sprite.bmp");

    // Allocation et initialisation des param�tres de l'acteur :
    acteur2 = (t_acteur *)malloc(1*sizeof(t_acteur));
    // Pour la position : multiples de l'unit� de d�placement...
    acteur2->x = 470;     acteur2->y = 45;
    //((acteur1->x)<=(acteur2->x+100)) && ((acteur1->x)>=(acteur2->x-100)) && ((acteur1->y)<=(acteur2->y+100)) && ((acteur1->y)>=(acteur2->y-100))) // creer un rectangle de detction autour du personnaage
    //((acteur4->x)<=(acteur2->x+100)) && ((acteur4->x)>=(acteur2->x-100)) && ((acteur4->y)<=(acteur2->y+100)) && ((acteur4->y)>=(acteur2->y-100))) // creer un rectangle de detction autour du personnaage
    //((acteur3->x)<=(acteur2->x+100)) && ((acteur3->x)>=(acteur2->x-100)) && ((acteur3->y)<=(acteur2->y+100)) && ((acteur3->y)>=(acteur2->y-100))) // creer un rectangle de detction autour du personnaage
    //acteur2->img = load_bitmap_check("sprite.bmp");

    // Allocation et initialisation des param�tres de l'acteur :
    acteur3 = (t_acteur *)malloc(1*sizeof(t_acteur));
    // Pour la position : multiples de l'unit� de d�placement...
    acteur3->x = 776;     acteur3->y = 420;
    //((acteur1->x)<=(acteur3->x+100)) && ((acteur1->x)>=(acteur3->x-100)) && ((acteur1->y)<=(acteur3->y+100)) && ((acteur1->y)>=(acteur3->y-100))) // creer un rectangle de detction autour du personnaage
    //((acteur2->x)<=(acteur3->x+100)) && ((acteur2->x)>=(acteur3->x-100)) && ((acteur2->y)<=(acteur3->y+100)) && ((acteur2->y)>=(acteur3->y-100))) // creer un rectangle de detction autour du personnaage
    //((acteur4->x)<=(acteur3->x+100)) && ((acteur4->x)>=(acteur3->x-100)) && ((acteur4->y)<=(acteur3->y+100)) && ((acteur4->y)>=(acteur3->y-100))) // creer un rectangle de detction autour du personnaage
    //acteur3->img = load_bitmap_check("sprite.bmp");

    // Allocation et initialisation des param�tres de l'acteur :
    acteur4 = (t_acteur *)malloc(1*sizeof(t_acteur));
    // Pour la position : multiples de l'unit� de d�placement...
    acteur4->x = 295;     acteur4->y = 530;
    //((acteur1->x)<=(acteur4->x+100)) && ((acteur1->x)>=(acteur4->x-100)) && ((acteur1->y)<=(acteur4->y+100)) && ((acteur1->y)>=(acteur4->y-100))) // creer un rectangle de detction autour du personnaage
    //((acteur2->x)<=(acteur4->x+100)) && ((acteur2->x)>=(acteur4->x-100)) && ((acteur2->y)<=(acteur4->y+100)) && ((acteur2->y)>=(acteur4->y-100))) // creer un rectangle de detction autour du personnaage
    //((acteur3->x)<=(acteur4->x+100)) && ((acteur3->x)>=(acteur4->x-100)) && ((acteur3->y)<=(acteur4->y+100)) && ((acteur3->y)>=(acteur4->y-100))) // creer un rectangle de detction autour du personnaage
    //acteur4->img = load_bitmap_check("sprite.bmp");

    bouledefeu = (t_acteur *)malloc(1*sizeof(t_acteur));
    bouledefeu->img =load_bitmap_check("boule.bmp");
    bouledefeu->x = 0;     bouledefeu->y = 0;

    t_coords tuileSouris;
    t_coords tuileJoueur;

        while ((!fin))
    {
        clear_bitmap(page);
        // Menu 1 :

        textprintf_centre_ex(page,font,400,100,makecol(0,255,0),0,"BIENVENU DANS SORTILEGES");//texte boutons jouer
        // Info curseur
        textprintf_ex(page,font,690,635,makecol(0,255,0),makecol(0,0,0),"x=%4d y=%4d",mouse_x,mouse_y);

       // Bord console utilisateur
        rect(page,0,0,800,650,makecol(0,255,0 ));
        rect(page,1,1,799,649,makecol(0,255,0 ));
        rect(page,2,2,798,648,makecol(0,255,0 ));
        rect(page,3,3,797,647,makecol(0,255,0 ));

        //boutons




        if(mouse_x<=500 && mouse_x>=300 && mouse_y<=250 && mouse_y>=150)//( mouse_x<=370 && mouse_x>=330 && mouse_y<=680 && mouse_y>=660)
        {
            rectfill(page,300,150,500,250,makecol(0,255,0 ));//rectangle boutons jouer
            textprintf_centre_ex(page,font,400,200,makecol(0,0,0),makecol(0,255,0),"Jouer");//texte boutons jouer
        }
        else
        {
            rect(page,300,150,500,250,makecol(0,255,0 ));//rectangle boutons jouer
            textprintf_centre_ex(page,font,400,200,makecol(0,255,0),0,"Jouer");//texte boutons jouer
        }

        if(mouse_x<=500 && mouse_x>=300 && mouse_y<=450 && mouse_y>=350)//( mouse_x<=370 && mouse_x>=330 && mouse_y<=680 && mouse_y>=660)
        {
            rectfill(page,300,350,500,450,makecol(0,255,0 ));//rectangle boutons quitter
            textprintf_centre_ex(page,font,400,400,makecol(0,0,0),makecol(0,255,0),"Quitter");//texte boutons quitter
        }
        else
        {
            rect(page,300,350,500,450,makecol(0,255,0 ));//rectangle boutons quitter
            textprintf_centre_ex(page,font,400,400,makecol(0,255,0),0,"Quitter");//texte boutons quitter
        }


        // les clics
        if (mouse_b & 1 && mouse_x<=500 && mouse_x>=300 && mouse_y<=250 && mouse_y>=150)  // gauche : dessiner en rouge
            {
                rectfill(page,300,150,500,250,makecol(0,200,0 ));//rectangle boutons jouer
                textprintf_centre_ex(page,font,400,200,makecol(0,0,0),makecol(0,200,0),"Jouer");//texte boutons jouer
                fin=1;
            }

        // prise en compte effective de la zone cliquable EXIT :
        // clic sur la case -> fin du programme
        if (mouse_b & 1 && mouse_x<=500 && mouse_x>=300 && mouse_y<=450 && mouse_y>=350) // droit : dessiner en bleu
            {
                rectfill(page,300,350,500,450,makecol(0,200,0 ));//rectangle boutons quitter
                textprintf_centre_ex(page,font,400,400,makecol(0,0,0),makecol(0,200,0),"Quitter");//texte boutons quitter
                fin=1;
                findetous=1;
            }


        // Affichage du buffer mis a jour a l'ecran
        blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);

        // On fait une petite pause
        rest(100);


    }


     // Boucle de jeu (rien pour l'instant)
    while (!findetous)
    {

      while ((!fin1))
    {
        clear_bitmap(page);

        // Menu 2 : Selection des joueurs
        // Info curseur
        textprintf_ex(page,font,690,635,makecol(0,255,0),makecol(0,0,0),"x=%4d y=%4d",mouse_x,mouse_y);

       // Bord console utilisateur
        rect(page,0,0,800,650,makecol(0,255,0 ));
        rect(page,1,1,799,649,makecol(0,255,0 ));
        rect(page,2,2,798,648,makecol(0,255,0 ));
        rect(page,3,3,797,647,makecol(0,255,0 ));

        //boutons
        textprintf_centre_ex(page,font,400,200,makecol(0,255,0),0,"Nombre de joueurs :");//texte boutons jouer



        if(mouse_x<=325 && mouse_x>=275 && mouse_y<=350 && mouse_y>=300)//( mouse_x<=370 && mouse_x>=330 && mouse_y<=680 && mouse_y>=660)
        {
            rectfill(page,275,300,325,350,makecol(0,255,0 ));//rectangle boutons 2
            textprintf_centre_ex(page,font,300,320,makecol(0,0,0),makecol(0,255,0),"2");//texte boutons 2
        }
        else
        {
            rect(page,275,300,325,350,makecol(0,255,0 ));//rectangle boutons 2
            textprintf_centre_ex(page,font,300,320,makecol(0,255,0),0,"2");//texte boutons 2
        }

        if(mouse_x<=425 && mouse_x>=375 && mouse_y<=350 && mouse_y>=300)//( mouse_x<=370 && mouse_x>=330 && mouse_y<=680 && mouse_y>=660)
        {
            rectfill(page,375,300,425,350,makecol(0,255,0 ));//rectangle boutons 3
            textprintf_centre_ex(page,font,400,320,makecol(0,0,0),makecol(0,255,0),"3");//texte boutons 3
        }
        else
        {
            rect(page,375,300,425,350,makecol(0,255,0 ));//rectangle boutons 3
            textprintf_centre_ex(page,font,400,320,makecol(0,255,0),0,"3");//texte boutons 3
        }

        if(mouse_x<=525 && mouse_x>=475 && mouse_y<=350 && mouse_y>=300)//( mouse_x<=370 && mouse_x>=330 && mouse_y<=680 && mouse_y>=660)
        {
            rectfill(page,475,300,525,350,makecol(0,255,0 ));//rectangle boutons 4
            textprintf_centre_ex(page,font,500,320,makecol(0,0,0),makecol(0,255,0),"4");//texte boutons 4
        }
        else
        {
            rect(page,475,300,525,350,makecol(0,255,0 ));//rectangle boutons 4
            textprintf_centre_ex(page,font,500,320,makecol(0,255,0),0,"4");//texte boutons 4
        }

        // prise en compte effective de la zone cliquable 2 :
        // clic sur la case 2-> nombre de joueur 2
        if (mouse_b & 1 && mouse_x<=325 && mouse_x>=275 && mouse_y<=350 && mouse_y>=300) // droit : dessiner en bleu
            {
                rectfill(page,275,300,325,350,makecol(0,255,0 ));//rectangle boutons 2
                textprintf_centre_ex(page,font,300,320,makecol(0,0,0),makecol(0,255,0),"2");//texte boutons 2
                nbjoueur=2;
                nbfinal=2;
                nbenvie=2;
                initialiseJoueurs(nbjoueur);
                fin1=1;
            }

        // prise en compte effective de la zone cliquable 3 :
        // clic sur la case 3-> nombre de joueur 3
        if (mouse_b & 1 && mouse_x<=425 && mouse_x>=375 && mouse_y<=350 && mouse_y>=300)  // gauche : dessiner en rouge
            {
                rectfill(page,375,300,425,350,makecol(0,200,0 ));//rectangle boutons 3
                textprintf_centre_ex(page,font,400,320,makecol(0,0,0),makecol(0,200,0),"3");//texte boutons 3
                nbjoueur=3;
                nbfinal=3;
                nbenvie=3;
                initialiseJoueurs(nbjoueur);
                fin1=1;
            }

        // prise en compte effective de la zone cliquable 4 :
        // clic sur la case 4-> nombre de joueur 4
        if (mouse_b & 1 && mouse_x<=525 && mouse_x>=475 && mouse_y<=350 && mouse_y>=300) // droit : dessiner en bleu
            {
                rectfill(page,475,300,525,350,makecol(0,200,0 ));//rectangle boutons 4
                textprintf_centre_ex(page,font,500,320,makecol(0,0,0),makecol(0,200,0),"4");//texte boutons 4
                nbjoueur=4;
                nbfinal=4;
                nbenvie=4;
                initialiseJoueurs(nbjoueur);
                fin1=1;
            }

        // Affichage du buffer mis a jour a l'ecran
        blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);

        // On fait une petite pause
        rest(100);
    }
      while ((!fin2))
    {
        // On fait une petite pause
        rest(500);
      for(i=0;i<nbjoueur;)
    {

        clear_bitmap(page);

        // Menu 3 : Selection des classes
        // Info curseur
        textprintf_ex(page,font,690,635,makecol(0,255,0),makecol(0,0,0),"x=%4d y=%4d",mouse_x,mouse_y);

       // Bord console utilisateur
        rect(page,0,0,800,650,makecol(0,255,0 ));
        rect(page,1,1,799,649,makecol(0,255,0 ));
        rect(page,2,2,798,648,makecol(0,255,0 ));
        rect(page,3,3,797,647,makecol(0,255,0 ));

        //boutons
        textprintf_centre_ex(page,font,400,25,makecol(0,255,0),0,"Choix de la classe du joueurs %d:",i+1);//texte boutons jouer
        rect(page,25,50,775,175,makecol(0,255,0 ));//rectangle boutons classe 1
        rect(page,25,200,775,325,makecol(0,255,0 ));//rectangle boutons classe 2
        rect(page,25,350,775,475,makecol(0,255,0 ));//rectangle boutons classe 3
        rect(page,25,500,775,625,makecol(0,255,0 ));//rectangle boutons classe 4
        textprintf_ex(page,font,30,55,makecol(0,255,0),0,"Classe 1: Soldat");//texte boutons 1
        textprintf_ex(page,font,30,205,makecol(0,255,0),0,"Classe 2: Mage");//texte boutons 2
        textprintf_ex(page,font,30,355,makecol(0,255,0),0,"Classe 3: Ninja");//texte boutons 3
        textprintf_ex(page,font,30,505,makecol(0,255,0),0,"Classe 4: Pyro");//texte boutons 4

        // il manque les info sur le pourcentage d'echec
        textprintf_ex(page,font,30,80,makecol(0,255,0),0,"PV : 100");//texte boutons 1
        textprintf_ex(page,font,30,230,makecol(0,255,0),0,"PV : 100");//texte boutons 2
        textprintf_ex(page,font,30,380,makecol(0,255,0),0,"PV : 100");//texte boutons 3
        textprintf_ex(page,font,30,530,makecol(0,255,0),0,"PV : 100");//texte boutons 4

        textprintf_ex(page,font,30,105,makecol(0,255,0),0,"PM : 3");//texte boutons 1
        textprintf_ex(page,font,30,255,makecol(0,255,0),0,"PM : 3");//texte boutons 2
        textprintf_ex(page,font,30,405,makecol(0,255,0),0,"PM : 3");//texte boutons 3
        textprintf_ex(page,font,30,555,makecol(0,255,0),0,"PM : 3");//texte boutons 4

        textprintf_ex(page,font,30,130,makecol(0,255,0),0,"PA : 10");//texte boutons 1
        textprintf_ex(page,font,30,280,makecol(0,255,0),0,"PA : 10");//texte boutons 2
        textprintf_ex(page,font,30,430,makecol(0,255,0),0,"PA : 10");//texte boutons 3
        textprintf_ex(page,font,30,580,makecol(0,255,0),0,"PA : 10");//texte boutons 4

        textprintf_ex(page,font,150,65,makecol(0,255,0),0,"Sort1:arc");//texte boutons 1
        textprintf_ex(page,font,150,215,makecol(0,255,0),0,"Sort1:baguette");//texte boutons 2
        textprintf_ex(page,font,150,365,makecol(0,255,0),0,"Sort1:shuriken");//texte boutons 3
        textprintf_ex(page,font,150,515,makecol(0,255,0),0,"Sort1:alumette");//texte boutons 4

        textprintf_ex(page,font,150,80,makecol(0,255,0),0,"Conso.PA: 2");//texte boutons 1
        textprintf_ex(page,font,150,230,makecol(0,255,0),0,"Conso.PA: 2");//texte boutons 2
        textprintf_ex(page,font,150,380,makecol(0,255,0),0,"Conso.PA: 2");//texte boutons 3
        textprintf_ex(page,font,150,530,makecol(0,255,0),0,"Conso.PA: 2");//texte boutons 4

        textprintf_ex(page,font,150,95,makecol(0,255,0),0,"1-3 degat");//texte boutons 1
        textprintf_ex(page,font,150,245,makecol(0,255,0),0,"1-3 degat");//texte boutons 2
        textprintf_ex(page,font,150,395,makecol(0,255,0),0,"1-3 degat");//texte boutons 3
        textprintf_ex(page,font,150,545,makecol(0,255,0),0,"1-3 degat");//texte boutons 4

        textprintf_ex(page,font,150,110,makecol(0,255,0),0,"portee 150-100p");//texte boutons 1
        textprintf_ex(page,font,150,260,makecol(0,255,0),0,"portee 150-100p");//texte boutons 2
        textprintf_ex(page,font,150,410,makecol(0,255,0),0,"portee 150-100p");//texte boutons 3
        textprintf_ex(page,font,150,560,makecol(0,255,0),0,"portee 150-100p");//texte boutons 4

        textprintf_ex(page,font,150,125,makecol(0,255,0),0,"1/10 d'echec");//texte boutons 1
        textprintf_ex(page,font,150,275,makecol(0,255,0),0,"1/10 d'echec");//texte boutons 2
        textprintf_ex(page,font,150,425,makecol(0,255,0),0,"1/10 d'echec");//texte boutons 3
        textprintf_ex(page,font,150,575,makecol(0,255,0),0,"1/10 d'echec");//texte boutons 4

        textprintf_ex(page,font,275,65,makecol(0,255,0),0,"Sort2:lance");//texte boutons 1
        textprintf_ex(page,font,275,215,makecol(0,255,0),0,"Sort2:malediction");//texte boutons 2
        textprintf_ex(page,font,275,365,makecol(0,255,0),0,"Sort2:Nunchaku");//texte boutons 3
        textprintf_ex(page,font,275,515,makecol(0,255,0),0,"Sort2:chalumeau");//texte boutons 4

        textprintf_ex(page,font,275,80,makecol(0,255,0),0,"Conso.PA: 5");//texte boutons 1
        textprintf_ex(page,font,275,230,makecol(0,255,0),0,"Conso.PA: 5");//texte boutons 2
        textprintf_ex(page,font,275,380,makecol(0,255,0),0,"Conso.PA: 5");//texte boutons 3
        textprintf_ex(page,font,275,530,makecol(0,255,0),0,"Conso.PA: 5");//texte boutons 4

        textprintf_ex(page,font,275,95,makecol(0,255,0),0,"7-13 degat");//texte boutons 1
        textprintf_ex(page,font,275,245,makecol(0,255,0),0,"7-13 degat");//texte boutons 2
        textprintf_ex(page,font,275,395,makecol(0,255,0),0,"7-13 degat");//texte boutons 3
        textprintf_ex(page,font,275,545,makecol(0,255,0),0,"7-13 degat");//texte boutons 4

        textprintf_ex(page,font,275,110,makecol(0,255,0),0,"portee 100-50p");//texte boutons 1
        textprintf_ex(page,font,275,260,makecol(0,255,0),0,"portee 100-50p");//texte boutons 2
        textprintf_ex(page,font,275,410,makecol(0,255,0),0,"portee 100-50p");//texte boutons 3
        textprintf_ex(page,font,275,560,makecol(0,255,0),0,"portee 100-50p");//texte boutons 4

        textprintf_ex(page,font,275,125,makecol(0,255,0),0,"1/10 d'echec");//texte boutons 1
        textprintf_ex(page,font,275,275,makecol(0,255,0),0,"1/10 d'echec");//texte boutons 2
        textprintf_ex(page,font,275,425,makecol(0,255,0),0,"1/10 d'echec");//texte boutons 3
        textprintf_ex(page,font,275,575,makecol(0,255,0),0,"1/10 d'echec");//texte boutons 4

        textprintf_ex(page,font,400,65,makecol(0,255,0),0,"Sort3:canon");//texte boutons 1
        textprintf_ex(page,font,400,215,makecol(0,255,0),0,"Sort3:dragon");//texte boutons 2
        textprintf_ex(page,font,400,365,makecol(0,255,0),0,"Sort3:sensei");//texte boutons 3
        textprintf_ex(page,font,400,515,makecol(0,255,0),0,"Sort3:bombe");//texte boutons 4

        textprintf_ex(page,font,400,80,makecol(0,255,0),0,"Conso.PA: 8");//texte boutons 1
        textprintf_ex(page,font,400,230,makecol(0,255,0),0,"Conso.PA: 8");//texte boutons 2
        textprintf_ex(page,font,400,380,makecol(0,255,0),0,"Conso.PA: 8");//texte boutons 3
        textprintf_ex(page,font,400,530,makecol(0,255,0),0,"Conso.PA: 8");//texte boutons 4

        textprintf_ex(page,font,400,95,makecol(0,255,0),0,"15-25 degat");//texte boutons 1
        textprintf_ex(page,font,400,245,makecol(0,255,0),0,"15-25 degat");//texte boutons 2
        textprintf_ex(page,font,400,395,makecol(0,255,0),0,"15-25 degat");//texte boutons 3
        textprintf_ex(page,font,400,545,makecol(0,255,0),0,"15-25 degat");//texte boutons 4

        textprintf_ex(page,font,400,110,makecol(0,255,0),0,"portee 50-32p");//texte boutons 1
        textprintf_ex(page,font,400,260,makecol(0,255,0),0,"portee 50-32p");//texte boutons 2
        textprintf_ex(page,font,400,410,makecol(0,255,0),0,"portee 50-32p");//texte boutons 3
        textprintf_ex(page,font,400,560,makecol(0,255,0),0,"portee 50-32p");//texte boutons 4

        textprintf_ex(page,font,400,125,makecol(0,255,0),0,"1/10 d'echec");//texte boutons 1
        textprintf_ex(page,font,400,275,makecol(0,255,0),0,"1/10 d'echec");//texte boutons 2
        textprintf_ex(page,font,400,425,makecol(0,255,0),0,"1/10 d'echec");//texte boutons 3
        textprintf_ex(page,font,400,575,makecol(0,255,0),0,"1/10 d'echec");//texte boutons 4

        textprintf_ex(page,font,525,65,makecol(0,255,0),0,"Sort4:bouclier");//texte boutons 1
        textprintf_ex(page,font,525,215,makecol(0,255,0),0,"Sort4:protection");//texte boutons 2
        textprintf_ex(page,font,525,365,makecol(0,255,0),0,"Sort4:meditation");//texte boutons 3
        textprintf_ex(page,font,525,515,makecol(0,255,0),0,"Sort4:feux de camp");//texte boutons 4

        textprintf_ex(page,font,525,80,makecol(0,255,0),0,"Conso.PA: 5");//texte boutons 1
        textprintf_ex(page,font,525,230,makecol(0,255,0),0,"Conso.PA: 5");//texte boutons 2
        textprintf_ex(page,font,525,380,makecol(0,255,0),0,"Conso.PA: 5");//texte boutons 3
        textprintf_ex(page,font,525,530,makecol(0,255,0),0,"Conso.PA: 5");//texte boutons 4

        textprintf_ex(page,font,525,95,makecol(0,255,0),0,"augmente 5-10pv");//texte boutons 1
        textprintf_ex(page,font,525,245,makecol(0,255,0),0,"augmente 5-10pv");//texte boutons 2
        textprintf_ex(page,font,525,395,makecol(0,255,0),0,"augmente 5-10pv");//texte boutons 3
        textprintf_ex(page,font,525,545,makecol(0,255,0),0,"augmente 5-10pv");//texte boutons 4

        textprintf_ex(page,font,525,110,makecol(0,255,0),0,"distance 100p");//texte boutons 1
        textprintf_ex(page,font,525,260,makecol(0,255,0),0,"distance 100p");//texte boutons 2
        textprintf_ex(page,font,525,410,makecol(0,255,0),0,"distance 100p");//texte boutons 3
        textprintf_ex(page,font,525,560,makecol(0,255,0),0,"distance 100p");//texte boutons 4

        textprintf_ex(page,font,525,125,makecol(0,255,0),0,"1/10 d'echec");//texte boutons 1
        textprintf_ex(page,font,525,275,makecol(0,255,0),0,"1/10 d'echec");//texte boutons 2
        textprintf_ex(page,font,525,425,makecol(0,255,0),0,"1/10 d'echec");//texte boutons 3
        textprintf_ex(page,font,525,575,makecol(0,255,0),0,"1/10 d'echec");//texte boutons 4

        textprintf_ex(page,font,650,65,makecol(0,255,0),0,"Attaque:epee");//texte boutons 1
        textprintf_ex(page,font,650,215,makecol(0,255,0),0,"Attaque:baton");//texte boutons 2
        textprintf_ex(page,font,650,365,makecol(0,255,0),0,"Attaque:katana");//texte boutons 3
        textprintf_ex(page,font,650,515,makecol(0,255,0),0,"Attaque:briquet");//texte boutons 4

        textprintf_ex(page,font,650,80,makecol(0,255,0),0,"Conso.PA: 2");//texte boutons 1
        textprintf_ex(page,font,650,230,makecol(0,255,0),0,"Conso.PA: 2");//texte boutons 2
        textprintf_ex(page,font,650,380,makecol(0,255,0),0,"Conso.PA: 2");//texte boutons 3
        textprintf_ex(page,font,650,530,makecol(0,255,0),0,"Conso.PA: 2");//texte boutons 4

        textprintf_ex(page,font,650,95,makecol(0,255,0),0,"5 degat");//texte boutons 1
        textprintf_ex(page,font,650,245,makecol(0,255,0),0,"5 degat");//texte boutons 2
        textprintf_ex(page,font,650,395,makecol(0,255,0),0,"5 degat");//texte boutons 3
        textprintf_ex(page,font,650,545,makecol(0,255,0),0,"5 degat");//texte boutons 4

        textprintf_ex(page,font,650,125,makecol(0,255,0),0,"1/10 d'echec");//texte boutons 1
        textprintf_ex(page,font,650,275,makecol(0,255,0),0,"1/10 d'echec");//texte boutons 2
        textprintf_ex(page,font,650,425,makecol(0,255,0),0,"1/10 d'echec");//texte boutons 3
        textprintf_ex(page,font,650,575,makecol(0,255,0),0,"1/10 d'echec");//texte boutons 4

        textprintf_ex(page,font,650,110,makecol(0,255,0),0,"portee 32p");//texte boutons 1
        textprintf_ex(page,font,650,260,makecol(0,255,0),0,"portee 32p");//texte boutons 2
        textprintf_ex(page,font,650,410,makecol(0,255,0),0,"portee 32p");//texte boutons 3
        textprintf_ex(page,font,650,560,makecol(0,255,0),0,"portee 32p");//texte boutons 4

        // prise en compte effective de la zone cliquable 2 :
        // clic sur la case 2-> nombre de joueur 2
        if (mouse_b & 1 && mouse_x<=775 && mouse_x>=25 && mouse_y<=175 && mouse_y>=50) // droit : dessiner en bleu
            {
                Joueures[i].classe=1;
                if (i==0)
                {
                    acteur1->img = load_bitmap_check("sprite.bmp");
                }
                if (i==1)
                {
                    acteur2->img = load_bitmap_check("sprite.bmp");
                }
                if (i==2)
                {
                    acteur3->img = load_bitmap_check("sprite.bmp");
                }
                if (i==3)
                {
                    acteur4->img = load_bitmap_check("sprite.bmp");
                }
                i++;
            }

        // prise en compte effective de la zone cliquable 3 :
        // clic sur la case 3-> nombre de joueur 3
        if (mouse_b & 1 && mouse_x<=775 && mouse_x>=25 && mouse_y<=325 && mouse_y>=200)  // gauche : dessiner en rouge
            {
                Joueures[i].classe=2;
                if (i==0)
                {
                    acteur1->img = load_bitmap_check("shaolin2.bmp");
                }
                if (i==1)
                {
                    acteur2->img = load_bitmap_check("shaolin2.bmp");
                }
                if (i==2)
                {
                    acteur3->img = load_bitmap_check("shaolin2.bmp");
                }
                if (i==3)
                {
                    acteur4->img = load_bitmap_check("shaolin2.bmp");
                }
                i++;
            }

        // prise en compte effective de la zone cliquable 4 :
        // clic sur la case 4-> nombre de joueur 4
        if (mouse_b & 1 && mouse_x<=775 && mouse_x>=25 && mouse_y<=475 && mouse_y>=350) // droit : dessiner en bleu
            {
                Joueures[i].classe=3;
                if (i==0)
                {
                    acteur1->img = load_bitmap_check("ninja.bmp");
                }
                if (i==1)
                {
                    acteur2->img = load_bitmap_check("ninja.bmp");
                }
                if (i==2)
                {
                    acteur3->img = load_bitmap_check("ninja.bmp");
                }
                if (i==3)
                {
                    acteur4->img = load_bitmap_check("ninja.bmp");
                }
                i++;
            }

        // prise en compte effective de la zone cliquable 4 :
        // clic sur la case 4-> nombre de joueur 4
        if (mouse_b & 1 && mouse_x<=775 && mouse_x>=25 && mouse_y<=625 && mouse_y>=500) // droit : dessiner en bleu
            {
                Joueures[i].classe=4;
                if (i==0)
                {
                    acteur1->img = load_bitmap_check("pyro.bmp");
                }
                if (i==1)
                {
                    acteur2->img = load_bitmap_check("pyro.bmp");
                }
                if (i==2)
                {
                    acteur3->img = load_bitmap_check("pyro.bmp");
                }
                if (i==3)
                {
                    acteur4->img = load_bitmap_check("pyro.bmp");
                }
                i++;
            }

        // Affichage du buffer mis a jour a l'ecran
        blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);

        // On fait une petite pause
        rest(250);

    }
    fin2=1;
    }

        clock_t tempsInitial;
        clock_t tempsActuel;
        clock_t deltaTemps;
        int dureeTourDeJeu = 0;

    tempsInitial = clock();
    j = (rand() % nbjoueur) + 1;//
    while ((!fin3))
    {

        //ennemi=5;

        Joueures[0].pm=3;
        Joueures[0].pa=10;
        Joueures[1].pm=3;
        Joueures[1].pa=10;
        Joueures[2].pm=3;
        Joueures[2].pa=10;
        Joueures[3].pm=3;
        Joueures[3].pa=10;


        for(j=j,ennemi=5;((j<nbjoueur)&&((Joueures[j].pv)>0));)
    {




        if (Joueures[j].pv<=0)
        {

          j++;
          j++;
        }

        tempsActuel = clock();
        deltaTemps = tempsActuel - tempsInitial;
        dureeTourDeJeu = (deltaTemps/CLOCKS_PER_SEC);
        if ((((dureeTourDeJeu)%15)==0)&&(dureeTourDeJeu !=0))
        {
            dureeTourDeJeu = 0;
            rest(1000);
            j++;
        }


        clear_bitmap(page);

        // Dessiner le terrain
        dessineTerrain(page, terrain);

    if((j==0)&&(Joueures[j].pm>0))
    {
        tuileSouris.ligne = mouse_y / TYTUILE;
        tuileSouris.colonne = mouse_x / TXTUILE;

        tuileJoueur.ligne = acteur1->y / TYTUILE;
        tuileJoueur.colonne = acteur1->x / TXTUILE;

        //tableau 2 valeurs : lorsque posActuelle - posStockee > Tuile
                            //alors on declenche le calcul et on actualise la posStockee

        //r�initialisation du tableau pour �viter probl�mes
        for(int i=0; i<PM_MAX; i++){
            tabChemin[i].colonne = 0;
            tabChemin[i].ligne = 0;
        }

        int isNewCheminDisponible = calculerNewChemin(tabChemin, terrain ,typeTuiles, tuileJoueur, tuileSouris, Joueures[j].pm);    //renvoie le nombre de d�placements (nombre de tuile � parcourir)
                                    //calculerNewChemin(tabChemin, terrain ,typeTuiles, tuileJoueur, tuileSouris, acteur->pm);
        if(isNewCheminDisponible != -1){
            //si le d�placement est possible, on colorie toutes les tuiles utilis�es pour le d�placement
            for(int i=0; i < isNewCheminDisponible; i++){
                peindreTuile(page, tabChemin[i], makecol(0,0,255));
                peindreTuile(page, tuileJoueur, makecol(0,255,0));
            }

            if(mouse_b & 1){    //si on clique sur la souris
                for(int i = 0; i < isNewCheminDisponible; i++){
                    acteur1->x = tabChemin[i].colonne*TXTUILE;
                    acteur1->y = tabChemin[i].ligne*TYTUILE;

                    if(i<PM_MAX - 1){
                            /*Pour animer correctement : Une fonction qui renvoie la direction du mouvement (dans quel sens et horizontal ou vertical)   */

                        dessineTerrain(page, terrain);
                        draw_sprite(page, acteur1->img, acteur1->x -acteur1->img->w/4 , acteur1->y - acteur1->img->h + 12);
                        blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);    //on affiche � l'�cran
                        rest(75);   //delai poour qu'on puisse voir l'animation

                    }
                }
                Joueures[j].pm=Joueures[j].pm-isNewCheminDisponible;//enlever isNewCheminDisponible � la PM du joueur
            }

        }
        else{
                peindreTuile(page, tuileJoueur, makecol(255,0,0));  //si le d�placement n'est pas possible, on peint la tuile sous les pieds du joueurs en Rouge
        }
    }

    if((j==1)&&(Joueures[j].pm>0))
    {
        tuileSouris.ligne = mouse_y / TYTUILE;
        tuileSouris.colonne = mouse_x / TXTUILE;

        tuileJoueur.ligne = acteur2->y / TYTUILE;
        tuileJoueur.colonne = acteur2->x / TXTUILE;

        //tableau 2 valeurs : lorsque posActuelle - posStockee > Tuile
                            //alors on declenche le calcul et on actualise la posStockee

        //r�initialisation du tableau pour �viter probl�mes
        for(int i=0; i<PM_MAX; i++){
            tabChemin[i].colonne = 0;
            tabChemin[i].ligne = 0;
        }

        int isNewCheminDisponible = calculerNewChemin(tabChemin, terrain ,typeTuiles, tuileJoueur, tuileSouris, Joueures[j].pm);    //renvoie le nombre de d�placements (nombre de tuile � parcourir)
                                    //calculerNewChemin(tabChemin, terrain ,typeTuiles, tuileJoueur, tuileSouris, acteur->pm);
        if(isNewCheminDisponible != -1){
            //si le d�placement est possible, on colorie toutes les tuiles utilis�es pour le d�placement
            for(int i=0; i < isNewCheminDisponible; i++){
                peindreTuile(page, tabChemin[i], makecol(0,0,255));
                peindreTuile(page, tuileJoueur, makecol(0,255,0));
            }

            if(mouse_b & 1){    //si on clique sur la souris
                for(int i = 0; i < isNewCheminDisponible; i++){
                    acteur2->x = tabChemin[i].colonne*TXTUILE;
                    acteur2->y = tabChemin[i].ligne*TYTUILE;

                    if(i<PM_MAX - 1){
                            /*Pour animer correctement : Une fonction qui renvoie la direction du mouvement (dans quel sens et horizontal ou vertical)   */

                        dessineTerrain(page, terrain);
                        draw_sprite(page, acteur2->img, acteur2->x -acteur2->img->w/4 , acteur2->y - acteur2->img->h + 12);
                        blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);    //on affiche � l'�cran
                        rest(75);   //delai poour qu'on puisse voir l'animation

                    }
                }
                Joueures[j].pm=Joueures[j].pm-isNewCheminDisponible;//enlever isNewCheminDisponible � la PM du joueur
            }

        }
        else{
                peindreTuile(page, tuileJoueur, makecol(255,0,0));  //si le d�placement n'est pas possible, on peint la tuile sous les pieds du joueurs en Rouge
        }
    }

    if((j==2)&&(Joueures[j].pm>0))
    {
        tuileSouris.ligne = mouse_y / TYTUILE;
        tuileSouris.colonne = mouse_x / TXTUILE;

        tuileJoueur.ligne = acteur3->y / TYTUILE;
        tuileJoueur.colonne = acteur3->x / TXTUILE;

        //tableau 2 valeurs : lorsque posActuelle - posStockee > Tuile
                            //alors on declenche le calcul et on actualise la posStockee

        //r�initialisation du tableau pour �viter probl�mes
        for(int i=0; i<PM_MAX; i++){
            tabChemin[i].colonne = 0;
            tabChemin[i].ligne = 0;
        }

        int isNewCheminDisponible = calculerNewChemin(tabChemin, terrain ,typeTuiles, tuileJoueur, tuileSouris, Joueures[j].pm);    //renvoie le nombre de d�placements (nombre de tuile � parcourir)
                                    //calculerNewChemin(tabChemin, terrain ,typeTuiles, tuileJoueur, tuileSouris, acteur->pm);
        if(isNewCheminDisponible != -1){
            //si le d�placement est possible, on colorie toutes les tuiles utilis�es pour le d�placement
            for(int i=0; i < isNewCheminDisponible; i++){
                peindreTuile(page, tabChemin[i], makecol(0,0,255));
                peindreTuile(page, tuileJoueur, makecol(0,255,0));
            }

            if(mouse_b & 1){    //si on clique sur la souris
                for(int i = 0; i < isNewCheminDisponible; i++){
                    acteur3->x = tabChemin[i].colonne*TXTUILE;
                    acteur3->y = tabChemin[i].ligne*TYTUILE;

                    if(i<PM_MAX - 1){
                            /*Pour animer correctement : Une fonction qui renvoie la direction du mouvement (dans quel sens et horizontal ou vertical)   */

                        dessineTerrain(page, terrain);
                        draw_sprite(page, acteur3->img, acteur3->x -acteur3->img->w/4 , acteur3->y - acteur3->img->h + 12);
                        blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);    //on affiche � l'�cran
                        rest(75);   //delai poour qu'on puisse voir l'animation

                    }
                }
                Joueures[j].pm=Joueures[j].pm-isNewCheminDisponible;//enlever isNewCheminDisponible � la PM du joueur
            }

        }
        else{
                peindreTuile(page, tuileJoueur, makecol(255,0,0));  //si le d�placement n'est pas possible, on peint la tuile sous les pieds du joueurs en Rouge
        }
    }

    if((j==3)&&(Joueures[j].pm>0))
    {
        tuileSouris.ligne = mouse_y / TYTUILE;
        tuileSouris.colonne = mouse_x / TXTUILE;

        tuileJoueur.ligne = acteur4->y / TYTUILE;
        tuileJoueur.colonne = acteur4->x / TXTUILE;

        //tableau 2 valeurs : lorsque posActuelle - posStockee > Tuile
                            //alors on declenche le calcul et on actualise la posStockee

        //r�initialisation du tableau pour �viter probl�mes
        for(int i=0; i<PM_MAX; i++){
            tabChemin[i].colonne = 0;
            tabChemin[i].ligne = 0;
        }

        int isNewCheminDisponible = calculerNewChemin(tabChemin, terrain ,typeTuiles, tuileJoueur, tuileSouris, Joueures[j].pm);    //renvoie le nombre de d�placements (nombre de tuile � parcourir)
                                    //calculerNewChemin(tabChemin, terrain ,typeTuiles, tuileJoueur, tuileSouris, acteur->pm);
        if(isNewCheminDisponible != -1){
            //si le d�placement est possible, on colorie toutes les tuiles utilis�es pour le d�placement
            for(int i=0; i < isNewCheminDisponible; i++){
                peindreTuile(page, tabChemin[i], makecol(0,0,255));
                peindreTuile(page, tuileJoueur, makecol(0,255,0));
            }

            if(mouse_b & 1){    //si on clique sur la souris
                for(int i = 0; i < isNewCheminDisponible; i++){
                    acteur4->x = tabChemin[i].colonne*TXTUILE;
                    acteur4->y = tabChemin[i].ligne*TYTUILE;

                    if(i<PM_MAX - 1){
                            /*Pour animer correctement : Une fonction qui renvoie la direction du mouvement (dans quel sens et horizontal ou vertical)   */

                        dessineTerrain(page, terrain);
                        draw_sprite(page, acteur4->img, acteur4->x -acteur4->img->w/4 , acteur4->y - acteur4->img->h + 12);
                        blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);    //on affiche � l'�cran
                        rest(75);   //delai poour qu'on puisse voir l'animation

                    }
                }
                Joueures[j].pm=Joueures[j].pm-isNewCheminDisponible;//enlever isNewCheminDisponible � la PM du joueur
            }

        }
        else{
                peindreTuile(page, tuileJoueur, makecol(255,0,0));  //si le d�placement n'est pas possible, on peint la tuile sous les pieds du joueurs en Rouge
        }
    }




        //( mouse_b&1 && mouse_x<=40 && mouse_x>=390 && mouse_y<=20 && mouse_y>=20)


        // G�rer d�placements en prenant en compte les obstacles
        if (Joueures[j].pm>0)
        {

        if ((    key[KEY_RIGHT] && !typeTerrain(acteur1,4,0,1) && j==0))//droite
            {acteur1->x+=16;Joueures[j].pm=Joueures[j].pm-1;}

        if ((    key[KEY_LEFT] && !typeTerrain(acteur1,-4,0,1) && j==0))//gauche
           {acteur1->x-=16;Joueures[j].pm=Joueures[j].pm-1;}

        if ((    key[KEY_DOWN] && !typeTerrain(acteur1,0,4,1) && j==0))//bas
           {acteur1->y+=16;Joueures[j].pm=Joueures[j].pm-1;}

        if ((    key[KEY_UP] && !typeTerrain(acteur1,0,-4,1) && j==0))//haut
           {acteur1->y-=16;Joueures[j].pm=Joueures[j].pm-1;}



        if ((    key[KEY_RIGHT] && !typeTerrain(acteur2,4,0,1) && j==1))//droite
            {acteur2->x+=16;Joueures[j].pm=Joueures[j].pm-1;}

        if ((    key[KEY_LEFT] && !typeTerrain(acteur2,-4,0,1) && j==1))//gauche
           {acteur2->x-=16;Joueures[j].pm=Joueures[j].pm-1;}

        if ((    key[KEY_DOWN] && !typeTerrain(acteur2,0,4,1) && j==1))//bas
           {acteur2->y+=16;Joueures[j].pm=Joueures[j].pm-1;}

        if ((    key[KEY_UP] && !typeTerrain(acteur2,0,-4,1) && j==1))//haut
           {acteur2->y-=16;Joueures[j].pm=Joueures[j].pm-1;}



        if ((    key[KEY_RIGHT] && !typeTerrain(acteur3,4,0,1) && j==2))//droite
            {acteur3->x+=16;Joueures[j].pm=Joueures[j].pm-1;}

        if ((    key[KEY_LEFT] && !typeTerrain(acteur3,-4,0,1) && j==2))//gauche
           {acteur3->x-=16;Joueures[j].pm=Joueures[j].pm-1;}

        if ((    key[KEY_DOWN] && !typeTerrain(acteur3,0,4,1) && j==2))//bas
           {acteur3->y+=16;Joueures[j].pm=Joueures[j].pm-1;}

        if ((    key[KEY_UP] && !typeTerrain(acteur3,0,-4,1) && j==2))//haut
           {acteur3->y-=16;Joueures[j].pm=Joueures[j].pm-1;}



        if ((    key[KEY_RIGHT] && !typeTerrain(acteur4,4,0,1) && j==3))//droite
            {acteur4->x+=16;Joueures[j].pm=Joueures[j].pm-1;}

        if ((    key[KEY_LEFT] && !typeTerrain(acteur4,-4,0,1) && j==3))//gauche
           {acteur4->x-=16;Joueures[j].pm=Joueures[j].pm-1;}

        if ((    key[KEY_DOWN] && !typeTerrain(acteur4,0,4,1) && j==3))//bas
           {acteur4->y+=16;Joueures[j].pm=Joueures[j].pm-1;}

        if ((    key[KEY_UP] && !typeTerrain(acteur4,0,-4,1) && j==3))//haut
           {acteur4->y-=16;Joueures[j].pm=Joueures[j].pm-1;}

        }

        textprintf_centre_ex(page,font,400,565,makecol(255,255,255),0,"Sur qui voulez vous utiliser vos capacites ?");

        if (nbjoueur==2)
    {
        if (j==0)
        {
        if(((acteur1->x)<=(acteur1->x+150)) && ((acteur1->x)>=(acteur1->x-150)) && ((acteur1->y)<=(acteur1->y+150)) && ((acteur1->y)>=(acteur1->y-150))) // creer un rectangle de detction autour du personnaage
        {
            rectfill(page,290,572,320,590,makecol(255,0,0 ));
            textprintf_ex(page,font,300,577,makecol(255,255,255),makecol(255,0,0),"J1");
            if ( mouse_b&1 && mouse_x<=320 && mouse_x>=290 && mouse_y<=590 && mouse_y>=572)
            {
                rectfill(page,290,572,320,590,makecol(200,0,0 ));
                textprintf_ex(page,font,300,577,makecol(200,200,200),makecol(200,0,0),"J1");
                ennemi=0;
            }

        }
        else
        {
            rect(page,290,572,320,590,makecol(255,0,0 ));
            textprintf_ex(page,font,300,577,makecol(255,255,255),0,"J1");
        }


        if(((acteur2->x)<=(acteur1->x+150)) && ((acteur2->x)>=(acteur1->x-150)) && ((acteur2->y)<=(acteur1->y+150)) && ((acteur2->y)>=(acteur1->y-150))) // creer un rectangle de detction autour du personnaage
        {
            rectfill(page,340,572,370,590,makecol(255,0,0 ));
            textprintf_ex(page,font,350,577,makecol(255,255,255),makecol(255,0,0),"J2");
            if ( mouse_b&1 && mouse_x<=370 && mouse_x>=340 && mouse_y<=590 && mouse_y>=572)
            {
                rectfill(page,340,572,370,590,makecol(200,0,0 ));
                textprintf_ex(page,font,350,577,makecol(200,200,200),makecol(200,0,0),"J2");
                ennemi=1;
            }

        }
        else
        {
            rect(page,340,572,370,590,makecol(255,0,0 ));
            textprintf_ex(page,font,350,577,makecol(255,255,255),0,"J2");
        }



        }

        if (j==1)
        {
        if(((acteur1->x)<=(acteur2->x+150)) && ((acteur1->x)>=(acteur2->x-150)) && ((acteur1->y)<=(acteur2->y+150)) && ((acteur1->y)>=(acteur2->y-150))) // creer un rectangle de detction autour du personnaage
        {
            rectfill(page,290,572,320,590,makecol(255,0,0 ));
            textprintf_ex(page,font,300,577,makecol(255,255,255),makecol(255,0,0),"J1");
            if ( mouse_b&1 && mouse_x<=320 && mouse_x>=290 && mouse_y<=590 && mouse_y>=572)
            {
                rectfill(page,290,572,320,590,makecol(200,0,0 ));
                textprintf_ex(page,font,300,577,makecol(200,200,200),makecol(200,0,0),"J1");
                ennemi=0;
            }

        }
        else
        {
            rect(page,290,572,320,590,makecol(255,0,0 ));
            textprintf_ex(page,font,300,577,makecol(255,255,255),0,"J1");
        }


        if(((acteur2->x)<=(acteur2->x+150)) && ((acteur2->x)>=(acteur2->x-150)) && ((acteur2->y)<=(acteur2->y+150)) && ((acteur2->y)>=(acteur2->y-150))) // creer un rectangle de detction autour du personnaage
        {
            rectfill(page,340,572,370,590,makecol(255,0,0 ));
            textprintf_ex(page,font,350,577,makecol(255,255,255),makecol(255,0,0),"J2");
            if ( mouse_b&1 && mouse_x<=370 && mouse_x>=340 && mouse_y<=590 && mouse_y>=572)
            {
                rectfill(page,340,572,370,590,makecol(200,0,0 ));
                textprintf_ex(page,font,350,577,makecol(200,200,200),makecol(200,0,0),"J2");
                ennemi=1;
            }

        }
        else
        {
            rect(page,340,572,370,590,makecol(255,0,0 ));
            textprintf_ex(page,font,350,577,makecol(255,255,255),0,"J2");
        }



        }

    }

        if (nbjoueur==3)
    {
        if (j==0)
        {
        if(((acteur1->x)<=(acteur1->x+150)) && ((acteur1->x)>=(acteur1->x-150)) && ((acteur1->y)<=(acteur1->y+150)) && ((acteur1->y)>=(acteur1->y-150))) // creer un rectangle de detction autour du personnaage
        {
            rectfill(page,290,572,320,590,makecol(255,0,0 ));
            textprintf_ex(page,font,300,577,makecol(255,255,255),makecol(255,0,0 ),"J1");
            if ( mouse_b&1 && mouse_x<=320 && mouse_x>=290 && mouse_y<=590 && mouse_y>=572)
            {
                rectfill(page,290,572,320,590,makecol(200,0,0 ));
                textprintf_ex(page,font,300,577,makecol(200,200,200),makecol(200,0,0 ),"J1");
                ennemi=0;
            }

        }
        else
        {
            rect(page,290,572,320,590,makecol(255,0,0 ));
            textprintf_ex(page,font,300,577,makecol(255,255,255),0,"J1");
        }


        if(((acteur2->x)<=(acteur1->x+150)) && ((acteur2->x)>=(acteur1->x-150)) && ((acteur2->y)<=(acteur1->y+150)) && ((acteur2->y)>=(acteur1->y-150))) // creer un rectangle de detction autour du personnaage
        {
            rectfill(page,340,572,370,590,makecol(255,0,0 ));
            textprintf_ex(page,font,350,577,makecol(255,255,255),makecol(255,0,0),"J2");
            if ( mouse_b&1 && mouse_x<=370 && mouse_x>=340 && mouse_y<=590 && mouse_y>=572)
            {
                rectfill(page,340,572,370,590,makecol(200,0,0 ));
                textprintf_ex(page,font,350,577,makecol(200,200,200),makecol(200,0,0 ),"J2");
                ennemi=1;
            }

        }
        else
        {
            rect(page,340,572,370,590,makecol(255,0,0 ));
            textprintf_ex(page,font,350,577,makecol(255,255,255),0,"J2");
        }


        if(((acteur3->x)<=(acteur1->x+150)) && ((acteur3->x)>=(acteur1->x-150)) && ((acteur3->y)<=(acteur1->y+150)) && ((acteur3->y)>=(acteur1->y-150))) // creer un rectangle de detction autour du personnaage
        {
            rectfill(page,390,572,420,590,makecol(255,0,0 ));
            textprintf_ex(page,font,400,577,makecol(255,255,255),makecol(255,0,0 ),"J3");
            if ( mouse_b&1 && mouse_x<=420 && mouse_x>=390 && mouse_y<=590 && mouse_y>=572)
            {
                rectfill(page,390,572,420,590,makecol(200,0,0 ));
                textprintf_ex(page,font,400,577,makecol(200,200,200),makecol(200,0,0 ),"J3");
                ennemi=2;
            }

        }
        else
        {
            rect(page,390,572,420,590,makecol(255,0,0 ));
            textprintf_ex(page,font,400,577,makecol(255,255,255),0,"J3");
        }



        }

        if (j==1)
        {
        if(((acteur1->x)<=(acteur2->x+150)) && ((acteur1->x)>=(acteur2->x-150)) && ((acteur1->y)<=(acteur2->y+150)) && ((acteur1->y)>=(acteur2->y-150))) // creer un rectangle de detction autour du personnaage
        {
            rectfill(page,290,572,320,590,makecol(255,0,0 ));
            textprintf_ex(page,font,300,577,makecol(255,255,255),makecol(255,0,0 ),"J1");
            if ( mouse_b&1 && mouse_x<=320 && mouse_x>=290 && mouse_y<=590 && mouse_y>=572)
            {
                rectfill(page,290,572,320,590,makecol(200,0,0 ));
                textprintf_ex(page,font,300,577,makecol(200,200,200),makecol(200,0,0 ),"J1");
                ennemi=0;
            }

        }
        else
        {
            rect(page,290,572,320,590,makecol(255,0,0 ));
            textprintf_ex(page,font,300,577,makecol(255,255,255),0,"J1");
        }


        if(((acteur2->x)<=(acteur2->x+150)) && ((acteur2->x)>=(acteur2->x-150)) && ((acteur2->y)<=(acteur2->y+150)) && ((acteur2->y)>=(acteur2->y-150))) // creer un rectangle de detction autour du personnaage
        {
            rectfill(page,340,572,370,590,makecol(255,0,0 ));
            textprintf_ex(page,font,350,577,makecol(255,255,255),makecol(255,0,0 ),"J2");
            if ( mouse_b&1 && mouse_x<=370 && mouse_x>=340 && mouse_y<=590 && mouse_y>=572)
            {
                rectfill(page,340,572,370,590,makecol(200,0,0 ));
                textprintf_ex(page,font,350,577,makecol(200,200,200),makecol(200,0,0 ),"J2");
                ennemi=1;
            }

        }
        else
        {
            rect(page,340,572,370,590,makecol(255,0,0 ));
            textprintf_ex(page,font,350,577,makecol(255,255,255),0,"J2");
        }


        if(((acteur3->x)<=(acteur2->x+150)) && ((acteur3->x)>=(acteur2->x-150)) && ((acteur3->y)<=(acteur2->y+150)) && ((acteur3->y)>=(acteur2->y-150))) // creer un rectangle de detction autour du personnaage
        {
            rectfill(page,390,572,420,590,makecol(255,0,0 ));
            textprintf_ex(page,font,400,577,makecol(255,255,255),makecol(255,0,0 ),"J3");
            if ( mouse_b&1 && mouse_x<=420 && mouse_x>=390 && mouse_y<=590 && mouse_y>=572)
            {
                rectfill(page,390,572,420,590,makecol(200,0,0 ));
                textprintf_ex(page,font,400,577,makecol(200,200,200),makecol(200,0,0 ),"J3");
                ennemi=2;
            }

        }
        else
        {
            rect(page,390,572,420,590,makecol(255,0,0 ));
            textprintf_ex(page,font,400,577,makecol(255,255,255),0,"J3");
        }



        }

        if (j==2)
        {
        if(((acteur1->x)<=(acteur3->x+150)) && ((acteur1->x)>=(acteur3->x-150)) && ((acteur1->y)<=(acteur3->y+150)) && ((acteur1->y)>=(acteur3->y-150))) // creer un rectangle de detction autour du personnaage
        {
            rectfill(page,290,572,320,590,makecol(255,0,0 ));
            textprintf_ex(page,font,300,577,makecol(255,255,255),makecol(255,0,0 ),"J1");
            if ( mouse_b&1 && mouse_x<=320 && mouse_x>=290 && mouse_y<=590 && mouse_y>=572)
            {
                rectfill(page,290,572,320,590,makecol(200,0,0 ));
                textprintf_ex(page,font,300,577,makecol(200,200,200),makecol(200,0,0 ),"J1");
                ennemi=0;
            }

        }
        else
        {
            rect(page,290,572,320,590,makecol(255,0,0 ));
            textprintf_ex(page,font,300,577,makecol(255,255,255),0,"J1");
        }


        if(((acteur2->x)<=(acteur3->x+150)) && ((acteur2->x)>=(acteur3->x-150)) && ((acteur2->y)<=(acteur3->y+150)) && ((acteur2->y)>=(acteur3->y-150))) // creer un rectangle de detction autour du personnaage
        {
            rectfill(page,340,572,370,590,makecol(255,0,0 ));
            textprintf_ex(page,font,350,577,makecol(255,255,255),makecol(255,0,0 ),"J2");
            if ( mouse_b&1 && mouse_x<=370 && mouse_x>=340 && mouse_y<=590 && mouse_y>=572)
            {
                rectfill(page,340,572,370,590,makecol(200,0,0 ));
                textprintf_ex(page,font,350,577,makecol(200,200,200),makecol(200,0,0 ),"J2");
                ennemi=1;
            }

        }
        else
        {
            rect(page,340,572,370,590,makecol(255,0,0 ));
            textprintf_ex(page,font,350,577,makecol(255,255,255),0,"J2");
        }


        if(((acteur3->x)<=(acteur3->x+150)) && ((acteur3->x)>=(acteur3->x-150)) && ((acteur3->y)<=(acteur3->y+150)) && ((acteur3->y)>=(acteur3->y-150))) // creer un rectangle de detction autour du personnaage
        {
            rectfill(page,390,572,420,590,makecol(255,0,0 ));
            textprintf_ex(page,font,400,577,makecol(255,255,255),makecol(255,0,0 ),"J3");
            if ( mouse_b&1 && mouse_x<=420 && mouse_x>=390 && mouse_y<=590 && mouse_y>=572)
            {
                rectfill(page,390,572,420,590,makecol(200,0,0 ));
                textprintf_ex(page,font,400,577,makecol(200,200,200),makecol(200,0,0 ),"J3");
                ennemi=2;
            }

        }
        else
        {
            rect(page,390,572,420,590,makecol(255,0,0 ));
            textprintf_ex(page,font,400,577,makecol(255,255,255),0,"J3");
        }



        }

    }

        if (nbjoueur==4)
    {
        if (j==0)
        {
        if(((acteur1->x)<=(acteur1->x+150)) && ((acteur1->x)>=(acteur1->x-150)) && ((acteur1->y)<=(acteur1->y+150)) && ((acteur1->y)>=(acteur1->y-150))) // creer un rectangle de detction autour du personnaage
        {
            rectfill(page,290,572,320,590,makecol(255,0,0 ));
            textprintf_ex(page,font,300,577,makecol(255,255,255),makecol(255,0,0 ),"J1");
            if ( mouse_b&1 && mouse_x<=320 && mouse_x>=290 && mouse_y<=590 && mouse_y>=572)
            {
                rectfill(page,290,572,320,590,makecol(200,0,0 ));
                textprintf_ex(page,font,300,577,makecol(200,200,200),makecol(200,0,0 ),"J1");
                ennemi=0;
            }

        }
        else
        {
            rect(page,290,572,320,590,makecol(255,0,0 ));
            textprintf_ex(page,font,300,577,makecol(255,255,255),0,"J1");
        }


        if(((acteur2->x)<=(acteur1->x+150)) && ((acteur2->x)>=(acteur1->x-150)) && ((acteur2->y)<=(acteur1->y+150)) && ((acteur2->y)>=(acteur1->y-150))) // creer un rectangle de detction autour du personnaage
        {
            rectfill(page,340,572,370,590,makecol(255,0,0 ));
            textprintf_ex(page,font,350,577,makecol(255,255,255),makecol(255,0,0 ),"J2");
            if ( mouse_b&1 && mouse_x<=370 && mouse_x>=340 && mouse_y<=590 && mouse_y>=572)
            {
                rectfill(page,340,572,370,590,makecol(200,0,0 ));
                textprintf_ex(page,font,350,577,makecol(200,200,200),makecol(200,0,0 ),"J2");
                ennemi=1;
            }

        }
        else
        {
            rect(page,340,572,370,590,makecol(255,0,0 ));
            textprintf_ex(page,font,350,577,makecol(255,255,255),0,"J2");
        }


        if(((acteur3->x)<=(acteur1->x+150)) && ((acteur3->x)>=(acteur1->x-150)) && ((acteur3->y)<=(acteur1->y+150)) && ((acteur3->y)>=(acteur1->y-150))) // creer un rectangle de detction autour du personnaage
        {
            rectfill(page,390,572,420,590,makecol(255,0,0 ));
            textprintf_ex(page,font,400,577,makecol(255,255,255),makecol(255,0,0 ),"J3");
            if ( mouse_b&1 && mouse_x<=420 && mouse_x>=390 && mouse_y<=590 && mouse_y>=572)
            {
                rectfill(page,390,572,420,590,makecol(200,0,0 ));
                textprintf_ex(page,font,400,577,makecol(200,200,200),makecol(200,0,0 ),"J3");
                ennemi=2;
            }

        }
        else
        {
            rect(page,390,572,420,590,makecol(255,0,0 ));
            textprintf_ex(page,font,400,577,makecol(255,255,255),0,"J3");
        }


        if(((acteur4->x)<=(acteur1->x+150)) && ((acteur4->x)>=(acteur1->x-150)) && ((acteur4->y)<=(acteur1->y+150)) && ((acteur4->y)>=(acteur1->y-150))) // creer un rectangle de detction autour du personnaage
        {
            rectfill(page,440,572,470,590,makecol(255,0,0 ));
            textprintf_ex(page,font,450,577,makecol(255,255,255),makecol(255,0,0 ),"J4");
            if ( mouse_b&1 && mouse_x<=470 && mouse_x>=440 && mouse_y<=590 && mouse_y>=572)
            {
                rectfill(page,440,572,470,590,makecol(200,0,0 ));
                textprintf_ex(page,font,450,577,makecol(200,200,200),makecol(200,0,0 ),"J4");
                ennemi=3;
            }

        }
        else
        {
            rect(page,440,572,470,590,makecol(255,0,0 ));
            textprintf_ex(page,font,450,577,makecol(255,255,255),0,"J4");
        }


        }

        if (j==1)
        {
        if(((acteur1->x)<=(acteur2->x+150)) && ((acteur1->x)>=(acteur2->x-150)) && ((acteur1->y)<=(acteur2->y+150)) && ((acteur1->y)>=(acteur2->y-150))) // creer un rectangle de detction autour du personnaage
        {
            rectfill(page,290,572,320,590,makecol(255,0,0 ));
            textprintf_ex(page,font,300,577,makecol(255,255,255),makecol(255,0,0 ),"J1");
            if ( mouse_b&1 && mouse_x<=320 && mouse_x>=290 && mouse_y<=590 && mouse_y>=572)
            {
                rectfill(page,290,572,320,590,makecol(200,0,0 ));
                textprintf_ex(page,font,300,577,makecol(200,200,200),makecol(200,0,0 ),"J1");
                ennemi=0;
            }

        }
        else
        {
            rect(page,290,572,320,590,makecol(255,0,0 ));
            textprintf_ex(page,font,300,577,makecol(255,255,255),0,"J1");
        }


        if(((acteur2->x)<=(acteur2->x+150)) && ((acteur2->x)>=(acteur2->x-150)) && ((acteur2->y)<=(acteur2->y+150)) && ((acteur2->y)>=(acteur2->y-150))) // creer un rectangle de detction autour du personnaage
        {
            rectfill(page,340,572,370,590,makecol(255,0,0 ));
            textprintf_ex(page,font,350,577,makecol(255,255,255),makecol(255,0,0 ),"J2");
            if ( mouse_b&1 && mouse_x<=370 && mouse_x>=340 && mouse_y<=590 && mouse_y>=572)
            {
                rectfill(page,340,572,370,590,makecol(200,0,0 ));
                textprintf_ex(page,font,350,577,makecol(200,200,200),makecol(200,0,0 ),"J2");
                ennemi=1;
            }

        }
        else
        {
            rect(page,340,572,370,590,makecol(255,0,0 ));
            textprintf_ex(page,font,350,577,makecol(255,255,255),0,"J2");
        }


        if(((acteur3->x)<=(acteur2->x+150)) && ((acteur3->x)>=(acteur2->x-150)) && ((acteur3->y)<=(acteur2->y+150)) && ((acteur3->y)>=(acteur2->y-150))) // creer un rectangle de detction autour du personnaage
        {
            rectfill(page,390,572,420,590,makecol(255,0,0 ));
            textprintf_ex(page,font,400,577,makecol(255,255,255),makecol(255,0,0 ),"J3");
            if ( mouse_b&1 && mouse_x<=420 && mouse_x>=390 && mouse_y<=590 && mouse_y>=572)
            {
                rectfill(page,390,572,420,590,makecol(200,0,0 ));
                textprintf_ex(page,font,400,577,makecol(200,200,200),makecol(200,0,0 ),"J3");
                ennemi=2;
            }

        }
        else
        {
            rect(page,390,572,420,590,makecol(255,0,0 ));
            textprintf_ex(page,font,400,577,makecol(255,255,255),0,"J3");
        }


        if(((acteur4->x)<=(acteur2->x+150)) && ((acteur4->x)>=(acteur2->x-150)) && ((acteur4->y)<=(acteur2->y+150)) && ((acteur4->y)>=(acteur2->y-150))) // creer un rectangle de detction autour du personnaage
        {
            rectfill(page,440,572,470,590,makecol(255,0,0 ));
            textprintf_ex(page,font,450,577,makecol(255,255,255),makecol(255,0,0 ),"J4");
            if ( mouse_b&1 && mouse_x<=470 && mouse_x>=440 && mouse_y<=590 && mouse_y>=572)
            {
                rectfill(page,440,572,470,590,makecol(200,0,0 ));
                textprintf_ex(page,font,450,577,makecol(200,200,200),makecol(200,0,0 ),"J4");
                ennemi=3;
            }

        }
        else
        {
            rect(page,440,572,470,590,makecol(255,0,0 ));
            textprintf_ex(page,font,450,577,makecol(255,255,255),0,"J4");
        }


        }

        if (j==2)
        {
        if(((acteur1->x)<=(acteur3->x+150)) && ((acteur1->x)>=(acteur3->x-150)) && ((acteur1->y)<=(acteur3->y+150)) && ((acteur1->y)>=(acteur3->y-150))) // creer un rectangle de detction autour du personnaage
        {
            rectfill(page,290,572,320,590,makecol(255,0,0 ));
            textprintf_ex(page,font,300,577,makecol(255,255,255),makecol(255,0,0 ),"J1");
            if ( mouse_b&1 && mouse_x<=320 && mouse_x>=290 && mouse_y<=590 && mouse_y>=572)
            {
                rectfill(page,290,572,320,590,makecol(200,0,0 ));
                textprintf_ex(page,font,300,577,makecol(200,200,200),makecol(200,0,0 ),"J1");
                ennemi=0;
            }

        }
        else
        {
            rect(page,290,572,320,590,makecol(255,0,0 ));
            textprintf_ex(page,font,300,577,makecol(255,255,255),0,"J1");
        }


        if(((acteur2->x)<=(acteur3->x+150)) && ((acteur2->x)>=(acteur3->x-150)) && ((acteur2->y)<=(acteur3->y+150)) && ((acteur2->y)>=(acteur3->y-150))) // creer un rectangle de detction autour du personnaage
        {
            rectfill(page,340,572,370,590,makecol(255,0,0 ));
            textprintf_ex(page,font,350,577,makecol(255,255,255),makecol(255,0,0 ),"J2");
            if ( mouse_b&1 && mouse_x<=370 && mouse_x>=340 && mouse_y<=590 && mouse_y>=572)
            {
                rectfill(page,340,572,370,590,makecol(200,0,0 ));
                textprintf_ex(page,font,350,577,makecol(200,200,200),makecol(200,0,0 ),"J2");
                ennemi=1;
            }

        }
        else
        {
            rect(page,340,572,370,590,makecol(255,0,0 ));
            textprintf_ex(page,font,350,577,makecol(255,255,255),0,"J2");
        }


        if(((acteur3->x)<=(acteur3->x+150)) && ((acteur3->x)>=(acteur3->x-150)) && ((acteur3->y)<=(acteur3->y+150)) && ((acteur3->y)>=(acteur3->y-150))) // creer un rectangle de detction autour du personnaage
        {
            rectfill(page,390,572,420,590,makecol(255,0,0 ));
            textprintf_ex(page,font,400,577,makecol(255,255,255),makecol(255,0,0 ),"J3");
            if ( mouse_b&1 && mouse_x<=420 && mouse_x>=390 && mouse_y<=590 && mouse_y>=572)
            {
                rectfill(page,390,572,420,590,makecol(200,0,0 ));
                textprintf_ex(page,font,400,577,makecol(200,200,200),makecol(200,0,0 ),"J3");
                ennemi=2;
            }

        }
        else
        {
            rect(page,390,572,420,590,makecol(255,0,0 ));
            textprintf_ex(page,font,400,577,makecol(255,255,255),0,"J3");
        }


        if(((acteur4->x)<=(acteur3->x+150)) && ((acteur4->x)>=(acteur3->x-150)) && ((acteur4->y)<=(acteur3->y+150)) && ((acteur4->y)>=(acteur3->y-150))) // creer un rectangle de detction autour du personnaage
        {
            rectfill(page,440,572,470,590,makecol(255,0,0 ));
            textprintf_ex(page,font,450,577,makecol(255,255,255),makecol(255,0,0 ),"J4");
            if ( mouse_b&1 && mouse_x<=470 && mouse_x>=440 && mouse_y<=590 && mouse_y>=572)
            {
                rectfill(page,440,572,470,590,makecol(200,0,0 ));
                textprintf_ex(page,font,450,577,makecol(200,200,200),makecol(200,0,0 ),"J4");
                ennemi=3;
            }

        }
        else
        {
            rect(page,440,572,470,590,makecol(255,0,0 ));
            textprintf_ex(page,font,450,577,makecol(255,255,255),0,"J4");
        }


        }

        if (j==3)
        {
        if(((acteur1->x)<=(acteur4->x+150)) && ((acteur1->x)>=(acteur4->x-150)) && ((acteur1->y)<=(acteur4->y+150)) && ((acteur1->y)>=(acteur4->y-150))) // creer un rectangle de detction autour du personnaage
        {
            rectfill(page,290,572,320,590,makecol(255,0,0 ));
            textprintf_ex(page,font,300,577,makecol(255,255,255),makecol(255,0,0 ),"J1");
            if ( mouse_b&1 && mouse_x<=320 && mouse_x>=290 && mouse_y<=590 && mouse_y>=572)
            {
                rectfill(page,290,572,320,590,makecol(200,0,0 ));
                textprintf_ex(page,font,300,577,makecol(200,200,200),makecol(200,0,0 ),"J1");
                ennemi=0;
            }

        }
        else
        {
            rect(page,290,572,320,590,makecol(255,0,0 ));
            textprintf_ex(page,font,300,577,makecol(255,255,255),0,"J1");
        }


        if(((acteur2->x)<=(acteur4->x+150)) && ((acteur2->x)>=(acteur4->x-150)) && ((acteur2->y)<=(acteur4->y+150)) && ((acteur2->y)>=(acteur4->y-150))) // creer un rectangle de detction autour du personnaage
        {
            rectfill(page,340,572,370,590,makecol(255,0,0 ));
            textprintf_ex(page,font,350,577,makecol(255,255,255),makecol(255,0,0 ),"J2");
            if ( mouse_b&1 && mouse_x<=370 && mouse_x>=340 && mouse_y<=590 && mouse_y>=572)
            {
                rectfill(page,340,572,370,590,makecol(200,0,0 ));
                textprintf_ex(page,font,350,577,makecol(200,200,200),makecol(200,0,0 ),"J2");
                ennemi=1;
            }

        }
        else
        {
            rect(page,340,572,370,590,makecol(255,0,0 ));
            textprintf_ex(page,font,350,577,makecol(255,255,255),0,"J2");
        }


        if(((acteur3->x)<=(acteur4->x+150)) && ((acteur3->x)>=(acteur4->x-150)) && ((acteur3->y)<=(acteur4->y+150)) && ((acteur3->y)>=(acteur4->y-150))) // creer un rectangle de detction autour du personnaage
        {
            rectfill(page,390,572,420,590,makecol(255,0,0 ));
            textprintf_ex(page,font,400,577,makecol(255,255,255),makecol(255,0,0 ),"J3");
            if ( mouse_b&1 && mouse_x<=420 && mouse_x>=390 && mouse_y<=590 && mouse_y>=572)
            {
                rectfill(page,390,572,420,590,makecol(200,0,0 ));
                textprintf_ex(page,font,400,577,makecol(200,200,200),makecol(200,0,0 ),"J3");
                ennemi=2;
            }

        }
        else
        {
            rect(page,390,572,420,590,makecol(255,0,0 ));
            textprintf_ex(page,font,400,577,makecol(255,255,255),0,"J3");
        }


        if(((acteur4->x)<=(acteur4->x+150)) && ((acteur4->x)>=(acteur4->x-150)) && ((acteur4->y)<=(acteur4->y+150)) && ((acteur4->y)>=(acteur4->y-150))) // creer un rectangle de detction autour du personnaage
        {
            rectfill(page,440,572,470,590,makecol(255,0,0 ));
            textprintf_ex(page,font,450,577,makecol(255,255,255),makecol(255,0,0 ),"J4");
            if ( mouse_b&1 && mouse_x<=470 && mouse_x>=440 && mouse_y<=590 && mouse_y>=572)
            {
                rectfill(page,440,572,470,590,makecol(200,0,0 ));
                textprintf_ex(page,font,450,577,makecol(200,200,200),makecol(200,0,0 ),"J4");
                ennemi=3;
            }

        }
        else
        {
            rect(page,440,572,470,590,makecol(255,0,0 ));
            textprintf_ex(page,font,450,577,makecol(255,255,255),0,"J4");
        }


        }


    }

        // Infos joueur
        textprintf_ex(page,font,5,580,makecol(255,0,0),makecol(0,255,0),"Joueur %d:",j+1);
        textprintf_ex(page,font,5,600,makecol(255,0,0),makecol(0,255,0),"PV: %d",Joueures[j].pv);
        textprintf_ex(page,font,100,600,makecol(255,0,0),makecol(0,255,0),"Compte: %d $",Joueures[j].compte);
        textprintf_ex(page,font,5,620,makecol(255,0,0),makecol(0,255,0),"PM: %d",Joueures[j].pm);
        textprintf_ex(page,font,5,640,makecol(255,0,0),makecol(0,255,0),"PA: %d",Joueures[j].pa);

        rectfill(page,10,655,130,668,makecol(0,255,0));
        textprintf_ex(page,font,15,658,makecol(255,255,255),makecol(0,255,0),"Joueur Suivant");
        if( mouse_b&1 && mouse_x<=130 && mouse_x>=10 && mouse_y<=668 && mouse_y>=655)
        {
            rectfill(page,10,655,130,668,makecol(0,200,0));
            textprintf_ex(page,font,15,658,makecol(200,200,200),makecol(0,200,0),"Joueur Suivant");
            j++;

        }
        rectfill(page,10,675,75,690,makecol(0,255,0));
        textprintf_ex(page,font,15,680,makecol(255,255,255),makecol(0,255,0),"Quitter");
        if( mouse_b&1 && mouse_x<=75 && mouse_x>=10 && mouse_y<=690 && mouse_y>=675)
        {

            rectfill(page,10,675,75,690,makecol(0,200,0));
            textprintf_ex(page,font,15,680,makecol(200,200,200),makecol(0,200,0),"Quitter");
            j=5;
            fin3=1;

            findetous=1;
        }


        textprintf_centre_ex(page,font,555,600,makecol(255,255,255),0,"Ordre:");
        if (nbjoueur==2)
    {
        if (j==0)
        {

            rectfill(page,540,610,570,630,makecol(0,255,0 ));
            textprintf_ex(page,font,550,615,makecol(255,0,0),makecol(0,255,0),"J1");


        }
        else
        {
            rect(page,540,610,570,630,makecol(0,255,0 ));
            textprintf_ex(page,font,550,615,makecol(255,0,0),0,"J1");
        }

        if (j==1)
        {

            rectfill(page,540,630,570,650,makecol(0,255,0 ));
            textprintf_ex(page,font,550,635,makecol(255,0,0),makecol(0,255,0),"J2");


        }
        else
        {
            rect(page,540,630,570,650,makecol(0,255,0 ));
            textprintf_ex(page,font,550,635,makecol(255,0,0),0,"J2");
        }
    }

        if (nbjoueur==3)
    {
        if (j==0)
        {

            rectfill(page,540,610,570,630,makecol(0,255,0 ));
            textprintf_ex(page,font,550,615,makecol(255,0,0),makecol(0,255,0 ),"J1");

        }
        else
        {
            rect(page,540,610,570,630,makecol(0,255,0 ));
            textprintf_ex(page,font,550,615,makecol(255,0,0),0,"J1");
        }




        if (j==1)
        {

            rectfill(page,540,630,570,650,makecol(0,255,0 ));
            textprintf_ex(page,font,550,635,makecol(255,0,0),makecol(0,255,0 ),"J2");

        }
        else
        {
            rect(page,540,630,570,650,makecol(0,255,0 ));
            textprintf_ex(page,font,550,635,makecol(255,0,0),0,"J2");
        }

        if (j==2)
        {
            rectfill(page,540,650,570,670,makecol(0,255,0 ));
            textprintf_ex(page,font,550,655,makecol(255,0,0),makecol(0,255,0 ),"J3");

        }
        else
        {
            rect(page,540,650,570,670,makecol(0,255,0 ));
            textprintf_ex(page,font,550,655,makecol(255,0,0),0,"J3");
        }
    }

        if (nbjoueur==4)
    {
        if (j==0)
        {

            rectfill(page,540,610,570,630,makecol(0,255,0 ));
            textprintf_ex(page,font,550,615,makecol(255,0,0),makecol(0,255,0 ),"J1");
        }
        else
        {
            rect(page,540,610,570,630,makecol(0,255,0 ));
            textprintf_ex(page,font,550,615,makecol(255,0,0),0,"J1");
        }




        if (j==1)
        {

            rectfill(page,540,630,570,650,makecol(0,255,0 ));
            textprintf_ex(page,font,550,635,makecol(255,0,0),makecol(0,255,0 ),"J2");

        }
        else
        {
            rect(page,540,630,570,650,makecol(0,255,0 ));
            textprintf_ex(page,font,550,635,makecol(255,0,0),0,"J2");
        }



        if (j==2)
        {

            rectfill(page,540,650,570,670,makecol(0,255,0 ));
            textprintf_ex(page,font,550,655,makecol(255,0,0),makecol(0,255,0 ),"J3");

        }
        else
        {
            rect(page,540,650,570,670,makecol(0,255,0 ));
            textprintf_ex(page,font,550,655,makecol(255,0,0),0,"J3");
        }


        if (j==3)
        {

            rectfill(page,540,670,570,690,makecol(0,255,0 ));
            textprintf_ex(page,font,550,675,makecol(255,0,0),makecol(0,255,0 ),"J4");


        }
        else
        {
            rect(page,540,670,570,690,makecol(0,255,0 ));
            textprintf_ex(page,font,550,675,makecol(255,0,0),0,"J4");
        }

    }


        // Commande

      /*  // bouton hauts
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
        //
        */

        // bouton attaque corps � corps


        if((zonedetect(acteur1,acteur2,acteur3,acteur4,j,32,0,ennemi)==1)&&(ennemi != j))//( mouse_x<=420 && mouse_x>=380 && mouse_y<=620 && mouse_y>=600)
        {
            rectfill(page,380,600,420,620,makecol(255,0,0 ));
            textprintf_centre_ex(page,font,400,605,makecol(255,255,255),makecol(255,0,0),"Arme");
        }
        else
        {
            rect(page,380,600,420,620,makecol(255,0,0 ));
            textprintf_centre_ex(page,font,400,605,makecol(255,255,255),makecol(0,0,0),"Arme");
        }


        if(( mouse_b&1 && mouse_x<=420 && mouse_x>=380 && mouse_y<=620 && mouse_y>=600)&&(zonedetect(acteur1,acteur2,acteur3,acteur4,j,32,0,ennemi)==1)&&((Joueures[j].pa-2)>=0)&&(ennemi != j))
        {
            rectfill(page,380,600,420,620,makecol(200,0,0 ));
            textprintf_centre_ex(page,font,400,605,makecol(200,200,200),makecol(200,0,0),"Arme");
            nbenvie=Arme(Joueures[j].classe,j,ennemi,nbenvie);
        }


        // bouton attaque � distance 1

        if ((zonedetect(acteur1,acteur2,acteur3,acteur4,j,150,100,ennemi)==1)&&(ennemi != j))//( mouse_x<=370 && mouse_x>=330 && mouse_y<=640 && mouse_y>=620)
        {
            rectfill(page,330,620,370,640,makecol(0,0,255));
            textprintf_centre_ex(page,font,350,625,makecol(255,255,255),makecol(0,0,255),"Sort1");
        }
        else
        {
            rect(page,330,620,370,640,makecol(0,0,255));
            textprintf_centre_ex(page,font,350,625,makecol(255,255,255),makecol(0,0,0),"Sort1");
        }



        if(( mouse_b&1 && mouse_x<=370 && mouse_x>=330 && mouse_y<=640 && mouse_y>=620)&&(zonedetect(acteur1,acteur2,acteur3,acteur4,j,150,100,ennemi)==1)&&((Joueures[j].pa-2)>=0)&&(ennemi != j))
        {
            rectfill(page,330,620,370,640,makecol(0,0,200));
            textprintf_centre_ex(page,font,350,625,makecol(200,200,200),makecol(0,0,200),"Sort1");
            nbenvie=Sort1(Joueures[j].classe,j,ennemi,nbenvie);
        }



        // bouton attaque � distance 2

        if((zonedetect(acteur1,acteur2,acteur3,acteur4,j,100,50,ennemi)==1)&&(ennemi != j))//( mouse_x<=470 && mouse_x>=430 && mouse_y<=640 && mouse_y>=620)
        {
           rectfill(page,430,620,470,640,makecol(0,0,255));
           textprintf_centre_ex(page,font,450,625,makecol(255,255,255),makecol(0,0,255),"Sort2");
        }
        else
        {
            rect(page,430,620,470,640,makecol(0,0,255));
            textprintf_centre_ex(page,font,450,625,makecol(255,255,255),makecol(0,0,0),"Sort2");
        }


        if(( mouse_b&1 && mouse_x<=470 && mouse_x>=430 && mouse_y<=640 && mouse_y>=620)&&(zonedetect(acteur1,acteur2,acteur3,acteur4,j,100,50,ennemi)==1)&&((Joueures[j].pa-2)>=0)&&(ennemi != j))
        {
            rectfill(page,430,620,470,640,makecol(0,0,200));
            textprintf_centre_ex(page,font,450,625,makecol(200,200,200),makecol(0,0,200),"Sort2");
           nbenvie=Sort2(Joueures[j].classe,j,ennemi,nbenvie);
        }


        // bouton attaque � distance 3

        if((zonedetect(acteur1,acteur2,acteur3,acteur4,j,50,32,ennemi)==1)&&(ennemi != j))//( mouse_x<=370 && mouse_x>=330 && mouse_y<=680 && mouse_y>=660)
        {
            rectfill(page,330,660,370,680,makecol(0,0,255));
            textprintf_centre_ex(page,font,350,665,makecol(255,255,255),makecol(0,0,255),"Sort3");
        }
        else
        {
            rect(page,330,660,370,680,makecol(0,0,255));
            textprintf_centre_ex(page,font,350,665,makecol(255,255,255),makecol(0,0,0),"Sort3");
        }



        if(( mouse_b&1 && mouse_x<=370 && mouse_x>=330 && mouse_y<=680 && mouse_y>=660)&&(zonedetect(acteur1,acteur2,acteur3,acteur4,j,50,0,ennemi)==1)&&((Joueures[j].pa-2)>=0)&&(ennemi != j))
        {
            rectfill(page,330,660,370,680,makecol(0,0,200));
            textprintf_centre_ex(page,font,350,665,makecol(200,200,200),makecol(0,0,200),"Sort3");
            nbenvie=Sort3(Joueures[j].classe,j,ennemi,nbenvie);
        }


        // bouton attaque � distance 4

        if(zonedetect(acteur1,acteur2,acteur3,acteur4,j,100,0,ennemi)==1)//  ( mouse_x<=470 && mouse_x>=430 && mouse_y<=680 && mouse_y>=660)
        {
            rectfill(page,430,660,470,680,makecol(0,0,255));
            textprintf_centre_ex(page,font,450,665,makecol(255,255,255),makecol(0,0,255),"Sort4");
        }
        else
        {
            rect(page,430,660,470,680,makecol(0,0,255));
            textprintf_centre_ex(page,font,450,665,makecol(255,255,255),makecol(0,0,0),"Sort4");
        }


        if(( mouse_b&1 && mouse_x<=470 && mouse_x>=430 && mouse_y<=680 && mouse_y>=660)&&(zonedetect(acteur1,acteur2,acteur3,acteur4,j,100,0,ennemi)==1)&&((Joueures[j].pa-2)>=0))
        {
            rectfill(page,430,660,470,680,makecol(0,0,200));
            textprintf_centre_ex(page,font,450,665,makecol(255,255,255),makecol(0,0,255),"Sort4");
            nbenvie=Sort4(Joueures[j].classe,j,ennemi,nbenvie);
        }




        // Infos ennemi 2
        if(nbjoueur==2)
        {
            textprintf_right_ex(page,font,792,580,makecol(255,0,0),makecol(0,255,0),"Joueur %d PV: %d",Joueures[0].num,Joueures[0].pv);
            textprintf_right_ex(page,font,792,600,makecol(255,0,0),makecol(0,255,0),"Joueur %d PV: %d",Joueures[1].num,Joueures[1].pv);
        }

        // Infos ennemi 3
        if(nbjoueur==3)
        {
            textprintf_right_ex(page,font,792,580,makecol(255,0,0),makecol(0,255,0),"Joueur %d PV: %d",Joueures[0].num,Joueures[0].pv);
            textprintf_right_ex(page,font,792,600,makecol(255,0,0),makecol(0,255,0),"Joueur %d PV: %d",Joueures[1].num,Joueures[1].pv);
            textprintf_right_ex(page,font,792,620,makecol(255,0,0),makecol(0,255,0),"Joueur %d PV: %d",Joueures[2].num,Joueures[2].pv);
        }

        // Infos ennemi 4
        if(nbjoueur==4)
        {
            textprintf_right_ex(page,font,792,580,makecol(255,0,0),makecol(0,255,0),"Joueur %d PV: %d",Joueures[0].num,Joueures[0].pv);
            textprintf_right_ex(page,font,792,600,makecol(255,0,0),makecol(0,255,0),"Joueur %d PV: %d",Joueures[1].num,Joueures[1].pv);
            textprintf_right_ex(page,font,792,620,makecol(255,0,0),makecol(0,255,0),"Joueur %d PV: %d",Joueures[2].num,Joueures[2].pv);
            textprintf_right_ex(page,font,792,640,makecol(255,0,0),makecol(0,255,0),"Joueur %d PV: %d",Joueures[3].num,Joueures[3].pv);
        }


        // Bord console utilisateur
        rect(page,0,560,800,700,makecol(0,255,0 ));
        rect(page,1,561,799,699,makecol(0,255,0 ));
        rect(page,2,562,798,698,makecol(0,255,0 ));
        rect(page,3,563,797,697,makecol(0,255,0 ));

        // Info curseur
        textprintf_ex(page,font,690,675,makecol(0,255,0),makecol(0,0,0),"%4d secondes",dureeTourDeJeu);
        textprintf_ex(page,font,690,685,makecol(0,255,0),makecol(0,0,0),"x=%4d y=%4d",mouse_x,mouse_y);

        if (nbjoueur==2)
        {
            // Afficher personnage (positionner par rapport � ses jambes)
        draw_sprite(page, acteur1->img, acteur1->x - acteur1->img->w/2, acteur1->y - acteur1->img->h + 8);

        // Afficher personnage (positionner par rapport � ses jambes)
        draw_sprite(page, acteur2->img, acteur2->x - acteur2->img->w/2, acteur2->y - acteur2->img->h + 8);
        }

        if (nbjoueur==3)
        {
            // Afficher personnage (positionner par rapport � ses jambes)
        draw_sprite(page, acteur1->img, acteur1->x - acteur1->img->w/2, acteur1->y - acteur1->img->h + 8);

        // Afficher personnage (positionner par rapport � ses jambes)
        draw_sprite(page, acteur2->img, acteur2->x - acteur2->img->w/2, acteur2->y - acteur2->img->h + 8);

        // Afficher personnage (positionner par rapport � ses jambes)
        draw_sprite(page, acteur3->img, acteur3->x - acteur3->img->w/2, acteur3->y - acteur3->img->h + 8);
        }

        if (nbjoueur==4)
        {
            // Afficher personnage (positionner par rapport � ses jambes)
        draw_sprite(page, acteur1->img, acteur1->x - acteur1->img->w/2, acteur1->y - acteur1->img->h + 8);

        // Afficher personnage (positionner par rapport � ses jambes)
        draw_sprite(page, acteur2->img, acteur2->x - acteur2->img->w/2, acteur2->y - acteur2->img->h + 8);

        // Afficher personnage (positionner par rapport � ses jambes)
        draw_sprite(page, acteur3->img, acteur3->x - acteur3->img->w/2, acteur3->y - acteur3->img->h + 8);

        // Afficher personnage (positionner par rapport � ses jambes)
        draw_sprite(page, acteur4->img, acteur4->x - acteur4->img->w/2, acteur4->y - acteur4->img->h + 8);

        }

        if (nbenvie==1)
        {
          fin3=1;
        }

        if (Joueures[j].pa==0)
        {
          j++;
        }


        // Affichage du buffer mis a jour a l'ecran
        blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);

        // On fait une petite pause
        rest(200);
    }

    if (nbjoueur==1)
    {
      fin3=1;
    }

    j=0;

    }
    while (!aurevoir)
    {
        clear_bitmap(page);

        rectfill(page,300,30,500,55,makecol(0,255,0 ));
        textprintf_ex(page,font,350,40,makecol(255,0,0),makecol(0,255,0),"FIN DU JEU");

        // Infos ennemi 2
        if(nbfinal==2)
        {
            textprintf_ex(page,font,300,80,makecol(255,0,0),makecol(0,255,0),"Joueur %d PV: %d",Joueures[0].num,Joueures[0].pv);
            textprintf_ex(page,font,300,100,makecol(255,0,0),makecol(0,255,0),"Compte: %d",Joueures[0].compte);
            textprintf_ex(page,font,300,140,makecol(255,0,0),makecol(0,255,0),"Joueur %d PV: %d",Joueures[1].num,Joueures[1].pv);
            textprintf_ex(page,font,300,160,makecol(255,0,0),makecol(0,255,0),"Compte: %d",Joueures[1].compte);
        }

        // Infos ennemi 3
        if(nbfinal==3)
        {
            textprintf_ex(page,font,300,80,makecol(255,0,0),makecol(0,255,0),"Joueur %d PV: %d",Joueures[0].num,Joueures[0].pv);
            textprintf_ex(page,font,300,100,makecol(255,0,0),makecol(0,255,0),"Compte: %d",Joueures[0].compte);
            textprintf_ex(page,font,300,140,makecol(255,0,0),makecol(0,255,0),"Joueur %d PV: %d",Joueures[1].num,Joueures[1].pv);
            textprintf_ex(page,font,300,160,makecol(255,0,0),makecol(0,255,0),"Compte: %d",Joueures[1].compte);
            textprintf_ex(page,font,300,200,makecol(255,0,0),makecol(0,255,0),"Joueur %d PV: %d",Joueures[2].num,Joueures[2].pv);
            textprintf_ex(page,font,300,220,makecol(255,0,0),makecol(0,255,0),"Compte: %d",Joueures[2].compte);
        }

        // Infos ennemi 4
        if(nbfinal==4)
        {
            textprintf_ex(page,font,300,80,makecol(255,0,0),makecol(0,255,0),"Joueur %d PV: %d",Joueures[0].num,Joueures[0].pv);
            textprintf_ex(page,font,300,100,makecol(255,0,0),makecol(0,255,0),"Compte: %d",Joueures[0].compte);
            textprintf_ex(page,font,300,140,makecol(255,0,0),makecol(0,255,0),"Joueur %d PV: %d",Joueures[1].num,Joueures[1].pv);
            textprintf_ex(page,font,300,160,makecol(255,0,0),makecol(0,255,0),"Compte: %d",Joueures[1].compte);
            textprintf_ex(page,font,300,200,makecol(255,0,0),makecol(0,255,0),"Joueur %d PV: %d",Joueures[2].num,Joueures[2].pv);
            textprintf_ex(page,font,300,220,makecol(255,0,0),makecol(0,255,0),"Compte: %d",Joueures[2].compte);
            textprintf_ex(page,font,300,260,makecol(255,0,0),makecol(0,255,0),"Joueur %d PV: %d",Joueures[3].num,Joueures[3].pv);
            textprintf_ex(page,font,300,280,makecol(255,0,0),makecol(0,255,0),"Compte: %d",Joueures[3].compte);
        }


    // Bord console utilisateur
        rect(page,0,0,800,650,makecol(0,255,0 ));
        rect(page,1,1,799,649,makecol(0,255,0 ));
        rect(page,2,2,798,648,makecol(0,255,0 ));
        rect(page,3,3,797,647,makecol(0,255,0 ));

        //boutons

        if(mouse_x<=500 && mouse_x>=300 && mouse_y<=450 && mouse_y>=350)//( mouse_x<=370 && mouse_x>=330 && mouse_y<=680 && mouse_y>=660)
        {
            rectfill(page,300,350,500,450,makecol(0,255,0 ));//rectangle boutons quitter
            textprintf_centre_ex(page,font,400,400,makecol(0,0,0),makecol(0,255,0),"Quitter");//texte boutons quitter
        }
        else
        {
            rect(page,300,350,500,450,makecol(0,255,0 ));//rectangle boutons quitter
            textprintf_centre_ex(page,font,400,400,makecol(0,255,0),0,"Quitter");//texte boutons quitter
        }



        // prise en compte effective de la zone cliquable EXIT :
        // clic sur la case -> fin du programme
        if (mouse_b & 1 && mouse_x<=500 && mouse_x>=300 && mouse_y<=450 && mouse_y>=350) // droit : dessiner en bleu
            {
                rectfill(page,300,350,500,450,makecol(0,200,0 ));//rectangle boutons quitter
                textprintf_centre_ex(page,font,400,400,makecol(0,0,0),makecol(0,200,0),"Quitter");//texte boutons quitter
                aurevoir=1;
                findetous=1;
            }


        // Affichage du buffer mis a jour a l'ecran
        blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);

        // On fait une petite pause
        rest(15);

    }
    }

return 0;
}


END_OF_MAIN();
