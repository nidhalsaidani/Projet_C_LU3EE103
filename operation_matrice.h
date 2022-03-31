#ifndef _operation_matrice_h_
#define _operation_matrice_h_

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "myBmpGris.h"


/** Fonction de creation d'une matrice
  * @param x est le nombre de lignes de la matrice
  * @param y est le nombre de colonnes de la matrice
  * @return une matrice de dimensions x et y
  */
float** Create_Mat (int dimX, int dimY);



/** Fonction de liberation de la matrice en memoire
  * @param  mat est la matrice a liberer
  * @param x est le nombre de lignes de matrice, une seule dimension est necessaire pour liberer la matrice
  */
void libere_mat (float*** mat, int dimX);



/** Fonction d'affichage d'une matrice
  * @param  mat est la matrice a afficher
  * @param  x est le nombre de ligne de la matrice mat
  * @param  y est le nombre de colonnes de la matrice mat
  * @return liberation de la matrice
  */
void affiche_mat (float** mat, int dimX, int dimY);



/** Fonction de lecture de la matrice
  * @param  fname est le nom du fichier texte ou est stockee la marice
  * @return la lecture du fichier texte
  */
float** readmat (char* fname);



/** Fonction d'ecriture de la matrice dans un fichier texte
  * @param  fname est le nom du fichier texte a creer et ou ecrire la matrice
  * @param mat est la matrice a ecrire dans le fichier texte
  * @param n est le nombre de lignes de la matrice
  * @param m est le nombre de colonnes de la matrice
  * @return fichier texte dans laquelle est ecrit la matrice
  */
void writemat(char* fname, float** mat, int dimX, int dimY);

#endif // _operation_matrice_h_
