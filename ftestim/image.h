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
  void dessinfourier(std::string file);
  float distanceEMD(image i2);
private:
  void updateMeta();
  void myfourier();
  void ComputeCenter();
  void ComputeMean();
  std::vector<std::vector<bool> > data;
  std::vector<std::vector<double> > fourier;
  int width;
  int height;
  float centerx;
  float centery;
  float mean;
};

#endif