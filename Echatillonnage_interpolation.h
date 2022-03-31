#ifndef _Echantillonnage_interpolation_h_
#define _Echantillonnage_interpolation_h_

#include<stdio.h>
#include<stdlib.h>
#include<math.h>



/** fonction de sous_echantillonnage de l'image en reduisant les dimensions de la matrice
    * @param Image est la matrice de l'image qu'on souhaite sous echantillonner
    * @param longueur est le nombre de lignes de la matrice image
    * @param largeur est le nombre de colonnes de la matrice image
    */
float **Sous_Echantillonnage(float **Image,int longueur,int largeur);




/** fonction de sur echantillonnage de l'mage en utilisant l'interpolation bilenaire pour retrouver les dimensions initiales
    * @param Echantillon est l'image sous echantillonnee precedemment
    * @param dimXe est le nombre de lignes de la matrice Echantillon
    * @param dimYe est le nombre de colonnes de la matrice Echantillon
    */

float **Sur_Echantillonnage(float **Echantillon,int dimXe,int dimYe);



#endif
