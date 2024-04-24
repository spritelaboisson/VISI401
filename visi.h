#define PI 3.14159265358979323846
#define K_REPULSION 0.10

#define DIST_MIN_REPULSION 1.0
#define DIST_MAX_REPULSION 1.7


#define MAX_POINTS 100000
#define AMPLITUDE 0.6


#define MAX_POINTS_PROCHES 1000


#define EPSILON 0.1 // Constante epsilon
#define SIGMA 1.0 // Constante sigma
#define ALPHA 0.5 // Constante alpha pour l'attirance
#define BETA 0.3 // Constante beta pour la répulsion

typedef struct {
    double x;
    double y;
} Point;


typedef struct {
    Point *points_proches;
    int nb_points_proches;
} ListePointsProches;


void genere_labyrinthe(Point tab_points[], int *nb_points, int nb_deplacements, char *nomfichier);
void init_cercle(Point tab[], int *N, double rayon);
void deplacement_aleatoire(Point points[], int *N, double amplitude);
double distance_entre_points(Point p1, Point p2);
void affiner_points(Point points[], int *nb_points, double distance_min, double distance_max);
ListePointsProches points_proches(Point point_donne, Point *tous_les_points, int *nb_points, double distance_max);
double lennard_jones(double r);
void application_forces(Point points[], int *nb_points, double distance_max);
void apply_lennard_jones(Point *p, ListePointsProches *liste);
void save_to_csv(Point tab[], int *N, char *filename);