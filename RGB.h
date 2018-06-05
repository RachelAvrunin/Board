#pragma once
#include <iostream>
#include <list>
#include <string>
#include "Pixel.h"
#include "Coordinate.h"
using namespace std;

class RGB {
    public:
        RGB(): red(255), green(255), blue(255){}
        RGB(uint8_t red, uint8_t green, uint8_t blue): red(red), green(green), blue(blue) {}
        uint8_t red, green, blue;



//Draw an X 
void drawx(RGB * image, int x, int n,int orig){
    for (int i=0; i<n; i++)
        for (int j=0; j<n; ++j)
            if (i == j || i == j+1 || i+1 == j || (n - i - 1 == j) || (n - i - 2 == j) || (n - i == j)){
                image[x+(i+orig%this->size()/2)*orig+j].red = 255;
                image[x+(i+orig%this->size()/2)*orig+j].green = 0;
                image[x+(i+orig%this->size()/2)*orig+j].blue = 0;
            }
}

//Draw an O
void drawo(RGB * image, int x, int n,int orig){
    for (int i=0; i<n; ++i)
        for (int j=0; j < n; ++j)
            if(((i-0.5*n)*(i-0.5*n) + (j-0.5*n)*(j-0.5*n) <= 0.5*n*0.5*n+n) &&
                ((i-0.5*n)*(i-0.5*n) + (j-0.5*n)*(j-0.5*n) >= 0.5*n*0.5*n-n)){
                image[x+(i+orig%this->size()/2)*orig+j].red = 0;
                image[x+(i+orig%this->size()/2)*orig+j].green = 0;
                image[x+(i+orig%this->size()/2)*orig+j].blue = 255;
            }
}

bool is_file_exist(const string fileName)
{
    std::ifstream infile(fileName);
    return infile.good();
}
};