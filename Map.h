#pragma once
#include <vector>
using namespace std;

class Map
{
public:
	Map(float size = 19); //initalise gameMap d'une taille voulue
	~Map();
	void drawMap();
	
	bool addToMap(unsigned int x, unsigned int y, int player);
	bool check(int x, int y, int player);
	vector<int> gameMap;

private:
	int size;
	

};
