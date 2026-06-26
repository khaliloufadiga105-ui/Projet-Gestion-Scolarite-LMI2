#ifndef TABLEAU_DYNAMIQUE_H
#define TABLEAU_DYNAMIQUE_H
#include "etudiant.h"

typedef struct {
    Etudiant **tableau; // Le double astérisque : c'est un tableau d'adresses (pointeurs)
    int nb_elements;
    int capacite_max;
} TabDynamique;

void initialiser_tab_dynamique(TabDynamique *td, int capacite_initiale);
int inserer_tab_dynamique(TabDynamique *td, Etudiant *e);
void afficher_tab_dynamique(TabDynamique *td);
void liberer_tab_dynamique(TabDynamique *td);

#endif
