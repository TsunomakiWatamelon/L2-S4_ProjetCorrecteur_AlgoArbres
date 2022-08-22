/* Auteur : Gaël PAQUETTE & Hervé NGUYEN
 * Création : 13/03/2022
 * Dernière modification : 20/03/2022 */
/* Main.c */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#include "../include/Listes.h"
#include "../include/ATR.h"

void strlower(char *mot){
    /*
    Fonction permettant de convertir en minuscule les lettres non accentués dans la chaine de caractère 'mot'
    qui sont en majuscule en minuscule.

    Renvoie rien
    */
    int i, taille;
    if (mot == NULL) return;
    taille = strlen(mot);
    for (i = 0; i < taille; i++){
        mot[i] = tolower(mot[i]);
    }
}


int main(int argc, char * argv[]) {
    /*
    Fonction principale du programme correcteur_0

    Effectue l'algorithme enoncé dans le sujet.
    */
    FILE *fichier_dico;
    FILE *fichier_texte;
    int erreur_open;
    Liste erreurs;
    ATR dico;
    char mot_dico[MAX_LETTRES];
    char mot_texte_raw[MAX_LETTRES];
    char mot_texte[MAX_LETTRES];


    erreur_open = 0;
    if (argc != 3){
        fprintf(stderr, "%s : Nombre d'arguments incorrect\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    fichier_texte = fopen(argv[1], "r");
    fichier_dico = fopen(argv[2], "r");
    if (fichier_texte == NULL) {
        fprintf(stderr, "%s : Texte introuvable \n", argv[0]);
        erreur_open = 1;
    }
    if (fichier_dico == NULL){
        fprintf(stderr, "%s : Dictionnaire introuvable \n", argv[0]);
        erreur_open = 1;
    }
    if (erreur_open){
        exit(EXIT_FAILURE);
    }

    while(fscanf(fichier_dico, "%s", mot_dico) != EOF){
        inserer_dans_ATR(&dico, mot_dico);
    }

    while(fscanf(fichier_texte, "%s[^.]", mot_texte_raw) != EOF){
        sscanf(mot_texte_raw, "%30[^.,'’]", mot_texte);
        strlower(mot_texte);
        if (!dans_ATR(dico, mot_texte)){
            if (!dans_Liste(erreurs, mot_texte)) {
                inserer_en_tete(&erreurs, mot_texte);
            }
        }
    }
    fprintf(stdout, "Mot(s) mal orthographié(s) :\n");
    afficher_Liste(erreurs);
    liberer_ATR(&(dico));
    liberer_Liste(&(erreurs));
    return 0;
}
