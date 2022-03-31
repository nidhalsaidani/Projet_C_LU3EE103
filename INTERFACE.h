#ifndef _INTERFACE_h_
#define _INTERFACE_h_
#include "Echatillonnage_interpolation.h"
#include "operation_matrice.h"
#include "filtreGaussien.h"
#include "myBmpGris.h"
#include "Horn_And_Schunk.h"


/** Fonction Pour choisir la methode par laquelle on estime le mouvement
  * @param Image_initiale le nom de l'mage a t
  * @param Image_finale le nom de l'image a t+1
  */
void Debut_Estimation(char* Image_initiale,char* Image_finale);



/** Fonction permettant le calcul des vecteurs vitesses avec la methode d'horn & schunk
  * @param Image_initiale a l'instant t
  * @param Image_finale a l'instant t+1
  */
void Horn_Schunk_Estimation(char* Image_initiale,char* Image_finale);



/** Fonction permettant le calcul des vecteurs vitesses avec la methode de multi resolution
  * @param Image_initiale a l'instant t
  * @param Image_finale a l'instant t+1
  */
void Multi_Resolution_Estimation(char* Image_initiale, char* Image_finale);


/** Fonction permettant le calcul des vecteurs vitesses avec la methode du filtre de Gauss
  * @param Image_initiale a l'instant t
  * @param Image_finale a l'instant t+1
  */
void Filtre_Gaussien_Estimation(char* Image_initiale, char* Image_finale);


#endif

