
#include "board.h"
#include <iostream>
#include <fstream>
#include <string>
//#include <vector> brukes ikke lenger
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



void Board::makeSets(){ //skal vi virkelig ha 81*3 sets?
	//enklere metode enn vektor:
	setHor[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	setVer[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	setBox[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	////std::set<int> box(0, 9);
	////vector<vector<vector<set<int> > > > setArray3D; //3D vector som inneholder sets!

	////skalere
	//setArray3D.resize(9);
	//for (int i = 0; i < 9; ++i) {
	//	setArray3D[i].resize(9);
	//	for (int j = 0; j < 9; ++j)
	//		setArray3D[i][j].resize(3);
	//}
	////tilordne sett'ene verdier
	//for (int i = 0; i < 9; ++i) { //horisontalt
	//	for (int j = 0; j < 9; ++j){ //vertikalt
	//		for (int y = 0; y < 3; y++){ //box  ---> eller istedet 9x9 plasser med 3 sets hver
	//			setArray3D[i][j][y] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };// siden det er sets tilodrner jeg alle verdier uten rekkefølge
	//		}
	//	}
	//}
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
			/*board[avsnitt][i] = line[i];*/
			setValue(avsnitt, i, line[i]);//dat new implementation

		}
		avsnitt++;
	}
	inFile.close(); //var det alt?

	makeSets();
	moveCount = 0;

	cout << "\t\tBoard Initialized";
}

Board::~Board(){
	
	delete[]board;
	//board = nullptr; //dette liker den ikke? lol

	//slett set!!
	delete[]setHor;
	delete[]setVer;
	delete[]setBox;

	//setHor[] = nullptr; nei det liker den ikke

	//men redudant uansett så lol

}

void Board::write(string filnavn){
	ofstream outFile;
	outFile.open(filnavn);

	if (outFile.fail()){
		cerr << "\t\tError creating file";
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

int Board::getBoxCoordinates(int hor, int ver){
	//kan dette forenkles?
	//kan jeg lage if - for setning elno? det hadde jo v'rt best, men da må jeg  kode variabelnavn, som kanskej ikke funker
	
	
	return (hor - 1) / 3 + 3 * ((ver - 1) / 3);
	
	
	//
	//if (hor < 4 && ver < 4){
	//	return 0;
	//}
	//else if (hor < 7 && ver < 4){
	//	return 1;
	//}
	//else if (hor < 10 && ver < 4){
	//	return 2;
	//}
	//else if (hor < 4 && ver < 7){ //forstørrer området sakte men sikkert, og trnger derfor ikke flere if'z
	//	return 3;
	//}
	//else if (hor < 7 && ver < 7){
	//	return 4;
	//}
	//else if (hor < 10 && ver < 7){
	//	return 5;
	//}
	//else if (hor < 4 && ver < 10){
	//	return 6;
	//}
	//else if (hor < 7 && ver < 10){
	//	return 7;
	//}
	//else if (hor < 10 && ver < 10){
	//	return 8;
	//}
	//else{
	//	cerr << "\t\tUgyldig plassering";
	//}
}


void Board::setValue(int hor, int ver, int value){
	board[hor][ver] = value; 

	setHor[hor].erase(value);
	setVer[ver].erase(value);
	setBox[getBoxCoordinates(hor, ver)].erase(value);

}

set<int > Board::possibleValues(int hor, int ver){ 

	set<int > rute = setHor[hor]; //funker dette for hvert element i setHor[hor]?

	//tar utgangspunkt i sethor
	for (auto it = (setHor[hor]).begin(); it != setHor[hor].end(); it++){ 
		//om den ikke finnes i enten ver eller box slettes den fra hor
		if (setVer[ver].find(*it) == setVer[ver].end() || setBox[getBoxCoordinates(hor, ver)].find(*it) == setBox[getBoxCoordinates(hor, ver)].end()){
			rute.erase(*it);
		}
	}
	return rute;
}


bool Board::possiblePlacement(int hor, int ver, int value){
	//er den lik end finnes den ikke
	if (possibleValues(hor, ver).find(value) != possibleValues(hor, ver).end()){
		return false;
	}
	return true;
}

void Board::makeMove(){
	int moveCount = 0;

	int hor, ver, value = 0;
	bool play = true;
	string action;
	while (play){
		cout << "Please enter horizontal coordinate: ";
		cin >> hor;
		cout << "Please enter vertical coordinate: ";
		cin >> ver;
		cout << "Please enter value";
		cin >> value;

		if (hor == 0 || ver == 0 || value == 0){ //gjør det heller sånn enn å spørre brukeren, blir "" det samme som uendret??
			cout << "Action menu, to skip back steps write back, for swag type swag\n Action: ";
			cin>>action
			play = false;

		}
		else{
			setValue(hor, ver, value);
			
			Trekk datMove;
			datMove.x = hor;
			datMove.y = ver;
			datMove.value = value;

			trekkVec.push_back(datMove);

		}
	}


}