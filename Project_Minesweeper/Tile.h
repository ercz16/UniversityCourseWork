#pragma once

#include <vector>
#include <iostream>

using std::vector;
using std::cout;
using std::endl;
using std::ifstream;
using std::string;

class Tile {
	bool revealed;
	bool flagged;
	bool mine;
	int numAdjMines;
	vector<Tile*> adjacentTiles;

public:
	Tile();
	Tile(bool mine);

	void addAdjTile(Tile* ptr);

	// Setters
	void reveal();
	void toggleRevealed();
	void toggleFlagged();
	void flag();
	void setAdjMines(int n);
	void countMines();

	// Getters
	bool isRevealed();
	bool isFlagged();
	bool isMine();
	int getAdjMines();

	void dumpAdjMines();
	void cascade(int& numRevealed);
};

class Board {
	int rows;
	int cols;
	int numMines;
	int numFlags;
	int numRevealed;
	string state;

	vector<vector<Tile> > board;

public:
	Board(string fileName);

	// Initialization
	void initAdjTiles();
	void initNumMines();
	void reset();

	// Getters 
	int getRows();
	int getCols();
	int getNumMines();
	int getNumFlags();
	int getNumRevealed();
	string getState();
	Tile& getTile(int ind1, int ind2);

	// Setter
	void setState(string st);

	// Actions
	void checkWin();
	void leftClick(int x, int y);
	void rightClick(int x, int y);
	void revealBoard();
	void debug();
	void print();
	void printNumMines();
};