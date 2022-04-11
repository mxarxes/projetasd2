////////////////////////////////////////////////////////////////////////////////
/// This file is part of the Aerial Image Project (AIP).
///
/// Copyright (c) ...
///
/// The sources of AIP are distributed WITHOUT ANY WARRANTY.
////////////////////////////////////////////////////////////////////////////////

#include <cstdlib>
#include <ctime>
#include <sstream>
#include "FireSimulator.h"

using namespace std;

int main(void)
{
  srand(time(nullptr));
  std::cout<<"Hello World!"<<endl;
  Image img(7,5);
  Image img2(img);
  //std::cout<<img.size()<<endl;
  //std::cout<<img.height()<<endl;
  //std::cout<<img.width()<<endl;
  img.setPixel(1,1,Color::Green);
  img.writeSVG("images/emptyImage_7x5",100);
  std::cout<<img.toIndex(100,100)<<endl;
  std::cout<<(img.toCoordinate(4445)).first<<","<<(img.toCoordinate(4445)).second<<endl;
  return 0;
}
