#include "Game/BoardLogic/ConnectedComponents.h"
#pragma once
class Randomizer
{
public:
	Randomizer();
	Randomizer(int side, double percentage);
	~Randomizer();
	ConnectedComponents getRandomized();
private:
	ConnectedComponents output;
	ConnectedComponents randomize(ConnectedComponents input, double percentage);
	bool isConnected(ConnectedComponents input, int startRow, int startCol, int endRow, int endCol);
	int separation(ConnectedComponents input, int startRow, int startCol, int endRow, int endCol);
	bool validate(ConnectedComponents input, int startRow, int startCol, int endRow, int endCol);

};

