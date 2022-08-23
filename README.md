# L2-S4_ProjetCorrecteur_AlgoArbres
 
Project for "Algorithmique des Arbres" in 2nd year of Computer Science at Université Gustave Eiffel.
It is a basic text correction program that utilizes linked list and tree data structures such as BK trees, ternary search trees.

This project has 3 programs :
- `correcteur_0` with minimal functionalities where it only reports typos with a ternary search tree
- `correcteur_1` with correction suggestion using a ternary search tree
- `correcteur_2` with the same functionalities as the last program but with a lower complexity using a BK tree.

To look for the most accurate correction possible, the two last programs looks for words with the lowest possible Levenshtein distance to the typo in the dictionary.

## Compilation

To compile these 3 programs, use the makefile located at the root directory of this repo with the terminal. (Unix systems only)

```bash
make
```

## Usage

### Text file and dictionary file

1. The text file to scan should be a regular text file in ASCII

Example :

```
Mercedes, not happy, Red Bull would be delighted. They've had shared a brilliant championship battle, but the championship can only be won by one. AND IT'S GOING DUTCH IN 2021, MAX VERSTAPPEN FOR THE FIRST TIME EVER IS THE CHAMPION OF THE WORLD!
```

2. The dictionary file should have one word per line and end with an empty line

Example :

```
apres
avait
avec
banquette
cherbourg
classe
de
denise
deux
dure
debarquee
freres
gare
la
lazare
nuit
ou
passee
pied
saint
ses
sur
train
troisieme
un
une
venue
wagon
etait

```

3. Program arguments

- [text_file] is the name of the file in the current directory to scan for typos
- [dictionary_file] is the name of the dictionary file in the current directory

### correcteur_0

Run the program on the terminal in this manner : 
```bash
./correcteur_0 [text_file] [dictionary_file]
```

The behavior expected should similar to this example :
```bash
watame@MacBook-Air-de-Watame L2-S4_ProjetCorrecteur_AlgoArbres %  ./correcteur_0 a_corriger_1.txt dico_3.dico
Mot(s) mal orthographié(s) :
c
faix
foie
foit
```

### correcteur_1

Run the program on the terminal in this manner : 
```bash
./correcteur_1 [text_file] [dictionary_file]
```

The behavior expected should be similar to this example :
```bash
watame@MacBook-Air-de-Watame L2-S4_ProjetCorrecteur_AlgoArbres %  ./correcteur_1 a_corriger_1.txt dico_3.dico
Mot mal orthographié : faix
paix, faux, fait, fais, faim
Mot mal orthographié : foie
voie, soie, oie, noie, joie, folie, fois, foire, foi
Mot mal orthographié : c
ca, y, x, v, s, i, ca, ci, ce, ca, a
Mot mal orthographié : faix
paix, faux, fait, fais, faim
Mot mal orthographié : foie
voie, soie, oie, noie, joie, folie, fois, foire, foi
Mot mal orthographié : foit
voit, toit, soit, fout, fort, font, fois, foi, fit, fait, doit, boit
```

### correcteur_2

First, this program can be run the same way as the previous one. The difference being the performance over bigger files.

There is two additional functionalities that shows the BK tree generated for the dictionnary :

- The BK tree is visualized on the terminal

Run the program in this manner : 
```bash
./correcteur_2 -a [dictionary_file]
```

A BK tree will be shown like this :

```bash
watame@MacBook-Air-de-Watame L2-S4_ProjetCorrecteur_AlgoArbres %  ./correcteur_2 -a dico_1.dico
Affichage de l'abreBK :
apres
|--4--> avait
        |--5--> de
                |--5--> passee
                |--3--> sur
                |--2--> une
        |--4--> lazare
|--3--> avec
        |--4--> dure
        |--5--> freres
        |--3--> gare
                |--4--> pied
                        |--3--> ses
|--7--> banquette
        |--5--> debarquee
|--8--> cherbourg
        |--9--> troisieme
|--5--> classe
        |--4--> denise
                |--6--> la
        |--6--> deux
                |--4--> nuit
                |--3--> ou
                        |--2--> un
        |--5--> saint
                |--3--> train
                        |--3--> etait
                |--5--> venue
                |--4--> wagon
```

Where the number represents the Levenshtein distance between the current word and it's parent. The explanation of how the BK Tree is contructed is in the 3rd project report in the `doc` directory.

- The BK tree is drawn in a .pdf file and opens it on evince (evince and graphviz should be installed

Run the program in this manner : 
```bash
./correcteur_2 -g [dictionary_file]
```
