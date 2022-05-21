#ifndef MABIBLIO_H_INCLUDED
#define MABIBLIO_H_INCLUDED


// Pour plus de simplicité : constantes des tuiles utilisées en globale
// ( pour gérer plusieurs ensembles de tuiles il faudrait
//   mettre ces informations dans une structure ... )

#define NTUILE     213   // Nombre de tuiles graphiques utilisées
#define TXTUILE    16    // Largeur des tuiles
#define TYTUILE    16    // Hauteur des tuiles
#define NCOLTUILE  20    // Nombre de colonnes de tuiles dans le fichier image

#define NXMAP      50      // Nombre de tuiles en largeur sur le terrain
#define NYMAP      35      // Nombre de tuiles en hauteur sur le terrain

#define PM_MAX 3
#define OBSTACLE 1      // un obstacle est représenté par le type 1 dans la matrice terrain


int typeTuiles[NTUILE];
int terrain[NYMAP][NXMAP];


// Sur cet exemple on a un seul ensemble de tuiles
// ( on s'autorise une globale, là encore pour simplifier )
BITMAP *tableTuiles;

/****************************/
/*     STRUCTURE ACTEUR     */
/****************************/

// données personnelles de chaque acteur qui se déplace
typedef struct acteur
{
    int x, y;          // coordonnées (en pixels) des pieds de l'acteur
    BITMAP *img;       // image de l'acteur
} t_acteur;

typedef struct enregistrementDesJoueurs
{
	int num;//
	int compte;//
	int classe;//
	int pv;
	int pm;
	int pa;

} Joueur;//

typedef struct Tuile{
int type;  //le type peut avoir 3 valeurs : 0 = normal, 1 = obstacle, 2 = eau
//int couleur;
//int occupeParJoueur;
//bool estAtteignable;
// bool estLibre = (occupeParJoueur >= 0) && (type != obst);

}t_tuile;

typedef struct coordonneesTuiles
{
    int ligne;
    int colonne;
}t_coords;


Joueur Joueures[4];//
t_acteur *acteur1;    // Un acteur (à créer)
t_acteur *acteur2;    // Un acteur (à créer)
t_acteur *acteur3;    // Un acteur (à créer)
t_acteur *acteur4;    // Un acteur (à créer)*/

void initialiseJoueurs(int nJoueures);
void dessineTuile(BITMAP *bmp, int ituile, int xmap, int ymap);
void dessineTerrain(BITMAP *bmp, int terrain[NYMAP][NXMAP]);
int typeTerrain(t_acteur *acteur, int dx, int dy, int type);
BITMAP * load_bitmap_check(char *nomImage);
int Arme(int numeroClasse,int i,int lattaque,int nJoueures);
int Sort1(int numeroClasse,int i,int lattaque,int nJoueures);
int Sort2(int numeroClasse,int i,int lattaque,int nJoueures);
int Sort3(int numeroClasse,int i,int lattaque,int nJoueures);
int Sort4(int numeroClasse,int i,int lattaque,int nJoueures);
int zonedetect(t_acteur *acteur1, t_acteur *acteur2, t_acteur *acteur3,t_acteur *acteur4,int j,int maxi,int mini,int ennemi);
void peindreTuile(BITMAP* bmp, t_coords tuile, int couleur);
int calculerNewChemin(t_coords tab_chemin[10], int terrain[NYMAP][NXMAP], int typeTuiles[NTUILE], t_coords positionInitiale, t_coords positionFinale, int pm);
t_coords calculerNouvellePosition(t_coords tab_chemin[10],  int terrain[NYMAP][NXMAP], int typeTuiles[NTUILE], t_coords positionDepart, t_coords positionFinale);
void ajouterPositionDansChemin(t_coords tab_chemin[10], t_coords position, int indiceTabChemin );
t_coords avancerVerticalement(int terrain[NYMAP][NXMAP], int typeTuiles[NTUILE], t_coords positionDepart, t_coords positionCible);
t_coords avancerHorizontalement(int terrain[NYMAP][NXMAP], int typeTuiles[NTUILE], t_coords positionDepart, t_coords positionCible);
bool sontDesPositionsIdentiques(t_coords position1, t_coords position2);
bool estUneTuileAvecObstacle(t_coords position, int terrain[NYMAP][NXMAP], int typeTuiles[NTUILE]);
#endif // MABIBLIO_H_INCLUDED
