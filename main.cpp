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
#include "Analyst.h"

using namespace std;

int main(void)
{
  srand(time(nullptr));
  std::cout<<"Hello World!"<<endl;
  Image img(5,5);
 img.fillRectangle(0,0,3,3,Color::Green);
 img.fillRectangle(2,1,4,2,Color::Red);
 img.fillRectangle(1,3,1,4,Color::Blue);
 img.writeAIP("yes");
 img.writeSVG("images/yes",10);
  Analyst an(img);
  // std::cout<<an.belongToTheSameZone(0,0,3,2)<<std::endl; //f
  // std::cout<<an.belongToTheSameZone(2,4,3,4)<<std::endl; //f
  // std::cout<<an.belongToTheSameZone(0,4,1,4)<<std::endl; //f
  // std::cout<<an.belongToTheSameZone(2,0,3,0)<<std::endl; //v
  // std::cout<<an.belongToTheSameZone(4,2,4,3)<<std::endl; //v
  Image img2(img);
  an.fillZone(1,1,Color::White).writeSVG("images/yeswhite",10);
  return 0;
}
