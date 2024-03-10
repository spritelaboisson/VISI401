import math
import csv
import random

def init_cercle(tab, N, rayon):
    """
    Initialise un tableau avec N points pour dessiner un cercle.
    """
    for i in range(N):
        angle = 2 * math.pi * i / N
        x = rayon * math.cos(angle)
        y = rayon * math.sin(angle)
        tab.append((round(x,3), round(y,3)))
        
        
def init_carre(tab, N, cote):
    """
    Initialise un tableau avec N points pour dessiner un carré.
    """
    # Nombre de points sur chaque côté du carré
    points_par_cote = N // 4
    
    # Ajouter les points sur chaque côté de manière consécutive
    for a in range(points_par_cote):
        # Côté du bas
        tab.append((cote * a / (points_par_cote - 1), 0))
    for b in range(1, points_par_cote):
        # Côté de droite
        tab.append((cote, cote * b / (points_par_cote - 1)))
    for c in range(1, points_par_cote):
        # Côté du haut
        tab.append((cote - cote * c / (points_par_cote - 1), cote))
    for d in range(1, points_par_cote - 1):
        # Côté de gauche
        tab.append((0, cote - cote * d / (points_par_cote - 1)))

def affiner_points(points, distance_max, distance_min):
    """
    Ajoute des points entre les points existants si la distance entre eux est trop grande,
    et supprime les points si la distance entre eux est trop petite.
    """
    i = 0
    while i < len(points) - 1:
        # Calculer la distance entre les points i et i+1
        dist = distance_entre_points(points[i], points[i+1])
        if dist > distance_max:
            # Ajouter un point intermédiaire
            new_point_x = (points[i][0] + points[i+1][0]) / 2
            new_point_y = (points[i][1] + points[i+1][1]) / 2
            new_point = (new_point_x, new_point_y)
            points.insert(i+1, new_point)
            # Passer au point suivant sans avancer l'index
            # car le point intermédiaire vient d'être ajouté
        elif dist < distance_min:
            # Supprimer le point i
            del points[i]
            # Si on supprime un point, nous devons vérifier la distance
            # entre le point précédent et le point actuel à nouveau
        i += 1

def force_repulsion(distance):
    """
    Calcule la force de répulsion entre deux points en fonction de leur distance.
    """
    k_repulsion = 0.10 # Constante de répulsion
    return k_repulsion / (distance ** 2)

def deplacement(points, amplitude):
    """
    Effectue un petit déplacement aléatoire sur chaque point du tableau tout en évitant les croisements de lignes.
    """
    n = len(points)
    for i in range(n-1):
        force_x, force_y = 0, 0
        for j in range(n-1):
            if i != j:
                dist_x = points[i][0] - points[j][0]
                dist_y = points[i][1] - points[j][1]
                distance = math.sqrt(dist_x ** 2 + dist_y ** 2)
                # Calcule la force de répulsion entre les points i et j
                force = force_repulsion(distance)
                # Ajoute la force à la somme totale
                force_x += force * (dist_x / distance)
                force_y += force * (dist_y / distance)
        # Effectue le déplacement en tenant compte de la amplitude et de la force de répulsion
        points[i] = (points[i][0] + amplitude * force_x, points[i][1] + amplitude * force_y)
            
def distance_entre_points(point1, point2):
    """
    Calcule la distance directe entre deux points.
    """
    x1, y1 = point1
    x2, y2 = point2
    distance = math.sqrt((x2 - x1)**2 + (y2 - y1)**2)
    return distance

def save_to_csv(filename, data):
    """
    Sauvegarde les données dans un fichier CSV.
    """
    with open(filename, 'w', newline='') as csvfile:
        writer = csv.writer(csvfile)
        writer.writerow(['X', 'Y'])  # Écrit la ligne d'en-tête
        for point in data:
            writer.writerow(point)     

def genere_labyrinthe(tab_points, nb_points, nb_deplacements):
    """
    Genere notre labyrinthe
    """
    init_cercle(tab_points, nb_points, 10)
    for i in range(nb_deplacements):
        print(i)
        deplacement(tab_points, 0.6) #Amplitude deplacement
        affiner_points(tab_points, 1.2, 7) #Distance max et distance min
        
    save_to_csv('CSV/en_cours.csv', tab_points)# Enregistrer les données dans un fichier CSV
    print("Nb points: " + str(len(tab_points)))
    print("Finish")
        


###################################################################################
points = []
genere_labyrinthe(points, 100, 300)





