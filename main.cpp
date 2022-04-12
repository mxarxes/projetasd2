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
  //img.fill(Color::Red);
  img.fillRectangle(1,1,3,3, Color::Black);
  img.writeSVG("images/emptyImage_7x5",10);
  std::cout<<img.toIndex(3,2)<<endl;
  std::cout<<(img.toCoordinate(17)).first<<","<<(img.toCoordinate(17)).second<<endl;
  cout<<img.areConsecutivePixels(0,0,1,1);
  cout<<img.areConsecutivePixels(0,1,1,1);
  cout<<img.areConsecutivePixels(4,2,3,2);
  cout<<img.areConsecutivePixels(1,0,2,1);
  return 0;
}
