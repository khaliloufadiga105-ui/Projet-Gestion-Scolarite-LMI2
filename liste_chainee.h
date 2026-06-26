#ifndef LISTE_CHAINEE_H
#define LISTE_CHAINEE_H
#include "etudiant.h"

// La "boîte" qui contient l'étudiant et les liens vers les autres
typedef struct Element {
    Etudiant donnees;
    struct Element *suivant;
    struct Element *precedent; // Le double chaînage exigé
} Element;

// Le contrôleur de la liste
typedef struct {
    Element *tete;   // Pointeur vers le premier élément
    Element *queue;  // Pointeur vers le dernier (Crucial pour le O(1))
    int taille;
} ListeDouble;

void initialiser_liste(ListeDouble *liste);
int inserer_en_queue(ListeDouble *liste, Etudiant e);
void afficher_liste(ListeDouble *liste);
void liberer_liste(ListeDouble *liste);

#endif
