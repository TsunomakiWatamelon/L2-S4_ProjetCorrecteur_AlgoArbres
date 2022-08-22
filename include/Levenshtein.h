/* Auteur : Gaël PAQUETTE & Hervé NGUYEN
 * Création : 31/03/2022
 * Dernière modification : 31/03/2022 */
/* Levenshtein.h */

#ifndef __levenshtein__
#define __levenshtein__

    #include <string.h>
    #include <assert.h>
    #include <stdio.h>
    #include <stdlib.h>

    /* Déclaration de la fonction affiche_erreur_exit */
    void affiche_erreur_exit(char * msg);

    /* Déclaration de la fonction init_distance */
    int **init_distance(int len_un, int len_deux);

    /* déclaration de la fonction init_cout*/
    int **init_cout(char *un, char *deux, int len_un, int len_deux);

    /* Déclaration de la fonction min2 */
    int min2(int a, int b);

    /* Déclaration de la fonction min3 */
    int min3(int a, int b, int c);

    /* Déclaration de la fonction Levenshtein */
    int Levenshtein(char * un, char *deux);

#endif
