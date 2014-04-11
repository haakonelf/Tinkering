#pragma once;
#include <string>
#include <set>
#include <vector>

class Board{

private:
	int board[9][9]; //Dette kunne egentlig ha vært bestemt i programmet

	//enklere løsning enn 3D vektor:
	//gjør det litt vanskeligere å lage kordinatsystem
	std::set<int> setHor[9];
	std::set<int> setVer[9];
	std::set<int> setBox[9];

	vector<Trekk> trekkVec;

	int moveCount;

public:

	void printBoard();
	Board(std::string filnavn); //c++ forstår ikke string elno
	~Board();

	void makeSets(); 
	void write(std::string filnavn); //den forstår ikke

	int getBoxCoordinates(int hor, int ver);

	void setValue(int, int, int);

	std::set<int > possibleValues(int, int);

	bool possiblePlacement(int, int, int);

	void makeMove();
};

struct Trekk{
	int x;
	int y;
	int value;
};


