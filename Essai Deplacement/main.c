#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <allegro.h>
#include <winalleg.h>

#define NTUILE     213   // Nombre de tuiles graphiques utilisées
#define TXTUILE    16    // Largeur des tuiles
#define TYTUILE    16    // Hauteur des tuiles
#define NCOLTUILE  20    // Nombre de colonnes de tuiles dans le fichier image

#define NXMAP      50      // Nombre de tuiles en largeur sur le terrain
#define NYMAP      35      // Nombre de tuiles en hauteur sur le terrain

#define PM_MAX 3
#define OBSTACLE 1      // un obstacle est représenté par le type 1 dans la matrice terrain


// ( on s'autorise une globale, pour simplifier )
BITMAP *tableTuiles;

// Pour gérer les collisions on indique les types de tuiles : 1 obstacle  2 : eau
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


/****************************/
/*     STRUCTURE ACTEUR     */
/****************************/

// données personnelles de chaque acteur qui se déplace
typedef struct acteur
{
    int x, y;          // coordonnées (en pixels) des pieds de l'acteur
    BITMAP *img;       // image de l'acteur
} t_acteur;

typedef struct coordonneesTuiles
{
    int ligne;
    int colonne;
}t_coords;

typedef struct Tuile{
int type;  //le type peut avoir 3 valeurs : 0 = normal, 1 = obstacle, 2 = eau
//int couleur;
//int occupeParJoueur;
//bool estAtteignable;
// bool estLibre = (occupeParJoueur >= 0) && (type != obst);

}t_tuile;

/******************************************/
/*         SOUS-PROGRAMMES                */
/******************************************/

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

void peindreTuile(BITMAP* bmp, t_coords tuile, int couleur)
{
    rectfill(bmp,tuile.colonne*TXTUILE, tuile.ligne*TYTUILE, tuile.colonne*TXTUILE+TXTUILE-1, tuile.ligne*TYTUILE +TYTUILE-1, couleur );
}

int main()
{
    t_acteur *acteur;    // Un acteur (à créer)
    BITMAP *page;// BITMAP buffer d'affichage
    t_coords tabChemin[10];

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

    //CREATION DU BUFFER D'AFFICHAGE à la taille de l'écran
    page = create_bitmap(SCREEN_W,SCREEN_H);
    clear_bitmap(page);

    // pour voir le pointeur de la souris
    show_mouse(screen);

    // Charger le fichier avec les tuiles
    tableTuiles=load_bitmap_check("tableTuiles.bmp");

    // Allocation et initialisation des paramètres de l'acteur :
    acteur = (t_acteur *)malloc(1*sizeof(t_acteur));
    // Pour la position : multiples de l'unité de déplacement...
    acteur->x = 512;     acteur->y = 368;
    acteur->img = load_bitmap_check("sprite.bmp");


    /*
    clock_t tempsInitial;
    clock_t tempsActuel;
    clock_t deltaTemps;
    double dureeTourDeJeu = 0;

    tempsInitial = clock();
    //dans boucle
    tempsActuel = clock();
        deltaTemps = tempsActuel - tempsInitial;
        dureeTourDeJeu = (deltaTemps/CLOCKS_PER_SEC);
    */

    t_coords tuileSouris;
    t_coords tuileJoueur;

    while (!key[KEY_ESC])  // && dureeTourDeJeu < 15 | reste dans la boucle pendant 3 secondes
    {


        // Dessiner le terrain
        dessineTerrain(page, terrain);

        tuileSouris.ligne = mouse_y / TYTUILE;
        tuileSouris.colonne = mouse_x / TXTUILE;

        tuileJoueur.ligne = acteur->y / TYTUILE;
        tuileJoueur.colonne = acteur->x / TXTUILE;

        //tableau 2 valeurs : lorsque posActuelle - posStockee > Tuile
                            //alors on declenche le calcul et on actualise la posStockee

        //réinitialisation du tableau pour éviter problèmes
        for(int i=0; i<PM_MAX; i++){
            tabChemin[i].colonne = 0;
            tabChemin[i].ligne = 0;
        }

        int isNewCheminDisponible = calculerNewChemin(tabChemin, terrain ,typeTuiles, tuileJoueur, tuileSouris, PM_MAX);    //renvoie le nombre de déplacements (nombre de tuile à parcourir)
                                    //calculerNewChemin(tabChemin, terrain ,typeTuiles, tuileJoueur, tuileSouris, acteur->pm);
        if(isNewCheminDisponible != -1){
            //si le déplacement est possible, on colorie toutes les tuiles utilisées pour le déplacement
            for(int i=0; i < isNewCheminDisponible; i++){
                peindreTuile(page, tabChemin[i], makecol(0,0,255));
                peindreTuile(page, tuileJoueur, makecol(0,255,0));
            }

            if(mouse_b & 1){    //si on clique sur la souris
                for(int i = 0; i < isNewCheminDisponible; i++){
                    acteur->x = tabChemin[i].colonne*TXTUILE;
                    acteur->y = tabChemin[i].ligne*TYTUILE;

                    if(i<PM_MAX - 1){
                            /*Pour animer correctement : Une fonction qui renvoie la direction du mouvement (dans quel sens et horizontal ou vertical)   */

                        dessineTerrain(page, terrain);
                        draw_sprite(page, acteur->img, acteur->x -acteur->img->w/4 , acteur->y - acteur->img->h + 12);
                        blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);    //on affiche à l'écran
                        rest(75);   //delai poour qu'on puisse voir l'animation

                    }
                }
                //enlever isNewCheminDisponible à la PM du joueur
            }

        }
        else{
                peindreTuile(page, tuileJoueur, makecol(255,0,0));  //si le déplacement n'est pas possible, on peint la tuile sous les pieds du joueurs en Rouge
        }


        // Bord console utilisateur - on trace plusieurs réctangle vert pour avoir un cadre plus épais
        rect(page,0,560,800,650,makecol(0,255,0 )); //ext1 vert
        rect(page,1,561,799,649,makecol(0,255,0 )); //ext2 vert
        rect(page,2,562,798,648,makecol(0,255,0 )); //ext3 vert
        rect(page,3,563,797,647,makecol(0,255,0 )); //ext4 vert
        rectfill(page, 4, 564, 796, 646, makecol(0,0,0));   //intérieur noir

        // Info curseur
        textprintf_ex(page,font,690,635,makecol(0,255,0),makecol(0,0,0),"x=%4d y=%4d",mouse_x,mouse_y);
        textprintf_ex(page, font, 600, 620, makecol(0,255,0), makecol(0,0,0), "tuileX = %d tuileY= %d", mouse_x/TXTUILE, mouse_y/TYTUILE);

        // Afficher personnage (positionner par rapport à ses jambes)
        draw_sprite(page, acteur->img, acteur->x -acteur->img->w/4 , acteur->y - acteur->img->h + 12);   //permet de dessiner le personnage parfaitement centré dans les cases //draw_sprite(page, acteur->img, acteur->x - acteur->img->w/2, acteur->y - acteur->img->h + 8);

        // Affichage du buffer mis a jour a l'ecran
        blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);

        // On fait une petite pause
        rest(15);

    }

    allegro_exit();

    return 0;
}
END_OF_MAIN();

