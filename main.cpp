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
  Image img(5,7);
  std::cout<<img.size()<<endl;
  img.writeSVG("imagecool",10);
  return 0;
}
