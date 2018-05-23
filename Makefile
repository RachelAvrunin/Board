CXX=clang++-5.0
CXXFLAGS=-std=c++14

all: Board.o Pixel.o Coordinate.o IllegalCoordinateException.o IllegalCharException.o Player.o TicTacToe.o Champion.o DummyPlayers.o



Board.o: Board.cpp Board.h Coordinate.h
	$(CXX) $(CXXFLAGS) --compile Board.cpp -o Board.o

Pixel.o: Pixel.cpp Pixel.h
	$(CXX) $(CXXFLAGS) --compile Pixel.cpp -o Pixel.o

IllegalCoordinateException.o: IllegalCoordinateException.cpp IllegalCoordinateException.h Board.h
	$(CXX) $(CXXFLAGS) -c  IllegalCoordinateException.cpp -o IllegalCoordinateException.o
	
IllegalCharException.o: IllegalCharException.cpp IllegalCharException.h
	$(CXX) $(CXXFLAGS) -c  IllegalCharException.cpp -o IllegalCharException.o

Coordinate.o: Coordinate.cpp Coordinate.h
	$(CXX) $(CXXFLAGS) --compile Coordinate.cpp -o Coordinate.o

Player.o: Player.cpp Player.h
	$(CXX) $(CXXFLAGS) --compile Player.cpp -o Player.o

TicTacToe.o: TicTacToe.cpp TicTacToe.h
	$(CXX) $(CXXFLAGS) --compile TicTacToe.cpp -o TicTacToe.o

Champion.o: Champion.cpp Champion.h
	$(CXX) $(CXXFLAGS) --compile Champion.cpp -o Champion.o

DummyPlayers.o: DummyPlayers.cpp DummyPlayers.h
	$(CXX) $(CXXFLAGS) --compile DummyPlayers.cpp -o DummyPlayers.o

clean: 
	rm *.o a.out