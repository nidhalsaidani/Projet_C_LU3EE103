#include "Horn_And_Schunk.h"
#include "operation_matrice.h"

#define alpha 0.5


/**Fonction de creation des vecteurs vitesses U et V
  *@param dimX est le nombre de lignes dans la matrice
  *@param dimY est le nombre de colonnes dans la matrice
  */
Vitesses creation_vitesse (int longueur,int largeur)
{
    Vitesses Vit;
    Vit.U = Create_Mat(longueur,largeur);
    Vit.V = Create_Mat(longueur,largeur);
    Vit.dimX = longueur;
    Vit.dimY = largeur;

    return Vit;

}


/**Fonction de creation des vecteurs vitesses U et V
  *@param dimX est le nombre de lignes dans la matrice
  *@param dimY est le nombre de colonnes dans la matrice
  */
Gradient creation_gradient (int longueur, int largeur)
{
    Gradient Grad;
    Grad.Ix = Create_Mat(longueur,largeur);
    Grad.Iy = Create_Mat(longueur,largeur);
    Grad.It = Create_Mat(longueur,largeur);
    Grad.dimX = longueur;
    Grad.dimY = largeur;

    return Grad;
}



/** Fonction de calcul de la moyenne Ubar et Vbar
  * @param  U_Vbar est une marice de meme taille que l'image et represente Ubar ou Vbar
  * @param U_V est une matrice de meme taille que l'image et represente les matrices U et V
  * @param largeur represente le nombre de colonnes de la matrice (donc l'image)
  * @param longueur represente le nombre de lignes de la matrice(donc l'image)
  * @return Les matrices vitesse moyenne Ubar et Vbar
  */


void Calcul_U_V_Bar(float **U_Vbar,float **U_V, int longueur, int largeur)
{
    int i,j;


    for(i=1; i<longueur-1; i++)
    {
        for(j=1; j<largeur-1; j++)
        {
            U_Vbar[i][j] = (1.0/8)*(U_V[i-1][j-1] + U_V[i-1][j] + U_V[i-1][j+1] + U_V[i][j-1] + U_V[i][j+1]
                                    + U_V[i+1][j-1] + U_V[i+1][j] + U_V[i+1][j+1]);
        }
    }

    U_Vbar[0][0] = (1.0/3)*(U_V[0][1] + U_V[1][0] + U_V[1][1]);
    U_Vbar[longueur-1][0] = (1.0/3)*(U_V[longueur-2][0] + U_V[longueur-2][1] + U_V[longueur-1][1]);
    U_Vbar[0][largeur-1] = (1.0/3)*(U_V[0][largeur-2] + U_V[1][largeur-2] + U_V[1][largeur-1]);
    U_Vbar[longueur-1][largeur-1] = (1.0/3)*(U_V[longueur-2][largeur-1] + U_V[longueur-1][largeur-2] + U_V[longueur-2][largeur-2]);


    for(j=1; j<largeur-1 ; j++)
    {
        U_Vbar[0][j] = (1.0/5)*(U_V[0][j-1] + U_V[0][j+1] + U_V[1][j-1] + U_V[1][j] + U_V[1][j+1] );
        U_Vbar[longueur-1][j] = (1.0/5)*(U_V[longueur-1][j-1] + U_V[longueur-1][j+1] + U_V[longueur-2][j-1] + U_V[longueur-2][j] + U_V[longueur-2][j+1] );
    }

    for(i=1; i<longueur-1; i++)
    {
        U_Vbar[i][0] = (1.0/5)*(U_V[i-1][0] + U_V[i+1][0] + U_V[i-1][1] + U_V[i][1] + U_V[i+1][1] );
        U_Vbar[i][largeur-1] = (1.0/5)*(U_V[i-1][largeur-1] + U_V[i+1][largeur-1] + U_V[i-1][largeur-2] + U_V[i][largeur-2] + U_V[i+1][largeur-2] );

    }

}



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
void Calcul_Gradient(float **IM1, float **IM2, Gradient* Grad)
{
    int i,j;
    int longueur,largeur;
    longueur = Grad->dimX;
    largeur  = Grad ->dimY;

    for(i=0 ; i<longueur ; i++)
    {
        for(j=0 ; j<largeur ; j++)
        {
            if(j==0)
            {
                Grad->Ix[i][j]=IM1[i][1]-IM1[i][0];
            }
            else if (j==largeur-1)
            {
                Grad->Ix[i][j]=IM1[i][largeur-1]-IM1[i][largeur-2];
            }
            else
            {
                Grad->Ix[i][j]=0.5*(IM1[i][j+1]-IM1[i][j-1]);
            }

            if(i==0)
            {
                Grad->Iy[i][j]=IM1[1][j]-IM1[0][j];
            }
            else if(i==longueur-1)
            {
                Grad->Iy[i][j]=IM1[longueur-1][j]-IM1[longueur-2][j];
            }
            else
            {
                Grad->Iy[i][j]=0.5*(IM1[i+1][j]-IM1[i-1][j]);
            }

            Grad->It[i][j]=IM2[i][j]-IM1[i][j];
        }
    }
}





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
void Calcul_Vitesses_UV(Vitesses* Vit, Gradient* Grad,float **Ubar,float **Vbar,float tolerance)
{
    int i,j;
    int longueur,largeur;
    longueur = Vit->dimX;
    largeur = Vit->dimY;

    float condition_arret1,condition_arret2;
    float **tmp1 = Create_Mat(longueur,largeur);
    float **tmp2 = Create_Mat(longueur,largeur);


    condition_arret1 = tolerance + 1.0;
    condition_arret2 = tolerance + 1.0;

    do
    {


        condition_arret1 = 0;
        condition_arret2 = 0;

        for(i=0; i<longueur; i++)
        {
            for(j=0; j<largeur; j++)
            {


                Vit->V[i][j] = Vbar[i][j] + (-Grad->Iy[i][j]*(Grad->Ix[i][j]*Ubar[i][j]+Grad->Iy[i][j]*Vbar[i][j]+Grad->It[i][j]))/(alpha + Grad->Ix[i][j]*Grad->Ix[i][j]+Grad->Iy[i][j]*Grad->Iy[i][j]);
                Vit->U[i][j] = Ubar[i][j] + (-Grad->Ix[i][j]*(Grad->Ix[i][j]*Ubar[i][j]+Grad->Iy[i][j]*Vbar[i][j]+Grad->It[i][j]))/(alpha + Grad->Ix[i][j]*Grad->Ix[i][j]+Grad->Iy[i][j]*Grad->Iy[i][j]);
                condition_arret1+= abs(Vit->U[i][j]-tmp1[i][j]);
                condition_arret2+= abs(Vit->V[i][j]-tmp2[i][j]);
                tmp1[i][j]=Vit->U[i][j];
                tmp2[i][j]=Vit->V[i][j];


            }


        }

        Calcul_U_V_Bar(Ubar,Vit->U,longueur,largeur);
        Calcul_U_V_Bar(Vbar,Vit->V,longueur,largeur);



    }
    while(condition_arret1>tolerance || condition_arret2>tolerance);


}







