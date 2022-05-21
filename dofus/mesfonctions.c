#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <allegro.h>
#include <time.h>
#include <winalleg.h>
#include "mabiblio.h"

// Pour gérer les collisions on indique les types de tuiles : 1 obstacle  2 eau
int typeTuiles[NTUILE] = {
    1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0,
    0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1,
    0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1,
    1, 1, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
    0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1,
    1, 1, 0, 1, 0, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    2, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1,
    0, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 2, 2, 2, 1, 1, 1, 1, 1,
    1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 1, 1, 1, 2, 1, 1, 2, 2
};
// Ici un seul terrain de jeu
// ( pour en avoir plusieurs faire un tableau de plusieurs des ces matrices
int terrain[NYMAP][NXMAP] = {
    {  0,   1,   2,   3,   4,   2,   3,   4,   2,   3,   4,   2,   3,   4,   2,   3,   5,   6,   6,   6,   6,   6,   6,   6,   7,   6,   6,   6,   7,   6,   6,   7,   7,   6,   6,   6,   8,   9,   6,   7,   8,  10,  11,  12,  12,  12,  13,  14,  15,  16 },
    { 17,  18,  19,  20,  21,  22,  20,  21,  22,  20,  21,  22,  20,  21,  23,  24,  25,   6,   6,   6,   7,   6,   6,   6,   6,   6,   6,   6,   6,   7,   7,   6,   6,   7,   6,  26,   8,   9,   6,   7,   8,  11,  27,  28,  28,  28,  14,  13,  14,  15 },
    { 29,  30,  31,  32,  33,  34,  32,  33,  34,  32,  33,  34,  32,  33,  35,  36,   6,   7,   6,   6,   6,   6,   6,   6,   7,  37,   6,   7,   6,   6,  38,  39,  39,  40,  26,  41,  42,  43,   6,   6,  44,  27,  45,  12,  12,  12,  13,  14,  13,  14 },
    { 46,  47,  48,  49,  50,  51,  49,  50,  51,  49,  50,  51,  49,  50,  52,   6,   6,   6,   7,  37,   7,   6,   6,   6,   6,   6,   6,  37,   6,   6,  39,  39,  38,  38,  41,  42,  43,   6,   6,   7,  53,  45,  27,  28,  28,  28,  14,  13,  14,  13 },
    { 54,  47,  55,  56,  57,  58,  56,  57,  58,  56,  57,  58,  56,  57,  59,   6,   6,  60,  61,   6,   6,  60,  61,   6,   6,   6,   7,   6,   6,   6,   6,   6,   6,   6,   8,   9,   6,   6,   6,   6,   6,  53,  45,  12,  12,  12,  13,  14,  13,  62 },
    { 63,  64,  65,  66,  67,  68,  66,  67,  68,  66,  67,  68,  66,  67,  69,   6,  60,  70,  71,  72,  73,  74,  75,  61,   6,   6,   6,   6,  76,  77,  78,  79,  80,   6,  44,  81,  82,   6,   6,   7,   6,   6,  53,  83,  83,  28,  14,  13,  62,   6 },
    {  6,   6,   6,   6,   6,   6,  84,  85,   6,   6,   6,   6,   6,   6,   6,  60,  70,  86,  12,  87,  88,  12,  89,  75,  61,   6,   6,   6,  90,  91,  92,  93,  94,   6,  53,  45,  81,  95,  95,  95,  95,  95,  95,  95,  96,  12,  13,  62,  97,  98 },
    { 99, 100,   6,   6,   6,  84, 101, 102, 103, 103, 103, 103, 103,  85,  60,  70,  86,  13, 104, 105, 106, 104,  45,  89,  75,  61,   6,   6, 107,   4,   2,   3,   5,   6,   6,  53,  45,  12,  12,  12,  12,  12,  12,  12,  13,  83,  62,   6, 108, 109 },
    {110, 111, 112,  82,   6,  63, 113, 113, 113, 113, 113, 113, 113,  64,  70,  86,  13, 114, 115, 116, 117, 115, 118,  45,  89,  75,   6, 119, 120,  21,  23,  24,  25,   7,   6,   7,  53,  83,  83,  83,  83,  83,  83,  83,  62,   6,  97,  98,   6,   6 },
    {121,   6, 122, 123,  82,  60, 124, 124, 124, 124, 124,  61,  99, 100, 125, 126, 114, 127, 128, 129, 129, 129, 130, 118, 131, 132,   6, 133,  32,  33,  35,  36, 134, 134,   7,   6,   6,   6,   6,   6,   6,   6,   6,   6,   6,   6, 108, 109,   6,   6 },
    {135,   6,   6, 136,  81,  74, 137, 137, 137, 137, 137,  71, 110, 111, 125, 138, 139, 129, 129, 140, 129, 129, 129, 141, 142, 132,   6,  48,  49,  50,  52, 134, 134, 134,  38,  38,  39,  40,   7,   6,   6,   7,   6, 143, 144,   6, 119, 120, 145, 146 },
    {  6,   6,   6, 147,  45,  12,  12,  12,  12,  12,  12,  12, 121,   6, 125, 138, 139, 129, 129, 129, 129, 128, 129, 141, 142, 132,   6,  55,  56,  57,  59, 134, 134, 134,  38,  38,  38,  38,   7,   6,   7,   6,   6, 148, 149,   6, 133,  32,  33, 150 },
    {  7,   6,  39,  40,  53,  83, 151, 152, 153, 154,  83,  83, 135,   6, 125, 138, 139, 129, 129, 129, 129, 129, 129, 141, 142, 132,  61,  65,  66,  67,  69,   6,   6,   7,   6,   7,   6,   6,   6,  37,   6,   6,   6,   7,   6,   6,  48,  49,  50,  52 },
    {  6,   7,  38,  38,   6,   6, 133,  32,  33, 150,   6,   6,   6,   6, 155, 156, 157, 158, 129, 129, 128, 129, 129, 141, 159,  89,  75,  61,   6,   6,   6, 112,  82,   6,   6,   6,   6,   6,   7,   6,   6,   6,   6,   6,  40,   6,  55,  56,  57,  59 },
    {  6,   6,   6,   6,   6,   6,  48,  49,  50,  52,   6,   6,   6,   6, 160, 155, 156, 157, 158, 129, 129, 140, 129, 130, 118,  45,  89,  75,  61,   6,   6, 122, 123,  95,  95,  82,   7,   6,   6,   7,   7,   6,   7,   6,   6,   6,  65,  66,  67,  69 },
    {  6,  76,  77,  78,  79,  77, 161, 162, 163,  78,  79,  80, 134,   6,   6, 160, 155, 156, 157, 158, 129, 129, 129, 129, 130, 118,  45,  89,  75,   6,   6,   6, 136,  12,  12,  81,  82,   6,   7,   6,   6,   6,   6,   6,   6,   6,   6,   6,   6,   6 },
    {  6,  90,  91,  92,  93,  91,  92,  93,  91,  92,  93,  94, 134, 134,   6,   6, 160, 155, 156, 157, 158, 129, 164, 165, 129, 130, 118, 131, 132,   6,   6,   7, 147,  83,  83,  45,  81,  82,   6,   6,   6,   6,   6,   6,   6,   6,   6,   6,   6,   6 },
    {  6, 107,   4,   2,   3,   4,   2,   3,   4,   2,   3,   5, 134,   6,   6,   6,   6, 160, 155, 156, 157, 158, 166, 167, 129, 129, 141, 142, 132,   6,   7,   6,   6,   6,   6,  53,  45,  81,  95,  95,  95,  95,  95,  82,   6,   6,   6,   7, 134,   6 },
    {  6, 168, 169, 170,  24, 169, 171,  20,  21,  22,  20, 145, 146, 134,   6,   6,   6,   7, 160, 155, 156, 157, 172, 173, 173, 174, 175, 176, 177,   6,  39,  40,   6,   6,   6,   6,  53,  45,  12,  12,  12,  12,  12,  81,  82,   6,   6, 134,   7,   6 },
    {  6,   6, 178, 179,  36, 178,  31,  32,  33,  34,  32,  33, 150, 134, 134,   6,   7,   6,   6, 160, 155, 156, 180, 181, 181, 182, 176, 177, 183,   6,  38,  38,   6, 134,   6,   6,   6,  53,  83,  83,  83,  83,  83,  45,  81,  82,   7,   6,   6,  99 },
    {  6,   6, 184,   6,   6,   6,  48,  49,  50,  51,  49,  50,  52, 134,   7,   6,  38,  39,  39,  40, 160, 155, 185, 185, 185, 185, 177, 183,   7,   6,  38,  39,   6,   7,   6,   6,   6,   6,   6,   6,   6,   6,   6,  53,  45,  81,  95,  95,  95,  96 },
    { 85,   6, 184, 184,   6, 184,  55,  56,  57,  58,  56,  57,  59, 134,   6,   7,  39,  39,  38,  38,   6, 160, 186, 186, 186, 186, 183,   6,   6,   7,  39,  39,   7,   6,   6,   6,   6,   6,   6,   6,   6,   6,   6,   6,  53,  45,  12,  12,  12,  13 },
    {102,  85,  84,  85,   6,   6,  65,  66,  67,  68,  66,  67,  69,   6,   6,   6,  39,  40,   6,   6,   6,   6,   6,   6, 187, 188,   6,   6, 189,   6,   6,   6,   6, 187, 190, 191, 188,   6,   6,   6,   6,   6,   6,   6,   6,  53,  83,  83,  83,  62 },
    {192, 102, 101, 102,  85,   6,   6,   6,   6,   6,   6,   6,   6,   6,   6,   6,  38,  38,   6, 187, 193, 103, 194, 190, 101, 102, 194, 188,   6,   6,   6, 187, 193, 101, 192, 192, 195, 191, 188,   6,   6,  84,  85,   6,   6,   6,   6,   6,   6,   6 },
    {192, 192, 192, 192, 102, 103, 103, 103, 103, 103, 103, 103, 103, 194, 188,  84, 103, 103, 103, 101, 192, 192, 192, 196, 113, 197, 192, 195, 103, 103, 103, 101, 192, 192, 192, 192, 192, 192, 102, 103, 103, 101, 102, 103, 103, 103, 103, 103, 103, 103 },
    {113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 197, 192, 195, 198, 196, 113, 113, 113, 113, 113, 199, 200,   6, 201, 202, 113, 113, 113, 203, 192, 192, 192, 192, 196, 113, 113, 113, 113, 113, 113, 113, 113, 197, 204, 192, 192, 192, 204 },
    {  6,   6,   6,   6,   6,   6,   6,   6,   6,   6,   6,   6,  63, 113, 113, 199, 200,   6,   6,   6,   6,   6,   6,   6,   6,   6,   6,   6,   6,   6,  63, 113, 113, 113, 113,  64,   6,   6,   6,   6,   6,   6,   6,   6,  63, 113, 113, 113, 113, 113 },
    { 78,  79,  77,  78,  79,  77,  78,  79,  77,  78,  79,  77,  78,  79,  80,   6,   6,   6,   6,   6,   6,   6, 134, 134,   6,   6, 134, 134,   6,  76,  77,  78,  79,  80,   6,   6,   6,  60, 124, 124, 124, 124, 124, 124, 124, 124, 124, 124, 124, 124 },
    { 92,  93,  91,  92,  93,  91,  92,  93,  91,  92,  93,  91,  92,  93,  94,   6,   6,   6,   6,   6,   6,   6,   6,   6, 134,   6,   6, 134,   6,  90,  91,  92,  93,  94,   6,   6,  60,  70, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137 },
    {  2,   3,   4,   2,   3,   4,   2,   3,   4,   2,   3,   4,   2,   3,   5,   6,   6,   6,   6,   6,   6,  76,  77,  78,  79,  80,   6,   6,   6, 107,   4,   2,   3,   5,   6,  60,  70,  86,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12 },
    { 22,  20,  21,  22,  20,  21,  22,  20,  21,  22,  20,  21,  22,  20, 145, 146,   6,   6,   6,   6,   6,  90,  91,  92,  93,  94,   6,   6, 119, 120,  21,  22,  20, 145, 146,  70,  86,  13, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104 },
    { 34,  32,  33,  34,  32,  33,  34,  32,  33,  34,  32,  33,  34,  32,  33, 150,   6,   6,   6,   6,   6, 107,   4,   2,   3,   5,   6,   6, 133,  32,  33,  34,  32,  33, 150, 125, 126, 114, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115 },
    { 51,  49,  50,  51,  49,  50,  51,  49,  50,  51,  49,  50,  51,  49,  50,  52,   6,   6,   6,   7,   6, 168, 169, 170,  24,  25,   6,   6,  48,  49,  50,  51,  49,  50,  52, 125, 138, 139, 129, 140, 129, 129, 129, 128, 129, 129, 129, 129, 129, 140 },
    { 58,  56,  57,  58, 205, 163, 206, 162, 163, 206, 162, 163, 206, 162, 207,  59,   6,   6,   6,   6,   6,   6, 178, 179,  36,   6,   7,   6,  55,  56,  57,  58,  56,  57,  59, 125, 138, 139, 129, 129, 129, 129, 129, 129, 208, 173, 173, 173, 173, 173 },
    { 68,  66,  67,  68, 209,  91,  92,  93,  91,  92,  93,  91,  92,  93, 210,  69,   6,   6, 134,   6,   6,   6,   6,   6,   6,   6,   6,   6,  65,  66,  67,  68,  66,  67,  69, 125, 138, 139, 129, 129, 129, 140, 129, 211, 212, 181, 181, 181, 181, 181 }
};

/******************************************/
/*         SOUS-PROGRAMMES                */
/******************************************/

// Dessine la tuile numéro ituile sur la bitmap bmp au coordonnées xmap ymap
// (unité en nombre de tuiles, pas en pixels)
void dessineTuile(BITMAP *bmp, int ituile, int xmap, int ymap){
    int lig, col; // ligne et colonne de la tuile source dans tableTuiles

    // Le numéro de ligne et de colonne dans un tableau 2D
    // à partir de l'indice du ième élément (en comptant de gauche à droite
    // et de haut en bas) s'obtiennent avec le quotient et le reste
    // dans la division de l'indice par le nombre de colonnes du tableau
    lig = ituile / NCOLTUILE;
    col = ituile % NCOLTUILE;

    // on copie juste le morceau concerné
    blit(tableTuiles, bmp, col*TXTUILE, lig*TYTUILE,
         xmap*TXTUILE, ymap*TYTUILE, TXTUILE, TYTUILE);

    if(1){
        rect(bmp, xmap*TXTUILE, ymap*TYTUILE, xmap*TXTUILE+TXTUILE-1, ymap*TYTUILE +TYTUILE-1, makecol(0,255,0));
    }

    // pour visualiser les types de tuiles (obstacle, eau)
    // ( à enlever pour un programme finalisé...)
    if (key[KEY_SPACE])
    {
        if (typeTuiles[ituile]==1)
            rect(bmp, xmap*TXTUILE, ymap*TYTUILE, xmap*TXTUILE+TXTUILE-1, ymap*TYTUILE +TYTUILE-1, makecol(255,0,0));
        if (typeTuiles[ituile]==2)
            rect(bmp, xmap*TXTUILE, ymap*TYTUILE, xmap*TXTUILE+TXTUILE-1, ymap*TYTUILE +TYTUILE-1, makecol(0,0,255));
    }
}

// Dessine un terrain complet sur une bitmap
void dessineTerrain(BITMAP *bmp, int terrain[NYMAP][NXMAP]){
    int xmap,ymap;

    for (ymap=0;ymap<NYMAP;ymap++)
            for (xmap=0;xmap<NXMAP;xmap++)
                dessineTuile(bmp,terrain[ymap][xmap],xmap,ymap);
}

// Tester si le déplacement dx dy ammène sur une tuile du type indiqué
// Si le type indiqué est 1 (obstacle) alors un déplacement
// en dehors du terrain retourne également vrai
// Retourne OUI : 1   NON : 0
int typeTerrain(t_acteur *acteur, int dx, int dy, int type){
    int xmap,ymap,ituile; // Coordonnées matrice et numéro de tuile
    int decx,decy;        // Pour visiter les coins...
    int cx,cy;            // Coordonnées des coins (en pixels)

    // Pour chacun des 4 coins...
    for (decy=-TYTUILE/2; decy<TYTUILE/2; decy+=TYTUILE-1)
        for (decx=-TXTUILE/2; decx<TXTUILE/2; decx+=TXTUILE-1)
        {
            // Coord. du coin
            cx=acteur->x+dx+decx;
            cy=acteur->y+dy+decy;

            // Si on sort du terrain...
            if (cx<0 || cx>=NXMAP*TXTUILE || cy<0 || cy>=NYMAP*TYTUILE)
            {
                if (type==1)  return 1;  // Oui c'est un obstacle
                else  return 0;          // Non ce n'est pas autre chose...
            }

            // Trouver les coordonnées matrice
            xmap=cx/TXTUILE;
            ymap=cy/TYTUILE;

            // Récupérer le numéro de tuile sur laquelle on arrive
            ituile=terrain[ymap][xmap];

            // Retourner OUI si le type de la tuile est bien celui recherché
            if (typeTuiles[ituile]==type)
                return 1;
        }

    // Donc NON, on n'a pas trouvé le type recherché
    return 0;
}

// Chargement "sécurisé" d'une image :
// interrompt le programme avec un message si problème...
BITMAP * load_bitmap_check(char *nomImage){
    BITMAP *bmp;
    bmp=load_bitmap(nomImage,NULL);
    if (!bmp)
    {
        allegro_message("pas pu trouver %s",nomImage);
        exit(EXIT_FAILURE);
    }
    return bmp;
}

void initialiseJoueurs(int nJoueures)
{

    for (int i = 0; i < nJoueures; i++)//
	{
	    Joueures[i].num = i+1;
		Joueures[i].compte = 100;//
        Joueures[i].classe=0;
		Joueures[i].pv = 100;//
		Joueures[i].pm=3;
		Joueures[i].pa=10;
	}
}

int Arme(int numeroClasse,int i,int lattaque,int nJoueures)
{
    int de3=0;
    int j;
    de3 = (rand() % 10) + 1;//
    if ((lattaque<nJoueures)&&(Joueures[lattaque].pv>0))
    {
      if (numeroClasse==1)
    {
        if((Joueures[i].pa-2)>=0)
        {
            if(de3!=5)
            {
                Joueures[i].pa=Joueures[i].pa-2;
                Joueures[lattaque].pv=Joueures[lattaque].pv-5;
                if(Joueures[lattaque].pv<=0)
                {
                    Joueures[lattaque].pv=0;
                    Joueures[i].compte=Joueures[i].compte+100;
                    Joueures[lattaque].compte=Joueures[lattaque].compte-100;
                    nJoueures = nJoueures-1;
                    if (lattaque==0)
            {
                acteur1->x = 1000;
                acteur1->y = 1000;
            }
            if (lattaque==1)
            {
                acteur2->y = 1000;
                acteur2->x = 1000;
            }
            if (lattaque==2)
            {
                acteur3->x = 1000;
                acteur3->y = 1000;
            }
            if (lattaque==3)
            {
                acteur4->x = 1000;
                acteur4->y = 1000;
            }
                }
            }

        }

    }

    if (numeroClasse==2)
    {
        if((Joueures[i].pa-2)>=0)
        {
            if(de3!=5)
            {
                Joueures[i].pa=Joueures[i].pa-2;
                Joueures[lattaque].pv=Joueures[lattaque].pv-5;
                if(Joueures[lattaque].pv<=0)
                {
                    Joueures[lattaque].pv=0;
                    Joueures[i].compte=Joueures[i].compte+100;
                    Joueures[lattaque].compte=Joueures[lattaque].compte-100;
                nJoueures = nJoueures-1;
                if (lattaque==0)
            {
                acteur1->x = 1000;
                acteur1->y = 1000;
            }
            if (lattaque==1)
            {
                acteur2->y = 1000;
                acteur2->x = 1000;
            }
            if (lattaque==2)
            {
                acteur3->x = 1000;
                acteur3->y = 1000;
            }
            if (lattaque==3)
            {
                acteur4->x = 1000;
                acteur4->y = 1000;
            }
                }
            }

        }


    }

    if (numeroClasse==3)
    {
        if((Joueures[i].pa-2)>=0)
        {
            if(de3!=5)
            {
                Joueures[i].pa=Joueures[i].pa-2;
                Joueures[lattaque].pv=Joueures[lattaque].pv-5;
                if(Joueures[lattaque].pv<=0)
                {
                    Joueures[lattaque].pv=0;
                    Joueures[i].compte=Joueures[i].compte+100;
                    Joueures[lattaque].compte=Joueures[lattaque].compte-100;

                nJoueures = nJoueures-1;
                if (lattaque==0)
            {
                acteur1->x = 1000;
                acteur1->y = 1000;
            }
            if (lattaque==1)
            {
                acteur2->y = 1000;
                acteur2->x = 1000;
            }
            if (lattaque==2)
            {
                acteur3->x = 1000;
                acteur3->y = 1000;
            }
            if (lattaque==3)
            {
                acteur4->x = 1000;
                acteur4->y = 1000;
            }
                }
            }

        }


    }

    if (numeroClasse==4)
    {
        if((Joueures[i].pa-2)>=0)
        {
            if(de3!=5)
            {
                Joueures[i].pa=Joueures[i].pa-2;
                Joueures[lattaque].pv=Joueures[lattaque].pv-5;
                if(Joueures[lattaque].pv<=0)
                {
                    Joueures[lattaque].pv=0;
                    Joueures[i].compte=Joueures[i].compte+100;
                    Joueures[lattaque].compte=Joueures[lattaque].compte-100;

                nJoueures = nJoueures-1;
                if (lattaque==0)
            {
                acteur1->x = 1000;
                acteur1->y = 1000;
            }
            if (lattaque==1)
            {
                acteur2->y = 1000;
                acteur2->x = 1000;
            }
            if (lattaque==2)
            {
                acteur3->x = 1000;
                acteur3->y = 1000;
            }
            if (lattaque==3)
            {
                acteur4->x = 1000;
                acteur4->y = 1000;
            }
                }
            }

        }


    }

    }
    return nJoueures;
}

int Sort1(int numeroClasse,int i,int lattaque,int nJoueures)
{
    int de3=0;
    int j ,k;
    de3 = (rand() % 10) + 1;//
    if ((lattaque<nJoueures)&&(Joueures[lattaque].pv>0))
    {
    if (numeroClasse==1)
    {
        if((Joueures[i].pa-2)>=0)
        {
            if(de3!=5)
            {
                Joueures[i].pa=Joueures[i].pa-2;
                Joueures[lattaque].pv=Joueures[lattaque].pv-2;
                if(Joueures[lattaque].pv<=0)
                {
                    Joueures[lattaque].pv=0;
                    Joueures[i].compte=Joueures[i].compte+100;
                    Joueures[lattaque].compte=Joueures[lattaque].compte-100;
                    nJoueures = nJoueures-1;
                    if (lattaque==0)
            {
                acteur1->x = 1000;
                acteur1->y = 1000;
            }
            if (lattaque==1)
            {
                acteur2->y = 1000;
                acteur2->x = 1000;
            }
            if (lattaque==2)
            {
                acteur3->x = 1000;
                acteur3->y = 1000;
            }
            if (lattaque==3)
            {
                acteur4->x = 1000;
                acteur4->y = 1000;
            }
                }
            }

        }


    }

    if (numeroClasse==2)
    {
        if((Joueures[i].pa-2)>=0)
        {
            if(de3!=5)
            {
                Joueures[i].pa=Joueures[i].pa-2;
                Joueures[lattaque].pv=Joueures[lattaque].pv-2;
                if(Joueures[lattaque].pv<=0)
                {
                    Joueures[lattaque].pv=0;
                    Joueures[i].compte=Joueures[i].compte+100;
                    Joueures[lattaque].compte=Joueures[lattaque].compte-100;

                nJoueures = nJoueures-1;
                if (lattaque==0)
            {
                acteur1->x = 1000;
                acteur1->y = 1000;
            }
            if (lattaque==1)
            {
                acteur2->y = 1000;
                acteur2->x = 1000;
            }
            if (lattaque==2)
            {
                acteur3->x = 1000;
                acteur3->y = 1000;
            }
            if (lattaque==3)
            {
                acteur4->x = 1000;
                acteur4->y = 1000;
            }
                }
            }

        }


    }

    if (numeroClasse==3)
    {
        if((Joueures[i].pa-2)>=0)
        {
            if(de3!=5)
            {
                Joueures[i].pa=Joueures[i].pa-2;
                Joueures[lattaque].pv=Joueures[lattaque].pv-2;
                if(Joueures[lattaque].pv<=0)
                {
                    Joueures[lattaque].pv=0;
                    Joueures[i].compte=Joueures[i].compte+100;
                    Joueures[lattaque].compte=Joueures[lattaque].compte-100;

                nJoueures = nJoueures-1;
                if (lattaque==0)
            {
                acteur1->x = 1000;
                acteur1->y = 1000;
            }
            if (lattaque==1)
            {
                acteur2->y = 1000;
                acteur2->x = 1000;
            }
            if (lattaque==2)
            {
                acteur3->x = 1000;
                acteur3->y = 1000;
            }
            if (lattaque==3)
            {
                acteur4->x = 1000;
                acteur4->y = 1000;
            }
                }
            }

        }


    }

    if (numeroClasse==4)
    {
        if((Joueures[i].pa-2)>=0)
        {
            if(de3!=5)
            {
                Joueures[i].pa=Joueures[i].pa-2;
                Joueures[lattaque].pv=Joueures[lattaque].pv-2;
                if(Joueures[lattaque].pv<=0)
                {
                    Joueures[lattaque].pv=0;
                    Joueures[i].compte=Joueures[i].compte+100;
                    Joueures[lattaque].compte=Joueures[lattaque].compte-100;

                nJoueures = nJoueures-1;
                if (lattaque==0)
            {
                acteur1->x = 1000;
                acteur1->y = 1000;
            }
            if (lattaque==1)
            {
                acteur2->y = 1000;
                acteur2->x = 1000;
            }
            if (lattaque==2)
            {
                acteur3->x = 1000;
                acteur3->y = 1000;
            }
            if (lattaque==3)
            {
                acteur4->x = 1000;
                acteur4->y = 1000;
            }
                }
            }

        }


    }
    }
    return nJoueures;
}

int Sort2(int numeroClasse,int i,int lattaque,int nJoueures)
{
    int de3=0;
    int j;
    de3 = (rand() % 10) + 1;//
    if (lattaque<nJoueures)
    {
    if (numeroClasse==1)
    {
        if((Joueures[i].pa-5)>=0)
        {
            if(de3!=5)
            {
                Joueures[i].pa=Joueures[i].pa-5;
                Joueures[lattaque].pv=Joueures[lattaque].pv-10;
                if(Joueures[lattaque].pv<=0)
                {
                    Joueures[lattaque].pv=0;
                    Joueures[i].compte=Joueures[i].compte+100;
                    Joueures[lattaque].compte=Joueures[lattaque].compte-100;

                nJoueures = nJoueures-1;
                if (lattaque==0)
            {
                acteur1->x = 1000;
                acteur1->y = 1000;
            }
            if (lattaque==1)
            {
                acteur2->y = 1000;
                acteur2->x = 1000;
            }
            if (lattaque==2)
            {
                acteur3->x = 1000;
                acteur3->y = 1000;
            }
            if (lattaque==3)
            {
                acteur4->x = 1000;
                acteur4->y = 1000;
            }
                }
            }

        }


    }

    if (numeroClasse==2)
    {
        if((Joueures[i].pa-5)>=0)
        {
            if(de3!=5)
            {
                Joueures[i].pa=Joueures[i].pa-5;
                Joueures[lattaque].pv=Joueures[lattaque].pv-10;
                if(Joueures[lattaque].pv<=0)
                {
                    Joueures[lattaque].pv=0;
                    Joueures[i].compte=Joueures[i].compte+100;
                    Joueures[lattaque].compte=Joueures[lattaque].compte-100;

                nJoueures = nJoueures-1;
                if (lattaque==0)
            {
                acteur1->x = 1000;
                acteur1->y = 1000;
            }
            if (lattaque==1)
            {
                acteur2->y = 1000;
                acteur2->x = 1000;
            }
            if (lattaque==2)
            {
                acteur3->x = 1000;
                acteur3->y = 1000;
            }
            if (lattaque==3)
            {
                acteur4->x = 1000;
                acteur4->y = 1000;
            }
                }
            }

        }


    }

    if (numeroClasse==3)
    {
        if((Joueures[i].pa-5)>=0)
        {
            if(de3!=5)
            {
                Joueures[i].pa=Joueures[i].pa-5;
                Joueures[lattaque].pv=Joueures[lattaque].pv-10;
                if(Joueures[lattaque].pv<=0)
                {
                    Joueures[lattaque].pv=0;
                    Joueures[i].compte=Joueures[i].compte+100;
                    Joueures[lattaque].compte=Joueures[lattaque].compte-100;

                nJoueures = nJoueures-1;
                if (lattaque==0)
            {
                acteur1->x = 1000;
                acteur1->y = 1000;
            }
            if (lattaque==1)
            {
                acteur2->y = 1000;
                acteur2->x = 1000;
            }
            if (lattaque==2)
            {
                acteur3->x = 1000;
                acteur3->y = 1000;
            }
            if (lattaque==3)
            {
                acteur4->x = 1000;
                acteur4->y = 1000;
            }
                }
            }

        }


    }

    if (numeroClasse==4)
    {
        if((Joueures[i].pa-5)>=0)
        {
            if(de3!=5)
            {
                Joueures[i].pa=Joueures[i].pa-5;
                Joueures[lattaque].pv=Joueures[lattaque].pv-10;
                if(Joueures[lattaque].pv<=0)
                {
                    Joueures[lattaque].pv=0;
                    Joueures[i].compte=Joueures[i].compte+100;
                    Joueures[lattaque].compte=Joueures[lattaque].compte-100;

                nJoueures = nJoueures-1;
                if (lattaque==0)
            {
                acteur1->x = 1000;
                acteur1->y = 1000;
            }
            if (lattaque==1)
            {
                acteur2->y = 1000;
                acteur2->x = 1000;
            }
            if (lattaque==2)
            {
                acteur3->x = 1000;
                acteur3->y = 1000;
            }
            if (lattaque==3)
            {
                acteur4->x = 1000;
                acteur4->y = 1000;
            }
                }
            }

        }


    }
  }
return nJoueures;
}

int Sort3(int numeroClasse,int i,int lattaque,int nJoueures)
{
    int j;
    int de3=0;
    de3 = (rand() % 10) + 1;//
    if (lattaque<nJoueures)
    {
    if (numeroClasse==1)
    {
        if((Joueures[i].pa-8)>=0)
        {
            if(de3!=5)
            {
                Joueures[i].pa=Joueures[i].pa-8;
                Joueures[lattaque].pv=Joueures[lattaque].pv-25;
                if(Joueures[lattaque].pv<=0)
                {
                    Joueures[lattaque].pv=0;
                    Joueures[i].compte=Joueures[i].compte+100;
                    Joueures[lattaque].compte=Joueures[lattaque].compte-100;

                nJoueures = nJoueures-1;
                if (lattaque==0)
            {
                acteur1->x = 1000;
                acteur1->y = 1000;
            }
            if (lattaque==1)
            {
                acteur2->y = 1000;
                acteur2->x = 1000;
            }
            if (lattaque==2)
            {
                acteur3->x = 1000;
                acteur3->y = 1000;
            }
            if (lattaque==3)
            {
                acteur4->x = 1000;
                acteur4->y = 1000;
            }
                }
            }

        }


    }

    if (numeroClasse==2)
    {
        if((Joueures[i].pa-8)>=0)
        {
            if(de3!=5)
            {
                Joueures[i].pa=Joueures[i].pa-8;
                Joueures[lattaque].pv=Joueures[lattaque].pv-25;
                if(Joueures[lattaque].pv<=0)
                {
                    Joueures[lattaque].pv=0;
                    Joueures[i].compte=Joueures[i].compte+100;
                    Joueures[lattaque].compte=Joueures[lattaque].compte-100;

                nJoueures = nJoueures-1;
                if (lattaque==0)
            {
                acteur1->x = 1000;
                acteur1->y = 1000;
            }
            if (lattaque==1)
            {
                acteur2->y = 1000;
                acteur2->x = 1000;
            }
            if (lattaque==2)
            {
                acteur3->x = 1000;
                acteur3->y = 1000;
            }
            if (lattaque==3)
            {
                acteur4->x = 1000;
                acteur4->y = 1000;
            }
                }
            }

        }


    }

    if (numeroClasse==3)
    {
        if((Joueures[i].pa-8)>=0)
        {
            if(de3!=5)
            {
                Joueures[i].pa=Joueures[i].pa-8;
                Joueures[lattaque].pv=Joueures[lattaque].pv-25;
                if(Joueures[lattaque].pv<=0)
                {
                    Joueures[lattaque].pv=0;
                    Joueures[i].compte=Joueures[i].compte+100;
                    Joueures[lattaque].compte=Joueures[lattaque].compte-100;

                nJoueures = nJoueures-1;
                if (lattaque==0)
            {
                acteur1->x = 1000;
                acteur1->y = 1000;
            }
            if (lattaque==1)
            {
                acteur2->y = 1000;
                acteur2->x = 1000;
            }
            if (lattaque==2)
            {
                acteur3->x = 1000;
                acteur3->y = 1000;
            }
            if (lattaque==3)
            {
                acteur4->x = 1000;
                acteur4->y = 1000;
            }
                }
            }

        }


    }

    if (numeroClasse==4)
    {
        if((Joueures[i].pa-8)>=0)
        {
            if(de3!=5)
            {
                Joueures[i].pa=Joueures[i].pa-8;
                Joueures[lattaque].pv=Joueures[lattaque].pv-25;
                if(Joueures[lattaque].pv<=0)
                {
                    Joueures[lattaque].pv=0;
                    Joueures[i].compte=Joueures[i].compte+100;
                    Joueures[lattaque].compte=Joueures[lattaque].compte-100;

                nJoueures = nJoueures-1;
                if (lattaque==0)
            {
                acteur1->x = 1000;
                acteur1->y = 1000;
            }
            if (lattaque==1)
            {
                acteur2->y = 1000;
                acteur2->x = 1000;
            }
            if (lattaque==2)
            {
                acteur3->x = 1000;
                acteur3->y = 1000;
            }
            if (lattaque==3)
            {
                acteur4->x = 1000;
                acteur4->y = 1000;
            }
                }
            }

        }


    }
  }
  return nJoueures;
}

int Sort4(int numeroClasse,int i,int lattaque,int nJoueures)
{
    int de3=0;
    int j;
    de3 = (rand() % 10) + 1;//
    if (lattaque<nJoueures)
    {
    if (numeroClasse==1)
    {
        if((Joueures[i].pa-5)>=0)
        {
            if(de3!=5)
            {
                Joueures[i].pa=Joueures[i].pa-5;
                Joueures[lattaque].pv=Joueures[lattaque].pv+10;
                if(Joueures[lattaque].pv<=0)
                {
                    Joueures[lattaque].pv=0;
                    Joueures[i].compte=Joueures[i].compte+100;
                    Joueures[lattaque].compte=Joueures[lattaque].compte-100;

                nJoueures = nJoueures-1;
                if (lattaque==0)
            {
                acteur1->x = 1000;
                acteur1->y = 1000;
            }
            if (lattaque==1)
            {
                acteur2->y = 1000;
                acteur2->x = 1000;
            }
            if (lattaque==2)
            {
                acteur3->x = 1000;
                acteur3->y = 1000;
            }
            if (lattaque==3)
            {
                acteur4->x = 1000;
                acteur4->y = 1000;
            }
                }
            }

        }


    }

    if (numeroClasse==2)
    {
        if((Joueures[i].pa-8)>=0)
        {
            if(de3!=5)
            {
                Joueures[i].pa=Joueures[i].pa-8;
                Joueures[lattaque].pv=Joueures[lattaque].pv+10;
                if(Joueures[lattaque].pv<=0)
                {
                    Joueures[lattaque].pv=0;
                    Joueures[i].compte=Joueures[i].compte+100;
                    Joueures[lattaque].compte=Joueures[lattaque].compte-100;

                nJoueures = nJoueures-1;
                if (lattaque==0)
            {
                acteur1->x = 1000;
                acteur1->y = 1000;
            }
            if (lattaque==1)
            {
                acteur2->y = 1000;
                acteur2->x = 1000;
            }
            if (lattaque==2)
            {
                acteur3->x = 1000;
                acteur3->y = 1000;
            }
            if (lattaque==3)
            {
                acteur4->x = 1000;
                acteur4->y = 1000;
            }
                }
            }

        }


    }

    if (numeroClasse==3)
    {
        if((Joueures[i].pa-8)>=0)
        {
            if(de3!=5)
            {
                Joueures[i].pa=Joueures[i].pa-8;
                Joueures[lattaque].pv=Joueures[lattaque].pv+10;
                if(Joueures[lattaque].pv<=0)
                {
                    Joueures[lattaque].pv=0;
                    Joueures[i].compte=Joueures[i].compte+100;
                    Joueures[lattaque].compte=Joueures[lattaque].compte-100;

                nJoueures = nJoueures-1;
                if (lattaque==0)
            {
                acteur1->x = 1000;
                acteur1->y = 1000;
            }
            if (lattaque==1)
            {
                acteur2->y = 1000;
                acteur2->x = 1000;
            }
            if (lattaque==2)
            {
                acteur3->x = 1000;
                acteur3->y = 1000;
            }
            if (lattaque==3)
            {
                acteur4->x = 1000;
                acteur4->y = 1000;
            }
                }
            }

        }


    }

    if (numeroClasse==4)
    {
        if((Joueures[i].pa-8)>=0)
        {
            if(de3!=5)
            {
                Joueures[i].pa=Joueures[i].pa-8;
                Joueures[lattaque].pv=Joueures[lattaque].pv+10;
                if(Joueures[lattaque].pv<=0)
                {
                    Joueures[lattaque].pv=0;
                    Joueures[i].compte=Joueures[i].compte+100;
                    Joueures[lattaque].compte=Joueures[lattaque].compte-100;

                nJoueures = nJoueures-1;
                if (lattaque==0)
            {
                acteur1->x = 1000;
                acteur1->y = 1000;
            }
            if (lattaque==1)
            {
                acteur2->y = 1000;
                acteur2->x = 1000;
            }
            if (lattaque==2)
            {
                acteur3->x = 1000;
                acteur3->y = 1000;
            }
            if (lattaque==3)
            {
                acteur4->x = 1000;
                acteur4->y = 1000;
            }
                }
            }

        }


    }
  }
  return nJoueures;
}

int zonedetect(t_acteur *acteur1, t_acteur *acteur2, t_acteur *acteur3,t_acteur *acteur4,int j,int maxi,int mini,int ennemi )
{

     if (j==0)
        {
        //&&((acteur1->x)>=(acteur1->x+mini)) && ((acteur1->x)<=(acteur1->x-mini)) && ((acteur1->y)>=(acteur1->y+mini)) && ((acteur1->y)<=(acteur1->y-mini)))
        if(((acteur1->x)<=(acteur1->x+maxi)) && ((acteur1->x)>=(acteur1->x-maxi)) && ((acteur1->y)<=(acteur1->y+maxi)) && ((acteur1->y)>=(acteur1->y-maxi))&&(ennemi==0))//&&((acteur1->x)>=(acteur1->x+mini)) && ((acteur1->x)<=(acteur1->x-mini)) && ((acteur1->y)>=(acteur1->y+mini)) && ((acteur1->y)<=(acteur1->y-mini))) // creer un rectangle de detction autour du personnaage
        {
            return 1;
        }

        //&&((acteur2->x)>=(acteur1->x+mini)) && ((acteur2->x)<=(acteur1->x-mini)) && ((acteur2->y)>=(acteur1->y+mini)) && ((acteur2->y)<=(acteur1->y-mini)))
        if(((acteur2->x)<=(acteur1->x+maxi)) && ((acteur2->x)>=(acteur1->x-maxi)) && ((acteur2->y)<=(acteur1->y+maxi)) && ((acteur2->y)>=(acteur1->y-maxi))&&(ennemi==1))  // creer un rectangle de detction autour du personnaage
        {
            if (((acteur2->x)>=(acteur1->x+mini)) || ((acteur2->x)<=(acteur1->x-mini)) || ((acteur2->y)>=(acteur1->y+mini)) || ((acteur2->y)<=(acteur1->y-mini)))
            {
               return 1;
            }

        }

        //&&((acteur3->x)>=(acteur1->x+mini)) && ((acteur3->x)<=(acteur1->x-mini)) && ((acteur3->y)>=(acteur1->y+mini)) && ((acteur3->y)<=(acteur1->y-mini)))
        if(((acteur3->x)<=(acteur1->x+maxi)) && ((acteur3->x)>=(acteur1->x-maxi)) && ((acteur3->y)<=(acteur1->y+maxi)) && ((acteur3->y)>=(acteur1->y-maxi))&&(ennemi==2))//&&((acteur3->x)>=(acteur1->x+mini)) && ((acteur3->x)<=(acteur1->x-mini)) && ((acteur3->y)>=(acteur1->y+mini)) && ((acteur3->y)<=(acteur1->y-mini))) // creer un rectangle de detction autour du personnaage
        {
            return 1;
        }

        //&&((acteur4->x)>=(acteur1->x+mini)) && ((acteur4->x)<=(acteur1->x-mini)) && ((acteur4->y)>=(acteur1->y+mini)) && ((acteur4->y)<=(acteur1->y-mini)))
        if(((acteur4->x)<=(acteur1->x+maxi)) && ((acteur4->x)>=(acteur1->x-maxi)) && ((acteur4->y)<=(acteur1->y+maxi)) && ((acteur4->y)>=(acteur1->y-maxi))&&(ennemi==3))//&&((acteur4->x)>=(acteur1->x+mini)) && ((acteur4->x)<=(acteur1->x-mini)) && ((acteur4->y)>=(acteur1->y+mini)) && ((acteur4->y)<=(acteur1->y-mini))) // creer un rectangle de detction autour du personnaage
        {
            return 1;
        }
        else
        {
            return 0;
        }
        }

        if (j==1)
        {

        //&&((acteur1->x)>=(acteur2->x+mini)) && ((acteur1->x)<=(acteur2->x-mini)) && ((acteur1->y)>=(acteur2->y+mini)) && ((acteur1->y)<=(acteur2->y-mini)))
        if(((acteur1->x)<=(acteur2->x+maxi)) && ((acteur1->x)>=(acteur2->x-maxi)) && ((acteur1->y)<=(acteur2->y+maxi)) && ((acteur1->y)>=(acteur2->y-maxi))&&(ennemi==0))//&&((acteur1->x)>=(acteur2->x+mini)) && ((acteur1->x)<=(acteur2->x-mini)) && ((acteur1->y)>=(acteur2->y+mini)) && ((acteur1->y)<=(acteur2->y-mini))) // creer un rectangle de detction autour du personnaage
        {
            return 1;
        }

        //&&((acteur2->x)>=(acteur2->x+mini)) && ((acteur2->x)<=(acteur2->x-mini)) && ((acteur2->y)>=(acteur2->y+mini)) && ((acteur2->y)<=(acteur2->y-mini)))
        if(((acteur2->x)<=(acteur2->x+maxi)) && ((acteur2->x)>=(acteur2->x-maxi)) && ((acteur2->y)<=(acteur2->y+maxi)) && ((acteur2->y)>=(acteur2->y-maxi))&&(ennemi==1))//&&((acteur2->x)>=(acteur2->x+mini)) && ((acteur2->x)<=(acteur2->x-mini)) && ((acteur2->y)>=(acteur2->y+mini)) && ((acteur2->y)<=(acteur2->y-mini))) // creer un rectangle de detction autour du personnaage
        {
            return 1;
        }

        //&&((acteur3->x)>=(acteur2->x+mini)) && ((acteur3->x)<=(acteur2->x-mini)) && ((acteur3->y)>=(acteur2->y+mini)) && ((acteur3->y)<=(acteur2->y-mini)))
        if(((acteur3->x)<=(acteur2->x+maxi)) && ((acteur3->x)>=(acteur2->x-maxi)) && ((acteur3->y)<=(acteur2->y+maxi)) && ((acteur3->y)>=(acteur2->y-maxi))&&(ennemi==2))//&&((acteur3->x)>=(acteur2->x+mini)) && ((acteur3->x)<=(acteur2->x-mini)) && ((acteur3->y)>=(acteur2->y+mini)) && ((acteur3->y)<=(acteur2->y-mini))) // creer un rectangle de detction autour du personnaage
        {
            return 1;
        }

        //&&((acteur4->x)>=(acteur2->x+mini)) && ((acteur4->x)<=(acteur2->x-mini)) && ((acteur4->y)>=(acteur2->y+mini)) && ((acteur4->y)<=(acteur2->y-mini)))
        if(((acteur4->x)<=(acteur2->x+maxi)) && ((acteur4->x)>=(acteur2->x-maxi)) && ((acteur4->y)<=(acteur2->y+maxi)) && ((acteur4->y)>=(acteur2->y-maxi))&&(ennemi==3))//&&((acteur4->x)>=(acteur2->x+mini)) && ((acteur4->x)<=(acteur2->x-mini)) && ((acteur4->y)>=(acteur2->y+mini)) && ((acteur4->y)<=(acteur2->y-mini))) // creer un rectangle de detction autour du personnaage
        {
            return 1;
        }
        else
        {
            return 0;
        }
        }

        if (j==2)
        {
        //&&((acteur1->x)>=(acteur3->x+mini)) && ((acteur1->x)<=(acteur3->x-mini)) && ((acteur1->y)>=(acteur3->y+mini)) && ((acteur1->y)<=(acteur3->y-mini)))
        if(((acteur1->x)<=(acteur3->x+maxi)) && ((acteur1->x)>=(acteur3->x-maxi)) && ((acteur1->y)<=(acteur3->y+maxi)) && ((acteur1->y)>=(acteur3->y-maxi))&&(ennemi==0))//&&((acteur1->x)>=(acteur3->x+mini)) && ((acteur1->x)<=(acteur3->x-mini)) && ((acteur1->y)>=(acteur3->y+mini)) && ((acteur1->y)<=(acteur3->y-mini))) // creer un rectangle de detction autour du personnaage
        {
            return 1;
        }

        //&&((acteur2->x)>=(acteur3->x+mini)) && ((acteur2->x)<=(acteur3->x-mini)) && ((acteur2->y)>=(acteur3->y+mini)) && ((acteur2->y)<=(acteur3->y-mini)))
        if(((acteur2->x)<=(acteur3->x+maxi)) && ((acteur2->x)>=(acteur3->x-maxi)) && ((acteur2->y)<=(acteur3->y+maxi)) && ((acteur2->y)>=(acteur3->y-maxi)&&(ennemi==1)))//&&((acteur2->x)>=(acteur3->x+mini)) && ((acteur2->x)<=(acteur3->x-mini)) && ((acteur2->y)>=(acteur3->y+mini)) && ((acteur2->y)<=(acteur3->y-mini))) // creer un rectangle de detction autour du personnaage
        {
            return 1;
        }


        //&&((acteur3->x)>=(acteur3->x+mini)) && ((acteur3->x)<=(acteur3->x-mini)) && ((acteur3->y)>=(acteur3->y+mini)) && ((acteur3->y)<=(acteur3->y-mini)))
        if(((acteur3->x)<=(acteur3->x+maxi)) && ((acteur3->x)>=(acteur3->x-maxi)) && ((acteur3->y)<=(acteur3->y+maxi)) && ((acteur3->y)>=(acteur3->y-maxi))&&(ennemi==2))//&&((acteur3->x)>=(acteur3->x+mini)) && ((acteur3->x)<=(acteur3->x-mini)) && ((acteur3->y)>=(acteur3->y+mini)) && ((acteur3->y)<=(acteur3->y-mini))) // creer un rectangle de detction autour du personnaage
        {
            return 1;
        }

        //&&((acteur4->x)>=(acteur3->x+mini)) && ((acteur4->x)<=(acteur3->x-mini)) && ((acteur4->y)>=(acteur3->y+mini)) && ((acteur4->y)<=(acteur3->y-mini)))
        if(((acteur4->x)<=(acteur3->x+maxi)) && ((acteur4->x)>=(acteur3->x-maxi)) && ((acteur4->y)<=(acteur3->y+maxi)) && ((acteur4->y)>=(acteur3->y-maxi))&&(ennemi==3))//&&((acteur4->x)>=(acteur3->x+mini)) && ((acteur4->x)<=(acteur3->x-mini)) && ((acteur4->y)>=(acteur3->y+mini)) && ((acteur4->y)<=(acteur3->y-mini))) // creer un rectangle de detction autour du personnaage
        {
            return 1;
        }
        else
        {
            return 0;
        }
        }

        if (j==3)
        {

        //&&((acteur1->x)>=(acteur4->x+mini)) && ((acteur1->x)<=(acteur4->x-mini)) && ((acteur1->y)>=(acteur4->y+mini)) && ((acteur1->y)<=(acteur4->y-mini)))
        if(((acteur1->x)<=(acteur4->x+maxi)) && ((acteur1->x)>=(acteur4->x-maxi)) && ((acteur1->y)<=(acteur4->y+maxi)) && ((acteur1->y)>=(acteur4->y-maxi))&&(ennemi==0))//&&((acteur1->x)>=(acteur4->x+mini)) && ((acteur1->x)<=(acteur4->x-mini)) && ((acteur1->y)>=(acteur4->y+mini)) && ((acteur1->y)<=(acteur4->y-mini))) // creer un rectangle de detction autour du personnaage
        {
            return 1;
        }

        //&&((acteur2->x)>=(acteur4->x+mini)) && ((acteur2->x)<=(acteur4->x-mini)) && ((acteur2->y)>=(acteur4->y+mini)) && ((acteur2->y)<=(acteur4->y-mini)))
        if(((acteur2->x)<=(acteur4->x+maxi)) && ((acteur2->x)>=(acteur4->x-maxi)) && ((acteur2->y)<=(acteur4->y+maxi)) && ((acteur2->y)>=(acteur4->y-maxi))&&(ennemi==1))//&&((acteur2->x)>=(acteur4->x+mini)) && ((acteur2->x)<=(acteur4->x-mini)) && ((acteur2->y)>=(acteur4->y+mini)) && ((acteur2->y)<=(acteur4->y-mini))) // creer un rectangle de detction autour du personnaage
        {
            return 1;
        }

        //&&((acteur3->x)>=(acteur4->x+mini)) && ((acteur3->x)<=(acteur4->x-mini)) && ((acteur3->y)>=(acteur4->y+mini)) && ((acteur3->y)<=(acteur4->y-mini)))
        if(((acteur3->x)<=(acteur4->x+maxi)) && ((acteur3->x)>=(acteur4->x-maxi)) && ((acteur3->y)<=(acteur4->y+maxi)) && ((acteur3->y)>=(acteur4->y-maxi))&&(ennemi==2))//&&((acteur3->x)>=(acteur4->x+mini)) && ((acteur3->x)<=(acteur4->x-mini)) && ((acteur3->y)>=(acteur4->y+mini)) && ((acteur3->y)<=(acteur4->y-mini))) // creer un rectangle de detction autour du personnaage
        {
            return 1;
        }

        //&&((acteur4->x)>=(acteur4->x+mini)) && ((acteur4->x)<=(acteur4->x-mini)) && ((acteur4->y)>=(acteur4->y+mini)) && ((acteur4->y)<=(acteur4->y-mini)))
        if(((acteur4->x)<=(acteur4->x+maxi)) && ((acteur4->x)>=(acteur4->x-maxi)) && ((acteur4->y)<=(acteur4->y+maxi)) && ((acteur4->y)>=(acteur4->y-maxi))&&(ennemi==3))//&&((acteur4->x)>=(acteur4->x+mini)) && ((acteur4->x)<=(acteur4->x-mini)) && ((acteur4->y)>=(acteur4->y+mini)) && ((acteur4->y)<=(acteur4->y-mini))) // creer un rectangle de detction autour du personnaage
        {
            return 1;
        }
        else
        {
            return 0;
        }


        }

        else
        {
            return 0;
        }

}

bool estUneTuileAvecObstacle(t_coords position, int terrain[NYMAP][NXMAP], int typeTuiles[NTUILE])
{
    bool estUnObstacle = false;
    if (typeTuiles[terrain[position.ligne][position.colonne]] == OBSTACLE)
    {
        estUnObstacle = true;
    }
    return estUnObstacle;
}

bool sontDesPositionsIdentiques(t_coords position1, t_coords position2)
{
    bool estMemePosition = false;
    if ( (position1.ligne == position2.ligne) && (position1.colonne == position2.colonne) ){
        estMemePosition = true;
    }
    return estMemePosition;
}

//avance d'une case horizontalement si c'est possible
//renvoie la position après déplacement. Si cette position est la même que la position initiale, c'est qu'il y a eu un obstacle
t_coords avancerHorizontalement(int terrain[NYMAP][NXMAP], int typeTuiles[NTUILE], t_coords positionDepart, t_coords positionCible)
{
    int deplacementHorizontal = positionCible.colonne - positionDepart.colonne;
    if (deplacementHorizontal == 0)
    {
        return positionDepart;
    }

    int direction = deplacementHorizontal/abs(deplacementHorizontal);
    t_coords positionFinale;

    positionFinale.ligne = positionDepart.ligne;
    positionFinale.colonne = positionDepart.colonne + direction;

    //si la position suivante n'est pas un obstacle, elle devient la position finale : le déplacement est possible
    if (estUneTuileAvecObstacle(positionFinale, terrain, typeTuiles))
    {
        //printf("\nimpossible d'avancer sur la case (%d, %d)",  positionFinale.ligne, positionFinale.colonne);
        positionFinale.ligne = positionDepart.ligne;
        positionFinale.colonne = positionDepart.colonne;
    }

//    printf("\nla position apres avancement horizontal est (%d, %d)",  positionFinale.ligne, positionFinale.colonne);
    return positionFinale;
}

//avance d'une case verticalement si c'est possible
//renvoie la position après déplacement. Si cette position est la même que la position initiale, c'est qu'il y a eu un obstacle
t_coords avancerVerticalement(int terrain[NYMAP][NXMAP], int typeTuiles[NTUILE], t_coords positionDepart, t_coords positionCible)
{
    int deplacementVertical = positionCible.ligne - positionDepart.ligne;
    if (deplacementVertical == 0)
    {
        return positionDepart;
    }
    t_coords positionFinale;

    int direction = deplacementVertical/abs(deplacementVertical);
    positionFinale.ligne = positionDepart.ligne + direction;
    positionFinale.colonne = positionDepart.colonne ;

    //si la position suivante n'est pas un obstacle, elle devient la position finale : le déplacement est possible
    if (estUneTuileAvecObstacle(positionFinale, terrain, typeTuiles))
    {
        //printf("\nimpossible d'avancer sur la case (%d, %d)",  positionFinale.ligne, positionFinale.colonne);
        positionFinale.ligne = positionDepart.ligne;
        positionFinale.colonne = positionDepart.colonne;

    }
    //printf("\nla position apres avancement vertical est (%d, %d)",  positionFinale.ligne, positionFinale.colonne);
    return positionFinale;
}

void ajouterPositionDansChemin(t_coords tab_chemin[10], t_coords position, int indiceTabChemin )
{
    tab_chemin[indiceTabChemin].ligne = position.ligne;
    tab_chemin[indiceTabChemin].colonne = position.colonne;
}

t_coords calculerNouvellePosition(t_coords tab_chemin[10],  int terrain[NYMAP][NXMAP], int typeTuiles[NTUILE], t_coords positionDepart, t_coords positionFinale)
{
    t_coords nouvellePosition = avancerHorizontalement(terrain, typeTuiles, positionDepart, positionFinale);
    if (sontDesPositionsIdentiques(nouvellePosition, positionDepart))
    {
        //printf("\npas possible d'avancer horizontalement depuis la case (%d, %d)", nouvellePosition.ligne, nouvellePosition.colonne);
        return avancerVerticalement(terrain, typeTuiles, positionDepart, positionFinale);
    }
    else {
        return nouvellePosition;
    }
}


int calculerNewChemin(t_coords tab_chemin[10], int terrain[NYMAP][NXMAP], int typeTuiles[NTUILE], t_coords positionInitiale, t_coords positionFinale, int pm)
{
    int nbreTuilesSurChemin = 0;


    int deplacementHorizontal = positionFinale.colonne - positionInitiale.colonne; //nbre de déplacements (d'une case) horizontaux

    int deplacementVertical = positionFinale.ligne - positionInitiale.ligne; //nbre de déplacements (d'une case) verticaux

    int nbreTuilesDeplacementSansObstacle = abs(deplacementHorizontal) + abs(deplacementVertical);
    //si la position finale est égale à la position initiale, pas de déplacement
    if (deplacementHorizontal == 0 && deplacementVertical == 0)
    {
        return 0;
    }

    if (nbreTuilesDeplacementSansObstacle > pm)
    {
        //printf("\ndeplacement de %d tuiles impossible, vous depassez la pm %d", nbreTuilesDeplacementSansObstacle, pm);
        return -1;
    }

    int indiceTabChemin = 0;
    int compteur = 0;
    t_coords positionDepart;
    t_coords nouvellePosition;
    positionDepart.ligne = positionInitiale.ligne;
    positionDepart.colonne = positionInitiale.colonne;

    nouvellePosition.ligne = positionInitiale.ligne;
    nouvellePosition.colonne = positionInitiale.colonne;

    while(compteur < pm && !sontDesPositionsIdentiques(nouvellePosition, positionFinale))
    {
        nouvellePosition = calculerNouvellePosition(tab_chemin, terrain, typeTuiles, positionDepart, positionFinale);
        if (sontDesPositionsIdentiques(nouvellePosition, positionDepart)) //on ne peut plus avancer
        {
            break;
        }
        ajouterPositionDansChemin(tab_chemin, nouvellePosition, indiceTabChemin);
        positionDepart.ligne = nouvellePosition.ligne;
        positionDepart.colonne = nouvellePosition.colonne;
        indiceTabChemin ++;
        nbreTuilesSurChemin ++;
        compteur ++;
    }

    if (sontDesPositionsIdentiques(nouvellePosition, positionFinale))
    {
        return nbreTuilesSurChemin;
    }
    else
    {
        return -1;
    }
}

void peindreTuile(BITMAP* bmp, t_coords tuile, int couleur)
{
    rectfill(bmp,tuile.colonne*TXTUILE, tuile.ligne*TYTUILE, tuile.colonne*TXTUILE+TXTUILE-1, tuile.ligne*TYTUILE +TYTUILE-1, couleur );
}
