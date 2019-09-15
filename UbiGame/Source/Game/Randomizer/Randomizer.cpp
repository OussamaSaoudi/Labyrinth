#include "Randomizer.h"
#include "Game/BoardLogic/ConnectedComponents.h"
#include <stdlib.h>
#include <cstdlib>
#include <ctime>


Randomizer::Randomizer()
{
}
Randomizer::Randomizer(int side, double percentage)
{
	srand(time(NULL));
	ConnectedComponents temp = ConnectedComponents(side);
	int startRow = (std::rand() % (side)) + 1;
	int startCol =( std::rand() % (side)) + 1;
	int endRow = (std::rand() % (side)) + 1;
	int endCol = (std::rand() % (side)) + 1;
	temp.setEnd(endRow, endCol);
	temp.setStart(startRow, startCol);
	temp = randomize(temp, percentage);
	while (true) {





		temp = ConnectedComponents(side); // sets arrays to all 0s
		startRow = ( std::rand() % (side)) + 1;
		startCol = ( std::rand() % (side)) + 1;
		endRow = ( std::rand() % (side)) + 1;
		endCol = ( std::rand() % (side)) + 1;
		temp.setEnd(endRow, endCol);
		temp.setStart(startRow, startCol);
		temp = randomize(temp, percentage);

		// Validation

		UnionFind connectionFinder = UnionFind(side* side);
		for (int i = 1; i <= side; i++) {
			for (int j = 1; j <= side; j++) { // Let i be for rows, j be for cols
				if (temp.getPos(i, j) ==-1) continue;
				if (i - 1 > 0 && (temp.getPos(i - 1, j) != -1)) { // Look above current cell
					connectionFinder.unionF(((i - 2) * side + j - 1), (i-1)* side + j -1);
				}
				if (i + 1 < side && (temp.getPos(i + 1, j) != -1)) { // Look below current cell
					connectionFinder.unionF(((i) * side -1 + j), (i-1)* side + j -1);
				}
				if (j + 1 < side && (temp.getPos(i, j + 1) != -1)) { // 
					connectionFinder.unionF(((i-1) * side + j - 1+ 1), (i-1)* side + j -1);
				}
				if (j - 1 > 0 && (temp.getPos(i, j - 1) != -1)) {
					connectionFinder.unionF(((i-1) * side + j - 2), (i-1)* side + j -1);
				}
			}
		}

		if (connectionFinder.connected((startRow - 1)*side + startCol - 1, (endRow - 1)*side + endCol - 1) && abs(startRow - endRow) + abs(startCol - endCol)) {
			break;
		}

		// Validation


	}
	output = temp;
}

ConnectedComponents Randomizer::getRandomized() {
	return output;
}


Randomizer::~Randomizer()
{
}

ConnectedComponents Randomizer::randomize(ConnectedComponents input, double percentage)
{
	int side = input.getSide();

	int bombsNumber = round(percentage * side*side);

	int row;
	int col;
	int i = 0;
	while(i < bombsNumber){
		row = (std::rand() % (side)) + 1;
		col = (std::rand() % (side)) + 1;
		if (!input.hasEntity(row, col)) {
			input.addBomb(row, col);
			i++;
		}
	}
	return input;
}
bool Randomizer::isConnected(ConnectedComponents input,int startRow,int startCol, int endRow, int endCol)
{
	int side = input.getSide();
	UnionFind connectionFinder = UnionFind(side* side);
	for (int i = 1; i <= input.getSide(); i++) {
		for (int j = 1; j <= input.getSide(); j++) {
			if (input.getPos(i, j) < 0 || input.getPos(i, j) != -6) continue;
			if (i - 1 > 0 &&( input.getPos(i - 1, j) >= 0 || input.getPos(i - 1, j) == -6)) {
				connectionFinder.unionF(((i - 1) * side + j), (i) * side + j);
			}
			if (i + 1 < side && (input.getPos(i + 1, j) >= 0 || input.getPos(i + 1, j) == -6)) {
				connectionFinder.unionF(((i + 1) * side + j), (i)* side + j);
			}
			if (j + 1 < side && (input.getPos(i, j + 1) >= 0 || input.getPos(i, j + 1) == -6)) {
				connectionFinder.unionF((i * side + j+1), (i)* side + j);
			}
			if (j - 1 > 0 && (input.getPos(i, j - 1) >= 0 || input.getPos(i, j - 1) == -6)) {
				connectionFinder.unionF((i * side + j - 1), (i)* side + j);
			}
		}
	}

	return connectionFinder.connected((startRow - 1)*side + startCol - 1, (endRow - 1)*side + endCol - 1);
}

int Randomizer::separation(ConnectedComponents input, int startRow, int startCol, int endRow, int endCol)
{
		return (abs(startRow - endRow) + abs(startCol - endCol));

}
bool Randomizer::validate(ConnectedComponents input, int startRow, int startCol, int endRow, int endCol)
{
	return separation(input, startRow, startCol, endRow, endCol) > input.getSide() && isConnected(input, startRow, startCol, endRow, endCol);
}

