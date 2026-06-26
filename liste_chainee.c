#include <stdio.h>
#include <stdlib.h>
#include "liste_chainee.h"

void initialiser_liste(ListeDouble *liste) {
    liste->tete = NULL;
    liste->queue = NULL;
    liste->taille = 0;
}

int inserer_en_queue(ListeDouble *liste, Etudiant e) {
    // On fabrique une nouvelle boîte en mémoire
    Element *nouvel_element = (Element *)malloc(sizeof(Element));
    
    if (nouvel_element == NULL) {
        printf("[ERREUR FATALE] Echec de l'allocation memoire pour la liste.\n");
        return 0; // Echec
    }

    nouvel_element->donnees = e;
    nouvel_element->suivant = NULL;
    nouvel_element->precedent = NULL;

    // Si la liste est complètement vide
    if (liste->taille == 0) {
        liste->tete = nouvel_element;
        liste->queue = nouvel_element;
    } 
    // Sinon, on l'accroche directement à l'arrière grâce au pointeur "queue"
    else {
        nouvel_element->precedent = liste->queue; // Le nouveau regarde l'ancien dernier
        liste->queue->suivant = nouvel_element;   // L'ancien dernier regarde le nouveau
        liste->queue = nouvel_element;            // Le nouveau devient officiellement le dernier
    }

    liste->taille++;
    return 1; // Succès
}

void afficher_liste(ListeDouble *liste) {
    printf("\n=== LISTE DOUBLEMENT CHAINEE (%d inscrits) ===\n", liste->taille);
    
    if (liste->taille == 0) {
        printf("La liste est vide.\n");
        return;
    }

    // On part du début et on lit jusqu'à la fin
    Element *courant = liste->tete;
    while (courant != NULL) {
        printf("ID: %d | Nom: %s %s | Age: %d | Moyenne: %.2f\n", 
            courant->donnees.immatriculation,
            courant->donnees.nom,
            courant->donnees.prenom,
            courant->donnees.age,
            courant->donnees.moyenne);
        courant = courant->suivant;
    }
    printf("==============================================\n\n");
}

void liberer_liste(ListeDouble *liste) {
    Element *courant = liste->tete;
    Element *suivant;
    
    // On détruit les boîtes une par une pour nettoyer la RAM
    while (courant != NULL) {
        suivant = courant->suivant;
        free(courant);
        courant = suivant;
    }
    
    liste->tete = NULL;
    liste->queue = NULL;
    liste->taille = 0;
}
