#pragma once
#include <iostream>
#include <list>
#include "IllegalCharException.h"
#include "IllegalCoordinateException.h"
#include "Pixel.h"
#include "Coordinate.h"

using namespace std;


struct RGB {
  uint8_t red, green, blue;
public:
  RGB(): red(255), green(255), blue(255){}
  RGB(uint8_t red, uint8_t green, uint8_t blue): red(red), green(green), blue(blue) {}
};


class Board{
	private:
        
        Pixel** board;
       
    public:
        int n;

        //Constructor
        Board();
        Board(int);
        Board(const Board &);
        ~Board();

        void free();
        Pixel& operator[](const Coordinate);
        const Pixel& operator[](const Coordinate) const;
        Board& operator=(char const &);
        Board operator=(Board const &);
        friend bool operator==(Board const & , Board const &);
        void inputInsert(Board & , string & , uint &);
        void inputChecker(string &);
        int size() const;
        string draw(int);
        void drawx(RGB *, int, int,int);
        void drawo(RGB *, int, int,int);
        bool is_file_exist(string);
        //Stream
        friend ostream& operator << (ostream &, Board const &);
        friend istream& operator >> (istream & ,Board &);

};
