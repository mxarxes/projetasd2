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
  img.fillRectangle(1,1,4,4,Color::Green);
  Image img2(img);
  img.fillRectangle(1,3,3,7,Color::White);
  cout << img.width() << "*" << img.height() << " = " << img.size()<<std::endl;
  img.writeAIP("yes");
  img2.writeAIP("yes2");
  img.writeSVG("images/yes",10);
  img2.writeSVG("images/yes2",10);
  return 0;
}
