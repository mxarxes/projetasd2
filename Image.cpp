////////////////////////////////////////////////////////////////////////////////
/// This file is part of the Aerial Image Project (AIP).
///
/// Copyright (c) ...
///
/// The sources of AIP are distributed WITHOUT ANY WARRANTY.
////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "Image.h"

Image::Image(int w, int h){
     (this->w) = w;
     (this->h) = h;
     //std::cout<<"size of matrice : "<<w<<"x"<<h<<std::endl;
     matrice = new Color*[w];
     for(int i=0; i < h; ++i){ // creating h rows
          matrice[i] = new Color[h];
          for(int j = 0; j < w; ++j){ // creating w columns
               //std::cout<<i<<","<<j<<" initialized"<<std::endl;
               matrice[i][j] = Color::Black;
          }
     }
     matrice[0][0] = Color::Red;
     matrice[h-1][w-1] = Color::Red;
}
Image::Image(const Image& img){
     (this->w) = img.width();
     (this->h) = img.height();
     matrice = new Color*[w];
     for(int i=0; i < img.height(); ++i){ // creating h rows
          matrice[i] = new Color[h];
          for(int j = 0; j < img.width(); ++j){ // creating w columns
               matrice[i][j] = img.getPixel(i+1,j+1);
          }
     }
}
//Destructor
Image::~Image(){
     //delete[] matrice;
}

int Image::width() const{
     return this->w;
}
int Image::height() const{
     return this->h;
}
int Image::size() const{
     return width()*height();
}
Color Image::getPixel(int i, int j) const{
     assert(i>0);
     assert(j>0);
     assert(j<=width());
     assert(i<=height());
     return matrice[i-1][j-1];
}

void Image::writeSVG(const std::string& filename, int pixelSize) const
{
  assert(pixelSize > 0);

  std::ofstream file;
  file.open(filename + ".svg");

  if (!file) throw std::runtime_error("error open file (write SVG)");

  file << "<?xml version=\"1.0\" encoding=\"utf-8\"?>"
       << std::endl
       << "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\""
       << pixelSize*width()
       << "\" height=\""
       << pixelSize*height()
       << "\">"
       << std::endl;

  for (int i = 1; i <= height(); ++i)
    for (int j = 1; j <= width(); ++j)
      file << "<rect width=\""
           << pixelSize
           << "\" height=\""
           << pixelSize
           << "\" x=\""
           << pixelSize*(j-1)
           << "\" y=\""
           << pixelSize*(i-1)
           << "\" fill=\""
           << getPixel(i, j)
           << "\" />"
           << std::endl;

  file << "</svg>"
       << std::endl;

  file.close();
}
