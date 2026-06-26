#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "etudiant.h"
#include "tableau_statique.h"
#include "tableau_dynamique.h"
#include "liste_chainee.h"
#include "persistance.h"

int main(int argc, char *argv[]) {
    
    BaseStatique *ma_base_statique = (BaseStatique *)malloc(sizeof(BaseStatique));
    if (ma_base_statique == NULL) return 1;
    initialiser_base(ma_base_statique);

    TabDynamique mon_tab_dynamique;
    initialiser_tab_dynamique(&mon_tab_dynamique, 2);

    ListeDouble ma_liste_chainee;
    initialiser_liste(&ma_liste_chainee);

    printf("--- INITIALISATION DU SYSTEME DE GESTION (LMI2) ---\n");
    charger_base(ma_base_statique, "sauvegarde_etudiants.bin");

    for (int i = 0; i < ma_base_statique->nombre_inscrits; i++) {
        inserer_tab_dynamique(&mon_tab_dynamique, &(ma_base_statique->liste[i]));
        inserer_en_queue(&ma_liste_chainee, ma_base_statique->liste[i]);
    }

    int choix = 0;
    do {
        printf("\n======================================================\n");
        printf("         MENU PRINCIPAL : GESTION DE SCOLARITE        \n");
        printf("======================================================\n");
        printf("  1. Inscrire un nouvel etudiant\n");
        printf("  2. Afficher la base de donnees\n");
        printf("  ----------------- RECHERCHE ------------------------\n");
        printf("  3. Recherche EXACTE (Par Immatriculation)\n");
        printf("  4. Recherche SECONDAIRE (Par prefixe de Nom)\n");
        printf("  5. Recherche SECONDAIRE (Par intervalle d'Age)\n");
        printf("  ---------------- MODIFICATION ----------------------\n");
        printf("  6. Mettre a jour un etudiant (Age & Moyenne)\n");
        printf("  7. Supprimer un dossier etudiant\n");
        printf("  ----------------- TRI & STATS ----------------------\n");
        printf("  8. Trier par Nom (Tri par Insertion)\n");
        printf("  9. Trier par Classement Moyenne (Tri a Bulles)\n");
        printf(" 10. Afficher les statistiques (Min, Max, Moyenne...)\n");
        printf("  ----------------------------------------------------\n");
        printf(" 11. Sauvegarder et Quitter le programme\n");
        printf("======================================================\n");
        printf("Votre choix : ");
        
        if (scanf("%d", &choix) != 1) {
            printf("\n[ATTENTION] Saisie incorrecte.\n");
            while (getchar() != '\n'); 
            continue;
        }

        switch (choix) {
            case 1: {
                Etudiant nouvel_etudiant;
                printf("\nImmatriculation : "); scanf("%d", &nouvel_etudiant.immatriculation);
                printf("Nom : "); scanf("%s", nouvel_etudiant.nom);
                printf("Prenom : "); scanf("%s", nouvel_etudiant.prenom);
                printf("Age : "); scanf("%d", &nouvel_etudiant.age);
                printf("Moyenne : "); scanf("%f", &nouvel_etudiant.moyenne);

                if (ajouter_etudiant_statique(ma_base_statique, nouvel_etudiant)) {
                    inserer_tab_dynamique(&mon_tab_dynamique, &(ma_base_statique->liste[ma_base_statique->nombre_inscrits - 1]));
                    inserer_en_queue(&ma_liste_chainee, nouvel_etudiant);
                    printf("\n[SUCCES] Etudiant enregistre !\n");
                }
                break;
            }
            case 2: afficher_base_statique(ma_base_statique); break;
            case 3: {
                int id; printf("\nImmatriculation a chercher : "); scanf("%d", &id);
                int pos = rechercher_immatriculation(ma_base_statique, id);
                if (pos != -1) {
                    printf("\nTROUVE : %s %s | Age: %d | Moy: %.2f\n", 
                        ma_base_statique->liste[pos].nom, ma_base_statique->liste[pos].prenom,
                        ma_base_statique->liste[pos].age, ma_base_statique->liste[pos].moyenne);
                } else { printf("\n[ERREUR] Introuvable.\n"); }
                break;
            }
            case 4: {
                char prefixe[50]; printf("\nPrefixe du nom : "); scanf("%s", prefixe);
                rechercher_prefixe_nom(ma_base_statique, prefixe); break;
            }
            case 5: {
                int min, max; printf("\nAge min : "); scanf("%d", &min); printf("Age max : "); scanf("%d", &max);
                rechercher_intervalle_age(ma_base_statique, min, max); break;
            }
            case 6: {
                int id; printf("\nImmatriculation a modifier : "); scanf("%d", &id);
                if (mettre_a_jour_etudiant(ma_base_statique, id)) {
                    printf("[SUCCES] Mise a jour effectuee !\n");
                } else { printf("[ERREUR] Etudiant introuvable.\n"); }
                break;
            }
            case 7: {
                int id; printf("\nImmatriculation a SUPPRIMER : "); scanf("%d", &id);
                if (supprimer_etudiant(ma_base_statique, id)) {
                    printf("[SUCCES] Dossier supprime !\n");
                } else { printf("[ERREUR] Etudiant introuvable.\n"); }
                break;
            }
            case 8: tri_insertion_nom(ma_base_statique); afficher_base_statique(ma_base_statique); break;
            case 9: tri_bulles_moyenne(ma_base_statique); afficher_base_statique(ma_base_statique); break;
            case 10: afficher_statistiques(ma_base_statique); break;
            case 11:
                printf("\n[PERSISTANCE] Sauvegarde en cours...\n");
                sauvegarder_base(ma_base_statique, "sauvegarde_etudiants.bin");
                printf("Fermeture du systeme.\n");
                break;
            default: if (choix != 11) printf("\n[ATTENTION] Choix invalide !\n");
        }
    } while (choix != 11);

    liberer_tab_dynamique(&mon_tab_dynamique);
    liberer_liste(&ma_liste_chainee);
    free(ma_base_statique);
    return 0;
}
