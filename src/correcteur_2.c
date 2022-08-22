/* Auteur : Gaël PAQUETTE & Hervé NGUYEN
 * Création : 21/04/2022
 * Dernière modification : 24/04/2022 */
/* Main_2.c */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#include <Listes.h>
#include <ATR.h>
#include <Levenshtein.h>
#include <ArbreBK.h>

static void strlower(char *mot){
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

static void affiche_propositions(Liste correction){
    /*
    Fonction qui affiche l'ensemble des mots en propositions de correction contenus dans la Liste "correction".

    Renvoie rien.
    */
    Liste tmp = correction;
    
    printf("Proposition(s) : ");
    while (tmp != NULL){
        fprintf(stdout, "%s", tmp->mot);
        if (tmp->next != NULL) fprintf(stdout, ", ");
        tmp = tmp->next;
    }
    fprintf(stdout, "\n");
}

static void affiche_correction(ArbreBK A, Liste *erreurs){
    /* 
    Fonction qui affiche les suggestions proposé pour chaque mots présents dans la liste 'erreurs'

    Renvoie rien.
    */ 
    Liste correction = NULL;
    Liste tmp = *erreurs;

    while(tmp != NULL){
        correction = rechercher_dans_ArbreBK(A, tmp->mot);
        printf("Mot mal orthographié : %s\n", tmp->mot);
        affiche_propositions(correction);
        liberer_Liste(&(correction));
        tmp = tmp->next;
    }
}

int main(int argc, char * argv[]) {
    /*
    Fonction principale du programme correcteur_1

    Effectue l'algorithme enoncé dans le sujet.
    Et fait des suggestions de correction orthographiques.

    Peut aussi afficher l'ArbreBK (terminal ou pdf) si demandé dans les arguments.
    */
    FILE *fichier_dico;
    FILE *fichier_texte = NULL;
    int erreur_open, affichage = 0;
    Liste erreurs;
    ArbreBK dico;
    char mot_texte[MAX_LETTRES];
    char mot_texte_raw[MAX_LETTRES];


    erreur_open = 0;
    if (argc < 3 || argc > 3){
        fprintf(stderr, "%s : Nombre d'arguments incorrect\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    if (strcmp(argv[1], "-a") == 0)
        affichage = 1;
    else if (strcmp(argv[1], "-g") == 0)
        affichage = 2;
    
    if (affichage == 0) fichier_texte = fopen(argv[1], "r");
    fichier_dico = fopen(argv[2], "r");

    if ((affichage == 0) && (fichier_texte == NULL)) {
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

    /* Création des arbres */
    dico = creer_ArbreBK(fichier_dico);
    fclose(fichier_dico);

    /* Mode correction */
    if (affichage == 0){
        while (fscanf(fichier_texte, "%s[^.]", mot_texte_raw) != EOF) {
            sscanf(mot_texte_raw, "%30[^.,'’]", mot_texte);
            strlower(mot_texte);
            if (!est_dans_ArbreBK(dico, mot_texte)) {
                inserer_en_tete(&erreurs, mot_texte);
            }
        }
        fclose(fichier_texte);
        /* Affichage des correction pour les mots mal orthographiés */
        affiche_correction(dico, &(erreurs));
    }
    /* Affichage de l'arbreBK */
    if (affichage == 2) {
        afficher2_ArbreBK("ArbreBK.dot", "ArbreBK.pdf", dico);
        system("evince ArbreBK.pdf &");
    } else if (affichage == 1) {
        printf("Affichage de l'abreBK :\n");
        afficher_ArbreBK(dico);
    }

    /* Libération des listes chainées et de l'ATR */
    libere_ArbreBK(&(dico));
    liberer_Liste(&(erreurs));
    return 0;
}
