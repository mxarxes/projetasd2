////////////////////////////////////////////////////////////////////////////////
/// This file is part of the Aerial Image Project (AIP).
///
/// Copyright (c) ...
///
/// The sources of AIP are distributed WITHOUT ANY WARRANTY.
////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include "Analyst.h"
#include <math.h>

Analyst::Analyst(const Image& img){
    tab = new t_case[img.size()];
    this->numberOfZones = img.size();
    this->nbPixels = img.size();
    this->w = img.width();
    this->h = img.height();
    std::pair<int,int> coordinatesCurrentPixel;
    std::pair<int,int> coordinatesComparingPixel;
    Color currentPixel;
    Color comparingPixel;
    for(int a = 0; a < img.size(); ++a){
        tab[a].zoneNumber = a;
        tab[a].col = img.getPixel(img.toCoordinate(a).first+1,img.toCoordinate(a).second+1);
    }
    for(int i = 0; i < img.size(); ++i){
        coordinatesCurrentPixel = img.toCoordinate(i);
        currentPixel = img.getPixel(coordinatesCurrentPixel.first+1,coordinatesCurrentPixel.second+1); // The pixel we are on
  
        if(img.toCoordinate(i).first < img.width()-1 && img.toCoordinate(i).second < img.height()-1){ // If we're not on the last pixel of a row or a column
        
            coordinatesComparingPixel.first = img.toCoordinate(i).first+1;
            coordinatesComparingPixel.second = img.toCoordinate(i).second; // Comparing with the pixel immediately on the right

            comparingPixel = img.getPixel(coordinatesComparingPixel.first+1,coordinatesComparingPixel.second+1);
                    
            if(currentPixel == comparingPixel){
                for(int k = 0; k < img.size();++k){
                    if(tab[k].zoneNumber == tab[img.toIndex(coordinatesComparingPixel.first,coordinatesComparingPixel.second)].zoneNumber){
                        tab[k].zoneNumber = tab[img.toIndex(coordinatesCurrentPixel.first,coordinatesCurrentPixel.second)].zoneNumber;
                    }
                }
            tab[img.toIndex(coordinatesComparingPixel.first,coordinatesComparingPixel.second)].zoneNumber = tab[img.toIndex(coordinatesCurrentPixel.first,coordinatesCurrentPixel.second)].zoneNumber;
            //std::cout<<"["<<coordinatesCurrentPixel.first<<";"<<coordinatesCurrentPixel.second<<"] and ["<<coordinatesComparingPixel.first<<";"<<coordinatesComparingPixel.second<<"] are in the same zone ("<<currentPixel<<"/"<<comparingPixel<<")"<<std::endl;

                }
            coordinatesComparingPixel.first = img.toCoordinate(i).first;
            coordinatesComparingPixel.second = img.toCoordinate(i).second+1;
            comparingPixel = img.getPixel(coordinatesComparingPixel.first+1,coordinatesComparingPixel.second+1); // Comparing with the pixel immediately below.
            if(currentPixel == comparingPixel){
                for(int k = 0; k < img.size();++k){
                    if(tab[k].zoneNumber == tab[img.toIndex(coordinatesComparingPixel.first,coordinatesComparingPixel.second)].zoneNumber){
                        tab[k].zoneNumber = tab[img.toIndex(coordinatesCurrentPixel.first,coordinatesCurrentPixel.second)].zoneNumber;
                    }
                }
                tab[img.toIndex(coordinatesComparingPixel.first,coordinatesComparingPixel.second)].zoneNumber = tab[img.toIndex(coordinatesCurrentPixel.first,coordinatesCurrentPixel.second)].zoneNumber;
                //std::cout<<"["<<coordinatesCurrentPixel.first<<";"<<coordinatesCurrentPixel.second<<"] and ["<<coordinatesComparingPixel.first<<";"<<coordinatesComparingPixel.second<<"] are in the same zone ("<<currentPixel<<"/"<<comparingPixel<<")"<<std::endl;
          
            }
        }
  
        else if(img.toCoordinate(i).second < img.height()-1){ // If we are on the last column but not on the last row
            coordinatesComparingPixel.first = img.toCoordinate(i).first;
            coordinatesComparingPixel.second = img.toCoordinate(i).second+1;
            comparingPixel = img.getPixel(coordinatesComparingPixel.first+1,coordinatesComparingPixel.second+1); // Only comparing with the pixel immediately below.
            if(currentPixel == comparingPixel){
                for(int k = 0; k < img.size();++k){
                    if(tab[k].zoneNumber == tab[img.toIndex(coordinatesComparingPixel.first,coordinatesComparingPixel.second)].zoneNumber){
                        tab[k].zoneNumber = tab[img.toIndex(coordinatesCurrentPixel.first,coordinatesCurrentPixel.second)].zoneNumber;
                    }
                }
                tab[img.toIndex(coordinatesComparingPixel.first,coordinatesComparingPixel.second)].zoneNumber = tab[img.toIndex(coordinatesCurrentPixel.first,coordinatesCurrentPixel.second)].zoneNumber;
                //std::cout<<"["<<coordinatesCurrentPixel.first<<";"<<coordinatesCurrentPixel.second<<"] and ["<<coordinatesComparingPixel.first<<";"<<coordinatesComparingPixel.second<<"] are in the same zone ("<<currentPixel<<"/"<<comparingPixel<<")"<<std::endl;

            }
        }

        else if(img.toCoordinate(i).first < img.width()-1){ // Last row but not last column
            coordinatesComparingPixel.first = img.toCoordinate(i).first+1;
            coordinatesComparingPixel.second = img.toCoordinate(i).second;
            comparingPixel = img.getPixel(coordinatesComparingPixel.first+1,coordinatesComparingPixel.second+1); // Comparing with the pixel immediately on the right
            if(currentPixel == comparingPixel){
                for(int k = 0; k < img.size();++k){
                    if(tab[k].zoneNumber == tab[img.toIndex(coordinatesComparingPixel.first,coordinatesComparingPixel.second)].zoneNumber){
                        tab[k].zoneNumber = tab[img.toIndex(coordinatesCurrentPixel.first,coordinatesCurrentPixel.second)].zoneNumber;
                    }
                }
                tab[img.toIndex(coordinatesComparingPixel.first,coordinatesComparingPixel.second)].zoneNumber = tab[img.toIndex(coordinatesCurrentPixel.first,coordinatesCurrentPixel.second)].zoneNumber;
                //std::cout<<"["<<coordinatesCurrentPixel.first<<";"<<coordinatesCurrentPixel.second<<"] and ["<<coordinatesComparingPixel.first<<";"<<coordinatesComparingPixel.second<<"] are in the same zone ("<<currentPixel<<"/"<<comparingPixel<<")"<<std::endl;
            
            }
        }
    }
    // for(int b = 0; b<img.size(); ++b){
    //     std::cout<<tab[b].zoneNumber<<";";
    //     if(img.toCoordinate(b).first == img.width()-1){
    //         std::cout<<std::endl;
    //     }
    // }
}
Analyst::~Analyst(){
    delete[] tab;
}

bool Analyst::belongToTheSameZone(int i1, int j1, int i2, int j2){
    return(tab[(j1*w)+i1].zoneNumber == tab[(j2*w)+i2].zoneNumber);
}
int Analyst::nbPixelsOfColor(Color c) const{
    int s = 0;
    for(int i = 0; i < h*w; ++i){
        if(tab[i].col == c){
            s++;
        }
    }
    return s;
}
int Analyst::nbZonesOfColor(Color c) const{
    std::set<int> zones;
    for(int i = 0; i < this->h*this->w; ++i){
        if(tab[i].col.toInt() == c.toInt()){
             zones.insert(tab[i].zoneNumber);
        }
        }
    return zones.size();
}
int Analyst::nbZones() const{
    std::set<int> zones;
    for(int i = 0; i < this->h*this->w; ++i){
            zones.insert(tab[i].zoneNumber);
        }
    return zones.size();
}
std::set<int> Analyst::zoneOfPixel(int i, int j){
    std::set<int> liste;
    for(int k = 0; k < h*w; ++k){
        if(tab[j*w+i].zoneNumber == tab[k].zoneNumber)//std::cout<<k<<" to coordinate is ("<<p.first<<","<<p.second<<")"<<std::endl;[k].zoneNumber){
            liste.insert(k);
        }
    return liste;
}
Image Analyst::fillZone(int i, int j, Color c){
    Image img2(w,h);
    for(int k = 0; k < w*h; ++k){
        if(tab[k].zoneNumber == tab[img2.toIndex(i,j)].zoneNumber){
            img2.setPixel((img2.toCoordinate(k).first)+1,(img2.toCoordinate(k).second)+1,c);
        }
    }
    return img2;
}