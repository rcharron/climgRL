#include "Tangente.h"


using namespace std;
using namespace DGtal;
using namespace DGtal::Z2i; //We'll only consider Z² digital space on
			    //32bit integers

///////////////////////////////////////////////////////////////////////////////

/*
typedef Object4_8::ConstIterator Iterator;

ArithmeticalDSSComputer< Iterator, Integer, 4> Tangentbis (MetaImage & image, Point p) {
	DigitalSet img_set (image.domain());
	SetFromImage<DigitalSet>::append<Image>(img_set, image, 0,255);
	Object4_8 obj (dt4_8, img_set);
	Object4_8 bord = obj.border();
//	DigitalSet bord_set = obj.pointSet();
//	if (bord_set.isInside(p)) {Iterator it = bord_set.begin();}
//        Iterator p_it = find (bord.begin(), bord.end(), bord[10]);
//	Iterator it = obj.begin();
        ArithmeticalDSSComputer< Iterator, Integer, 4> tangent;
//        tangent.init( p_it );
//        while ( tangent.end() != bord.end() && tangent.extendFront() && tangent.begin() != bord.begin() && tangent.extendBack() );
        return tangent;                      
} */

//typedef vector<Point>::const_iterator Iterator;

/*
vector<Point> Voisins(Point p){
  vector<Point> voisins;
  voisins.push_back(Point(p[0]-1,p[1]));
  voisins.push_back(Point(p[0],p[1]-1));
  voisins.push_back(Point(p[0]+1,p[1]));
  voisins.push_back(Point(p[0],p[1]+1));
  return voisins;
}

Point Suivant (Domain & domain, DigitalSet & set, vector<Point> & bord) {
  Point P2 = bord[bord.size()-1];
  Point P1 = bord[bord.size()-2];
  Point Pres;
  int init;
  if (P1[0] == P2[0]) {
    if (P1[1] < P2[1]) { init = 2; }
    else { init = 0;}    
  } else {
    if (P1[0] < P2[0]) { init = 1; }
    else { init = 3;}
  }
  vector<Point> voisins = Voisins(P2);  
  int i = 0;
  while (i < 3 && (!domain.isInside(voisins[(i+init)%4])) || !set(voisins[(i+init)%4])) {
   i++;
  }
  if (i==3) { return P2; }
  else { 
    return (voisins[(i+init)%4]);
  }
}

vector<Point> ExtractBorder(DigitalSet & set, Point p)
{
  vector<Point> bord;
  Domain domain =  set.domain();
//  Point debut = *(set.begin());
  Point debut = p;
  while ( domain.isInside(Point(debut[0]+1,debut[1])) && set(Point(debut[0]+1,debut[1])) ){
    debut[0]++;
  }
  bord.push_back(debut);
  vector<Point> voisins = Voisins(debut);
  int i = 0;
  while (i < 4 && (!domain.isInside(voisins[i])) || !set(voisins[i])) {
   i++;
  }
  if (i == 4) {return bord; }
  else {
    bord.push_back(voisins[i]);
    while (Suivant(domain, set, bord) != bord[bord.size()-1] && Suivant(domain, set, bord) != debut){
      bord.push_back(Suivant(domain, set, bord));
    }
    return bord;
  }
}*/


ArithmeticalDSSComputer< Iterator, Integer, 4> Tangent (vector<Point> & bord, Point p) {
        Iterator p_it = find (bord.begin(), bord.end(), p);
        ArithmeticalDSSComputer< Iterator, Integer, 4> tangent;
        tangent.init( p_it );
        while ( tangent.end() != bord.end() && tangent.extendFront() && tangent.begin() != bord.begin() && tangent.extendBack() );
        return tangent;                      
}

ArithmeticalDSSComputer< Iterator, Integer, 4> Left_Tangent (vector<Point> & bord, Point p) {
        Iterator p_it = find (bord.begin(), bord.end(), p);
        ArithmeticalDSSComputer< Iterator, Integer, 4> tangent;
        tangent.init( p_it );
        while ( tangent.begin() != bord.begin() && tangent.extendBack() );
        return tangent;                      
}

ArithmeticalDSSComputer< Iterator, Integer, 4> Right_Tangent (vector<Point> & bord, Point p) {
        Iterator p_it = find (bord.begin(), bord.end(), p);
        ArithmeticalDSSComputer< Iterator, Integer, 4> tangent;
        tangent.init( p_it );
        while ( tangent.end() != bord.end() && tangent.extendFront() );
        return tangent;                      
}