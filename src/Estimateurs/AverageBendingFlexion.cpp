#include "AverageBendingFlexion.h"

using namespace std;
using namespace DGtal;
using namespace DGtal::Z2i; //We'll only consider Z² digital space on
			    //32bit integers


double dist (Point A, Point B){
  return (sqrt(((A[0]-B[0])*(A[0]-B[0]))+((A[1]-B[1])*(A[1]-B[1]))));
}

double aire (Domain & domain, Point A, Point B, Point C){
  DigitalSet BC = ConstructLine(domain, B, C);
  double min_dist = dist (A,B);
  for(auto it = BC.begin(), itend = BC.end(); it != itend; it++){
    if (dist(A,*it) < min_dist) {min_dist = dist(A,*it);}
  }
  double hauteur = min_dist;
  return (dist(B,C)*hauteur/2);
}


double Curvature (Domain & domain, vector<Point> & bord, Point P){
  ArithmeticalDSSComputer< Iterator, Integer, 4> LeftTangent = Left_Tangent(bord,P);
  ArithmeticalDSSComputer< Iterator, Integer, 4> RightTangent = Right_Tangent(bord,P);
  Point Q = RightTangent.front();
  if (Q == P) {Q = RightTangent.back();}  //au cas où
  Point O = LeftTangent.back();
  if (O == P) {O = LeftTangent.front();}  //au cas où
  return ((dist(P,O)*dist(P,Q)*dist(O,Q))/(4*aire(domain,P,O,Q)));
}


double AverageBendingFlexion (MetaImage & image){
  Remplissage(image);
  Domain domain = image.domain();
  DigitalSet img_set (domain);
  SetFromImage<DigitalSet>::append<Image>(img_set, image, 0,255);
  Object4_8 obj (dt4_8, img_set);
  Object4_8 bord = obj.border();
  int N = 0;
  double curvature_sum = 0;
  vector<Point> bord_vector;
  for(auto it = bord.begin(), itend = bord.end(); it != itend; it++){
    bord_vector.push_back(*it);
  }
  for(auto it = bord.begin(), itend = bord.end(); it != itend; it++){
    N++;
    curvature_sum += Curvature(domain,bord_vector,*it);
  }
  return (curvature_sum/(double)N);
}

