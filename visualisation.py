import csv
import matplotlib.pyplot as plt

# /usr/bin/python3 /home/lilisan/COURS/visi/visualisation.py

def afficher_points(nom_fichier, nom_image):
    x = []
    y = []
    try:
        with open(nom_fichier, 'r', newline='') as fichier:
            lecteur_csv = csv.reader(fichier)
            next(lecteur_csv)
            for ligne in lecteur_csv:
                x.append(float(ligne[0]))
                y.append(float(ligne[1]))
        plt.plot(x, y, marker='o')
        plt.xlabel('X')
        plt.ylabel('Y')
        plt.title('Points à partir du fichier CSV')
        plt.savefig(nom_image)
        plt.close()
        print(f"Graphique sauvegardé dans '{nom_image}'")
    except FileNotFoundError:
        print("Le fichier n'existe pas.")

# Exemple d'utilisation :
afficher_points('visi.csv', 'graphique_points.png')
