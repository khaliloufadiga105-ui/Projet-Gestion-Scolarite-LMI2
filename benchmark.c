#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include "etudiant.h"
#include "tableau_statique.h"

// Fonction pour générer des données aléatoires
void generer_donnees_aleatoires(BaseStatique *base, int n) {
    initialiser_base(base);
    for (int i = 0; i < n; i++) {
        Etudiant e;
        e.immatriculation = i + 1;
        e.moyenne = (rand() % 2001) / 100.0; 
        ajouter_etudiant_statique(base, e);
    }
}

int main(int argc, char *argv[]) {
    srand(time(NULL)); 

    int tailles[] = {100, 1000, 10000, 50000}; 
    int nb_tests = 4;
    int repetitions = 10; 

    printf("===================================================\n");
    printf("   LABORATOIRE DE COMPLEXITE (BENCHMARK LMI2)      \n");
    printf("===================================================\n\n");

    BaseStatique *ma_base = (BaseStatique *)malloc(sizeof(BaseStatique));
    if (ma_base == NULL) return 1;

    printf("--- TEST 1 : COMPLEXITE DU TRI A BULLES O(n^2) ---\n");
    printf("Taille (n) | Temps Moyen (ms)\n");
    printf("--------------------------------\n");

    for (int t = 0; t < nb_tests; t++) {
        int n = tailles[t];
        double temps_total_ms = 0.0;

        for (int rep = 0; rep < repetitions; rep++) {
            generer_donnees_aleatoires(ma_base, n);
            
            clock_t debut = clock(); 
            tri_bulles_moyenne(ma_base); 
            clock_t fin = clock();

            double temps_ecoule = ((double)(fin - debut) / CLOCKS_PER_SEC) * 1000.0;
            temps_total_ms += temps_ecoule;
        }
        double temps_moyen = temps_total_ms / repetitions;
        printf("n = %-6d | %f ms\n", n, temps_moyen);
    }

    free(ma_base);
    return 0;
}
