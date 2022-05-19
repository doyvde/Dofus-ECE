#ifndef MABIBLIO_H_INCLUDED
#define MABIBLIO_H_INCLUDED


// Pour plus de simplicit� : constantes des tuiles utilis�es en globale
// ( pour g�rer plusieurs ensembles de tuiles il faudrait
//   mettre ces informations dans une structure ... )

#define NTUILE     213   // Nombre de tuiles graphiques utilis�es
#define TXTUILE    16    // Largeur des tuiles
#define TYTUILE    16    // Hauteur des tuiles
#define NCOLTUILE  20    // Nombre de colonnes de tuiles dans le fichier image

#define NXMAP      50      // Nombre de tuiles en largeur sur le terrain
#define NYMAP      35      // Nombre de tuiles en hauteur sur le terrain

int typeTuiles[NTUILE];
int terrain[NYMAP][NXMAP];


// Sur cet exemple on a un seul ensemble de tuiles
// ( on s'autorise une globale, l� encore pour simplifier )
BITMAP *tableTuiles;

/****************************/
/*     STRUCTURE ACTEUR     */
/****************************/

// donn�es personnelles de chaque acteur qui se d�place
typedef struct acteur
{
    int x, y;          // coordonn�es (en pixels) des pieds de l'acteur
    BITMAP *img;       // image de l'acteur
} t_acteur;

typedef struct enregistrementDesJoueurs
{
	char Nom[10];//
	int compte;//
	int classe;//
	int pv;
	int pm;
	int pa;

} Joueur;//

Joueur Joueures[4];//

void initialiseJoueurs(int nJoueures);
void dessineTuile(BITMAP *bmp, int ituile, int xmap, int ymap);
void dessineTerrain(BITMAP *bmp, int terrain[NYMAP][NXMAP]);
int typeTerrain(t_acteur *acteur, int dx, int dy, int type);
BITMAP * load_bitmap_check(char *nomImage);
void Arme(int numeroClasse,int i,int lattaque);
void Sort1(int numeroClasse,int i,int lattaque);
void Sort2(int numeroClasse,int i,int lattaque);
void Sort3(int numeroClasse,int i,int lattaque);
void Sort4(int numeroClasse,int i,int lattaque);

#endif // MABIBLIO_H_INCLUDED
