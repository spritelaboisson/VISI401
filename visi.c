#include "visi.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        
        
        
        printf("Usage: %s <nom_fichier>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *nomfichier = argv[argc - 1];
    Point points[MAX_POINTS];
    int N = 100;

    genere_labyrinthe(points, &N, 50, nomfichier);

    return EXIT_SUCCESS;
}

void genere_labyrinthe(Point tab_points[], int *nb_points, int nb_deplacements, char *nomfichier) {
    init_cercle(tab_points, nb_points, 5);
    for (int i = 0; i < nb_deplacements; i++) {
        deplacement_aleatoire(tab_points, nb_points, AMPLITUDE);
        affiner_points(tab_points,nb_points,1.2,1.9);
        printf("%d %d\n",i, *nb_points);
        application_forces(tab_points, nb_points,3);
    }
    printf("Nb points total : %d\n", *nb_points);
    save_to_csv(tab_points, nb_points, nomfichier);
}

void init_cercle(Point tab[], int *N, double rayon) {
    for (int i = 0; i < (*N) ; i++) {
        double angle = 2 * PI * i / *N;
        tab[i].x = rayon * cos(angle);
        tab[i].y = rayon * sin(angle);
    }
}

void deplacement_aleatoire(Point points[], int *N, double amplitude) {
    for (int i = 0; i < (*N) -1; i++) {
        double angle = ((double)rand() / RAND_MAX) * 2 * PI;
        double dir_x = cos(angle);
        double dir_y = sin(angle);
        double random_norm = amplitude;
        points[i].x += dir_x * random_norm;
        points[i].y += dir_y * random_norm;
    }
}
double distance_entre_points(Point p1, Point p2) {
    if (p1.x == p2.x && p1.y == p2.y) {
        return 0.0; // Si les points sont les mêmes, retourner 0 pour éviter une division par zéro
    } else {
        return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
    }
}

void affiner_points(Point points[], int *nb_points, double distance_min, double distance_max){
    for(int i = 0;i < (*nb_points) - 1;i++) {
            double dst = distance_entre_points(points[i], points[i + 1]);

            if (dst < distance_min) {
                // Supprimer le point suivant
                for (int j = i + 1; j < (*nb_points)-1; j++) {
                    points[j] = points[j+1];
                }
                (*nb_points)--;
            } else if (dst > distance_max && (*nb_points) < MAX_POINTS -1) {
                // Insérer un nouveau point à mi-chemin
                Point newpoint;
                newpoint.x = (points[i].x + points[i + 1].x) / 2;
                newpoint.y = (points[i].y + points[i + 1].y) / 2;

                // Décaler les points suivants pour faire de la place
                for (int j = (*nb_points) - 1; j > i; j--) {
                    points[j + 1] = points[j];
                }

                points[i + 1] = newpoint;
                (*nb_points)++;
            }
        
    }
    
}

ListePointsProches points_proches(Point point_donne, Point *tous_les_points, int *nb_points, double distance_max) {
    ListePointsProches liste;
    liste.points_proches = malloc(sizeof(Point) * (*nb_points));
    if (liste.points_proches == NULL) {
        printf("Erreur d'allocation de mémoire\n");
        exit(EXIT_FAILURE);
    }
    liste.nb_points_proches = 0;

    for (int i = 0; i < *nb_points; i++) {
        if (&tous_les_points[i] != &point_donne) {
            double dst = distance_entre_points(point_donne, tous_les_points[i]);
            if(dst !=0 && dst < distance_max){
                if (liste.nb_points_proches >= MAX_POINTS_PROCHES) {
                    printf("Trop de points proches\n");
                    exit(EXIT_FAILURE);
                }
                liste.points_proches[liste.nb_points_proches++] = tous_les_points[i];
            }
        }
    } 
    return liste;
}

void application_forces(Point points[], int *nb_points, double distance_max) {
    for (int i = 0; i < (*nb_points) - 1; i++) {
        ListePointsProches liste = points_proches(points[i], points, nb_points, distance_max);
        apply_lennard_jones(&points[i], &liste);
        free(liste.points_proches); // Libérer la mémoire allouée pour la liste de points proches
    }
}

void apply_lennard_jones(Point *p, ListePointsProches *liste) {
    for (int i = 0; i < liste->nb_points_proches; i++) {
        double force_x = 0.0;
        double force_y = 0.0;

    
        double d = distance_entre_points(*p, liste->points_proches[i]);

        // Calcul de la composante de force dans chaque direction
        if (d != 0) {
            double lj_force = lennard_jones(d);


            force_x += ALPHA * lj_force * (liste->points_proches[i].x - p->x) / d;
            force_y += ALPHA * lj_force * (liste->points_proches[i].y - p->y) / d;
        }
         // Appliquer la force résultante au point
        p->x += BETA * force_x;
        p->y += BETA * force_y;
    }

   
}
double lennard_jones(double r) {
    //24 *EPSILON * (pow(SIGMA / r, 12) - pow(SIGMA / r, 6))
    return 0.10/(r * r) ;
}

void save_to_csv(Point tab[], int *N, char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "X,Y\n");
    for (int i = 0; i < *N; i++) {
        fprintf(file, "%f,%f\n", tab[i].x, tab[i].y);
    }
    fclose(file);
}