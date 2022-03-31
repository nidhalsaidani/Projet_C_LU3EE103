#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "filtreGaussien.h"
#include "operation_matrice.h"
#include "Horn_And_Schunk.h"
#include "myBmpGris.h"
#include "Echatillonnage_interpolation.h"
#include "INTERFACE.h"

//Choix de l'image a tester
#define Image_Initiale "image1.bmp"
#define Image_Finale "image2.bmp"




int main()
{

    printf ("######################PROJET ESTIMATION DE MOUVEMENT#############################\n\n");
    printf (" Le Programme suivant permet d'estimer le mouvement entre deux images bitmap \n"
            " Le mouvement estime entre ces deux est relativement petit.\n"
            " Il est important de verifier que les anciens fichier texte sont bien supprime pour une meilleure clarete"
            "Pour Modifier les images il suffit de changer le nom dans les defines\n");


    printf ("Veuillez choisir par quelle methode vous souhaitez estimer le mouvement : \n\n");
    printf ("1 : Methode de Horn & Schunck\n"
            "2 : Methode de multi resolution\n"
            "3 : Methode du filtre gaussien\n\n"
            "Votre Choix : ");


    Debut_Estimation(Image_Initiale,Image_Finale);




    return 0;

}
