#ifndef ETUDIANT_H
#define ETUDIANT_H

typedef struct {
    int immatriculation;
    char nom[50];
    char prenom[50];
    int age;
    int niveau_licence; 
    float moyenne;
} Etudiant;

#endif
