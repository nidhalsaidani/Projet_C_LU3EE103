#ifndef _filtreGaussien_h_
#define _filtreGaussien_h_

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define sigma 1
#define pi 3.14159265359
#define alpha 0.5

#define Coeff 6 // constante de la taille du filtre gaussien

typedef struct
{
    float** u;
    float** v;
} UV;

/** Fonction de produit de matrice terme à terme
  * @param  mat1 et mat2 matrice
  * @param x et y longeur et largeur de la matrice
  * @return le produit de la matrice terme à terme
  */
float** prod_mat_termeaterme (float** mat1, float** mat2, int dimX, int dimY);


/** Fonction de calcul de la gaussienne
  * @param x et y longeur et largeur de la matrice
  * @return le coefficient gaussien
  */
float gaussienne (int x, int y);



/** Fonction de calcul du filtre gaussien
  * @param sig est le sigma du filtre
  * @return le filtre gaussien de taille sigma*6+1
  */
float** filtre_gauss (int sig); // sig pour definir la taille de la matrice [-3*sig ; 3*sig]


/** Fonction booléen permettant de savoir si l'indice de la matrice est sur le bord
  * @param *i et *j pointeur sur les indices de la matrice
  * @param x et y la taille de la matrice
  * @return 1 ou 0 selon si l'indice est sur le bord de la matrice ou non.
  */
int b(int *i, int* j, int dimX, int dimY);


/** Fonction de convolution d'un pixel de l'image
  * @param dimf dimension du filtre gaussien
  * @param imResult pixel de l'image résultat
  * @param i et j les indice de l'image resultat
  * @param x et y la taille de l'image (longueur, largeur respectivement)
  * @param image est la matrice de l'image
  * @param filt est la matrice du filtre gaussien
  * @return le pixel convoluer de l'image
  */
float conv1terme (int dimF,float imResult, int i, int j, int dimX, int dimY, float** image, float**filt);


/** Fonction de convolution de l'image
  * @param image est la matrice de l'image
  * @param filtgauss est la matrice du filtre gaussien
  * @param x et y la taille de l'image (longueur, largeur respectivement)
  * @param dimf dimension du filtre gaussien
  * @return l'image convoluer avec un filtre
  */
float** convolution(float** image, float** filtgauss, int dimX, int dimY, int dimF);


/** Fonction de resolution de U et V avec la convolution du filtre Gaussien
  * @param image est la matrice de l'image
  * @param filtgauss est la matrice du filtre gaussien
  * @param x et y la taille de l'image (longueur, largeur respectivement)
  * @param dimf dimension du filtre gaussien
  * @return le struct UV qui est composé de la vitesse u et v
  */
UV resolutionUV (float** ubar, float**vbar, float** Ix, float** Iy, float** It, float** W, int dimX, int dimY, int dimF, float tolerance);


#endif // _filtreGaussien_h_
