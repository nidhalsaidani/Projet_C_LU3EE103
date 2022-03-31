#include "operation_matrice.h"



/** Fonction de creation d'une matrice
  * @param x est le nombre de lignes de la matrice
  * @param y est le nombre de colonnes de la matrice
  * @return une matrice de dimensions x et y
  */
float** Create_Mat (int dimX, int dimY)
{
    float** mat = calloc(dimX, sizeof(float*));
    int i;
    for (i=0; i<dimX; i++)
    {
        mat[i]=calloc(dimY, sizeof(float));
    }
    return mat;
}


/** Fonction de liberation de la matrice en memoire
  * @param  mat est la matrice a liberer
  * @param x est le nombre de lignes de matrice, une seule dimension est necessaire pour liberer la matrice
  */
void libere_mat (float*** mat, int dimX)
{
    int i;
    for (i=0; i<dimX; i++)
    {
        free(*mat[i]);
    }
    free(*mat);
    *mat=NULL;
}


/** Fonction d'affichage d'une matrice
  * @param  mat est la matrice a afficher
  * @param  x est le nombre de ligne de la matrice mat
  * @param  y est le nombre de colonnes de la matrice mat
  * @return liberation de la matrice
  */
void affiche_mat (float** mat, int dimX, int dimY)
{
    int i, j;
    for (i=0; i<dimX; i++)
    {
        for(j=0; j<dimY; j++)
        {
            printf("%f\t", mat[i][j]);
        }
        printf("\n");
    }
}


/** Fonction de lecture de la matrice
  * @param  fname est le nom du fichier texte ou est stockee la marice
  * @return la lecture du fichier texte
  */

float** readmat (char* fname)
{
    int i, j;
    int n,m;
    FILE* ftext = fopen(fname, "r");
    if (ftext == NULL)
    {
        printf("Erreur d'ouverture\n");
        return NULL ;
    }
    else
    {

        fscanf(ftext, "%d %d\n", &n, &m); //lecture des dimensions
        float** res = Create_Mat(n,m);
        for(i=0; i<n; i++)
        {
            for (j=0; j<m; j++)
            {
                fscanf(ftext, "%f ", &(res[i][j]));
            }
        }
        return res;
    }
    fclose(ftext);

}



/** Fonction d'ecriture de la matrice dans un fichier texte
  * @param  fname est le nom du fichier texte a creer et ou ecrire la matrice
  * @param mat est la matrice a ecrire dans le fichier texte
  * @param n est le nombre de lignes de la matrice
  * @param m est le nombre de colonnes de la matrice
  * @return fichier texte dans laquelle est ecrit la matrice
  */
void writemat(char* fname, float** mat, int dimX, int dimY)
{
    FILE* ftext = fopen(fname, "w");
    if(ftext != NULL)
    {
        int i,j;
        for (i=0; i<dimX; i++)
        {
            for (j=0; j<dimY; j++)
            {
                fprintf(ftext, "%2f ", mat[i][j]);
            }
            fprintf(ftext, "\n");
        }
        fclose(ftext);
    }
    else
    {
        printf("Erreur d'ouverture\n");
    }
}



