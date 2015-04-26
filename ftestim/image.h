#ifndef IMAGE_H
#define IMAGE_H
#include <string>

class image
{
public:
  image(std::string file);
  bool getValue(int i,int j);
private:
  void updateMeta();
  void ComputeCenter();
  void ComputeMean();
  vector<vector<bool> > data;
  int width;
  int height;
  float centerx;
  float centery;
  float mean;
};

#endif