import csv
import matplotlib.pyplot as plt

# Fonction pour charger les données depuis un fichier CSV
def charger_de_csv(nom_fichier):
    points = []
    with open(nom_fichier, 'r', newline='', encoding='utf-8') as csvfile:
        reader = csv.reader(csvfile)
        next(reader)  # Ignorer l'en-tête
        for row in reader:
            points.append((float(row[0]), float(row[1])))
    return points

# Charger les données du fichier CSV
points_cercle = charger_de_csv('./CSV/en_cours.csv')




# Traçage du cercle avec des lignes reliant les points
x = [point[0] for point in points_cercle]
y = [point[1] for point in points_cercle]

plt.figure(figsize=(6, 6))
plt.plot(x, y, marker='o', linestyle='-',markersize=2)
plt.gca().set_aspect('equal', adjustable='box')
plt.title('VISI401')
plt.xlabel('X')
plt.ylabel('Y')
plt.grid(True)
plt.show()
