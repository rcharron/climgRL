///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <vector>
#include <queue>
#include <DGtal/base/Common.h>
#include <DGtal/io/boards/Board2D.h>
#include <DGtal/helpers/StdDefs.h>
#include <DGtal/geometry/curves/ArithmeticalDSSComputer.h>
#include <iostream>
#include <DGtal/io/readers/PGMReader.h>
#include "DGtal/images/imagesSetsUtils/SetFromImage.h"
#include "DGtal/images/ImageContainerBySTLVector.h"
#include "../MetaImage.h"
///////////////////////////////////////////////////////////////////////////////

/*
REMPLISSAGE
*/


using namespace std;
using namespace DGtal;
using namespace DGtal::Z2i; //We'll only consider Z² digital space on
			    //32bit integers

/* Fait une liste des huits voisins d'un point */
vector<Point> Remplissage_Make_Voisins(Point p){
  vector<Point> voisins;
  voisins.push_back(Point(p[0]-1,p[1]));
  voisins.push_back(Point(p[0],p[1]-1));
  voisins.push_back(Point(p[0]+1,p[1]));
  voisins.push_back(Point(p[0],p[1]+1));
  voisins.push_back(Point(p[0]-1,p[1]-1));
  voisins.push_back(Point(p[0]+1,p[1]-1));
  voisins.push_back(Point(p[0]+1,p[1]+1));
  voisins.push_back(Point(p[0]-1,p[1]+1));  
  return voisins;
}

MetaImage Apply_Remplissage (MetaImage & image){
  Domain domain = image.domain();
  /* Crée une nouvelle image toute blanche */
  MetaImage new_image = MetaImage(domain);
  for (Domain::Iterator it = domain.begin(); it != domain.end();it++){
    new_image.setValue(*it,1);
  }
  /* Colorie en noir les bords */
  queue<Point> myqueue;
  Point current;
  for (Point it = domain.lowerBound(); domain.isInside(it);(it)[0]++){ //itère sur les points en bas
    if (!image(it)) { new_image.setValue(it,0); myqueue.push(it); }
  }
  for (Point it = domain.lowerBound(); domain.isInside(it);(it)[1]++){ //itère sur les points à gauche
    if (!image(it)) { new_image.setValue(it,0); myqueue.push(it); } 
  }
  for (Point it = domain.upperBound(); domain.isInside(it);(it)[0]--){ //itère sur les points en haut
    if (!image(it)) { new_image.setValue(it,0); myqueue.push(it); } 
  }
  for (Point it = domain.upperBound(); domain.isInside(it);(it)[1]--){ //itère sur les points à droite
    if (!image(it)) { new_image.setValue(it,0); myqueue.push(it); }  
  }
  while (!myqueue.empty()){
    vector<Point> voisins = Remplissage_Make_Voisins(myqueue.front());    
    for (int i = 0; i < voisins.size(); i++){
      current = voisins[i];
      if (domain.isInside(current) && !image(current)){		//si le voisin est dans l'image et que sa couleur est noire, on le traite et on l'ajoute à la queue
	new_image.setValue(current,0);
	myqueue.push(current);
      }
    }
    myqueue.pop();
  }
  /* Renvoie l'image ainsi obtenue */
  return new_image;
}

void Remplissage (MetaImage & image){
  image = Apply_Remplissage(image);
}

    
    
    
    
    
    
    
    
    
    
    
    
    
    
    

    

    

   
