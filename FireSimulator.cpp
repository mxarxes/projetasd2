////////////////////////////////////////////////////////////////////////////////
/// This file is part of the Aerial Image Project (AIP).
///
/// Copyright (c) ...
///
/// The sources of AIP are distributed WITHOUT ANY WARRANTY.
////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include "Analyst.h"
#include "FireSimulator.h"

FireSimulator::FireSimulator(const Image& img){
    Analyst an(img);
    time = 0;
    timeTable = new int[img.size()];
    for(int i = 0; i < img.size(); ++i){
        timeTable[i] = 0;
    }
    img.writeAIP("tests/forest_0");
}
Image FireSimulator::tilt(){
    std::string filename = "tests/forest_"+std::to_string(this->time);
    Image img2(img2.readAIP(filename));

    std::cout<<"time : "<<this->time<<std::endl;
    // If time = 0, selecting a green pixel at random and set it on fire
    if(this->time == 0){
        int randPixel = rand() % img2.size();
        while(img2.getPixel(img2.toCoordinate(randPixel).first+1,img2.toCoordinate(randPixel).second+1) != Color::Green){
            randPixel = rand() % img2.size();
    }
        img2.setPixel(img2.toCoordinate(randPixel).first+1,img2.toCoordinate(randPixel).second+1,Color::Red);
        std::cout<<img2.toCoordinate(randPixel).first+1<<","<<img2.toCoordinate(randPixel).second+1<<" is on fire"<<std::endl;
    }
    else{
        for(int i = 1; i < img2.size(); ++i){
            if(img2.getPixel(img2.toCoordinate(i).first+1,img2.toCoordinate(i).second+1) == Color::Red){
                std::cout<<"yo"<<std::endl;
                propagateFire(img2, img2.toCoordinate(i).first,img2.toCoordinate(i).second);
                timeTable[i]++;
                if(timeTable[i] > 7){
                    img2.setPixel(img2.toCoordinate(i).first+1,img2.toCoordinate(i).second+1,Color::Black);
                }
            }
            else{
                std::cout<<img2.getPixel(img2.toCoordinate(i).first+1,img2.toCoordinate(i).second+1)<<" != "<<Color::Red<<std::endl;
            }
        }
    }
    ++(this->time);
    std::string title = ("tests/forest_"+std::to_string(time));
    img2.writeAIP(title);
    return img2;
}

void FireSimulator::passTime(int t){
    for(int i = 0; i < t; ++i){
        tilt();
    }
}
Image FireSimulator::propagateFire(const Image& img, int i, int j){
    std::cout<<"Fire propagating"<<std::endl;
    Image img2(img);
    Analyst an(img2);

    int leftPixel;
    int upPixel;
    int rightPixel;
    int downPixel;

    int remainingForest = an.zoneOfPixel(i,j).size();
    int newRedPixelsMax = (int)remainingForest/2; 
    int reddedPixels = 0;
    if(i > 0){ // If we're not on the first column, consider left pixel
        leftPixel = img.toIndex(i-1,j);
        if(rand()%4 == 1 && reddedPixels < newRedPixelsMax){
            img2.setPixel(img2.toCoordinate(leftPixel).first+1,img2.toCoordinate(leftPixel).second+1,Color::Red);
        }
    }
    if(j > 0){ // If not on the first row, consider upper pixel 
        upPixel = img.toIndex(i,j-1);
        if(rand()%4 == 1 && reddedPixels < newRedPixelsMax){
            img2.setPixel(img2.toCoordinate(upPixel).first+1,img2.toCoordinate(upPixel).second+1,Color::Red);
        }
    }
    if(i < img.width()){ // If not on the last column, consider right pixel
        rightPixel = img.toIndex(i+1,j);
        if(rand()%4 == 1 && reddedPixels < newRedPixelsMax){
            img2.setPixel(img2.toCoordinate(rightPixel).first+1,img2.toCoordinate(rightPixel).second+1,Color::Red);
        }
    }
    if(j < img.height()){ // If not on the last row, consider lower pixel
        downPixel = img.toIndex(i,j+1);
        if(rand()%4 == 1 && reddedPixels < newRedPixelsMax){
            img2.setPixel(img2.toCoordinate(downPixel).first+1,img2.toCoordinate(downPixel).second+1,Color::Red);
        }
    }
    return img2;

}
Image FireSimulator::generateImage(int t){
   // Image img2(passTime(t));
    //return img2;
    Image img(3,3);
    return img;
}