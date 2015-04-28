#include "DSS_Bresenham.h"


using namespace std;
using namespace DGtal;
using namespace DGtal::Z2i; //We'll only consider Z² digital space on
			    //32bit integers

///////////////////////////////////////////////////////////////////////////////


DigitalSet ConstructLineFstOctant(Domain & domain, Point p1, Point p2)
{
  DigitalSet Line(domain);
  int x1 = p1[0];
  int y1 = p1[1];
  int x2 = p2[0];
  int y2 = p2[1];
  int e = x2 - x1;
  int dx = 2*e;
  int dy = 2*(y2 - y1);
  while (x1 < x2){
    Line.insert(Point(x1,y1));
    x1 ++;
    e -= dy;
    if (e <= 0){
      y1 ++;
      e += dx;
    }
  }
  Line.insert(p2);
  return Line;
}

DigitalSet ConstructLineFstQuart(Domain & domain, Point p1, Point p2)
{
  DigitalSet Line(domain);
  Point p = p2 - p1;
  DigitalSet LineFstOctant(domain);
  if (p[1] <= p[0]) {
    Line = ConstructLineFstOctant(domain,p1,p2);
  } else {
//    cout << "construit ligne premier octant :\n";    
    LineFstOctant = ConstructLineFstOctant(domain,Point(0,0),Point(p[1],p[0]));
//    cout << "construit vraie ligne:\n";
    for (DigitalSet::Iterator it = LineFstOctant.begin(); it != LineFstOctant.end(); it++){
      Point to_add ((*it)[1],(*it)[0]);
      to_add = to_add + p1;
      Line.insert(to_add);
    }    
  }
  return Line;
}  

DigitalSet ConstructLine(Domain & domain, Point p1, Point p2)
{
  DigitalSet Line(domain);
  DigitalSet LineFstQuart(domain);
  Point p = p2 - p1;
  if (p[1] >= 0){
    if (p[0] >= 0){
//	cout << "construit ligne premier quart :\n";
        Line = ConstructLineFstQuart(domain,p1,p2);
    } else {
	LineFstQuart = ConstructLineFstQuart(domain,Point(0,0),Point(-p[0],p[1]));
	for (DigitalSet::Iterator it = LineFstQuart.begin(); it != LineFstQuart.end(); it++){
	  Point to_add (-(*it)[0],(*it)[1]);
	  to_add = to_add + p1;
	  Line.insert(to_add);
	}
    }
  } else {
    if (p[0] >= 0){
	LineFstQuart = ConstructLineFstQuart(domain,Point(0,0),Point(p[0],-p[1]));
	for (DigitalSet::Iterator it = LineFstQuart.begin(); it != LineFstQuart.end(); it++){
	  Point to_add ((*it)[0],-(*it)[1]);
	  to_add = to_add + p1;
	  Line.insert(to_add);	  
	}	
    } else {
        Line = ConstructLineFstQuart(domain,p2,p1);      
    }    
  }
  return Line;  
}

void Trace_Line (DigitalSet & s, Point p1, Point p2)
{
  Domain domain = s.domain();
  DigitalSet Line(domain);
  Line = ConstructLine(domain, p1, p2);
  for (DigitalSet::Iterator it = Line.begin(); it != Line.end(); it++){
    s.insert(*it);
  }  
}
                                                                           
                                                                           
///////////////////////////////////////////////////////////////////////////////



// ALGO :
/*
e = x_2 - x_1
dx = 2*e
dy = 2*(y_2 - y_1)
while (x_1 < x_2)
  display(x_1,y_1);
  x_1 ++;
  e  -= dy;
  if (e <= 0)
     y_1 ++;
     e += dx:
*/

