#include "AverageBendingFlexion.h"

using namespace std;
using namespace DGtal;
using namespace DGtal::Z2i; //We'll only consider Z² digital space on
			    //32bit integers


double dist (Point A, Point B){
  return (sqrt(((A[0]-B[0])*(A[0]-B[0]))+((A[1]-B[1])*(A[1]-B[1]))));
}

double aire (Domain & domain, Point A, Point B, Point C){
  if (A == B) { cout << "P = 0\n"; }
  if (A == C) { cout << "P = Q\n"; }
  if (B == C) { cout << "Q = 0\n"; }
  DigitalSet BC = ConstructLine(domain, B, C);
  double min_dist = dist (A,B);
  for(auto it = BC.begin(), itend = BC.end(); it != itend; it++){
    cout << "min_dist = " << min_dist << "\n";
    if (dist(A,*it) < min_dist) {min_dist = dist(A,*it);}
  }
  double hauteur = min_dist;
  cout << "base = " << dist (B,C) << "\n";
  cout << "hauteur = " << hauteur << "\n";
  if (hauteur == 0) {return 0;}
  return (dist(B,C)*hauteur/2);
}


double Curvature (Board2D board, Domain & domain, vector<Point> & bord, Point P){
  ArithmeticalDSSComputer< Iterator, Integer, 4> LeftTangent = Left_Tangent(bord,P);
  ArithmeticalDSSComputer< Iterator, Integer, 4> RightTangent = Right_Tangent(bord,P);
  //We draw the DSS points
  board << SetMode(Point().className(), "Grid")
        << SetMode(LeftTangent.primitive().className(), "Points")
        << LeftTangent.primitive() ;
  //..and the DSS bounding box
  board << SetMode(Point().className(), "Grid")
	<< SetMode(LeftTangent.primitive().className(), "BoundingBox")
	<< LeftTangent.primitive() ;
  //We draw the DSS points
  board << SetMode(Point().className(), "Grid")
        << SetMode(RightTangent.primitive().className(), "Points")
        << RightTangent.primitive() ;
  //..and the DSS bounding box
  board << SetMode(Point().className(), "Grid")
	<< SetMode(RightTangent.primitive().className(), "BoundingBox")
	<< RightTangent.primitive() ;  
  Point Q = RightTangent.front();
  if (Q == P) {Q = RightTangent.back();}  //au cas où
  Point O = LeftTangent.back();
  if (O == P) {O = LeftTangent.front();}  //au cas où
  cout << "P : " << P << "  ;  Q : " << Q << "  ;  O : " << O << "\n";
  cout << "aire = " << aire(domain,P,O,Q)  << "\n";
  if (aire(domain,P,O,Q) == 0.0) {return 0.0;}
  return ((dist(P,O)*dist(P,Q)*dist(O,Q))/(4.0*aire(domain,P,O,Q)));
}


double AverageBendingFlexion (MetaImage & image){
  Remplissage(image);
  Domain domain = image.domain();
  Board2D board;
  board << domain ;
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
    curvature_sum += Curvature(board, domain,bord_vector,*it);
  }
  cout << "curvature_sum = " << curvature_sum << "\n";
  cout << "N = " << N << "\n";
  Color green(0, 255, 0 );
  Color transparent(0,0,0,0);     
  for (unsigned int i = 0; i<bord.size(); i++){
    Point p = bord_vector[i];
    board << CustomStyle(p.className(), new CustomColors(transparent, green)) << p;
  }
  board.saveSVG("../src/Tests/Scaling/apple-tangentes.svg");   
  return (curvature_sum/(double)N);
}

