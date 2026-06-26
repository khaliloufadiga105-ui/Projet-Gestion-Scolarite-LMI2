#include <stdio.h>
#include <stdlib.h>
#include "persistance.h"

int sauvegarder_base(BaseStatique *base, const char *nom_fichier) {
    // Ouverture du fichier en mode écriture binaire (wb)
    FILE *fichier = fopen(nom_fichier, "wb");
    if (fichier == NULL) {
        printf("[ERREUR] Impossible de creer le fichier de sauvegarde.\n");
        return 0; // Échec
    }

    // Étape 1 : On écrit d'abord le nombre d'étudiants inscrits
    fwrite(&(base->nombre_inscrits), sizeof(int), 1, fichier);

    // Étape 2 : On écrit tout le bloc du tableau d'un seul coup de pinceau !
    if (base->nombre_inscrits > 0) {
        fwrite(base->liste, sizeof(Etudiant), base->nombre_inscrits, fichier);
    }

    fclose(fichier); // On ferme toujours le flux pour valider l'écriture
    printf("[PERSISTANCE] Sauvegarde reussie dans \"%s\" (%d etudiants enregistres).\n", nom_fichier, base->nombre_inscrits);
    return 1; // Succès
}

int charger_base(BaseStatique *base, const char *nom_fichier) {
    // Ouverture du fichier en mode lecture binaire (rb)
    FILE *fichier = fopen(nom_fichier, "rb");
    if (fichier == NULL) {
        // Si le fichier n'existe pas encore, ce n'est pas une erreur, c'est juste le premier démarrage
        printf("[PERSISTANCE] Aucun fichier de sauvegarde trouve. Base initialisee a vide.\n");
        base->nombre_inscrits = 0;
        return 0;
    }

    // Étape 1 : On lit le nombre d'étudiants stockés
    fread(&(base->nombre_inscrits), sizeof(int), 1, fichier);

    // Étape 2 : On aspire toutes les données directement dans notre tableau en RAM
    if (base->nombre_inscrits > 0) {
        fread(base->liste, sizeof(Etudiant), base->nombre_inscrits, fichier);
    }

    fclose(fichier);
    printf("[PERSISTANCE] Chargement reussi ! %d etudiants recuperes depuis \"%s\".\n", base->nombre_inscrits, nom_fichier);
    return 1;
}
