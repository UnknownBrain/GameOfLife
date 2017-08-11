#include <iostream>
#include <vector>
#include <windows.h>
#include <cstdlib>
#include <ctime>

#define PAUSE 300

using namespace std;

class Board {
	private:
		const int width;
		const int height;
		vector<vector<int>> cells;
		vector<vector<int>> copyCells;
		void initializingBoard();

	public:
		Board(int _width, int _height) : width(_width), height(_height) {
			initializingBoard();
		}

		void paintingBoard();
		void mutatingBoard();
		int livingCellsAround(int xPos, int yPos);
		void makeCopyOfCells();
};

int main() {
	int xTam, yTam;
	//This is a simple comment for git testing. :)
	cout << "This is game Conway's Game of Life! :D" << endl;
	//Asking to user how big the board is gonna be
	cout << "Input the Board's width: "; 
	cin >> xTam;
	cout << "Input the Board's height: ";
	cin >> yTam;

	system("cls");

	//Creating the board with previous typed values.
	Board board(xTam, yTam);

	while (true) {
		board.paintingBoard();
		Sleep(PAUSE);
		board.mutatingBoard();
		system("cls");
	}

	system("pause>nul");
	return 0;
}

void Board::initializingBoard() {
	//Setting up the seed to generate random numbers
	srand((unsigned int)time(NULL));

	//Setting up cells' scenary
	cells.resize(height);
	copyCells.resize(height);

	for (int i = 0; i < height; i++) {
		cells[i].resize(width);
		copyCells[i].resize(width);
	}

	//Variable where we're gonna be holding random numbers throughout each iteration over the inner for.
	int random;

	for (int h = 0; h < height; h++) {
		for (int w = 0; w < width; w++) {
			random = rand() % 100;
			
			if (random <= 10) {
				cells[h][w] = 1;
			}
			else {
				cells[h][w] = 0;
			}
		}
	}
}

void Board::paintingBoard() {
	for (int h = 0; h < height; h++) {
		for (int w = 0; w < width; w++) {
			//cout << cells[h][w];
			if (cells[h][w] == 1) {
				cout << char(178);
			} else if(cells[h][w] == 0) { 
				cout << char(176);
			}
		}
		cout << endl;
	}
}

int Board::livingCellsAround(int xPos, int yPos) {
	int livingCells = 0;

	for (int y = yPos - 1; y <= yPos + 1; y++) {
		for (int x = xPos - 1; x <= xPos + 1; x++) {
			if ((x == xPos && y == yPos) || x == -1 || y == -1 || x == width || y == height) {
				continue;
			}

			if (copyCells[y][x] == 1) {
				livingCells += 1;
			}
		}
	}

	return livingCells;
}

void Board::mutatingBoard() {
	int livingCells;

	makeCopyOfCells();

	for (int h = 0; h < height; h++) {
		for (int w = 0; w < width; w++) {
			livingCells = livingCellsAround(w, h);

			if (!(copyCells[h][w] == 1 && (livingCells == 2 || livingCells == 3))) {
				cells[h][w] = 0;
			}

			if (copyCells[h][w] == 0 && livingCells == 3) {
				cells[h][w] = 1;
			}
		}
	}
}

void Board::makeCopyOfCells() {
	for (int h = 0; h < height; h++) {
		for (int w = 0; w < width; w++) {
			copyCells[h][w] = cells[h][w];
		}
	}
}