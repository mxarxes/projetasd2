////////////////////////////////////////////////////////////////////////////////
/// This file is part of the Aerial Image Project (AIP).
///
/// Copyright (c) ...
///
/// The sources of AIP are distributed WITHOUT ANY WARRANTY.
////////////////////////////////////////////////////////////////////////////////

#ifndef FIRE_SIMULATOR_H
#define FIRE_SIMULATOR_H

#include <vector>
#include "Image.h"
#include "Analyst.h"

////////////////////////////////////////////////////////////////////////////////
/// This is a fire simulator.
///
/// Given a pixel of forest in an image, it simulates a fire in the zone
/// of forest of the given pixel.
////////////////////////////////////////////////////////////////////////////////
class FireSimulator {
public:
// Constructor
FireSimulator(const Image& img);

// Passes one time unit. 
// If time was 0, creates a fire on a random green pixel.
Image tilt();

// Passes t time units.
void passTime(int t);

// Sets the pixel (i,j) red.
Image setOnFire(const Image& img, int i, int j);

// Propagate a random proportion of red pixels on adjacent 
//green pixels.
Image propagateFire(const Image& img, int i, int j);

// Makes the pixel (i,j) black.
void killPixel(int i, int j);

// Generate an image for a given time t.
Image generateImage(int t);



private:
int w;
int time;

// A matrice of ints. 
// Each int is the time the corresponding pixel on the image
// has been red for.
int *timeTable; 
};

#endif
