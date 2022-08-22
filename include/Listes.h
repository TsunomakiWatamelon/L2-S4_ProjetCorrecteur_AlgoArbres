/* Auteur : Gaël PAQUETTE & Hervé NGUYEN
 * Création : 09/03/2022
 * Dernière modification : 09/03/2022 */
/* Listes.h */

#ifndef __LISTES__
#define __LISTES__

    #include <string.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <assert.h>
    
    /* Déclaration de la structure Liste */
    typedef struct __cellule__ {
        char* mot;
        struct __cellule__* next;
    } Cellule, *Liste;

    /* Déclaration de la fonction allouer_Cellule */
    Cellule * allouer_Cellule(char * mot);

    /* Déclaration de la fonction inserer_en_tete */
    int inserer_en_tete(Liste * L, char * mot);

    /* Déclaration de la fonction liberer_Liste */
    void liberer_Liste(Liste * L);

    /* Déclaration de la fonction afficher_Liste */
    void afficher_Liste(Liste L);

    /* Déclaration de la fonction dans_Liste */
    int dans_Liste(Liste L, char *mot);

#endif
