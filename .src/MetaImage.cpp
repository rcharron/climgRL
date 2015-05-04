#include "MetaImage.h"
#include <cmath>
#include <queue>
#include <set>
#include <unordered_set>


using namespace std;
using namespace DGtal;
using namespace DGtal::Z2i;

MetaImage::MetaImage(string filename):Image(PGMReader<Image>::importPGM(filename))
{
  updateMeta();
}

MetaImage::MetaImage(Image img):Image(img)
{
  updateMeta();
}
 
MetaImage::operator DigitalSet()
{
  DigitalSet set2d( this->domain() );
  SetFromImage<DigitalSet>::append<Image>(set2d, *this, 0, 255);
  
  return set2d;
}

MetaImage::operator Board2D()
{
  DigitalSet set2d( this->domain() );
  SetFromImage<DigitalSet>::append<Image>(set2d, *this, 0, 255);
  
  Board2D board;
  board << set2d.domain() << set2d;
  return board;
}

void MetaImage::savePGM(string filename)
{
  ofstream os(filename);
  if(os.fail())throw string("échec écriture "+filename);
  os<<"P5"<<endl<<width<<" "<<height<<endl<<1<<endl;
  for(int j=height-1;j>=0;j--)
  {
    for(int i=0;i<width;i++)
    {
      os<<(char)(*this)(Point(i,j));
    }
  }
  //static_cast<Board2D>(*this).saveSVG(filename.c_str());
  //PGMWriter<Image>::exportPGM(filename,*this);
}

void MetaImage::updateMeta()
{
  width=this->domain().upperBound()[0];
  height=this->domain().upperBound()[1];
//  cout << "width : " << width << "  ;  height : " << height << endl;
//  cout << "width : " << this->domain().lowerBound()[0] << "  ;  height : " << this->domain().lowerBound()[1] << endl;
  ComputeCenter();
  ComputeMean();
}


void MetaImage::ComputeCenter()
{
  centerx=0;
  centery=0;
  int p=0;
  for(int i=0;i<width;i++)
  {
    for (int j=0;j<height;j++)
    {
      if((*this)(Point(i,j))>0)
      {
	centerx+=static_cast<float>(i);
	centery+=static_cast<float>(j);
	p++;
      }
    }
  }
  centerx/=static_cast<float>(p);
  centery/=static_cast<float>(p);
}

void MetaImage::ComputeMean()
{
  mean=0;
  int p=0;
  float dist;
  for(int i=0;i<width;i++)
  {
    for (int j=0;j<height;j++)
    {
      if((*this)(Point(i,j)))
      {
	dist=(centerx-static_cast<float>(i))*(centerx-static_cast<float>(i))+(centery-static_cast<float>(j))*(centery-static_cast<float>(j));
	dist=sqrt(dist);
	mean+=dist;
	p++;
      }
    }
  }
  //cout<<"test !0 "<<p<<endl;
  mean/=static_cast<float>(p);
}

bool MetaImage::CanonicalValue(float x, float y)
{
  x-=0.5f;
  y-=0.5f;
  int i=static_cast<int>(centerx+x*4.0f*mean);
  int j=static_cast<int>(centery+y*4.0f*mean);
  if(domain().isInside(Point(i,j)))
    return (*this)(Point(i,j))>0;
  return false;
}

vector< Point > MetaImage::TheVoisins(Point p)
{
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



bool MetaImage::removeNoise()
{
    Domain mydomain = this->domain();
    int l,h;
    l=mydomain.upperBound()[0]+1;
    h=mydomain.upperBound()[1]+1;
    vector<vector<bool> > newcol(l,vector<bool>(h,false));
  
  bool change=false;
  for (Domain::Iterator it = mydomain.begin(); it != mydomain.end();it++){
    int noirs =0; 		//variable indiquant le nombre de noirs
    int blancs =0;		//variable indiquant le nombre de blancs
    bool couleur=(*this)(*it)>0;
    couleur?blancs=1:noirs=1;
    vector<Point> voisins = TheVoisins(*it);
    for (unsigned int i = 0; i < voisins.size(); i++){
        if (mydomain.isInside(voisins[i])){
	    (*this)(voisins[i])>0?blancs++:noirs++;
	    //noirs  += 1-image(voisins[i]);
	    //blancs += image(voisins[i]);
	}
    }
    if((blancs>noirs)^couleur)change=true;
    if (noirs < blancs) {newcol[(*it)[0]][(*it)[1]]=1;}
//    new_image.setValue(*it,(1+(noirs>blancs)) %2);
  }
  
  for(int i=0;i<l;i++)
    for(int j=0;j<h;j++)
      setValue(Point(i,j),newcol[i][j]);
  return change;

}

void MetaImage::iterRemoveNoise()
{
  for(int i=0;i<8&&removeNoise();i++);
}


void MetaImage::Open()
{
    Domain mydomain = this->domain();
    //int l,h;
    //l=domain.upperBound()[0]+1;
    //h=domain.upperBound()[1]+1;
    queue<Point> colorize;
  
  for (Domain::Iterator it = mydomain.begin(); it != mydomain.end();it++){
    if((*this)(*it)>0)
    {
      vector<Point> voisins = TheVoisins(*it);
      for(Point p:voisins)
	if (mydomain.isInside(p))
	  colorize.push(*it);
    }
  }
  
  while(!colorize.empty())
  {
      setValue(colorize.front(),1);
      colorize.pop();
  }

}



MetaImage MetaImage::getNormalized()
{

  MetaImage res(Domain(Point(0,0),Point(799,799)));
  for(int i=0;i<800;i++)
  {
    for(int j=0;j<800;j++)
    {
      res.setValue(Point(i,j),CanonicalValue((1.0f/800)*static_cast<float>(i),(1.0f/800)*static_cast<float>(j)));
      
    }
  }
  res.updateMeta();
  return res;
}


Object8_4 MetaImage::Skelton()
{
  DigitalSet set2d( domain() );
  SetFromImage<DigitalSet>::append<Image>(set2d, *this, 0, 255);
  Object8_4 object(dt8_4, set2d);
  queue<Point> P;
  
  Object8_4 border= object.border();
  for(DigitalSet::ConstIterator it = border.begin(), itend = border.end(); it != itend; ++it)
  {
    //Remember (*it) is a Point
    if (object.isSimple( *it ))
      P.push(*it);
  }
    
  while(!P.empty())
  {
    Point lp=P.front();
    P.pop();
    if(object.pointSet()(lp)&&object.isSimple(lp)&&object.neighborhoodSize(lp)>1)
    {
      object.pointSet().erase(lp);
      SmallObject8_4 N=object.properNeighborhood(lp);
      for(auto it=N.begin();it!=N.end();++it )
      {
	if(object.neighborhoodSize(lp)>1)
	  P.push(*it);
      }
    }  
  }
  return object;
}


void MetaImage::Skelton(string file)
{
DigitalSet set2d( domain() );
  SetFromImage<DigitalSet>::append<Image>(set2d, *this, 0, 255);
  Object8_4 object(dt8_4, set2d);
  queue<Point> P;
  
  Object8_4 border= object.border();
  for(DigitalSet::ConstIterator it = border.begin(), itend = border.end(); it != itend; ++it)
  {
    //Remember (*it) is a Point
    if (object.isSimple( *it ))
      P.push(*it);
  }
    
  while(!P.empty())
  {
    Point lp=P.front();
    P.pop();
    if(object.pointSet()(lp)&&object.isSimple(lp)&&object.neighborhoodSize(lp)>1)
    {
      object.pointSet().erase(lp);
      SmallObject8_4 N=object.properNeighborhood(lp);
      for(auto it=N.begin();it!=N.end();++it )
      {
	if(object.neighborhoodSize(lp)>1)
	  P.push(*it);
      }
    }  
  }
  MetaImage img(domain());
  for(DigitalSet::ConstIterator it = object.begin(), itend = object.end();it != itend; ++it)
    img.setValue(*it,1);
  img.savePGM(file);
}


void MetaImage::Fill()
{
  Domain mydomain = this->domain();
  /* Crée une nouvelle image toute blanche */
  int l,h;
    l=mydomain.upperBound()[0]+1;
    h=mydomain.upperBound()[1]+1;
    vector<vector<bool> > new_image(l,vector<bool>(h,true));
//  cout << "a créé nvelle image\n";
  /* Colorie en noir les bords */
  queue<Point> myqueue;
  Point current;
  for (Point it = mydomain.lowerBound(); mydomain.isInside(it);(it)[0]++){ //itère sur les points en bas
    if (!(*this)(it)) { new_image[it[0]][it[1]]=false; myqueue.push(it); }
  }
  for (Point it = mydomain.lowerBound(); mydomain.isInside(it);(it)[1]++){ //itère sur les points à gauche
    if (!(*this)(it)) { new_image[it[0]][it[1]]=false; myqueue.push(it); } 
  }
  for (Point it = mydomain.upperBound(); mydomain.isInside(it);(it)[0]--){ //itère sur les points en haut
    if (!(*this)(it)) { new_image[it[0]][it[1]]=false; myqueue.push(it); } 
  }
  for (Point it = mydomain.upperBound(); mydomain.isInside(it);(it)[1]--){ //itère sur les points à droite
    if (!(*this)(it)) { new_image[it[0]][it[1]]=false; myqueue.push(it); }  
  }
//  cout << "avant boucle while \n";
  while (!myqueue.empty()){
    vector<Point> voisins = TheVoisins(myqueue.front());    
    for (unsigned int i = 0; i < voisins.size(); i++){
      current = voisins[i];
      if (mydomain.isInside(current) && new_image[current[0]][current[1]] && !(*this)(current)){		//si le voisin est dans l'image et non traité et que sa couleur est noire, on le traite et on l'ajoute à la queue
	new_image[current[0]][current[1]]=false;
	myqueue.push(current);
      }
    }
    myqueue.pop();
  }
  /* Renvoie l'image ainsi obtenue */
//  cout << "end\n\n";
  for(int i=0;i<l;i++)
    for(int j=0;j<h;j++)
      setValue(Point(i,j),new_image[i][j]);
  
}


Object8_4 MetaImage::cleanSkelton()
{
  Object8_4 object=Skelton();
  if(object.computeConnectedness()==CONNECTED)return object;
  //cout<<"non conecté"<<endl;
  set<Point> representant;
  vector<Point> composante;
  vector<Point> bestcomposante;
  vector<Point> trash;
  
  for(DigitalSet::ConstIterator it = object.begin(), itend = object.end();it != itend; ++it)
  {
    if(representant.find(*it)!=representant.end())continue;
    queue<Point> q;
    q.push(*it);
    while(!q.empty())
    {
      Point pt=q.front();
      q.pop();
      if(representant.find(pt)!=representant.end())continue;
      representant.insert(pt);
      composante.push_back(pt);
      SmallObject8_4 N=object.properNeighborhood(pt);
      for(auto sit=N.begin();sit!=N.end();++sit )
      {
	
	if(representant.find(*sit)==representant.end())
	  q.push(*sit);
      }
    }
    if(composante.size()>bestcomposante.size())
      bestcomposante.swap(composante);
    for(Point pt:composante)
      trash.push_back(pt);
    composante.clear();
  }
  for(Point pt:trash)
    object.pointSet().erase(pt);
  return object;
}

int MetaImage::spineLength()
{
  Object8_4 object=cleanSkelton();
  Point pt=findExtremite(object);//*object.begin();
  object.pointSet().erase(pt);
  //cout<<"coucou spine de "<<pt[0]<<" "<<pt[1]<<endl;
  //try{
  pair<int,int> res=spineLength(object,pt);
  return max(res.first+1,res.second);
  //}
  //catch(exception e)
  //{
  //  cout<<e.what()<<endl;
  //  return 0;
  //}
}

pair<int,int> MetaImage::spineLength(Object8_4& object,Point depart)
{
  int length = 0;
  SmallObject8_4 N=object.neighborhood(depart);
  if(N.size()==0)return pair<int,int>(0,0);
  length++;
  while(N.size()==1)
  {
    length++;
    depart=*N.begin();
    object.pointSet().erase(depart);
    N=object.neighborhood(depart);
  }
  if(N.size()==0)return pair<int,int>(length,0);
  int l1,l2,l3;
  l1=l2=l3=0;
  for(auto sit=N.begin();sit!=N.end();++sit )
  {
    object.pointSet().erase(*sit);
      pair<int,int> res=spineLength(object,*sit);
      l3=max(l3,res.second);
      if(res.first>l2)
      {
	l2=11;
	l1=res.first;
      }
      else if(res.first>l1)l1=res.first;
  }
  return pair<int,int>(length+l1,max(l3,l1+l2));
}

DGtal::ImageContainerBySTLVector< Domain, unsigned int >::Point MetaImage::findExtremite(Object8_4& object)
{
    for(DigitalSet::ConstIterator it = object.begin(), itend = object.end();it != itend; ++it)
    {
      if((object.neighborhoodSize(*it)==2)||(object.neighborhoodSize(*it)==1))return *it;
    }
    throw string("Pas d'extremité");
}
