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


// Pour plus de simplicité : constantes des tuiles utilisées en globale
// ( pour gérer plusieurs ensembles de tuiles il faudrait
//   mettre ces informations dans une structure ... )

#define NTUILE     213   // Nombre de tuiles graphiques utilisées
#define TXTUILE    16    // Largeur des tuiles
#define TYTUILE    16    // Hauteur des tuiles
#define NCOLTUILE  20    // Nombre de colonnes de tuiles dans le fichier image

#define NXMAP      50      // Nombre de tuiles en largeur sur le terrain
#define NYMAP      35      // Nombre de tuiles en hauteur sur le terrain

// Sur cet exemple on a un seul ensemble de tuiles
// ( on s'autorise une globale, là encore pour simplifier )
BITMAP *tableTuiles;

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



/****************************/
/*     STRUCTURE ACTEUR     */
/****************************/

// données personnelles de chaque acteur qui se déplace
typedef struct acteur
{
    int x, y;          // coordonnées (en pixels) des pieds de l'acteur
    BITMAP *img;       // image de l'acteur
} t_acteur;


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


/******************************************/
/* PROGRAMME PRINCIPAL                    */
/* initialisation puis boucle de jeu      */
/******************************************/

int main()
{
    t_acteur *acteur;    // Un acteur (à créer)
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
    acteur = (t_acteur *)malloc(1*sizeof(t_acteur));
    // Pour la position : multiples de l'unité de déplacement...
    acteur->x = 32;     acteur->y = 200;
    acteur->img = load_bitmap_check("sprite.bmp");

    textprintf_ex(page,font,4,6,makecol(255,0,0),makecol(0,255,0),"EXIT");



    // Boucle de jeu (rien pour l'instant)
    while (!key[KEY_ESC])
    {
        // dessiner le terrain
        dessineTerrain(page, terrain);

        //( mouse_b&1 && mouse_x<=40 && mouse_y<=20)

        // gérer déplacements en prenant en compte les obstacles
        if (    key[KEY_RIGHT] && !typeTerrain(acteur,4,0,1) )
            acteur->x+=4;

        if (    key[KEY_LEFT] && !typeTerrain(acteur,-4,0,1) )
           acteur->x-=4;

        if (    key[KEY_DOWN] && !typeTerrain(acteur,0,4,1) )
           acteur->y+=4;

        if (    key[KEY_UP] && !typeTerrain(acteur,0,-4,1) )
           acteur->y-=4;

        // détecter interactions avec des éléments spéciaux
        if ( typeTerrain(acteur,0,0,2) ) // dans l'eau ?
            textprintf_centre_ex(page,font,400,560,makecol(255,255,255),0," NAGE ");
        else
            textprintf_centre_ex(page,font,400,560,makecol(255,255,255),0,"MARCHE");

        textprintf_ex(page,font,0,580,makecol(255,0,0),makecol(0,255,0),"Joueur 1:");
        textprintf_ex(page,font,0,600,makecol(255,0,0),makecol(0,255,0),"PV:|||||||||||||||||||||||||||||");
        textprintf_ex(page,font,0,620,makecol(255,0,0),makecol(0,255,0),"PM:|||");
        textprintf_centre_ex(page,font,400,580,makecol(255,255,255),0,"Z");
        textprintf_centre_ex(page,font,400,600,makecol(255,255,255),0,"S");
        textprintf_centre_ex(page,font,390,590,makecol(255,255,255),0,"Q");
        textprintf_centre_ex(page,font,410,590,makecol(255,255,255),0,"D");
        textprintf_centre_ex(page,font,350,630,makecol(255,255,255),0,"Arme");
        textprintf_centre_ex(page,font,450,630,makecol(255,255,255),0,"Sort");
        textprintf_right_ex(page,font,600,580,makecol(255,0,0),makecol(0,255,0),"Ennemi :");
        textprintf_right_ex(page,font,792,600,makecol(255,0,0),makecol(0,255,0),"PV:|||||||||||||||||||||||||||||");

        // afficher personnage (positionner par rapport à ses jambes)
        draw_sprite(page, acteur->img, acteur->x - acteur->img->w/2, acteur->y - acteur->img->h + 8);

        // affichage du buffer mis a jour a l'ecran
        blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);

        // on fait une petite pause
        rest(15);

    }

    return 0;
}
END_OF_MAIN();
