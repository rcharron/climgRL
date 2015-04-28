#include "ConvexHull.h"

using namespace std;
using namespace DGtal;
using namespace DGtal::Z2i; //We'll only consider Z² digital space on
			    //32bit integers


int Determinant(Point p, Point q) { return (p[0]*q[1] - p[1]*q[0]);}

Point lepointp;

bool CompOr(Point a, Point b)
{
  if (a == lepointp){return true;}
  if (b == lepointp){return false;}
  int det = Determinant((a-lepointp),(b-lepointp));
//  cout << "det : " << det << "\n";
  if (det > 0) {
    return true;
  } else {
    if ((det == 0) && (a[0] < b[0])) {return true;}
    else {return false;}
  }
}

bool Orientationof(Point p, Point q, Point r){
  int det = Determinant((q-p),(r-q));
  if (det >= 0) {return true;} else {return false;}
}


vector<Point> Build_ConvexHull(DigitalSet & s)  //TODO amélioration : on ne considère que les points du contour (plus rapide)
{
  /*  Tri des Points  */
  Point p = *(s.begin()); //ce sera le point d'abcisse minimal = "le repère"
  int absmin = p[0];
  Domain domain = s.domain();
//  int i = 0;
  for (DigitalSet::Iterator it = s.begin(); it != s.end(); it++){
//    i++;
//    cout << "Je rentre ds la boucle " << i << "\n";
    if ((*it)[0] < absmin) {p = *it; }
  }
//  cout << "Je sors de la boucle\n";
  vector<Point> L (s.begin(),s.end()); // on transforme le set en vector pour pouvoir trier
  lepointp=p;
  sort(L.begin(),L.end(),CompOr);
  //  sort(L.begin(),L.end(),CompOr(p));
//  cout << "J'ai trié\n";
//  vector<Point>::iterator it;
//  it = find (L.begin(), L.end(), p);
//  if (it != L.end())
//    std::cout << "Element found in myvector: \n";
//  else
//    std::cout << "Element not found in myvector\n";
//  if (p == L[0]) { cout << "premier element ok\n"; } else { cout << "premier element pas ok\n"; }
//  cout << "p appartient à L : " << it != L.end() << "\n";
//  cout << "p est le premier élément de L : " << p==L[0] << "\n";
  vector<Point> convhull;
//  convhull.insert(p);
  /*  Formation de l'enveloppe  */
  // On prend une pile, on empile les trois premiers, à partir de là : on prend chaque point dans l'ordre, on teste si ça tourne dans le bon sens (grace à Orientationof2(p,q,r), si c'est pas le cas on enlève le haut de la pile et on recommence) 
  stack<Point> mystack;
//  mystack.push(p);
//  cout << "Point p : " << p << "\n";
  mystack.push(L[0]);
//  cout << "Point " << 0 << " : " << L[0] << "\n";
  mystack.push(L[1]);
//  cout << "Point " << 1 << " : " << L[1] << "\n";
//  cout << "début de l'itération sur le vecteur\n";
  for (int i = 2; i < L.size(); i++){
//    cout << "Point " << i << " : " << L[i] << "\n";
    if (mystack.size() > 1){
      Point p2 = mystack.top();
      mystack.pop();
      Point p1 = mystack.top();
//      cout << "Point p1 : " << p1 << "\n";
//      cout << "Point p2 : " << p2 << "\n";
      if (!Orientationof(p1,p2,L[i])) {
//	cout << "Pas bonne orientation\n"; 
	i--;
      } else {
//	cout << "Bonne orientation\n"; 
	mystack.push(p2);
	mystack.push(L[i]);
      }
    } else {
//      cout << "Stack.size <= 1\n"; 
      mystack.push(L[i]);
    }
  }
//  cout << "convex hull built\n";
  while (!mystack.empty()){
    convhull.push_back(mystack.top());
    mystack.pop();
  }
  return convhull;
}

DigitalSet Contours_ConvexHull(Domain domain, vector<Point> & convhull){
  DigitalSet s(domain);
  for (int i = 0; i < convhull.size(); i++){
    Trace_Line (s, convhull[i], convhull[(i+1)%convhull.size()]);
  }
  return s;
}

void ConvexHull (MetaImage& img){
  Domain domain = img.domain();
  DigitalSet img_set(domain);
  SetFromImage<DigitalSet>::append<Image>(img_set, img, 0, 255);
  MetaImage new_image = MetaImage(domain);
//  cout << "j'ai pas encore construit convexhull" << endl; 
  vector<Point> convhull = Build_ConvexHull(img_set);
//  cout << "j'ai construit convexhull mais pas les contours" << endl;
  DigitalSet contours_convhull = Contours_ConvexHull(domain, convhull);
//  cout << "j'ai construit les contours" << endl;
  for (Point a : contours_convhull){
//    cout << "je suis dans la boucle (nark nark)" << endl;
//    cout<< a[0] << "," << a[1] << endl;
    img.setValue(a,1);
  }
//  img = new_image;
} 
