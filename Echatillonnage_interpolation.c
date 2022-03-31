#include "Echatillonnage_interpolation.h"



/** fonction de sous_echantillonnage de l'image en reduisant les dimensions de la matrice
    * @param Image est la matrice de l'image qu'on souhaite sous echantillonner
    * @param longueur est le nombre de lignes de la matrice image
    * @param largeur est le nombre de colonnes de la matrice image
    */

// Reduction des dimensions d'une matrice d'un facteur 2 et echantillonnage

float **Sous_Echantillonnage(float **Image,int longueur,int largeur)
{
    int dimXe,dimYe;
    int i,j;

    if(longueur%2 != 0)
        dimXe = (longueur/2) +1;
    else
        dimXe = longueur/2;
    if(largeur%2 != 0)
        dimYe = (largeur/2) + 1;
    else
        dimYe = largeur/2;

    float **Echantillon = Create_Mat(dimXe,dimYe);

    for(i=0; i<dimXe; i++)
    {
        for(j=0; j<dimYe; j++)
        {
            Echantillon[i][j] = Image[i*2][j*2];
        }

    }

    return Echantillon;
}





/** fonction de sur echantillonnage de l'mage en utilisant l'interpolation bilenaire pour retrouver les dimensions initiales
    * @param Echantillon est l'image sous echantillonnee precedemment
    * @param dimXe est le nombre de lignes de la matrice Echantillon
    * @param dimYe est le nombre de colonnes de la matrice Echantillon
    */
//Interpolation pour agrandir l'image d'un facteur 2

float **Sur_Echantillonnage(float **Echantillon,int dimXe,int dimYe)
{
    int longueur,largeur;
    int dimX_impair,dimX_pair,dimY_impair,dimY_pair;
    int i,j,k=0,s=0;


    if(dimXe%2 != 0)
        longueur = 2*dimXe-1;
    else
        longueur = 2*dimXe;
    if(dimYe%2 != 0)
        largeur = 2*dimYe-1;
    else
        largeur = 2*dimYe;



    float **Image = Create_Mat(longueur,largeur);

    for(i=0; i<dimXe; i++)
    {
        s=0;
        for(j=0; j<dimYe; j++)
        {
            Image[i*2][j*2] = Echantillon[k][s];
            s++;
        }
        k++;
    }



    if((longueur%2 !=0) && (largeur%2 !=0))
    {
        for(i=0; i<longueur; i++)
        {
            for(j=0; j<largeur; j++)
            {
                if ( (i%2 == 0) && (j%2 !=0) )   //Sur les lignes paires et colonnes impaires
                {
                    Image[i][j] = (Image[i][j-1] + Image[i][j+1])/(2.0);

                }
                else if ( (i%2!=0) && (j%2==0) )   //Sur les lignes impaires et colonnes paires
                {
                    Image[i][j] = (Image[i+1][j] + Image[i-1][j])/(2.0);
                }
                else if ( (i%2!=0) && (j%2!=0))   //Pixel entouré par 4 pixels en diagonale
                {
                    Image[i][j] = (Image[i-1][j-1] + Image[i-1][j+1] + Image[i+1][j-1] + Image[i+1][j+1])/(4.0);
                }
            }
        }
    }
    if((longueur%2)==0 && (largeur%2)==0)
    {
        for(i=0; i<longueur; i++)
        {
            for(j=0; j<largeur; j++)
            {
                if ( (i%2)== 0 && (j%2)!=0 )  //Sur les lignes paires et colonnes impaires
                {
                    if(j == largeur-1)
                    {
                        Image[i][j] = (Image[i][j-1])/(2.0);
                    }
                    else
                    {
                        Image[i][j] = (Image[i][j-1] + Image[i][j+1])/(2.0);
                    }
                }
                else if ( (i%2)!=0 && (j%2)==0 )   //Sur les lignes impaires et colonnes paires
                {
                    if(i == longueur-1)
                    {
                        Image[i][j] = Image[i-1][j]/(2.0);
                    }
                    else
                    {
                        Image[i][j] = (Image[i+1][j] + Image[i-1][j])/(2.0);
                    }

                }
                else if ( (i%2)!=0 && (j%2)!=0)   //Pixel entouré par 4 pixels en diagonale
                {
                    if(i == longueur-1)
                    {
                        Image[i][j] = (Image[i-1][j-1] + Image[i-1][j-1])/(4.0);
                        if(j == largeur-1) Image[i][j] = Image[i-1][j-1]/(4.0);;
                    }
                    else if(j == largeur-1)
                    {
                        Image[i][j] = (Image[i-1][j-1] + Image[i+1][j-1])/(4.0);
                        if(i == longueur-1) Image[i][j] = Image[i-1][j-1]/(4.0);;
                    }

                    else
                    {
                        Image[i][j] = (Image[i-1][j-1] + Image[i-1][j+1] + Image[i+1][j-1] + Image[i+1][j+1])/(4.0);
                    }
                }
            }
        }
    }

    if((longueur%2 ==0) && (largeur%2 !=0))
    {
        for(i=0; i<longueur; i++)
        {
            for(j=0; j<largeur; j++)
            {
                if ( (i%2)== 0 && (j%2)!=0 )   //Sur les lignes paires et colonnes impaires
                {
                    Image[i][j] = (Image[i][j-1] + Image[i][j+1])/(2.0);

                }
                else if ( (i%2)!=0 && (j%2)==0 )   //Sur les lignes impaires et colonnes paires
                {
                    if(i == longueur-1)
                    {
                        Image[i][j] = Image[i-1][j]/(2.0);
                    }
                    else
                    {
                        Image[i][j] = (Image[i+1][j] + Image[i-1][j])/(2.0);
                    }

                }
                else if ( (i%2)!=0 && (j%2)!=0)   //Pixel entouré par 4 pixels en diagonale
                {
                    if(i == longueur-1)
                    {
                        Image[i][j] = (Image[i-1][j-1] + Image[i-1][j-1])/(4.0);
                        if(j == largeur-1) Image[i][j] = Image[i-1][j-1]/(4.0);;
                    }
                    else
                    {
                        Image[i][j] = (Image[i-1][j-1] + Image[i-1][j+1] + Image[i+1][j-1] + Image[i+1][j+1])/(4.0);
                    }
                }
            }
        }
    }

    if((longueur%2 !=0) && (largeur%2 ==0))
    {
        for(i=0; i<longueur; i++)
        {
            for(j=0; j<largeur; j++)
            {
                if ( (i%2)== 0 && (j%2)!=0 )   //Sur les lignes paires et colonnes impaires
                {
                    if(j == largeur-1)
                    {
                        Image[i][j] = (Image[i][j-1])/(2.0);
                    }
                    else
                    {
                        Image[i][j] = (Image[i][j-1] + Image[i][j+1])/(2.0);
                    }

                }
                else if ( (i%2)!=0 && (j%2)==0 )   //Sur les lignes impaires et colonnes paires
                {
                    Image[i][j] = (Image[i+1][j] + Image[i-1][j])/(2.0);

                }
                else if ( (i%2)!=0 && (j%2)!=0)   //Pixel entouré par 4 pixels en diagonale
                {
                    if(j == largeur-1)
                    {
                        if(i == longueur-1) Image[i][j] = Image[i-1][j-1]/(4.0);
                        else Image[i][j] = (Image[i-1][j-1] + Image[i+1][j-1])/(4.0);

                    }
                    else
                    {
                        Image[i][j] = (Image[i-1][j-1] + Image[i-1][j+1] + Image[i+1][j-1] + Image[i+1][j+1])/(4.0);
                    }
                }
            }
        }
    }

    return Image;




}






