/* Auteur : Gaël PAQUETTE & Hervé NGUYEN
 * Création : 19/04/2022
 * Dernière modification : 23/04/2022 */
/* ArbreBK.c */

#include <ArbreBK.h>


/* Insertion */

int inserer_dans_ArbreBK_aux(ArbreBK *A, char* mot, int valeur){
    /*
        Fonction (auxilliaire, pour parcourir les noeuds qui ne sont pas la racine) qui permet d'insérer un élément (mot) dans un arbre BK,
        en utilisant la distance de Levenshtein.

        Renvoie 1 si l'insertion a été faite.
                0 si le mot est déjà présent
                -1 si il y a un échec au niveau du malloc.
    */
    int distance;
    assert(A != NULL);
    assert(mot != NULL);

    if (*A == NULL){
        *A = alloue_ArbreBK_cellule(mot, valeur);
        if (*A == NULL){
            fprintf(stderr, "inserer_dans_ArbreBK (aux) : echec insertion\n");
            return -1; /* Echec insertion */
        }
        return 1; /* Succes */
    }
    if (strcmp((*A)->mot, mot) == 0) return 0; /* Deja present */

    if (valeur == (*A)->valeur){
        distance = Levenshtein((*A)->mot, mot);
        return inserer_dans_ArbreBK_aux(&((*A)->filsG), mot, distance);
    }
    else return inserer_dans_ArbreBK_aux((&(*A)->frereD), mot, valeur);
}

int inserer_dans_ArbreBK(ArbreBK* A, char* mot){
    /*
        Fonction qui permet d'insérer un élément (mot) dans un arbre BK, en utilisant la distance de Levenshtein.

        Renvoie 1 si l'insertion a été faite.
                0 si le mot est déjà présent
                -1 si il y a un échec au niveau du malloc.
    */
    int distance;
    assert(A != NULL);
    assert(mot != NULL);
    if (*A == NULL){
        *A = alloue_ArbreBK_cellule(mot, 0);
        if (*A == NULL){
            fprintf(stderr, "inserer_dans_ArbreBK (main) : echec insertion\n");
            return -1; /* Echec insertion */
        }
        return 1; /* Succes */
    }
    if (strcmp((*A)->mot, mot) == 0) return 0; /* Deja present */

    distance = Levenshtein((*A)->mot, mot);
    return inserer_dans_ArbreBK_aux(&((*A)->filsG), mot, distance);
}


/* Vérification si un mot est dans l'Arbre BK */

int est_dans_ArbreBK_aux(ArbreBK A, char * mot, int valeur) {
    /*
    Fonction (auxiliaire) qui permet de chercher dans l'ArbreBK 'A' si le mot 'mot'(description par variable) est present.

    Renvoie un int : 0 si non.
                     1 si oui.
    */
    int distance;

    if (!A)
        return 0;
    if (strcmp(A->mot, mot) == 0)
        return 1;   /* Le mot est present */
    if (valeur == A->valeur) {
        distance = Levenshtein(A->mot, mot);
        return est_dans_ArbreBK_aux(A->filsG, mot, distance);
    }
    return est_dans_ArbreBK_aux(A->frereD, mot, valeur);
}

int est_dans_ArbreBK(ArbreBK A, char * mot) {
    /*
    Fonction (principale) qui permet de chercher dans l'ArbreBK 'A' si le mot 'mot'(description par variables) est present.

    Renvoie un int : 0 si non.
                     1 si oui.
    */
    int distance;

    if (!A)
        return 0;
    if (strcmp(A->mot, mot) == 0)
        return 1;   /* Le mot est present */
    distance = Levenshtein(A->mot, mot);
    return est_dans_ArbreBK_aux(A->filsG, mot, distance);
}


/* Création de l'arbre */

ArbreBK creer_ArbreBK(FILE* dico){
    /*
        Fonction qui lis un fichier 'dico' et insère l'ensemble des mots contenu dans ce fichier dans un Arbre BK.

        Renvoie cet ArbreBK
    */
    ArbreBK new = NULL;
    char mot_dico[31];

    while(fscanf(dico, "%s", mot_dico) != EOF){
        inserer_dans_ArbreBK(&new, mot_dico);
    }
    return new;
}


/* Libération de l'arbre */

void libere_ArbreBK_aux(ArbreBK A) {
    /*
    Fonction (auxiliaire) qui libère l'ArbreBK 'A' passé par adresse.

    Renvoie rien.
    */
    if (A == NULL) return;
    else {
        if (A->filsG != NULL) libere_ArbreBK_aux(A->filsG);
        if (A->frereD != NULL)  libere_ArbreBK_aux(A->frereD);
        free(A);
    }
}

void libere_ArbreBK(ArbreBK* A) {
    /* 
    Fonction (principale) qui libère l'ArbreBK 'A' passé par adresse.

    Renvoie rien.
    */
    if (A == NULL) return;
    if (*A == NULL) return;
    libere_ArbreBK_aux(*A);
    *A = NULL;
}


/* Allocation d'une cellule / noeud */

NoeudBK * alloue_ArbreBK_cellule(char* mot, int valeur) {
    /*
    Fonction qui alloue la place mémoire à une Cellule et initialise celle-ci à la chaine de caractère 'mot' et l'entier 'valeur'.

    Renvoie l'adresse de cette cellule 'new'. 
    */
    NoeudBK * new = (NoeudBK*)malloc(sizeof(NoeudBK));
    new->mot = (char*)malloc(sizeof(char) * 31);
    if (new == NULL) {
        fprintf(stderr, "ArbreBK (alloue_ArbreBK_cellule) : echec malloc\n");
        return NULL;
    }
    strcpy(new->mot, mot);
    new->valeur = valeur;
    new->filsG = NULL;
    new->frereD = NULL;
    return new;
}


/* Recherche */

int rechercher_dans_ArbreBK_aux(ArbreBK A, Liste* corrections, char* mot, int* seuil) {
    /*
    Fonction (auxiliaire) qui recherche une chaîne de caractère 'mot' dans l'ArbreBK 'A'.
    Et ajoute l'equivalent du mot présent dans l'ArbreBK 'A' dans la Liste 'corrections'.

    Renvoie un int:     0 si l'arbre est vide ou le mot n'existe pas.
                        1 sinon.
    */
    int distance;
    ArbreBK tmp;
    int res = 0;
    if (!A)
        return 0;
    else {
        distance = Levenshtein(A->mot, mot);
        if (distance <= *seuil) {
            if (distance < *seuil) {
                *seuil = distance;
                liberer_Liste(corrections);
            }
            inserer_en_tete(corrections, A->mot);
            res = 1;
        }
        if (A->filsG != NULL) {
            tmp = A->filsG;
            while (tmp != NULL) {
                if (abs(distance - tmp->valeur) <= *seuil){
                    if (!rechercher_dans_ArbreBK_aux(tmp, corrections, mot, seuil)) res = 1;
                }
                tmp = tmp->frereD;
            }
        }
        return res;
    }
}

Liste rechercher_dans_ArbreBK(ArbreBK A, char* mot) {
    /*
    Fonction (principale) qui recherche une chaîne de caractère 'mot' dans l'ArbreBK 'A'.
    Et ajoute l'equivalent du mot présent dans l'ArbreBK 'A' dans la Liste 'corrections'.

    Renvoie un int:     0 si l'arbre est vide ou le mot n'existe pas.
                        1 sinon.
    */
    Liste corrections = NULL;
    int seuil = 10;

    rechercher_dans_ArbreBK_aux(A, &(corrections), mot, &(seuil));
    return corrections;
}


/* Affichage */

void afficher_ArbreBK_aux(ArbreBK A, int profondeur) {
    /* 
    Fonction (auxiliaire) qui affiche l'ArbreBK 'A'.

    Renvoie rien.
    */
    ArbreBK tmp = A;
    int i;
    if (!tmp)
        return;
    else {
        printf("%s\n", tmp->mot);
        if (tmp->filsG != NULL) {
            for (i = 0; i < profondeur + 1; i++) printf("        ");
            printf("|--%d--> ", tmp->filsG->valeur);
            afficher_ArbreBK_aux(tmp->filsG, profondeur + 1);
        }
        if (tmp->frereD != NULL) {
            for (i = 0; i < profondeur; i++) printf("        ");
            printf("|--%d--> ", tmp->frereD->valeur);
            afficher_ArbreBK_aux(tmp->frereD, profondeur);
        }
    }
}

void afficher_ArbreBK(ArbreBK A) {
    /* 
    Fonction (principale) qui affiche l'ArbreBK 'A'.

    Renvoie rien.
    */
    int profondeur = -1;
    afficher_ArbreBK_aux(A, profondeur);
}


/* Affichage Graphique */

static void ecrireDebut(FILE* f) {
    /*
    Fonction qui ecrit le debut d'un fichier dot permettant
    de représenter un arbre.

    Renvoie rien.
    */
    fprintf(f, "digraph arbre {\n");
    fprintf(f, "    node [shape=record , height=.1]\n");
    fprintf(f, "    edge [tailclip=false , arrowtail = dot , dir=both];\n");
    fprintf(f, "    \n");
}

static void ecrire_ArbreBK_aux(FILE* f, ArbreBK A) {
    /* 
    Fonction qui écrit l'encodage de l'arbre dans le fichier dot.

    Renvoie rien.
    */
    ArbreBK tmp = A;

    if (!tmp)
        return;
    else {
        fprintf(f, "    n%p [label=\"<gauche> |{ <mot> %s | <valeur> %d }| <droit>\"];\n", (void*)A, A->mot, A->valeur);
        if ((A->filsG != NULL) || (A->frereD != NULL)) {
            if (A->filsG != NULL) {
                fprintf(f, "    n%p:gauche:c -> n%p:valeur;\n", (void*)A, (void*)(A->filsG));
                ecrire_ArbreBK_aux(f, A->filsG);
            }
            if (A->frereD != NULL) {
                fprintf(f, "    n%p:droit:c -> n%p:valeur;\n", (void*)A, (void*)(A->frereD));
                ecrire_ArbreBK_aux(f, A->frereD);
            }
        }
    }
}

static void ecrireFin(FILE* f) {
    /*
    Fonction qui ecrit la fin d'un fichier dot permettant de 
    représenter un arbre.

    Renvoie rien.
    */
    fprintf(f, "}\n");
}

static void dessine(FILE* out, ArbreBK a) {
    /*
    Fonction qui permet d'écrire un fichier dot.

    Renvoie rien.
    */
    ecrireDebut(out);
    ecrire_ArbreBK_aux(out, a);
    ecrireFin(out);
}

void afficher2_ArbreBK(char* dot, char* pdf, ArbreBK A) {
    /* 
    Fonction qui crée un pdf à partir du fichier dot de l'ArbreBK.

    Renvoie rien.
    */
    int len;
    FILE* out = fopen(dot, "w");
    dessine(out, A);
    fclose(out);
    len = strlen(dot) + strlen(pdf) + 15;
    char cmd[len];
    strcpy(cmd, "dot -Tpdf ");
    strcat(cmd, dot);
    strcat(cmd, " -o ");
    strcat(cmd, pdf);
    system(cmd);
}
