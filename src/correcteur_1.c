/* Auteur : Gaël PAQUETTE & Hervé NGUYEN
 * Création : 13/03/2022
 * Dernière modification : 20/03/2022 */
/* Main.c */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#include <Listes.h>
#include <ATR.h>
#include <Levenshtein.h>

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

static void suggestion(char * m, const char * fichier, Liste *correction) {
    /* 
    Fonction qui détermine des suggestions de corrections du mot mal orthographiés en utilisant la distance de Levenshtein.
    Modifie la Liste "correction" reçue par addresse.

    Renvoie rien.
    */
    char mot[MAX_LETTRES];
    int distance = 50000, dmin = 50000;
    FILE * fichier_dico;

    fichier_dico = fopen(fichier, "r");
    *correction = NULL;

    while (fscanf(fichier_dico, "%s", mot) != EOF) {
        distance = Levenshtein(mot, m);
        if (distance <= dmin) {
            if (distance < dmin) {
                dmin = distance;
                liberer_Liste(correction);
            }
            inserer_en_tete(correction, mot);
        }
    }
    fclose(fichier_dico);
}

static void affiche_propositions(Liste correction){
    /*
    Fonction qui affiche l'ensemble des mots en propositions de correction contenus dans la Liste "correction".

    Renvoie rien.
    */
    Liste tmp = correction;
    while (tmp != NULL){
        fprintf(stdout, "%s", tmp->mot);
        if (tmp->next != NULL) fprintf(stdout, ", ");
        tmp = tmp->next;
    }
    fprintf(stdout, "\n");
}

static void affiche_correction(Liste *erreurs, const char *fichier){
    /* 
    Fonction qui affiche les suggestions proposé pour chaque mots présents dans la liste 'erreurs'

    Renvoie rien.
    */ 
    Liste correction = NULL;
    Liste tmp = *erreurs;

    while(tmp != NULL){
        suggestion(tmp->mot, fichier, &(correction));
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
    */
    FILE *fichier_dico;
    FILE *fichier_texte;
    int erreur_open;
    Liste erreurs;
    ATR dico;
    const char* fichier;
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
    fichier = argv[2];
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
    fclose(fichier_dico);

    while (fscanf(fichier_texte, "%s[^.]", mot_texte_raw) != EOF) {
        sscanf(mot_texte_raw, "%30[^.,'’;]", mot_texte);
        strlower(mot_texte);
        if (!dans_ATR(dico, mot_texte)) {
            inserer_en_tete(&erreurs, mot_texte);
        }
    }
    fclose(fichier_texte);
    
    /* Affichage des correction pour les mots mal orthographiés */
    affiche_correction(&(erreurs), fichier);

    /* Libération des listes chainées et de l'ATR */
    liberer_ATR(&(dico));
    liberer_Liste(&(erreurs));
    return 0;
}
