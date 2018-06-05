#include <iostream>
#include <string>
#include <fstream>
#include "Board.h"

using namespace std;

Board::Board(){
	this->n = 0;
	this->board = nullptr;
}

Board::Board(int n){
	if(n < 0)
		throw "wrong input";
	this->n = n;
	board = new Pixel*[n];
	for(int i = 0; i < n; i++){
		board[i] = new Pixel[n];
	}
}

Board::Board(const Board & b){
    n = b.n;
    board = new Pixel*[b.n];
    for(uint i = 0; i < b.n; i++){
        board[i] = new Pixel[n];
        for(uint j = 0 ; j < b.n ; j++)
            (*this)[{i,j}] = b[{i,j}];
    }
}

//Destructor
Board::~Board(){
	this-> free();
}

void Board::free(){
	for(int i = 0 ; i < n ; i++)
		delete [] board[i];
	delete [] board;
}

int Board::size() const{
    return this->n;
}


Pixel& Board::operator[](const Coordinate c){
    if(c.xPlace > n-1 || c.yPlace > n-1)
        throw IllegalCoordinateException({(int)c.xPlace,(int)c.yPlace});
	int a = c.xPlace;
	int b = c.yPlace;
		return this->board[a][b];
}

const Pixel& Board::operator[](const Coordinate c) const{
    if(c.xPlace > n-1 || c.yPlace > n-1)
        throw IllegalCoordinateException({(int)c.xPlace,(int)c.yPlace});
	int a = c.xPlace;
	int b = c.yPlace;
		return this->board[a][b];
}

Board& Board:: operator=(char const& c){
	if (c!='.' && c!='X' && c!='O')
		throw IllegalCharException(c);
	for(uint i=0;i<this->n;++i){
		for(uint j=0;j<this->n;++j){
			(*this)[{i,j}] = c;
		}
	}
	return *this;
}

Board Board::operator=(Board const & b){
	this-> free();
    n = b.n;
    board = new Pixel*[b.n];
    for(uint i = 0; i < b.n; i++){
        board[i] = new Pixel[n];
        for(uint j = 0 ; j < b.n ; j++)
            (*this)[{i,j}] = b[{i,j}];
    }
    return *this;
}

void Board::inputChecker(string & line){
    for(uint i = 0 ; i < line.length() ; i++)
        if(line.at(i) != 'X' && line.at(i) != 'O' && line.at(i) != '.')
            throw "wrong input";
}

void Board::inputInsert(Board & board, string & line, uint & counter){
    for(uint i = 0 ; i < board.n ; i++){
        board[{counter,i}] = line.at(i);
    }
        counter++;
}

istream& operator >> (istream & is,Board & board){
    string tmp;
    uint counter = 0;
    uint length = 0;
    while(is >> tmp){
        if(!counter){
            length = tmp.length();
            board.free();
            board.n = length;
            board.board = new Pixel*[length];
            for(uint i = 0; i < length; i++){
                board.board[i] = new Pixel[length];
            }
            board.inputChecker(tmp);
            board.inputInsert(board,tmp,counter);
        }
        else if(counter < length && tmp.length() == length){
            board.inputChecker(tmp);
            board.inputInsert(board,tmp,counter);
        } else{ 
            board.free();
            throw "wrong input";
        }
    }
    return is;
}

ostream& operator << (ostream & os, Board const & b){
    for(int i = 0 ; i < b.n ; i++){
        for(int j = 0 ; j < b.n ; j++){
            os << b.board[i][j];
        }
        os << endl;
    }
    return os;
}
string Board::draw(int n){
    RGB image[n*n];
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++){
                image[i*n + j].red = 255;
                image[i*n + j].green = 255;
                image[i*n + j].blue = 225;
        }
    int k = n/this->size();
    for(uint i = 0; i < this->size(); i++){
        for(uint j = 0; j < this->size(); j++){
            if((*this)[{i,j}] == 'X')
                drawx(image, i*(n*k)+j*k + n%this->size()/2, k,n);
            else if((*this)[{i,j}] == 'O')
                drawo(image, i*(n*k)+j*k + n%this->size()/2, k,n);
        }
    }
    for(int i = 0; i < n-n%this->size(); i++){
        for(int j = 0; j < n-n%this->size(); j++){
            if(j>0 && j % k == 0 && j< n-k+1){
                image[(i+n%this->size()/2)*n + j+n%this->size()/2].red = 0;
                image[(i+n%this->size()/2)*n + j+n%this->size()/2].green = 0;
                image[(i+n%this->size()/2)*n + j+n%this->size()/2].blue = 0;
            }
            if(i>0 && i % k == 0 && i< n-k+1){
                image[(i+n%this->size()/2)*n + j+n%this->size()/2].red = 0;
                image[(i+n%this->size()/2)*n + j+n%this->size()/2].green = 0;
                image[(i+n%this->size()/2)*n + j+n%this->size()/2].blue = 0;
            }
        }
    }
    string filename = to_string(n);
    int counter = 0;

    while (is_file_exist(filename+".ppm")){
        counter++;
        filename = to_string(n) + "_" + to_string(counter);
    }
    filename += ".ppm";
    ofstream out(filename, ios::out | ios::binary);
    out << "P6" << endl << n << " " << n << endl << 255 << endl;
    out.write(reinterpret_cast<char*>(&image), 3*n*n);
    out.close();
    return filename;
}

void Board::drawx(RGB * image, int x, int n,int orig){
    for (int i=0; i<n; i++)
        for (int j=0; j<n; ++j)
            if (i == j || i == j+1 || i+1 == j || (n - i - 1 == j) || (n - i - 2 == j) || (n - i == j)){
                image[x+(i+orig%this->size()/2)*orig+j].red = 255;
                image[x+(i+orig%this->size()/2)*orig+j].green = 0;
                image[x+(i+orig%this->size()/2)*orig+j].blue = 0;
            }
}

void Board::drawo(RGB * image, int x, int n,int orig){
    for (int i=0; i<n; ++i)
        for (int j=0; j < n; ++j)
            if(((i-0.5*n)*(i-0.5*n) + (j-0.5*n)*(j-0.5*n) <= 0.5*n*0.5*n+n) &&
                ((i-0.5*n)*(i-0.5*n) + (j-0.5*n)*(j-0.5*n) >= 0.5*n*0.5*n-n)){
                image[x+(i+orig%this->size()/2)*orig+j].red = 255;
                image[x+(i+orig%this->size()/2)*orig+j].green = 0;
                image[x+(i+orig%this->size()/2)*orig+j].blue = 255;
            }
}

bool Board::is_file_exist(const string fileName)
{
    std::ifstream infile(fileName);
    return infile.good();
}