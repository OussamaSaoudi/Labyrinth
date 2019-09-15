#include "UnionFind.h"
#include <vector>
#pragma once

#ifndef  CONNECTEDCOMPONENTS_H
#define	CONNECTEDCOMPONENTS_H

using namespace std;
class ConnectedComponents
{
public:
	ConnectedComponents();
	ConnectedComponents(int n); // creates n*n grid
	~ConnectedComponents();

	int uncover(int row, int col); // Uncovers tile of it hasn't been uncovered already
	bool isUncovered(int row, int col); // Checks if position has been uncovered
	bool hasEntity(int row, int col); // Returns true if position has bomb
	int numberOfUncoveredSites(); // Reveals number of uncovered sites
	void addBomb(int row, int col); // Adds a bomb to given position, and increases threat level of adjacent squares
	void setStart(int row, int col);
	void setEnd(int row, int col);
	int getPos(int row, int col);

	int getSide();

private:
	std::vector<std::vector<int>> grid;
	UnionFind finder;
	int openSites;
	int size;
	int side;
	int startRow;
	int startCol;
	int endRow;
	int endCol;

};

#endif // ! CONNECTEDCOMPONENTS_H
