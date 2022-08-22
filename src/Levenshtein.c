/* Auteur : Gaël PAQUETTE & Hervé NGUYEN
 * Création : 31/03/2022
 * Dernière modification : 31/03/2022 */
/* Levenshtein.c */

#include <Levenshtein.h>

void affiche_erreur_exit(char * msg){
    /*
    Fonction qui affiche un message d'erreur sur la sortie d'erreur et quitte le programme.

    Renvoie rien.
    */
    assert(msg != NULL);
    fprintf(stderr, "Module Levenshtein %s\n", msg);
    exit(1);
}

int **init_distance(int len_un, int len_deux){
    /* 
    Fonction qui initialise sur le tas un tableaux à deux dimensions permettant de
    calculer la distance de Levenshtein de deux mots de longueur "len_un" et "len_deux"

    Renvoie un int ** : distance. (Le tableau en question)
    */
    int i, j;
    int **distance;

    assert(len_un > 0);
    assert(len_deux > 0);
    
    distance = (int**)malloc(sizeof(int*) * (len_un + 1));
    if (distance == NULL) affiche_erreur_exit("(init_distance) : echec malloc 1");

    for (i = 0; i <= len_un; i++){
        distance[i] = (int*)malloc(sizeof(int) * (len_deux + 1));
        if (distance[i] == NULL) affiche_erreur_exit("(init_distance) : echec malloc 2");
        distance[i][0] = i;
    }
    for (j = 0; j <= len_deux; j++){
        distance[0][j] = j;
    }
    return distance;
}

int **init_cout(char *un, char *deux, int len_un, int len_deux){
    /*
    Fontion qui initialise sur le tas un tableau à deux dimensions qui permet de représenter
    les coût de substitutions entre chaque lettre de "un" et "deux".

    Renvoie un int ** : cout (Le tableau en question)
    */
    int i, j;
    int **cout;

    assert(un != NULL);
    assert(deux != NULL);
    assert(len_un > 0);
    assert(len_deux > 0);

    cout = (int**)malloc(sizeof(int*) * (len_un));
    if (cout == NULL) affiche_erreur_exit("(init_cout) : echec malloc 1");

    for (i = 0; i < len_un; i++){

        cout[i] = (int*)malloc(sizeof(int) * (len_deux));
        if (cout[i] == NULL) affiche_erreur_exit("(init_cout) : echec malloc 2");

        for (j = 0; j < len_deux; j++){
            if (un[i] == deux[j]) cout[i][j] = 0;
            else cout[i][j] = 1;
        }
    }
    return cout;
}

int min2(int a, int b){
    /* 
    Fonction qui renvoie le minimun entre deux nombre 'a' et 'b':

    Renvoie un int : minimun des deux nombres.
    */
    if (a < b) return a;
    return b;
}

int min3(int a, int b, int c){
    /*
    Fonction qui renvoie le minimun entre trois nombre 'a', 'b' et 'c'.

    Renvoie un int : minimun des trois nombres.
    */
    return min2(a, min2(b , c));
}

int Levenshtein(char * un, char *deux){
    /* 
    Fonction qui calcul et renvoie la distance de Levenshtein entre deux mot 'un' et 'deux'.
    Cette distance est une distance mathématique entre deux chaînes de caractères qui représente le nombre minimum d'opération
    pour passer de la chaine "un" à "deux".

    Renvoie un in : distance de Levenshtein.
    */
    int **distance;
    int **cout;
    int len_un, len_deux;
    int i, j;
    int res;

    assert(un != NULL);
    assert(deux != NULL);

    len_un = strlen(un);
    len_deux = strlen(deux);

    distance = init_distance(len_un, len_deux);
    cout = init_cout(un, deux, len_un, len_deux);

    for (i = 1; i <= len_un; i++){
        for(j = 1; j <= len_deux; j++){
            distance[i][j] = min3(distance[i - 1][j - 1] + cout[i - 1][j - 1], distance[i][j - 1] + 1, distance[i - 1][j] + 1);
        }
    }

    res = distance[len_un][len_deux];

    for (i = 0; i <= len_un; i++){
        free(distance[i]);
    }
    free(distance);

    for (i = 0; i < len_un; i++){
        free(cout[i]);
    }
    free(cout);


    return res;
}

