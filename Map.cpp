#include "Map.h"
#include <iostream>

//initialise une Map (non graphique)
Map::Map(float size)
{
	this->size = int(size);
	for (int i = 0; i < size * size; i++)
	{
		gameMap.push_back(0);
	}
}

Map::~Map()
{
	gameMap.clear();
}

//affiche une map sur la console
void Map::drawMap()
{
	system("CLS");
	cout << "  ";
	for (int i = 0; i < size; i++)
	{
		cout << " " << i << " ";
	}
	cout << endl;
	for (int i = 0; i < size; i++)
	{
		cout << i;
		if (i < 10)
		{
			cout << " ";
		}
		for (int j = 0; j < size; j++)
		{
			switch (gameMap[j + i * size])
			{
			case 0:
				cout << " - ";
				break;
			case 1:
				cout << " 1 ";
				break;
			case 2:
				cout << " 2 ";
				break;
			default:
				cout << " - ";
				break;
			}
			if (j >= 10)
			{
				cout << " ";
			}
		}
		cout << endl;
	}
}


//retourne vrai si un pion rentre dans le tableau sinon false (condition : coordonnées valide, case vide, la case n'est pas un coin)
bool Map::addToMap(unsigned int x, unsigned int y, int player)
{

	if (x >= 0 && x < gameMap.size() && y >= 0 && y < gameMap.size())
	{
		if (x == 0 && y == 0 || x == 0 && y == size-1 || x== size-1 && y==0 || x == size - 1 && y == size - 1)
		{
			return 0;

		}
		else
		{
			if (this->gameMap[x + y * size] == 0)
			{
				this->gameMap[x + y * size] = player;
				return 1;
			}
			else
			{
				return 0;
			}
		}
		
	}
	else
	{
		return false;
	}
	
}


//retourne vrai si un pion le pion(x,y) ajouté fait alligner 5 jetons ou plus
//ainsi la vérification ne se fait pas sur tout le tableau mais uniquement sur les extrémités du pion joué
bool Map::check(int x, int y, int player)
{
	int diag1 = 0, diag2 = 0, horizon = 0, vertical = 0;

	for (int i = -4; i <= 4; i++)  
	{
		// check vertical des points
		if (y + i >= 0 && y + i < size)
		{
			if (gameMap[x + (y + i) * size] == player)
			{
				vertical++;
			}
			else
			{
				vertical = 0;
			}
		}
		else
		{
			vertical = 0;
		}

		// check hoizontal des points
		if (x + i >= 0 && x + i < size)
		{
			if (gameMap[x + i + y * size] == player)
			{
				horizon++;
			}
			else
			{
				horizon = 0;
			}
		}
		else
		{
			horizon = 0;
		}

		// check diagonal des points (N-O to S-E)
		if (y + i >= 0 && y + i < size && x + i >= 0 && x + i < size)
		{
			if (gameMap[x + i + (y + i) * size] == player)
			{
				diag1++;
			}
			else
			{
				diag1 = 0;
			}
		}
		else
		{
			diag1 = 0;
		}

		// check diagonal des points (N-E to S-O)
		if (y + i >= 0 && y + i < size && x - i >= 0 && x - i < size)
		{
			if (gameMap[x - i + (y + i) * size] == player)
			{
				diag2++;
			}
			else
			{
				diag2 = 0;
			}
		}
		else
		{
			diag2 = 0;
		}

		//Si la condition de victoire (nombre de pionts alligné >= 5 
		if (diag1 >= 5 || diag2 >= 5 || horizon >= 5 || vertical >= 5)
		{
			return 1;
		}
		if (i > -4)
		{
			//si on atteint la partie droite de la grille le delta entre la coordonné n et n-1 sera au-delà de 1 car on reviens au debut d'une nouvelle ligne ... 
			if ((x + i) - (x + i - 1) != 1) 
			{
				diag1 = 0;
				horizon = 0;
				cout << "delete" << endl;
			}
			//si on atteint la partie basse de la grille ...
			if ((y + i) - (y + i - 1) != 1)
			{
				diag1 = 0;
				horizon = 0;
				cout << " delete 2" << endl;
			}
			//si on atteint la partie gauche de la grille
			if ((x + i - 1) - (x + i) != -1)
			{
				diag2 = 0;
				cout << " delete3" << endl;
			}
		}
	}

	return 0;


}


