#ifndef TABLEAU_STATIQUE_H
#define TABLEAU_STATIQUE_H
#include "etudiant.h"

#define MAX_ETUDIANTS 100000

typedef struct {
    Etudiant liste[MAX_ETUDIANTS]; 
    int nombre_inscrits;           
} BaseStatique;

void initialiser_base(BaseStatique *base);
int ajouter_etudiant_statique(BaseStatique *base, Etudiant nouveau);
void afficher_base_statique(BaseStatique *base);

int rechercher_immatriculation(BaseStatique *base, int id);
void rechercher_prefixe_nom(BaseStatique *base, const char *prefixe);
void rechercher_intervalle_age(BaseStatique *base, int age_min, int age_max);

int mettre_a_jour_etudiant(BaseStatique *base, int id);
int supprimer_etudiant(BaseStatique *base, int id);

void tri_insertion_nom(BaseStatique *base);
void tri_bulles_moyenne(BaseStatique *base);

// --- L'ULTIME OPERATION : LES STATISTIQUES ---
void afficher_statistiques(BaseStatique *base);

#endif
