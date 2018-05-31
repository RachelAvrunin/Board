#include <iostream>
#include <string>
#include <time.h>


#include "Board.h"
#include "BMPgenerator.h"

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
    int i, j;

    vector<vector<RGB_data>> buffer(n, vector<RGB_data>(n, {0xff, 0xff, 0xff}));

    int x = n - 35;
    int y = 35;
    for (int i = 0; i < this->n; i++){
        y = 35;
        for (int j = 0; j < this->n; j++){
            if (board[i][j] == 'X'){
                drawX(buffer, x, y);
            }
            else if (board[i][j] == 'O'){
                drawO(buffer, x, y);
            }
            else if (board[i][j] == '.'){
                drawDot(buffer, x, y);
            }
            y = y + 35;
        }
        x = x - 35;
    }

    RGB_data a[n*n];

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            a[i*n+j] = buffer[i][j];
        }
    }

    // std::chrono::high_resolution_clock::time_point t = std::chrono::high_resolution_clock::now();
    // string time = t.time_since_epoch();
    
    time_t rawtime;
    struct tm * timeinfo;

    time (&rawtime);
    timeinfo = localtime (&rawtime);
    char* t;
    strftime (t,80,"%F_%T",timeinfo);
    strcat(t,"_img.bmp");
    cout << t << endl;
    bmp_generator(t, n, n, (BYTE *)a);

    return (string)t;//need to return the name of the file which is in t so we need to returno we need to retur that (cast t to string and return it)
}