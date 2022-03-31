#ifndef _Horn_And_Schunk_h
#define _Horn_And_Schunk_h




typedef struct
{
    float** Ix;
    float** Iy;
    float** It;
    int dimX;
    int dimY;
} Gradient;



typedef struct
{
    float **U;
    float **V;
    int dimX;
    int dimY;
} Vitesses;




/**Fonction de creation des vecteurs vitesses U et V
  *@param dimX est le nombre de lignes dans la matrice
  *@param dimY est le nombre de colonnes dans la matrice
  */
Vitesses creation_vitesse (int dimX,int dimY);




/**Fonction de creation des vecteurs vitesses U et V
  *@param dimX est le nombre de lignes dans la matrice
  *@param dimY est le nombre de colonnes dans la matrice
  */
Gradient creation_gradient (int dimX, int dimY);




/** Fonction de calcul de la moyenne Ubar et Vbar
  * @param  U_Vbar est une marice de meme taille que l'image et represente Ubar ou Vbar
  * @param U_V est une matrice de meme taille que l'image et represente les matrices U et V
  * @param largeur represente le nombre de colonnes de la matrice (donc l'image)
  * @param longueur represente le nombre de lignes de la matrice(donc l'image)
  * @return Les matrices vitesse moyenne Ubar et Vbar
  */

void Calcul_U_V_Bar(float **U_Vbar,float **U_V, int largeur, int longueur);




/** Fonction de calcul des gradients Ix,Iy et It
  * @param  IM1 est la premiere image
  * @param IM2 est la deuxieme image (premiere image apres un temps t)
  * @param Ix gradient suivant l'axe x
  * @param Iy gradient suivant l'axe y
  * @param It gradient temporel
  * @param longueur est nombre de ligne de l'image
  * @param largeur est le nombre de colonnes de l'image
  * @return les matrices gradients Ix, Iy et It

  */

void Calcul_Gradient(float **IM1, float **IM2, Gradient* Grad);



/** Fonction de calcul des U et V
  * @param  U et V les matrices de vitesse
  * @param Ubar et Vbar les matrices des vitesses moyennes
  * @param Ix gradient suivant l'axe x
  * @param Iy gradient suivant l'axe y
  * @param It gradient temporel
  * @param alpha est un parametre pour calculer les vitesses
  * @param longueur est nombre de ligne de l'image
  * @param largeur est le nombre de colonnes de l'image
  * @param tolerance est une constante qui definit quand nos iterations s'arretent
  * @return les matrices vitesses U et V

  */

void Calcul_Vitesses_UV(Vitesses* Vit, Gradient* Grad,float **Ubar,float **Vbar,float tolerance);











#endif // _Horn_And_Schunk_h
