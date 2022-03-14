////////////////////////////////////////////////////////////////////////////////
/// This file is part of the Aerial Image Project (AIP).
///
/// Copyright (c) ...
///
/// The sources of AIP are distributed WITHOUT ANY WARRANTY.
////////////////////////////////////////////////////////////////////////////////

#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include "Color.h"

////////////////////////////////////////////////////////////////////////////////
/// This a rectangular colored image.
////////////////////////////////////////////////////////////////////////////////
class Image {
public:
  /// Creates a black rectangular image with w*h pixels
  /// w is the width of this image, h is its height
  Image(int w, int h);

  /// Destructor
  ~Image();

  /// Copy constructor
  Image(const Image& img);

  /// No assignment
  Image& operator=(const Image& img) = delete;

  /// Returns the width of this
  int width() const;

  /// Returns the height of this
  int height() const;

  /// Returns the number of pixels of this
  int size() const;

  /// Gets the pixel in the i-th row and j-th column
  /// 1 <= i <= height(), 1 <= j <= width()
  Color getPixel(int i, int j) const;

  /// Sets the pixel in the i-th row and j-th column
  /// 1 <= i <= height(), 1 <= j <= width()
  /// col is the new color
  //void setPixel(int i, int j, Color col);

  /// Maps a coordinate (i, j) to a unique identifier
  //int toIndex(int i, int j) const;

  /// Maps an identifier to the corresponding coordinates
  /// Given the result p, p.first is the row and p.second is the column 
  //std::pair<int, int> toCoordinate(int k) const;

  /// Fills this with a given color
  //void fill(Color c);

  /// Fills a rectangle in this with a given color
  /// (i1, j1) is the upper left corner
  /// (i2, j2) is the lower right corner
  //void fillRectangle(int i1, int j1, int i2, int j2, Color c);
  
  /// Generates a SVG image given a filename without the extension
  /// The file name is of this image is filename.svg
  /// Each pixel is represented by a square of side pixelSize
  /// Throws an exception std::runtime_error if an error occurs
  void writeSVG(const std::string& filename, int pixelSize) const;

  /// Saves this in a text file using a specific format:
  ///   - width and height of this on the first line;
  ///   - followed by the lines of this such that each digit
  ///     corresponds to the color of the corresponding pixel.
  /// An example of output file follows:
  ///   5 3
  ///   10014
  ///   01233
  ///   23101
  /// The output file is named filename.aip
  /// Throws an exception std::runtime_error if an error occurs
  //void writeAIP(const std::string& filename) const;

  /// Creates an image from an AIP file
  /// The file name must be given without the extension
  /// Throws an exception std::runtime_error if an error occurs
  //static Image readAIP(const std::string& filename);

  /// Returns true if this and img are equal
  //bool operator==(const Image& img) const;

  /// Returns true if this and img are different
  //bool operator!=(const Image& img) const;

  /// Returns true if (i1, j1) and (i2, j2) are two consecutive piels of this
  //bool areConsecutivePixels(int i1, int j1, int i2, int j2);

private:
int w;
int h;
Color** matrice;
  /// Tests if (i,j) is the coordinates of some pixel of this
  //bool isValidCoordinate(int i, int j) const;
};

/// Generates an image of width w and height h such that each pixel is
/// selected randomly.
//Image makeRandomImage(int w, int h);

#endif
