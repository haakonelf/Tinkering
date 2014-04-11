#pragma once;
#include <string>
#include <set>

class Board{

private:
	int board[9][9]; //Dette kunne egentlig ha v�rt bestemt i programmet
	vector<vector<vector<set<int> > > > setArray3D; //3D vector som inneholder sets!


public:

	void printBoard();
	Board(string filnavn); //c++ forst�r ikke string elno
	~Board();

	void makeSets(); 
	void write(string filnavn); //den forst�r ikke


};