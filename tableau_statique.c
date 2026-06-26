#include <stdio.h>
#include <string.h>
#include <math.h> // OBLIGATOIRE POUR L'ECART-TYPE (sqrt et pow)
#include "tableau_statique.h"

void initialiser_base(BaseStatique *base) { base->nombre_inscrits = 0; }

int ajouter_etudiant_statique(BaseStatique *base, Etudiant nouveau) {
    if (base->nombre_inscrits >= MAX_ETUDIANTS) return 0; 
    base->liste[base->nombre_inscrits] = nouveau;
    base->nombre_inscrits++; 
    return 1; 
}

void afficher_base_statique(BaseStatique *base) {
    printf("\n=== BASE DE DONNEES STATIQUE (%d/%d inscrits) ===\n", base->nombre_inscrits, MAX_ETUDIANTS);
    if (base->nombre_inscrits == 0) {
        printf("Aucun etudiant enregistre.\n");
        return;
    }
    for (int i = 0; i < base->nombre_inscrits; i++) {
        printf("ID: %d | Nom: %s %s | Age: %d | Moyenne: %.2f\n", 
            base->liste[i].immatriculation, base->liste[i].nom,
            base->liste[i].prenom, base->liste[i].age, base->liste[i].moyenne);
    }
    printf("===============================================\n\n");
}

int rechercher_immatriculation(BaseStatique *base, int id) {
    for (int i = 0; i < base->nombre_inscrits; i++) {
        if (base->liste[i].immatriculation == id) return i; 
    }
    return -1; 
}

void rechercher_prefixe_nom(BaseStatique *base, const char *prefixe) {
    int trouves = 0; int taille = strlen(prefixe); 
    printf("\n--- Resultats pour \"%s\" ---\n", prefixe);
    for (int i = 0; i < base->nombre_inscrits; i++) {
        if (strncmp(base->liste[i].nom, prefixe, taille) == 0) {
            printf("-> ID %d | %s %s\n", base->liste[i].immatriculation, base->liste[i].nom, base->liste[i].prenom);
            trouves++;
        }
    }
    if (trouves == 0) printf("Aucun etudiant ne correspond.\n");
}

void rechercher_intervalle_age(BaseStatique *base, int age_min, int age_max) {
    int trouves = 0; printf("\n--- Tranche %d a %d ans ---\n", age_min, age_max);
    for (int i = 0; i < base->nombre_inscrits; i++) {
        if (base->liste[i].age >= age_min && base->liste[i].age <= age_max) {
            printf("-> ID %d | %s %s | Age: %d\n", base->liste[i].immatriculation, base->liste[i].nom, base->liste[i].prenom, base->liste[i].age);
            trouves++;
        }
    }
    if (trouves == 0) printf("Aucun etudiant trouve.\n");
}

int mettre_a_jour_etudiant(BaseStatique *base, int id) {
    int position = rechercher_immatriculation(base, id);
    if (position == -1) return 0; 
    printf("\nNouvel age : "); scanf("%d", &base->liste[position].age);
    printf("Nouvelle moyenne : "); scanf("%f", &base->liste[position].moyenne);
    return 1; 
}

int supprimer_etudiant(BaseStatique *base, int id) {
    int position = rechercher_immatriculation(base, id);
    if (position == -1) return 0; 
    for (int i = position; i < base->nombre_inscrits - 1; i++) { base->liste[i] = base->liste[i + 1]; }
    base->nombre_inscrits--; 
    return 1; 
}

void tri_insertion_nom(BaseStatique *base) {
    for (int i = 1; i < base->nombre_inscrits; i++) {
        Etudiant cle = base->liste[i]; int j = i - 1;
        while (j >= 0 && strcmp(base->liste[j].nom, cle.nom) > 0) {
            base->liste[j + 1] = base->liste[j]; j = j - 1;
        }
        base->liste[j + 1] = cle;
    }
    printf("\n[SUCCES] Base triee par ordre alphabetique.\n");
}

void tri_bulles_moyenne(BaseStatique *base) {
    for (int i = 0; i < base->nombre_inscrits - 1; i++) {
        for (int j = 0; j < base->nombre_inscrits - i - 1; j++) {
            if (base->liste[j].moyenne < base->liste[j + 1].moyenne) {
                Etudiant temp = base->liste[j];
                base->liste[j] = base->liste[j + 1];
                base->liste[j + 1] = temp;
            }
        }
    }
}

// =========================================================
//         NOUVELLE FONCTION : AGREGATIONS STATISTIQUES
// =========================================================
void afficher_statistiques(BaseStatique *base) {
    if (base->nombre_inscrits == 0) {
        printf("\n[ERREUR] Aucun etudiant pour calculer les statistiques.\n");
        return;
    }

    float min = base->liste[0].moyenne;
    float max = base->liste[0].moyenne;
    float somme = 0.0;

    // 1. Min, Max et Somme
    for (int i = 0; i < base->nombre_inscrits; i++) {
        if (base->liste[i].moyenne < min) min = base->liste[i].moyenne;
        if (base->liste[i].moyenne > max) max = base->liste[i].moyenne;
        somme += base->liste[i].moyenne;
    }

    // 2. Moyenne de la classe
    float moyenne_classe = somme / base->nombre_inscrits;

    // 3. Médiane (Nécessite de trier le tableau d'abord !)
    tri_bulles_moyenne(base); 
    float mediane = 0.0;
    int n = base->nombre_inscrits;
    if (n % 2 == 0) { // Si nombre pair, on fait la moyenne des deux du milieu
        mediane = (base->liste[(n - 1) / 2].moyenne + base->liste[n / 2].moyenne) / 2.0;
    } else { // Si nombre impair, on prend celui du milieu
        mediane = base->liste[n / 2].moyenne;
    }

    // 4. Ecart-type
    float somme_ecarts = 0.0;
    for (int i = 0; i < base->nombre_inscrits; i++) {
        somme_ecarts += pow(base->liste[i].moyenne - moyenne_classe, 2);
    }
    float ecart_type = sqrt(somme_ecarts / base->nombre_inscrits);

    printf("\n============= STATISTIQUES LMI2 =============\n");
    printf(" Plus basse moyenne   : %.2f\n", min);
    printf(" Plus haute moyenne   : %.2f\n", max);
    printf(" Moyenne de la classe : %.2f\n", moyenne_classe);
    printf(" Mediane des notes    : %.2f\n", mediane);
    printf(" Ecart-type           : %.2f\n", ecart_type);
    printf("=============================================\n");
}
