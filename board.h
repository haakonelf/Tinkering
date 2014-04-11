#pragma once;
#include <string>
#include <set>

class Board{

private:
	int board[9][9]; //Dette kunne egentlig ha v�rt bestemt i programmet

	//enklere l�sning enn 3D vektor:
	//gj�r det litt vanskeligere � lage kordinatsystem
	std::set<int> setHor[9];
	std::set<int> setVer[9];
	std::set<int> setBox[9];


public:

	void printBoard();
	Board(string filnavn); //c++ forst�r ikke string elno
	~Board();

	void makeSets(); 
	void write(string filnavn); //den forst�r ikke

	int getBoxCoordinates(int hor, int ver);

	void setValue(int, int, int);

};