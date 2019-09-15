#include "ConnectedComponents.h"
#include "UnionFind.h"
#include <vector>

using namespace std;
ConnectedComponents::ConnectedComponents() {}

ConnectedComponents::ConnectedComponents(int n)
{
	openSites = 0;
	size = n * n;
	side = n;

	// initializes the grid. Can change later.
	
	for (int i = 0; i < n; i++) {
		std::vector<int> input;
		for (int j = 0; j < n; j++){
			input.push_back(0);
		}
		grid.push_back(input);
	}


}


ConnectedComponents::~ConnectedComponents()
{
}

// Uncovers tile of it hasn't been uncovered already
int ConnectedComponents::uncover(int row, int col)
{
	if (isUncovered(row, col)) return 0;
	openSites++;


	// Checks on all sides of the square to perform a union with adjacent squares
	// Deals with edge cases as well
	int positioner = -1;
	while (positioner != 1) {
		if (col + positioner > 0 && col + positioner <= side && isUncovered(row, col + positioner)) {
			finder.unionF(((row - 1) * side + col + positioner - 1), (row - 1) * side + col - 1);
		}
		if (row + positioner > 0 && row + positioner <= side && isUncovered(row + positioner, col)) {
			finder.unionF((row - 1) * side + positioner * side + col - 1, (row - 1) * side + col - 1);
		}
		positioner += 2;
	}
	int positionVal = grid[col - 1][row - 1];
	if (positionVal < -1) {
		grid[col - 1][row - 1] *= -1; // If the tile has a threat level
		return 0; 
	}
	else if (positionVal == 0) { //If the value is just uncovered
		grid[col - 1][row - 1] = 1;
		return 0; 
	}

		return -1;
	
}
bool ConnectedComponents::isUncovered(int row, int col)
{
	return grid[col - 1][row - 1] > 0;
}
// Returns true if position has bomb
bool ConnectedComponents::hasBomb(int row, int col)
{
	return grid[col - 1][row - 1] == -1;
}

void ConnectedComponents::addBomb(int row, int col) {
	grid[col - 1][row - 1] = -1; // Sets bomb

	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (1 <= row + j && row + j <= side && 1 <= col + i && col + i <=  side) { // Checks if row and column are within bounds

				if (hasBomb(row + j, col + i)) continue;
				if (isUncovered(row + j, col + i)) { //Increases threat level for known tiles
					grid[col+i-1][row+j-1] ++;
				}
				else if (grid[col + i-1][row + j-1] < 0){ // Increases threat level for unknown tiles with a threat level
					grid[col + i-1][row + j-1]--;
				} else{ //Increases threat level to first level for unknown tiles without a threat level
				grid[col + i-1][row + j-1] = -2;
			}
		}
	}
		// Returs number of uncovered sites

		
}
	}
	int ConnectedComponents::numberOfUncoveredSites()
	{
		return openSites;
	}


