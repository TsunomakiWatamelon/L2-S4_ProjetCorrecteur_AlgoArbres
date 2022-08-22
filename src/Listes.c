/* Auteur : Gaël PAQUETTE & Hervé NGUYEN
 * Création : 09/03/2022
 * Dernière modification : 20/03/2022 */
/* Listes.c */

#include <Listes.h>

Cellule * allouer_Cellule(char * mot) {
    /*
    Fonction qui alloue de la place mémoire à une Cellule et initialise celle ci avec la chaine de caractère 'mot'(description par variable).
    
    Renvoie l'adresse de cette Cellule 'new_cell'.
    */
    Cellule * new_cell = (Cellule*)malloc(sizeof(Cellule));
    new_cell->mot = (char*)malloc(sizeof(char) * 31);
    if (new_cell == NULL){
        fprintf(stderr, "Listes (allouer_Cellule) : echec malloc");
        return NULL;
    }
    strcpy(new_cell->mot, mot);
    new_cell->next = NULL;
    return new_cell;
}

int inserer_en_tete(Liste * L, char * mot) {
    /*
    Fonction qui insère en tête de la Liste 'L' (passée par adresse) la cellule correspondant au mot 'mot'(description par variable)

    Renvoie 1 si l'opération est un succès
            0 si l'adresse de la nouvelle cellule est NULL (pas possible car allouer_Cellule termine le programme si malloc renvoie NULL)
    */
    Liste new;
    new = allouer_Cellule(mot);
    if (!new) return 0;
    new->next = *L;
    *L = new;
    return 1;
}

void liberer_Liste(Liste * L) {
    /*
    Fonction qui supprime la Liste 'L' (passée par adresse) et libère la mémoire.

    Renvoie rien
    */
    Liste tmp = *L;
    Liste tmp2;
    while(tmp != NULL){
        tmp2 = tmp;
        tmp = tmp->next;
        if (tmp2->mot != NULL) free(tmp2->mot);
        free(tmp2);
    }
    *L = NULL;
}

void afficher_Liste(Liste L) {
    /*
    Fonction qui affiche ligne par ligne les mots contenu dans la liste 'L'.

    Renvoie rien
    */
    Liste tmp = L;
    while (tmp != NULL){
        printf("%s\n", tmp->mot);
        tmp = tmp->next;
    }
}

int dans_Liste(Liste L, char *mot){
    /*
    Fonction qui vérifie si le mot/chaine de caractère 'mot'(description par variable) est contenu dans la Liste 'L'.

    Renvoie 1 si oui
            0 sinon
    */
    if (L == NULL) return 0;
    if (mot == NULL) return 0;
    if (strcmp(L->mot, mot) == 0) return 1;
    return dans_Liste(L->next, mot);
}
