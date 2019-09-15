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
	bool hasBomb(int row, int col); // Returns true if position has bomb
	int numberOfUncoveredSites(); // Reveals number of uncovered sites
	void addBomb(int row, int col); // Adds a bomb to given position, and increases threat level of adjacent squares

private:
	std::vector<std::vector<int>> grid;
	UnionFind finder;
	int openSites;
	int size;
	int side;
};

#endif // ! CONNECTEDCOMPONENTS_H
