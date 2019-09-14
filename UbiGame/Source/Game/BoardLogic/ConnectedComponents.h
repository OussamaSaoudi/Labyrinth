#pragma once
#include "UnionFind.cpp"
class ConnectedComponents
{
public:
	ConnectedComponents();
	~ConnectedComponents();

	void uncover(int row, int col); // Uncovers tile of it hasn't been uncovered already
	bool hasBomb(int row, int col); // Returns true if position has bomb
	int numberOfUncoveredSites(); // Reveals number of uncovered sites

private:
	int *grid;
	UnionFind *finder;
	int openSites;
	int size;
};

