#include <stdio.h>
#include <stdlib.h>
#include "tableau_dynamique.h"

void initialiser_tab_dynamique(TabDynamique *td, int capacite_initiale) {
    td->capacite_max = capacite_initiale;
    td->nb_elements = 0;
    // Allocation de la mémoire pour stocker des POINTEURS
    td->tableau = (Etudiant **)malloc(td->capacite_max * sizeof(Etudiant *));
    
    if (td->tableau == NULL) {
        printf("[ERREUR] Echec de l'allocation initiale.\n");
    }
}

int inserer_tab_dynamique(TabDynamique *td, Etudiant *e) {
    // REDIMENSIONNEMENT GÉOMÉTRIQUE : Si le tableau est plein, on double sa taille
    if (td->nb_elements == td->capacite_max) {
        td->capacite_max *= 2; 
        td->tableau = (Etudiant **)realloc(td->tableau, td->capacite_max * sizeof(Etudiant *));
        
        if (td->tableau == NULL) {
            printf("[ERREUR FATALE] Echec du realloc.\n");
            return 0; // Echec
        }
        printf("[INFO TECHNIQUE] Tableau plein. Realloc reussi. Nouvelle capacite : %d\n", td->capacite_max);
    }
    
    // On ajoute l'ADRESSE de l'étudiant dans la première case vide
    td->tableau[td->nb_elements] = e;
    td->nb_elements++;
    
    return 1; // Succès
}

void afficher_tab_dynamique(TabDynamique *td) {
    printf("\n=== TABLEAU DYNAMIQUE (%d/%d places utilisees) ===\n", td->nb_elements, td->capacite_max);
    
    if (td->nb_elements == 0) {
        printf("Le tableau est vide.\n");
        return;
    }

    for (int i = 0; i < td->nb_elements; i++) {
        // Attention : On utilise td->tableau[i]-> car la case contient une adresse
        printf("ID: %d | Nom: %s %s | Age: %d | Moyenne: %.2f\n", 
            td->tableau[i]->immatriculation,
            td->tableau[i]->nom,
            td->tableau[i]->prenom,
            td->tableau[i]->age,
            td->tableau[i]->moyenne);
    }
    printf("====================================================\n\n");
}

void liberer_tab_dynamique(TabDynamique *td) {
    // On rend le tableau à la mémoire vive pour éviter les fuites (Memory Leaks)
    if (td->tableau != NULL) {
        free(td->tableau);
        td->tableau = NULL;
    }
    td->nb_elements = 0;
    td->capacite_max = 0;
}
