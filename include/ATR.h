/* Auteur : Gaël PAQUETTE & Hervé NGUYEN
 * Création : 13/03/2022
 * Dernière modification : 13/03/2022 */
/* ATR.h */

#ifndef __ATR__
#define __ATR__

    #define MAX_LETTRES 30
    #include <stdlib.h>
    #include <stdio.h>
    #include <assert.h>
    
    /* Déclaration de la structure ATR */
    typedef struct _atrcell_ {
        char lettre;
        struct _atrcell_ *mil;
        struct _atrcell_ *inf;
        struct _atrcell_ *sup;
    } ATRcell, *ATR;

    /* Déclaration de la fonction creer_ATR_vide */
    ATR creer_ATR_vide();

    /* Déclaration de la fonction alloue_ATR_cellule */
    ATR alloue_ATR_cellule(char lettre);

    /* Déclaration de la fonction liberer_ATR_aux */
    void liberer_ATR_aux(ATR A);

    /* Déclaration de la fonction liberer_ATR */
    void liberer_ATR(ATR * A);

    /* Déclaration de la fonction ajoute_branche */
    void ajoute_branche(ATR * A, char * mot);

    /* Déclaration de la fonction inserer_dans_ATR */
    int inserer_dans_ATR(ATR * A, char * mot);

    /* Déclaration de la fonction supprimer_dans_ATR_aux */
    int supprimer_dans_ATR_aux(ATR * A, char * mot);

    /* Déclaration de la fonction supprimer_dans_ATR */
    void supprimer_dans_ATR(ATR * A, char * mot);

    /* Déclaration de la fonction afficher_ATR_aux */
    void afficher_ATR_aux(ATR A, char buffer[], int indice);

    /* Déclaration de la fonction afficher_ATR */
    void afficher_ATR(ATR A);

    /* Déclaration de la fonction dans_ATR */
    int dans_ATR(ATR A, char *mot);

#endif
