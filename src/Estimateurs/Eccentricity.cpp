#include "Eccentricity.h"

using namespace std;
using namespace DGtal;
using namespace DGtal::Z2i; //We'll only consider Z² digital space on
			    //32bit integers
    
pair<pair<Point,Point>,int> Find_PlusEloignes (vector<Point> ListePoints){
  Point p1 = ListePoints[0];
  Point p2 = ListePoints[1];
  int distance = 0;
  for (int i = 0; i < ListePoints.size(); i++){
    for (int j = i+1; j < ListePoints.size(); j++){
      int distance_temp, abs, ord;
      abs = ListePoints[j][0] - ListePoints[i][0];
      ord = ListePoints[j][1] - ListePoints[i][1];
      distance_temp = abs*abs + ord*ord;
      if (distance_temp > distance){
	distance = distance_temp;
	p1 = ListePoints[0];
	p1 = ListePoints[1];
      }
    }
  }
  return make_pair(make_pair(p1,p2),distance);
}

int Dist_Max_Vert (MetaImage & image){
  int res = 0;
  Domain domain = image.domain();
  for (int i = domain.lowerBound()[0]; i < domain.upperBound()[0]; i++){
    bool find_fst = false;
    bool find_snd = false;
    int fst = domain.lowerBound()[1];
    int snd = domain.lowerBound()[1];
    for (int j = domain.lowerBound()[1]; j < domain.upperBound()[1]; j++){
      if (!find_fst && image(Point(i,j))) {
	find_fst = true;
	fst = j;
      }
      if (find_fst && !find_snd && !image(Point(i,j))){
	find_snd = true;
	snd = j-1;
      }
    }
    if ((snd-fst) > res) {res = snd-fst;}
  }
  return res;
}
    
    
double Eccentricity (MetaImage & image){
  Domain domain = image.domain();
  DigitalSet img_set(domain);
  SetFromImage<DigitalSet>::append<MetaImage>(img_set, image, 0, 255);  
  vector<Point> convhull = Build_ConvexHull(img_set);
  pair<pair<Point,Point>,int> res_plus_eloignes = Find_PlusEloignes(convhull);
  Point p1 = res_plus_eloignes.first.first;
  Point p2 = res_plus_eloignes.first.second;
  int longueur = res_plus_eloignes.second;
  double tangente = (double)(p2[1]-p1[1])/(double)(p2[0]-p1[0]);
  image = Rotate(image, atan(tangente));
  ConvexHull(image);
  Remplissage(image);
  int largeur = Dist_Max_Vert(image);
  return ((double)largeur/(double)longueur);
}

