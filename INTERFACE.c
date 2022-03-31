#include "INTERFACE.h"
#include <stdlib.h>
#include <stdio.h>
#define N 2
#define TOLERANCE 0.01
#define SIGMA 1





/** Fonction Pour choisir la methode par laquelle on estime le mouvement
  * @param Image_initiale le nom de l'mage a t
  * @param Image_finale le nom de l'image a t+1
  */
void Debut_Estimation(char* Image_initiale,char* Image_finale)
{

    int rep = 0;
    int compteur = 0;
    while (compteur<3)
    {
        if (scanf ("%d",&rep) !=1)
        {
            printf ("Erreur fatale a la saisie\n");
            exit (-1);
        }
        if (rep ==1 || rep ==2 || rep==3)
        {
            compteur=3;
            if (rep==1)   //Calcul des vitesses avec la methode d'HORN & SCHUNK
            {
                Horn_Schunk_Estimation(Image_initiale,Image_finale);
                printf ("\n\n Les fichiers ont ete correctement cree et sont disponible dans le fichier du projet. \n"
                        "Vous pouvez relancer ce programme pour choisir une autre option !\n\n\n");
            }
            if (rep==2)   //Calcul des vitesses avec la methode de multi resolution
            {
                Multi_Resolution_Estimation(Image_initiale,Image_finale);
                printf ("\n\n  Les fichiers ont ete correctement cree et sont disponible dans le fichier du projet. \n"
                        "Vous pouvez relancer ce programme pour choisir une autre option !\n\n\n");
            }
            if (rep==3)   //calcul des vitesses avec la methode du filtre de gauss
            {
                Filtre_Gaussien_Estimation(Image_initiale,Image_finale);
                printf ("\n\n  Les fichiers ont ete correctement cree et sont disponible dans le fichier du projet. \n"
                        "Vous pouvez relancer ce programme pour choisir une autre option !\n\n\n");
            }
        }
        else
        {
            compteur++;
            printf ("\nErreur lors de la saisi du nombre (choisissez 1,2 ou 3)\n\n"
                    "Il vous reste %d essai(s) : ",3-compteur);
        }
    }
}



/** Fonction permettant le calcul des vecteurs vitesses avec la methode d'horn & schunk
  * @param Image_initiale a l'instant t
  * @param Image_finale a l'instant t+1
  */
void Horn_Schunk_Estimation(char* Image_initiale,char* Image_finale)
{
    printf("Vous avez choisi une estimation par la methode d'Horn & Schunk\n"
           "Bon Choix !\n"
           "Estimation en cours Veuillez patienter ...\n\n");
    int i,j;

    //Dimensions des images (même dimensions)

    int dimX,dimY;

    //Lecture des images Bitmap et remplissage des matrices
    FILE* ftext1=fopen("image_initiale.txt","w");
    if (ftext1!=NULL)
    {
        BmpImg Image_init = readBmpImage(Image_initiale);
        dimX = Image_init.dimX;
        dimY = Image_init.dimY;
        fprintf(ftext1,"%d %d\n",dimX,dimY);
        for(i=0; i<dimX; i++)
            for(j=0; j<dimY; j++)
                fprintf(ftext1,"%d ",Image_init.img[i][j]);
    }


    FILE* ftext2=fopen("image_finale.txt","w");
    if (ftext2!=NULL)
    {
        BmpImg Image_fin = readBmpImage(Image_finale);

        fprintf(ftext2,"%d %d\n",dimX,dimY);
        for(i=0; i<dimX; i++)
            for(j=0; j<dimY; j++)
                fprintf(ftext2,"%d ",Image_fin.img[i][j]);
    }


    //LECTURE DES MATRICES ECRITES

    float** matrice1 = readmat("Image_initiale.txt" ) ;
    printf("\nLECTURE IMAGE 1 -> ok\n");
    float** matrice2 = readmat("Image_finale.txt");
    printf("LECTURE IMAGE 2 -> ok\n");

    //CREATION DES MATRICES GRADIENT ET VITESSES
    Gradient Grad1 = creation_gradient(dimX,dimY);
    Vitesses Vit1 = creation_vitesse(dimX,dimY);

    float** Ubar = Create_Mat(dimX, dimY);
    float** Vbar = Create_Mat(dimX, dimY);

    //CALCUL DES GRADIENTS
    Calcul_Gradient(matrice1, matrice2,&Grad1);
    printf("CALCUL DES GRADIENTS -> ok\n");

    //ECRITURE DES GRADIENTS DANS DES FICHIERS TEXTES
    writemat("Ix.txt", Grad1.Ix, dimX, dimY);
    writemat("Iy.txt", Grad1.Iy, dimX, dimY);
    writemat("It.txt", Grad1.It, dimX, dimY);

    //CREATION DES IMAGES DE GRADIENTS
    BmpImg IxIM=createBmpImg("Ix.bmp",Grad1.dimX,Grad1.dimY);
    for(i = 0 ; i <Grad1.dimX; i++ )
    {
        for( j = 0 ; j <Grad1.dimY; j++)
        {
            IxIM.img[i][j]=(int)Grad1.Ix[i][j];
        }
    }
    writeBmpImage("Ix.bmp",&IxIM);

    BmpImg IyIM=createBmpImg("Iy.bmp",Grad1.dimX,Grad1.dimY);
    for(i = 0 ; i <Grad1.dimX; i++ )
    {
        for( j = 0 ; j <Grad1.dimY; j++)
        {
            IyIM.img[i][j]=(int)Grad1.Iy[i][j];
        }
    }
    writeBmpImage("Iy.bmp",&IyIM);

    BmpImg ItIM=createBmpImg("It.bmp",Grad1.dimX,Grad1.dimY);
    for(i = 0 ; i <Grad1.dimX; i++ )
    {
        for( j = 0 ; j <Grad1.dimY; j++)
        {
            ItIM.img[i][j]=(int)Grad1.It[i][j];
        }
    }
    writeBmpImage("It.bmp",&ItIM);

    printf("CREATION DES IMAGES GRADIENTS -> OK");


    //CALCUL DE U ET V
    printf ("\n Je procede au calcul de U et V, quelques instants svp ...");
    Calcul_Vitesses_UV(&Vit1, &Grad1, Ubar, Vbar, TOLERANCE);

    //CREATION DES FICHIERS TEXTES DE U, V , UBAR ET VBAR

    writemat("U.txt", Vit1.U, dimX, dimY);
    writemat("V.txt", Vit1.V, dimX, dimY);
    writemat("Ubar.txt", Ubar, dimX, dimY);
    writemat("Vbar.txt", Vbar, dimX, dimY);


}

/** Fonction permettant le calcul des vecteurs vitesses avec la methode de multi resolution
  * @param Image_initiale a l'instant t
  * @param Image_finale a l'instant t+1
  */
void Multi_Resolution_Estimation(char* Image_initiale, char* Image_finale)
{
    printf("Vous avez choisi une estimation par la methode de Multi Resoltion\n"
           "Bon Choix !\n"
           "Estimation en cours Veuillez patienter ...\n\n");
    //Dimensions des images (même dimensions)

    int i,j;
    int dimX,dimY;



    //Lecture des images Bitmap et remplissage des matrices
    FILE* ftext1=fopen("image_initiale.txt","w");
    if (ftext1!=NULL)
    {
        BmpImg Image_init = readBmpImage(Image_initiale);
        dimX = Image_init.dimX;
        dimY = Image_init.dimY;
        fprintf(ftext1,"%d %d\n",dimX,dimY);
        for(i=0; i<dimX; i++)
            for(j=0; j<dimY; j++)
                fprintf(ftext1,"%d ",Image_init.img[i][j]);
    }


    FILE* ftext2=fopen("image_finale.txt","w");
    if (ftext2!=NULL)
    {
        BmpImg Image_fin = readBmpImage(Image_finale);

        fprintf(ftext2,"%d %d\n",dimX,dimY);
        for(i=0; i<dimX; i++)
            for(j=0; j<dimY; j++)
                fprintf(ftext2,"%d ",Image_fin.img[i][j]);
    }

    //LECTURE DES MATRICES ECRITES

    float** matrice1 = readmat("Image_initiale.txt" ) ;
    printf("\nLECTURE IMAGE 1 -> OK\n");
    float** matrice2 = readmat("Image_finale.txt");
    printf("LECTURE IMAGE 2 -> OK\n");

    //SOUS ECHANTILLONAGE DES IMAGES /2

    float** SouEchan2_matrice1 = Sous_Echantillonnage(matrice1, dimX, dimY);
    float** SouEchan2_matrice2 = Sous_Echantillonnage(matrice2, dimX, dimY);

    printf("SOUS ECHANTILLONNAGE DES IMAGES PAR UN FACTEUR 2 -> OK\n");
    //SOUS ECHANTILLONAGE DES IMAGES /4

    float** SouEchan4_matrice1 = Sous_Echantillonnage(SouEchan2_matrice1, dimX/N, dimY/N);
    float** SouEchan4_matrice2 = Sous_Echantillonnage(SouEchan2_matrice2, dimX/N, dimY/N);

    printf("SOUS ECHANTILLONNAGE DES IMAGES PAR UN FACTEUR 4 -> OK\n");

    //CREATION D'IMAGES SOUS ECHANTILLONNEES

    BmpImg image1_SousEchantillonne=createBmpImg("SouEchan4_matrice1.bmp",dimX/(N*N),dimY/(N*N));
    for(i = 0 ; i <dimX/(N*N); i++ )
    {
        for( j = 0 ; j <dimY/(N*N); j++)
        {
            image1_SousEchantillonne.img[i][j]=(int)SouEchan4_matrice1[i][j];
        }
    }
    writeBmpImage("image1_SousEchantillonne.bmp",&image1_SousEchantillonne);


     BmpImg image2_SousEchantillonne=createBmpImg("SouEchan4_matrice2.bmp",dimX/(N*N),dimY/(N*N));
    for(i = 0 ; i <dimX/(N*N); i++ )
    {
        for( j = 0 ; j <dimY/(N*N); j++)
        {
            image2_SousEchantillonne.img[i][j]=(int)SouEchan4_matrice2[i][j];
        }
    }
    writeBmpImage("image2_SousEchantillonne.bmp",&image2_SousEchantillonne);

    printf("CREATION DES IMAGES SOUS ECHANTILLONNEES -> OK\n");
    //CREATION DES MATRICES GRADIENT ET VITESSES
    Gradient Grad2 = creation_gradient(dimX/(N*N),dimY/(N*N));
    Vitesses Vit2 = creation_vitesse(dimX/(N*N),dimY/(N*N));

    float** Ubar2 = Create_Mat(dimX/(N*N), dimY/(N*N));
    float** Vbar2 = Create_Mat(dimX/(N*N), dimY/N*N);

    //CALCUL DES GRADIENTS
    Calcul_Gradient(SouEchan4_matrice1, SouEchan4_matrice2,&Grad2);
    printf("CALCUL DES GRADIENTS SUR LES IMAGES SOUS ECHANTILLONNEES -> OK\n");

    //CALCUL DE U ET V
    printf ("\n Je procede au calcul de U et V, quelques instants svp ...");
    Calcul_Vitesses_UV(&Vit2, &Grad2, Ubar2, Vbar2, TOLERANCE);

    // INTERPOLATION DES VITESSES d'un facteur 2
    float** SurEchan2_U = Sur_Echantillonnage(Vit2.U,dimX/(N*N),dimY/(N*N));
    float** SurEchan2_V = Sur_Echantillonnage(Vit2.V,dimX/(N*N),dimY/(N*N));
    printf("\nINTERPOLATION DES VITESSES U ET V D'UN FACTEUR 2 -> OK\n");


    // INTERPOLATION DES VITESSES d'un facteur 4

    float** SurEchan4_U = Sur_Echantillonnage(SurEchan2_U,dimX/(N),dimY/(N));
    float** SurEchan4_V = Sur_Echantillonnage(SurEchan2_V,dimX/(N),dimY/(N));
    printf("INTERPOLATION DES VITESSES U ET V D'UN FACTEUR 4 -> OK\n");



    //CREATION DES FICHIERS TEXTES DE U et V

    writemat("U_MultiRes.txt", SurEchan4_U, dimX, dimY);
    writemat("V_MultiRes.txt", SurEchan4_V, dimX, dimY);


}


/** Fonction permettant le calcul des vecteurs vitesses avec la methode du filtre de Gauss
  * @param Image_initiale a l'instant t
  * @param Image_finale a l'instant t+1
  */
void Filtre_Gaussien_Estimation(char* Image_initiale, char* Image_finale)
{
    printf("Vous avez choisi une estimation par la methode du Filtre de Gauss\n"
           "Bon Choix !\n"
           "Estimation en cours Veuillez patienter ...\n\n");

    int i,j;

    //Dimensions des images (même dimensions)

    int dimX,dimY;

    //Lecture des images Bitmap et remplissage des matrices
    FILE* ftext1=fopen("image_initiale.txt","w");
    if (ftext1!=NULL)
    {
        BmpImg Image_init = readBmpImage(Image_initiale);
        dimX = Image_init.dimX;
        dimY = Image_init.dimY;
        fprintf(ftext1,"%d %d\n",dimX,dimY);
        for(i=0; i<dimX; i++)
            for(j=0; j<dimY; j++)
                fprintf(ftext1,"%d ",Image_init.img[i][j]);
    }


    FILE* ftext2=fopen("image_finale.txt","w");
    if (ftext2!=NULL)
    {
        BmpImg Image_fin = readBmpImage(Image_finale);

        fprintf(ftext2,"%d %d\n",dimX,dimY);
        for(i=0; i<dimX; i++)
            for(j=0; j<dimY; j++)
                fprintf(ftext2,"%d ",Image_fin.img[i][j]);
    }

    //LECTURE DES MATRICES ECRITES

    float** matrice1 = readmat("Image_initiale.txt" ) ;
    printf("\nLECTURE IMAGE 1 -> OK\n");
    float** matrice2 = readmat("Image_finale.txt");
    printf("LECTURE IMAGE 2 -> OK\n");

    // Filtre Gaussien
    float** W = filtre_gauss(SIGMA) ;
    int dimf = SIGMA*Coeff+1 ;
    float** matrice1filt = convolution(matrice1, W, dimX, dimY,dimf);
    float** matrice2filt = convolution(matrice2, W, dimX, dimY,dimf);
    printf("CONVOLUTION DES IMAGES AVEC LE FILTRE DE GAUSS -> OK\n");


    //CREATION D'IMAGES FILTRES
    BmpImg Filtim1=createBmpImg("Filtim1.Bmp",dimX,dimY);
    for(i=0; i<dimX; i++)
    {
        for(j=0; j<dimY; j++)
        {
            Filtim1.img[i][j]=(int)matrice1filt[i][j];
        }
    }
    writeBmpImage("Filtim1.Bmp",&Filtim1);

    BmpImg Filtim2=createBmpImg("Filtim2.Bmp",dimX,dimY);
    for(i=0; i<dimX; i++)
    {
        for(j=0; j<dimY; j++)
        {
            Filtim2.img[i][j]=(int)matrice2filt[i][j];
        }
    }
    writeBmpImage("Filtim2.Bmp",&Filtim2);

    printf("CREATION DES IMAGES FILTRES -> OK\n");

    //SOUS ECHANTILLONAGE DES IMAGES FILTRES/2

    float** SouEchan2_matrice1filt = Sous_Echantillonnage(matrice1filt, dimX, dimY);
    float** SouEchan2_matrice2filt = Sous_Echantillonnage(matrice2filt, dimX, dimY);

    printf("SOUS ECHANTILLONNAGE DES IMAGES FILTRES D'UN FACTEUR 2");

    // LISSAGE DES IMAGES SOUS ECHANTILLONNES /2
    float** FiltSouEchan2_matrice1filt = convolution(SouEchan2_matrice1filt, W, dimX/N, dimY/N, dimf);
    float** FiltSouEchan2_matrice2filt = convolution(SouEchan2_matrice2filt, W, dimX/N, dimY/N, dimf);
    printf("CONVOLUTION DES IMAGES SOUS ECHANTILLONNEES D'UN FACTEUR 2 AVEC LE FILTRE DE GAUSS -> OK\n");


    //SOUS ECHANTILLONNAGE DES IMAGES FILTRES /4

    float** SouEchan4_matrice1filt = Sous_Echantillonnage(FiltSouEchan2_matrice1filt, dimX/N, dimY/N);
    float** SouEchan4_matrice2filt = Sous_Echantillonnage(FiltSouEchan2_matrice2filt, dimX/N, dimY/N);

    printf("ECHANTILLONNAGE D'UN FACTEUR 4->OK \n");
    //CREATION DES MATRICES GRADIENT ET VITESSES
    Gradient Grad4 = creation_gradient(dimX/(N*N),dimY/(N*N));
    Vitesses Vit4 = creation_vitesse(dimX/(N*N),dimY/(N*N));

    float** Ubar4 = Create_Mat(dimX/(N*N), dimY/(N*N));
    float** Vbar4 = Create_Mat(dimX/(N*N), dimY/N*N);

    //CALCUL DES GRADIENTS

    Calcul_Gradient(SouEchan4_matrice1filt, SouEchan4_matrice2filt,&Grad4);
    printf("CALCUL DES GRADIENTS SUR LA PLUS PETITE IMAGES FILTRE ->OK");


    //CALCUL DE U ET V
    printf ("\n Je procede au calcul de U et V, quelques instants svp ...");
    Calcul_Vitesses_UV(&Vit4, &Grad4, Ubar4, Vbar4, TOLERANCE);

    // INTERPOLATION DES VITESSES d'un facteur 2
    float** SurEchan2_matrice1filt_U = Sur_Echantillonnage(Vit4.U,dimX/(N*N),dimY/(N*N));
    float** SurEchan2_matrice2filt_V = Sur_Echantillonnage(Vit4.V,dimX/(N*N),dimY/(N*N));

    printf("\nINTERPOLATION DES VITESSES D'UN FACTEUR 2 -> OK\n");


    // INTERPOLATION DES VITESSES d'un facteur 4

    float** SurEchan4_matrice1filt_U = Sur_Echantillonnage(SurEchan2_matrice1filt_U,dimX/(N),dimY/(N));
    float** SurEchan4_matrice2filt_V = Sur_Echantillonnage(SurEchan2_matrice2filt_V,dimX/(N),dimY/(N));
    printf("INTERPOLATION DES VITESSES D'UN FACTEUR 4 -> OK\n");

    //CREATION DES FICHIERS TEXTES DE U et V

    writemat("U_FILTRE_MultiRes.txt", SurEchan4_matrice1filt_U, dimX, dimY);
    writemat("V_FILTRE_MultiRes.txt", SurEchan4_matrice2filt_V, dimX, dimY);
}
