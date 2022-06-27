#include <fstream>

#include "Tile.h"
#include "Random.h"

using std::vector;
using std::cout;
using std::endl;
using std::ifstream;
using std::string;

Tile::Tile() {
	flagged = false;
	mine = false;
	revealed = false;
	numAdjMines = 0;
}

Tile::Tile(bool isMine) {
	flagged = false;
	mine = isMine;
	revealed = false;
	numAdjMines = 0;
}

void Tile::addAdjTile(Tile* ptr) {
	adjacentTiles.push_back(ptr);
}

void Tile::reveal() {
	revealed = true;
}

void Tile::toggleRevealed() {
	revealed = !revealed;
}

void Tile::toggleFlagged() {
	flagged = !flagged;
}

void Tile::flag() {
	flagged = true;
}

void Tile::setAdjMines(int n) {
	numAdjMines = n;
}

void Tile::countMines() {
	for(unsigned int i = 0; i < adjacentTiles.size(); ++i) {
		if(adjacentTiles[i]->isMine()) {
		   	numAdjMines++;
		}
	}
}

bool Tile::isRevealed() {
	return revealed;
}

bool Tile::isFlagged() {
	return flagged;
}

bool Tile::isMine() {
	return mine;
}

int Tile::getAdjMines() {
	return numAdjMines;
}

void Tile::dumpAdjMines() {
	for(unsigned int i = 0; i < adjacentTiles.size(); ++i) {
		cout << adjacentTiles[i]->isMine() << endl;
	}
}

void Tile::cascade(int& numRevealed) {
	if(isMine()) return;
	if(isRevealed()) return;
	if(isFlagged()) return;

	reveal();
	numRevealed++;

	if(getAdjMines() == 0)
		for(unsigned int i = 0; i < adjacentTiles.size(); ++i)
			adjacentTiles[i]->cascade(numRevealed);
}

Board::Board(string fileName) {
	state = "pending";
	numFlags = 0;
	numRevealed = 0;
    ifstream file("boards/config.cfg");
    file >> cols >> rows >> numMines;
    file.close();

    file.open("boards/" + fileName);
    char c;
    for(int i = 0; i < rows; ++i) {
	    vector<Tile> v;
        for(int j = 0; j < cols; ++j) {
        	file >> c;
        	if (c == '1') {
        		v.push_back(Tile(true));
        	}
        	else {
        		v.push_back(Tile(false));
        	}
        }
        board.push_back(v);
        file.ignore();
    }
}

void Board::initAdjTiles() {
	for(int i = 0; i < rows; ++i) {
		for(int j = 0; j < cols; ++j) {
			if(i > 0)
				board[i][j].addAdjTile(&board[i-1][j]);

			if(i > 0 && j < cols - 1)
				board[i][j].addAdjTile(&board[i-1][j+1]);

			if(j < cols - 1)
				board[i][j].addAdjTile(&board[i][j+1]);

			if(i < rows - 1 && j < cols - 1)
				board[i][j].addAdjTile(&board[i+1][j+1]);

			if(i < rows - 1)
				board[i][j].addAdjTile(&board[i+1][j]);

			if(i < rows - 1 && j > 0)
				board[i][j].addAdjTile(&board[i+1][j-1]);

			if(j > 0)
				board[i][j].addAdjTile(&board[i][j-1]);

			if(i > 0 && j > 0)
				board[i][j].addAdjTile(&board[i-1][j-1]);
		}
	}
}

void Board::initNumMines() {
	for(int i = 0; i < rows; ++i) {
		for(int j = 0; j < cols; ++j) {
			board[i][j].countMines();
		}
	}
}

void Board::reset() {
	state = "pending";
	board.clear();
	numFlags = 0;
	numRevealed = 0;

	int size = rows * cols;
	int arr[size];
	for(int i = 0; i < size; ++i) arr[i] = 0;

	int minesGenerated = 0;
	while (minesGenerated < numMines) {
		int pos = Random::Int(0, size - 1);
		if (arr[pos] != 1) {
			arr[pos] = 1;
			minesGenerated++;
		}
	}

    for(int i = 0; i < rows; ++i) {
	    vector<Tile> v;
        for(int j = 0; j < cols; ++j) {
        	if (arr[i * cols + j] == 1) {
        		v.push_back(Tile(true));
        	}
        	else {
        		v.push_back(Tile(false));
        	}
        }
        board.push_back(v);
    }

    initAdjTiles();
    initNumMines();
}

int Board::getRows() {
	return rows;
}

int Board::getCols() {
	return cols;
}

int Board::getNumMines() {
	int tot = 0;
	for(int i = 0; i < rows; ++i)
		for(int j = 0; j < cols; ++j)
			if(board[i][j].isMine())
				tot++;

	return tot;
}

int Board::getNumFlags() {
	return numFlags;
}

int Board::getNumRevealed() {
	return numRevealed;
}

string Board::getState() {
	return state;	
}

Tile& Board::getTile(int ind1, int ind2) {
	return board[ind1][ind2];
}

void Board::setState(string st) {
	state = st;
}

void Board::checkWin() {
	if(state != "lose" && rows * cols - getNumMines() == numRevealed) {
		state = "win";
		for(int i = 0; i < rows; ++i)
			for(int j = 0; j < cols; ++j) {
				if(board[i][j].isMine()) {
					if(board[i][j].isRevealed()) {
						board[i][j].toggleRevealed();
					}
					if(!board[i][j].isFlagged()) {
						board[i][j].flag();
						numFlags++;
					}
				}
			}
	}
}

void Board::leftClick(int row, int col) {
	if(board[row][col].isFlagged())
		return;
	if(board[row][col].isMine()) {
		setState("lose");	
		for(int i = 0; i < rows; ++i) {
			for( int j = 0; j < cols; ++j) {
				board[i][j].reveal();
				numRevealed++;
			}
		}
	} else {
		board[row][col].cascade(numRevealed);
	}
}

void Board::rightClick(int row, int col) {
	if(!board[row][col].isRevealed()) {
		board[row][col].toggleFlagged();
		if(board[row][col].isFlagged())
			numFlags++;
		else
			numFlags--;
	}
}

void Board::revealBoard() {
	for(int i = 0; i < rows; ++i) {
		for( int j = 0; j < cols; ++j) {
			board[i][j].toggleRevealed();
		}
	}
}

void Board::debug() {
	for(int i = 0; i < rows; ++i) {
		for( int j = 0; j < cols; ++j) {
			if(board[i][j].isMine())
				board[i][j].toggleRevealed();
		}
	}
}

void Board::print() {
	for(int i = 0; i < rows; ++i) {
		for(int j = 0; j < cols; ++j) {
			if(board[i][j].isMine())
				cout << 1;
			else
				cout << 0;
		}
		cout << endl;
	}
}

void Board::printNumMines() {
	for(int i = 0; i < rows; ++i) {
		for(int j = 0; j < cols; ++j) {
			cout << board[i][j].getAdjMines();
		}
		cout << endl;
	}
}
