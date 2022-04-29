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

 img.writeAIP("yes");

  Analyst an(img);
  FireSimulator fs(img);


  return 0;
}
