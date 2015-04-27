#ifndef IMAGE_H
#define IMAGE_H
#include <string>
#include <vector>

class image
{
public:
  image(std::string file);
  bool getValue(int i,int j);
  void write(std::string file);
  int CanonicalValue(float x, float y);
  float getNormMean();
  float getNormVar();
private:
  void updateMeta();
  void ComputeCenter();
  void ComputeMean();
  void ComputeVariance();
  std::vector<std::vector<bool> > data;
  int width;
  int height;
  float centerx;
  float centery;
  float mean;
  float var;
  float extrema;
  float remplissage;
};

#endif