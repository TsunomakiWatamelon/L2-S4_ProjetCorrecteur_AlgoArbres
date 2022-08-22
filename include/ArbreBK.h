/* Auteur : Gaël PAQUETTE & Hervé NGUYEN
 * Création : 19/04/2022
 * Dernière modification : 22/04/2022 */
/* ArbreBK.h */

#ifndef __ARBREBK__
#define __ARBREBK__

    #include <stdio.h>
    #include <stdlib.h>
    #include <assert.h>
    #include <string.h>

    #include <Listes.h>
    #include <ATR.h>
    #include <Levenshtein.h>
    
    /* Déclaration de la structure de l'arbre */
    typedef struct noeudBK {
        char* mot;
        int valeur;
        struct noeudBK* filsG;
        struct noeudBK* frereD;
    } NoeudBK, *ArbreBK;

    /* Déclaration de la fonction inserer_dans_ArbreBK_aux */
    int inserer_dans_ArbreBK_aux(ArbreBK * A, char * mot, int valeur);

    /* Déclaration de la fonction inserer_dans_ArbreBK */
    int inserer_dans_ArbreBK(ArbreBK * A, char * mot);

    /* Déclaration de la fonction est_dans_ArbreBK_aux */
    int est_dans_ArbreBK_aux(ArbreBK A, char * mot, int valeur);

    /* Déclaration de la fonction est_dans_ArbreBK */
    int est_dans_ArbreBK(ArbreBK A, char * mot);

    /* Déclaration de la fonction creer_ArbreBK */
    ArbreBK creer_ArbreBK(FILE* dico);

    /* Déclaration de la fonction libere_ArbreBK_aux */
    void libere_ArbreBK_aux(ArbreBK A);

    /* Déclaration de la fonction libere_ArbreBK */
    void libere_ArbreBK(ArbreBK* A);

    /* Déclaration de la fonction alloue_ArbreBK_cellule */
    NoeudBK * alloue_ArbreBK_cellule(char* mot, int valeur);

    /* Déclaration de la fonction rechercher_dans_ArbreBK_aux */
    int rechercher_dans_ArbreBK_aux(ArbreBK A, Liste* corrections, char* mot, int* seuil);

    /* Déclaration de la fonction rechercher_dans_ArbreBK */
    Liste rechercher_dans_ArbreBK(ArbreBK A, char* mot);

    /* Déclaration de la fonction afficher_ArbreBK_aux */
    void afficher_ArbreBK_aux(ArbreBK A, int profondeur);

    /* Déclaration de la fonction afficher_ArbreBK */
    void afficher_ArbreBK(ArbreBK A);

    /* Déclaration de la fonction afficher2_ArbreBK */
    void afficher2_ArbreBK(char* dot, char* pdf, ArbreBK A);

#endif