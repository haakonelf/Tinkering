
#include "board.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

void Board::printBoard(){


	for (int i = 0; i < 9; i++){
		//en linje
		for (int j = 0; j < 9; j++){
			//for en rute
			if ((j % 3) == 0){
				std::cout << "|";//får å få den fine ekstra linjen imellom 3x3 rutene, skjer ved index 3 og 6
			}
			if (board[i][j] == 0){
				std::cout << "|" << "_";
			}
			else{
				std::cout << "|" << board[i][j]; //prøvde template her, funka ikke?
			}
		}
	std::cout << endl;
	}
}

Board::Board(string filnavn){ //c++ finner ikke denne funksjonen her?
	int board[9][9] = {0}; //her erstatter jeg senere 0 med _ .

	ifstream inFile;
	inFile.open(filnavn);

	if (inFile.fail()){
		cerr << "Error opening file";
		exit(1);
	}
	string line;
	int avsnitt = 0;
	while (getline(inFile, line)){
		for (int i = 0; i < 9; i++){
			board[avsnitt][i] = line[i];
		}
		avsnitt++;
	}
	inFile.close(); //var det alt?
	cout << "\t\tBoard Initialized";
}

Board::~Board(){

	delete[]board;
	//board = nullptr; //dette liker den ikke? lol

	//slett vector!!

}

void Board::write(string filnavn){
	ofstream outFile;
	outFile.open(filnavn);

	if (outFile.fail()){
		cerr << "Error creating file";
		exit(1);
	}
	
	for (int i = 0; i < 9; i++){
		for (int j = 0; j < 9; j++){
			outFile << board[i][j]; //legger denne på endl? isåfall må jeg <<\b
		}
		outFile << endl;
	}
	outFile.close();
	cout << "\t\tBoard written";
}






void Board::makeSets(){ //skal vi virkelig ha 81*3 sets?

	//std::set<int> box(0, 9);
	//vector<vector<vector<set<int> > > > setArray3D; //3D vector som inneholder sets!


	//skalere
	setArray3D.resize(9);
	for (int i = 0; i < 9; ++i) {
		setArray3D[i].resize(9);
		for (int j = 0; j < 9; ++j)
			setArray3D[i][j].resize(9);
	}
	//tilordne sett'ene verdier
	for (int i = 0; i < 9; ++i) { //horisontalt
		for (int j = 0; j < 9; ++j){ //vertikalt
			for (int y = 0; y < 9; y++){ //box
				setArray3D[i][j][y] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };// siden det er sets tilodrner jeg alle verdier uten rekkefølge

			}
		}
	}





}


