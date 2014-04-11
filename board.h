#pragma once;
#include <string>
#include <set>

class Board{

private:
	int board[9][9]; //Dette kunne egentlig ha vært bestemt i programmet

	//enklere løsning enn 3D vektor:
	//gjør det litt vanskeligere å lage kordinatsystem
	std::set<int> setHor[9];
	std::set<int> setVer[9];
	std::set<int> setBox[9];


public:

	void printBoard();
	Board(string filnavn); //c++ forstår ikke string elno
	~Board();

	void makeSets(); 
	void write(string filnavn); //den forstår ikke

	int getBoxCoordinates(int hor, int ver);

	void setValue(int, int, int);

};