////////////////////////////////////////////////////////////////////////////////
/// This file is part of the Aerial Image Project (AIP).
///
/// Copyright (c) ...
///
/// The sources of AIP are distributed WITHOUT ANY WARRANTY.
////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <math.h>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "Image.h"

Image::Image(int w, int h){
     (this->w) = w;
     (this->h) = h;
     //std::cout<<"size of matrice : "<<w<<"x"<<h<<std::endl;
     matrice = new Color[w*h];
     for(int i=0; i < w*h; ++i){
               //std::cout<<i<<","<<j<<" initialized"<<std::endl;
               matrice[i] = Color::Black;
          }
     }
Image::Image(const Image& img){
     (this->w) = img.width();
     (this->h) = img.height();
     matrice = new Color[w*h];
     std::pair<int,int> point;
     for(int i=0; i < img.size(); ++i){
               point = toCoordinate(i);
               matrice[i] = img.getPixel(point.first+1,point.second+1);
     }
}
//Destructor
Image::~Image(){
     delete[] matrice;
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
     assert(i<=width());
     assert(j>0);
     assert(j<=height());
     return matrice[(j-1)*width()+(i-1)];
}

void Image::setPixel(int i, int j, Color col){
     assert(i>0);
     assert(i<=width());
     assert(j>0);
     assert(j<=height());
     matrice[(j-1)*width()+(i-1)] = col;
}

int Image::toIndex(int i, int j) const{
     return j*width()+i;
}

std::pair<int, int> Image::toCoordinate(int k) const{
     std::pair<int, int> p;
     p.first = (k%width());
     p.second = (int)(k/width());
     return p;
}
void Image::fill(Color c){
          for(int i=0; i < size()-1; ++i){ // creating h rows
               setPixel(toCoordinate(i).first,toCoordinate(i).second,c);
          }
     }
void Image::fillRectangle(int i1, int j1, int i2, int j2, Color c){
     for(int h = j1; h <= j2; ++h){ // For each row
          for(int k = i1; k <=i2; ++k){ // for each column of the rectangle
               setPixel(h+1,k+1,c);
          }
     }
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
           << getPixel(j,i)
           << "\" />"
           << std::endl;

  file << "</svg>"
       << std::endl;

  file.close();
}
void Image::writeAIP(const std::string& filename) const{
     std::cout<<"writing AIP : "<<filename<<std::endl;
     std::ofstream file;
     file.open(filename + ".aip");
     if (!file) throw std::runtime_error("error open file (write AIP)");
     file << width() <<" "<<height()<<std::endl;
     for(int i = 1 ; i <= height(); ++i){
          for(int j = 1 ; j <= width(); ++j){
               file << getPixel(j,i).toInt();
          }
          file<<std::endl;
     }
  }
/// Creates an image from an AIP file
/// The file name must be given without the extension
/// Throws an exception std::runtime_error if an error occurs
Image Image::readAIP(const std::string& filename)
{
    int width, height, tempo;
    std::string s1,s2;
    Color* c = new Color();
    std::ifstream file;
    file.open(filename + ".aip");

    if (!file) throw std::runtime_error("error open file (read AIP)");

    getline(file, s1);
    while(s1.at(0) != 32){
      s2 = s2 + s1.at(0);
      s1.erase(0,1);
    }

    height = stoi(s2);
    s1.erase(0,1);
    width = stoi(s1);

    Image* img = new Image(width, height);

    for (int i = 1; i <= height; ++i) {
      getline(file, s1);
        for (int j = 1; j <= width; ++j) {
          s2 = s1.at(0);
          tempo = stoi(s2);
          img->matrice[j*width+i] = c->makeColor(tempo+1);
          s1.erase(0,1);
        }
    }

    file.close();
    return *img;
}
bool Image::operator==(const Image& img) const{
     for(int i = 1; i <= height(); ++i){
          for(int j = 1; j <= width(); ++j){
               if(getPixel(i,j) != img.getPixel(i,j)){
                    return false;
               }
          }
     }
     return true;
}
bool Image::operator!=(const Image& img) const{
          for(int i = 1; i <= size(); ++i){
               if(getPixel(toCoordinate(i).first,toCoordinate(i).second) != img.getPixel(toCoordinate(i).first,toCoordinate(i).second)){
                    return true;
               }
          }
     return false;
}
bool Image::isValidCoordinate(int i, int j) const{
     return (i> 0 && j > 0 && i <= width() && j <= height());
}
bool Image::areConsecutivePixels(int i1, int j1, int i2, int j2){
     return sqrt(pow(i1-i2,2) + pow(j1-j2,2)) == 1;
}
