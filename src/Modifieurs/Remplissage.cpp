#include "Remplissage.h"

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
//  cout << "début fonction\n";
  Domain domain = image.domain();
  /* Crée une nouvelle image toute blanche */
  MetaImage new_image = MetaImage(domain);
  for (Domain::Iterator it = domain.begin(); it != domain.end();it++){
    new_image.setValue(*it,1);
  }
//  cout << "a créé nvelle image\n";
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
//  cout << "avant boucle while \n";
  while (!myqueue.empty()){
    vector<Point> voisins = Remplissage_Make_Voisins(myqueue.front());    
    for (int i = 0; i < voisins.size(); i++){
      current = voisins[i];
      if (domain.isInside(current) && new_image(current) && !image(current)){		//si le voisin est dans l'image et non traité et que sa couleur est noire, on le traite et on l'ajoute à la queue
	new_image.setValue(current,0);
	myqueue.push(current);
      }
    }
    myqueue.pop();
  }
  /* Renvoie l'image ainsi obtenue */
//  cout << "end\n\n";
  return new_image;
}

void Remplissage (MetaImage & image){
  image = Apply_Remplissage(image);
}

    
    
    
    
    
    
    
    
    
    
    
    
    
    
    

    

    

   
