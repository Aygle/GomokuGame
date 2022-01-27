#pragma once
#include<iostream>
#include"SFML/Graphics.hpp"
#include"Map.h"
#include<vector>
#include<windows.h>
using namespace std;
using namespace sf;

class Game : Map
{
private : 

//---------- Partie Feunêtre ----------------------//

	Vector2u size;										//taille 2D de window
	RenderWindow window;
	

//---------- Partie Jeu --------------------------//
	
	Vector2i mouse;										//Coordonnées de la souris 
	bool playing = 0;									//indique si le Jeu est en cours d'utilisation
	int player = 1, playerMax = 2, winner = 0;
	
	float nbPt = 30;									//taille de la grille (en points) 
	double tailleCase = 600. / (nbPt-1);					//taille d'une case (en pixels)
	
	

//---------- Partie Graphique --------------------//

	//définie la texture de l'arrière plan
	Texture texture;
	Sprite background;

	//Variable textuelles du jeu
	Font font;
	Text gomokuTittle;
	Text info;

	//Shapes formant la Grille du Gomoku
	vector<RectangleShape> grille;
	vector<CircleShape> points;
	

public:
	Game();

	/* INITIALISATION */
	//Ouvre la feunêtre Game::window
	void newWindow(int width, int heigth);

	//Load les fichiers qui sont gardés chacun dans une variable de Game::(...)
	void loadFiles();


	void setGraphics();

	//Set les coordonnées dans Game::mouse(x/y)
	void setMousePos();

	//Regroupe toutes les fonctions intervenant avec l'affichage de la feunêtre
	void display();

	//Ajoute graphiquement un point sur la grille en fonction des coordonées du pions joué et du joueur
	void addPointToWindow(int x, int y, int player );

	/* NODE */	
	//Ajoute la node en haut à gauche de la feunêtre, indiquant aux joueurs leur tour
	void addNode();
	//Met à jour la node en fonction du tour du joueur actuel
	void updateNode();

};

