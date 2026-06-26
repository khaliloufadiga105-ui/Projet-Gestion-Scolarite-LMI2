# Système de Gestion de Scolarité - Projet LMI2

Ce projet est une application modulaire en C permettant la gestion des dossiers étudiants. Il propose une étude comparative des performances entre un tableau statique, un tableau dynamique et une liste doublement chaînée.

## 🛠️ Compilation et Exécution
Le projet inclut un `Makefile` pour automatiser la compilation sous environnement Unix/Linux ou MinGW (Windows).

1. Ouvrez un terminal dans le dossier du projet.
2. Compilez le projet en tapant : `make`
3. Exécutez le programme : `./gestion_scolarite_LMI2`
4. Pour nettoyer les fichiers compilés : `make clean`

## 📁 Organisation du Dépôt
- `main.c` : Point d'entrée et menu interactif.
- `etudiant.h/c` : Définition de l'entité de base.
- `tableau_statique.h/c` : Implémentation via allocation contiguë sur le Tas.
- `tableau_dynamique.h/c` : Implémentation via pointeurs et réallocation géométrique.
- `liste_chainee.h/c` : Implémentation avec pointeur de queue O(1).
- `persistance.h/c` : Sauvegarde et chargement binaire.
- `benchmark.c` : Script de chronométrage (Complexité).