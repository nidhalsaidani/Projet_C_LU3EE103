#include "filtreGaussien.h"
#include "operation_matrice.h"

/** Fonction de produit de matrice terme à terme
  * @param  mat1 et mat2 matrice
  * @param x et y longeur et largeur de la matrice
  * @return le produit de la matrice terme à terme
  */
float** prod_mat_termeaterme (float** mat1, float** mat2, int dimX, int dimY)
{
    float** matr = Create_Mat(dimX,dimY);
    int i, j;
    for (i=0; i<dimX; i++)
    {
        for (j=0; j<dimY; j++)
        {
            matr[i][j]= mat1[i][j]*mat2[i][j];
        }
    }
    return matr;
}


/** Fonction de calcul de la gaussienne
  * @param x et y longeur et largeur de la matrice
  * @return le coefficient gaussien
  */
float gaussienne (int x, int y)
{
    float g = exp(-(x*x + y*y)/(2*sigma*sigma));
    g = g/ 2*pi*sigma*sigma ;
    return g;
}


/** Fonction de calcul du filtre gaussien
  * @param sig est le sigma du filtre
  * @return le filtre gaussien de taille sigma*6+1
  */
//Coeff le nombre generale de la taille de la fenetre de chaque coté de sigma (sig)
float** filtre_gauss (int sig)
{
    int taille = (sig*Coeff)+1;
    float** fgauss = Create_Mat(taille, taille);
    int fenetre[taille];
    int e = -1 *(Coeff*sig/2); // indice pour les valeurs de le fenetre
    float som =0; // on fait la normalisation du filtre pour que la somme de ses coefficient soit egale a 1
    int i, j;
    //calcul des coefficient de la fenetre soit de [-3*sigma ; 3*sigma]
    for (i=0; i<taille; i++)
    {
        fenetre[i]=e ;
        e++;
    }
    for (i=0; i<taille; i++)
    {
        for(j=0; j<taille; j++)
        {
            fgauss[i][j]= gaussienne(fenetre[i], fenetre[j]);
            som = som+ fgauss[i][j] ;
        }
    }

    return fgauss ;
}


/** Fonction booléen permettant de savoir si l'indice de la matrice est sur le bord
  * @param *i et *j pointeur sur les indices de la matrice
  * @param x et y la taille de la matrice
  * @return 1 ou 0 selon si l'indice est sur le bord de la matrice ou non.
  */
//condition des indices pour eviter les effets de bords
int b(int *i, int* j, int dimX, int dimY)
{

    if (*i<0 )
    {
        *i=0;
        return 0;
    }
    if (*j<0)
    {
        *j = 0;
        return 0;
    }
    if (*i>=dimX)
    {
        *i=dimX-1;
        return 0;
    }
    if (*j>=dimY)
    {
        *j=dimY-1;
        return 0;
    }
    return 1;

}



/** Fonction de convolution d'un pixel de l'image
  * @param dimf dimension du filtre gaussien
  * @param imResult pixel de l'image résultat
  * @param i et j les indice de l'image resultat
  * @param x et y la taille de l'image (longueur, largeur respectivement)
  * @param image est la matrice de l'image
  * @param filt est la matrice du filtre gaussien
  * @return le pixel convoluer de l'image
  */
//calcul de convolution d'un pixel
float conv1terme (int dimF,float imResult, int i, int j, int dimX, int dimY, float** image, float**filt)
{
    int h, v;
    int bol=0; //booleen pour les bords
    int i2, j2;
    int cx=(dimF-1)/2*(-1);
    int cy=-1*(dimF-1)/2*(-1); // indice des cotés du filtre [-3*signma ; 3*simga]
    for(h=dimF-1; h>=0; h--)  // l'image est convolué avec la transposé du filtre
    {
        cy=(dimF-1)/2*(-1);
        for (v=dimF-1; v>=0; v--)
        {
            i2 = i+cx;
            j2 = j+cy;
            bol=b(&i2, &j2, dimX, dimY) ; // si b=0 on passe à l'indice suivant
            if (bol==1)  //aucune modif a ete faites sur les indices
            {
                imResult += (filt[h][v] * image[i2][j2] ) ;
            }
            cy++ ;
        }
        cx++;
    }
    return imResult;
}



/** Fonction de convolution de l'image
  * @param image est la matrice de l'image
  * @param filtgauss est la matrice du filtre gaussien
  * @param x et y la taille de l'image (longueur, largeur respectivement)
  * @param dimf dimension du filtre gaussien
  * @return l'image convoluer avec un filtre
  */
//calcul du produit de convolution de matrice avec un filtre de taille dimf=6*sigma+1
float** convolution(float** image, float** filt, int dimX, int dimY, int dimF)
{
    float** imResult = Create_Mat(dimX, dimY);
    int i, j;
    for (i=0; i<dimX; i++)  //on commence par 1 pour eviter les effets de bord
    {
        for(j=0; j<dimY; j++)
        {
            imResult[i][j]= conv1terme(dimF, imResult[i][j], i, j, dimX, dimY, image, filt);
        }
    }

    return imResult ;
}



/** Fonction de resolution de U et V avec la convolution du filtre Gaussien
  * @param image est la matrice de l'image
  * @param filtgauss est la matrice du filtre gaussien
  * @param x et y la taille de l'image (longueur, largeur respectivement)
  * @param dimf dimension du filtre gaussien
  * @return le struct UV qui est composé de la vitesse u et v
  */
//resolution du systeme avec le calcul de u et v
UV resolutionUV(float** ubar, float** vbar, float** Ix, float** Iy, float** It, float** W, int dimX, int dimY, int dimF, float tolerance)
{
    float** u = Create_Mat(dimX,dimY);
    float** v = Create_Mat(dimX,dimY);
    UV res = {u,v};
    // calcul des produit de matrice terme a terme
    float** IxIx= prod_mat_termeaterme(Ix,Ix,dimX,dimY);
    float** IyIy= prod_mat_termeaterme(Iy,Iy,dimX,dimY);
    float** IxIy= prod_mat_termeaterme(Ix,Iy,dimX,dimY);
    float** IyIt= prod_mat_termeaterme(Iy,It,dimX,dimY);
    float** IxIt= prod_mat_termeaterme(Ix,It,dimX,dimY);

    //calcul des convolution avec les matrices
    float** Ix2W= convolution(IxIx,W,dimX,dimY,dimF);
    float** Iy2W= convolution(IyIy,W,dimX,dimY,dimF);
    float** IxIyW= convolution(IxIy,W,dimX,dimY,dimF);
    float** IyItW= convolution(IyIt,W,dimX,dimY,dimF);
    float** IxItW= convolution(IxIt,W,dimX,dimY,dimF);

    float denomi=0; // denomiteur de l'eaquation
    float numU = 0; // numerateur pour l'equation de la vitesse u
    float numV = 0; // numerateur pour l'equation de la vitesse v

    float condition_arret1,condition_arret2;
    float **tmp1 = Create_Mat(dimX,dimY);
    float **tmp2 = Create_Mat(dimX,dimY);

    condition_arret1 = tolerance + 1.0;
    condition_arret2 = tolerance + 1.0;
    int i, j;
// calcul des vitesses comme pour la méthode de horn & schunk
    do
    {
        condition_arret1 = 0;
        condition_arret2 = 0;

        for(i=0; i<dimX; i++)
        {
            for(j=0; j<dimY; j++)
            {

                denomi= alpha + Iy2W[i][j] + Ix2W[i][j];
                numU = IxItW[i][j] + vbar[i][j]*IxIyW[i][j] + ubar[i][j]*Ix2W[i][j];
                res.u[i][j] = ubar[i][j] - (numU/denomi) ;
                numV = ubar[i][j]*IxIyW[i][j] + vbar[i][j]*Iy2W[i][j] + IyItW[i][j] ;
                res.v[i][j] = vbar[i][j] - (numV/denomi) ;

                condition_arret1+= abs(res.u[i][j]-tmp1[i][j]);
                condition_arret2+= abs(res.v[i][j]-tmp2[i][j]);
                tmp1[i][j]=res.u[i][j];
                tmp2[i][j]=res.v[i][j];

            }
        }
        Calcul_U_V_Bar(ubar,res.u,dimX,dimY);
        Calcul_U_V_Bar(vbar,res.v,dimX,dimY);
    }
    while(condition_arret1>tolerance || condition_arret2>tolerance);


    return res ;
}
