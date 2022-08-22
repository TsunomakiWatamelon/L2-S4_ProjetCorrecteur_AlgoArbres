/* Auteur : Gaël PAQUETTE & Hervé NGUYEN
 * Création : 13/03/2022
 * Dernière modification : 20/03/2022 */
/* ATR.c */

#include <ATR.h>

ATR creer_ATR_vide(){
    /*
    Fonction qui renvoie un ATR vide
    */
    ATR new;
    new = NULL;
    return new;
}

ATR alloue_ATR_cellule(char lettre){
    /*
    Fonction qui alloue de la mémoire pour une cellule d'ATR.
    Affecte le char 'lettre' à la lettre correspondant à cette cellule.

    Renvoie l'adresse de cette cellule
    */
    ATR new = (ATR)malloc(sizeof(ATRcell));
    new->lettre = lettre;
    new->inf = NULL;
    new->mil = NULL;
    new->sup = NULL;
    return new;
}

void liberer_ATR_aux(ATR A){
    /*
    Fonction (auxilliaire) qui libere la mémoire occupée par l'ATR 'A'

    Renvoie rien
    */
    if (A == NULL) return;
    else {
        if (A->sup != NULL) liberer_ATR_aux(A->sup);
        if (A->mil != NULL) liberer_ATR_aux(A->mil);
        if (A->inf != NULL) liberer_ATR_aux(A->inf);
        free(A);
    }
}

void liberer_ATR(ATR * A){
    /*
    Fonction (principale) qui libere la mémoire occupée par l'ATR 'A'

    Renvoie rien
    */
    if (A == NULL) return;
    if (*A == NULL) return;
    liberer_ATR_aux(*A);
    *A = NULL;
}

int dans_ATR(ATR A, char *mot){
    /*
    Fonction qui permet de chercher dans l'ATR 'A' si le mot 'mot'(description par variable) est présent.

    Renvoie 1 si oui,
    0 sinon.
    */
    if (A == NULL) return 0;
    if (A->lettre > *mot)
        return dans_ATR(A->inf, mot);
    if (A->lettre < *mot)
        return dans_ATR(A->sup, mot);
    if (A->lettre == *mot) {
        if (*mot != '\0')
            return dans_ATR(A->mil, mot + 1); 
        else
            return 1;
    }
    return 0;
}

void ajoute_branche(ATR * A, char * mot) {
    /*
    Fonction qui ajoute une 'branche' dans l'ATR 'A' pour stocker le mot 'mot'(description par variable).
    Cette fonction est utilisée quand on se retrouve dans une portion vide d'un ATR,
    donc il suffit juste de créer ce qu'il reste du mot lors de l'utilisation de la fonction inserer_dans_ART.

    Renvoie rien
    */

    assert(A != NULL);

    /*
    if (A == NULL){
        fprintf(stderr, "ATR.c : A est NULL \n");
        exit(EXIT_FAILURE);
    }
    */

    *(A) = alloue_ATR_cellule(mot[0]);
    if (*A == NULL){
        fprintf(stderr, "ATR.c : echec malloc \n");
        exit(EXIT_FAILURE);
    }
    if (*mot != '\0') ajoute_branche(&((*A)->mil), mot + 1);
}

int inserer_dans_ATR(ATR * A, char * mot){
    /*
    Fonction qui insère dans l'ATR 'A' la chaine de caractère 'mot'(description par variable).

    Renvoie 1 si l'opération est un succès,
            2 si le mot est déjà present.
    */
    if (!(*A)){
        ajoute_branche(A, mot);
        return 1;
    }       
    if ((*A)->lettre > *mot)   /* La première lettre du noeud est plus petite que celle du mot selon l'ordre alphabétique alors on insere dans inf */
        return inserer_dans_ATR(&((*A)->inf), mot);
    if ((*A)->lettre < *mot)   /* La première lettre du noeud est plus grande que celle du mot selon l'ordre alphabétique alors on insere dans sup */
        return inserer_dans_ATR(&((*A)->sup), mot);
    else {   /* la première lettre du mot est égale à celle du noeud selon l'ordre alphabétique alor on insere dans mil */
        if (*mot != '\0')   /* Mot non présent dans l'arbre */
            return inserer_dans_ATR(&((*A)->mil), mot + 1); 
        else /* Mot déjà présent dans l'arbre */
            return 2;
    }
}

int supprimer_dans_ATR_aux(ATR * A, char * mot) {
    /*
    Fonction (auxiliaire) permet de supprimer le mot 'mot'(description par variable) de l'ATR passé par adresse 'A'.

    Renvoie 1 si il y a un chainage au delà de la cellule supprimée, on arrête le processus de suppression pour ne pas perdre d'information.
            2 si la cellule qui viens d'être supprimée (dans l'appel récursif) n'a pas de fils.
    
    La valeur de renvoie 2, permet de continuer la suppression au delà de la suppression simple de la cellule qui représente '\0' pour
    le mot 'mot'(description par variable).
    */
    ATR tmp;
    if (*mot == '\0') {
        if ((*A)->sup != NULL) {
            tmp = (*A)->sup;
            liberer_ATR_aux(*A);
            *A = tmp;
            return 1;
        }
        else return 2; /* il faut supprimer le lettre précédente */
    }
    if ((*A)->lettre < *mot)
        return supprimer_dans_ATR_aux(&((*A)->sup), mot);
    if ((*A)->lettre > *mot)
        return supprimer_dans_ATR_aux(&((*A)->inf), mot);
    if ((*A)->lettre == *mot)
        if (supprimer_dans_ATR_aux(&((*A)->mil), mot + 1) == 2) {
            if ((*A)->inf == NULL && (*A)->sup == NULL) {
                liberer_ATR_aux(*A);
                *A = NULL;
                return 2;
            } else 
                return 1;
        }
    return 0;
}

void supprimer_dans_ATR(ATR * A, char * mot) {
    /*
    Fonction (principale) permet de supprimer le mot 'mot'(description par variable) de l'ATR passé par adresse 'A'.

    Renvoie rien
    */
    assert(A != NULL);
    supprimer_dans_ATR_aux(A, mot);
}

void afficher_ATR_aux(ATR A, char buffer[], int indice) {
    /*
    Fonction (auxiliaire) qui permet d'afficher chaque mot dans l'ATR 'A'.

    On parcours de manière récursive l'ATR et dès qu'on trouve un '\0' on affiche le mot construit.

    Renvoie rien
    */
    if (A != NULL) {
        buffer[indice] = A->lettre;
        if (A->lettre == '\0')
            printf("%s\n", buffer);
        else 
            afficher_ATR_aux(A->mil, buffer, indice + 1);
        if (A->inf != NULL)
            afficher_ATR_aux(A->inf, buffer, indice);
        if (A->sup != NULL)
            afficher_ATR_aux(A->sup, buffer, indice);
    }
}

void afficher_ATR(ATR A) {
    /*
    Fonction (principale) qui permet d'afficher chaque mot dans l'ATR 'A'.

    Renvoie rien
    */
    char buffer[MAX_LETTRES];
    int courant = 0; /* case à remplir */

    if (!A) return;
    afficher_ATR_aux(A, buffer, courant);
}
