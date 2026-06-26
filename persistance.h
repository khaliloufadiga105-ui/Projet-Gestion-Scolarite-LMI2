#ifndef PERSISTANCE_H
#define PERSISTANCE_H
#include "tableau_statique.h"

// Fonctions pour sauvegarder et charger les données sur le disque dur
int sauvegarder_base(BaseStatique *base, const char *nom_fichier);
int charger_base(BaseStatique *base, const char *nom_fichier);

#endif
