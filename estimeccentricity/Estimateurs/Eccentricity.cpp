#include "Eccentricity.h"

using namespace std;
using namespace DGtal;
using namespace DGtal::Z2i; //We'll only consider Z² digital space on
			    //32bit integers

/*
pair<pair<Point,Point>,int> Find_PlusEloignes (vector<Point> ListePoints){
//  if (ListePoints.empty()) cout << "La convexhull est vide !!\n";
  Point p1 = ListePoints[0];
  Point p2 = ListePoints[1];
  int distance = 0;
  for (unsigned int i = 0; i < ListePoints.size(); i++){
    for (unsigned int j = i+1; j < ListePoints.size(); j++){
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
} */

double Eccentricity_Dist (Point A, Point B){
  return (sqrt(((A[0]-B[0])*(A[0]-B[0]))+((A[1]-B[1])*(A[1]-B[1]))));
}

pair<pair<Point,Point>,int> Find_PlusEloignes (DigitalSet & s){
//  if (ListePoints.empty()) cout << "La convexhull est vide !!\n";
  int distance = 0;
  Point p1, p2;
  for (auto it1 = s.begin(); it1 != s.end(); it1++){
    for (auto it2 = s.begin(); it2 != s.end(); it2++){
      if (Eccentricity_Dist(*it1,*it2) > distance) { distance = Eccentricity_Dist(*it1,*it2); p1 = *it1; p2 = *it2;}
    }
  }
  return make_pair(make_pair(p1,p2),distance);
}

int Dist_Max_Vert (MetaImage & image){
  int res = 0;
  Domain domain = image.domain();
  for (int i = domain.lowerBound()[0]; i < domain.upperBound()[0]; i++){
    bool find_fst = false;
//    bool find_snd = false;
    int fst = domain.lowerBound()[1];
    int snd = domain.lowerBound()[1];
    for (int j = domain.lowerBound()[1]; j < domain.upperBound()[1]; j++){
      if (!find_fst && image(Point(i,j))) {
	find_fst = true;
	fst = j;
      }
      if (find_fst && image(Point(i,j))){
//	find_snd = true;
	snd = j;
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
//  vector<Point> convhull = Build_ConvexHull(img_set);
//  pair<pair<Point,Point>,int> res_plus_eloignes = Find_PlusEloignes(convhull);
  Object4_8 obj (dt4_8, img_set);
  Object4_8 bord = obj.border();
  DigitalSet & s = bord.pointSet();
  pair<pair<Point,Point>,int> res_plus_eloignes = Find_PlusEloignes(s);
  Point p1 = res_plus_eloignes.first.first;
  Point p2 = res_plus_eloignes.first.second;
  int longueur = res_plus_eloignes.second;
//  cout << p2[0]-p1[0] << "\n";
  if (p2[0]-p1[0] == 0){ image = Rotate(image, 0); }
  else {
  double tangente = (double)(p2[1]-p1[1])/(double)(p2[0]-p1[0]);
//  cout << "tangente : " << tangente << "\n";
//  cout << "atan : " << atan(tangente) << "\n";
  image = Rotate(image, atan(tangente)); }
//  cout << "pas encore segfaulté\n";
//  ConvexHull(image);
//  cout << "a segfaulté\n";
  Remplissage(image);
  int largeur = Dist_Max_Vert(image);
//  cout << "longueur : " << longueur << "\n";
//  cout << "largeur : " << largeur << "\n";
  return ((double)longueur/(double)largeur);
}

