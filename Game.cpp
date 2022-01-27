#include "Game.h"
#include <math.h>

using namespace std;
using namespace sf;

//Ouvre la fenêtre Game::window
void Game::newWindow(int width, int height)
{
	this->window.create(VideoMode(width, height), "Gomoku", Style::None);
	
	window.setTitle("Gomoku");
	size = window.getSize();
	window.setPosition(Vector2i(window.getSize().x / 2 , (window.getSize().y / 2) - (height/2)));
	window.setFramerateLimit(60);
}

//Load les fichiers qui sont gardés chacun dans une variable de Game::(...)
void Game::loadFiles()
{
	//load le fond d'écran du jeu
	texture.setRepeated(true);
	if (!texture.loadFromFile("C:/Users/Administrateur/Documents/CIR 2/Info/Tp objet/GomokuSFML/GomokuSFML/fond-ecran.jpg"))
	{
		cout << "texture loading error" << endl;
	}
	this->background.setTexture(texture);
	background.setColor(sf::Color(255, 255, 255, 128)); //rend plus sombre le background

	//load le font (police d'écriture du jeu)
	if (!font.loadFromFile("font/font.otf"))
	{
		cout << "font loading error" << endl;
	}
	gomokuTittle.setFont(font);
	info.setFont(font);
}

void Game::setGraphics()
{
	loadFiles();
	
	//set les paramètres de titre du Menu
	gomokuTittle.setString("Gomoku");
	gomokuTittle.setCharacterSize(60);
	gomokuTittle.setOutlineColor(Color::Black);
	gomokuTittle.setOutlineThickness(5.);

	auto u = gomokuTittle.getGlobalBounds();
	gomokuTittle.setOrigin(u.width/2.f, u.height/2.f);
	gomokuTittle.setPosition(float(size.x/2), float(size.y /3));

	//set les paramètres du message informatif
	info.setString("Cliquez n'importe où pour commencer");
	info.setCharacterSize(30);
	info.setOutlineColor(Color::Black);
	info.setOutlineThickness(4.);

	auto t = info.getGlobalBounds();
	info.setOrigin(t.width / 2, t.height / 2);
	info.move(float(window.getSize().x / 2), float(window.getSize().y/2));
	
	//set les coordonnées des traits de la grille en fonction du nombre de case totale
	for (int i = 1; i < nbPt-1; i++)
	{
		RectangleShape rectangle(Vector2f(1.f, 600.f ));
		rectangle.setPosition(Vector2f(float(50 + tailleCase * i), 50.f));
		grille.push_back(rectangle);
		
	}
	for (int i = 1; i < nbPt-1; i++)
	{
		RectangleShape rectangle(Vector2f(600.f, 1.f));
		rectangle.setPosition(Vector2f(50.f , float(50 + tailleCase * i)));
		grille.push_back(rectangle);

	}

	addNode();
	
}

//Set les coordonnées dans Game::mouse(x/y)
void Game::setMousePos()
{
	mouse = Mouse::getPosition(window);

}

//Regroupe toutes les fonctions intervenant avec l'affichage de la fenêtre
void Game::display()
{
	window.clear();
	window.draw(background);
	if (!playing)
	{
		
		window.draw(gomokuTittle);
		window.draw(info);
	}
	else
	{
		//affiche les barres de la grille
		for (auto i : grille)
		{
			window.draw(i);
		}
		//affiche les point sur la grille (+ la Node)
		for (auto i : points)
		{
			window.draw(i);
		}
	}

	window.display();

	


	
}

//Ajoute graphiquement un point sur la grille en fonction des coordonées du pions joué et du joueur
void Game::addPointToWindow(int x, int y, int player)
{
	CircleShape shape(float(tailleCase/4));
	if (player == 2)
	{
		shape.setFillColor(Color::Black);
	}
	shape.setOrigin(shape.getRadius(), shape.getRadius());
	shape.setPosition(float(50. + x * tailleCase), float(50 + y * tailleCase));
	points.push_back(shape);
}

//Ajoute la node en haut à gauche de la fenêtre, indiquant aux joueurs leur tour
void Game::addNode()
{
	CircleShape shape(26.f);
	shape.setOrigin(shape.getRadius(), shape.getRadius());
	shape.setPosition(28, 28);
	points.push_back(shape);
}

//set la couleur de la node en fonction de la couleur du joueur qui doit jouer
void Game::updateNode()
{
	if (player == 1)
	{
		points[0].setFillColor(Color::White);
	}
	if (player == 2)
	{
		points[0].setFillColor(Color::Black);
	}
	
}

Game::Game() {
	
	newWindow(700, 700);
	setGraphics();
	Map gomoku(nbPt);

	while (window.isOpen()){
		Event event;
		while (window.pollEvent(event)){

			// évènement "touche échap pressée" : on ferme la fenêtre
			if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape)) window.close();
			
			// évènement "clic gauche de souris"
			if (Mouse::isButtonPressed(Mouse::Left)){

				//Ce if n'est déclenché que lorsque le jeu est à l'arret
				// Ainsi ce clique déclenche le début du Jeu
				if (!playing || winner != 0) { 
					playing = true; 
					winner = 0;
					Sleep(300);
				}

				//Le jeu est en cours dans ce cas 
				//On détermine donc où le pion est joué
				else
				{
					setMousePos();

					//Regarde si le clic est dans le cadre de jeu
					if (mouse.x > 25 && mouse.y > 25 && mouse.x < 675 && mouse.y < 675)
					{
						//Déduction de coordonnée de la case suite au clic de souris
						auto Xcase = fabs(round((mouse.x - 50) / tailleCase));
						auto Ycase = fabs(round((mouse.y - 50) / tailleCase));

						gomoku.drawMap(); //draw sur la console

						//ajoute implicitement un piont 
						if (gomoku.addToMap(unsigned int(Xcase), unsigned int(Ycase), player))
						{
							addPointToWindow(int(Xcase), int(Ycase), player);
							
							gomoku.drawMap();

							cout << Xcase << "  " << Ycase << endl;

							//Appelle implicitement la vérification de la grille et retourne Vrai si 5 pions sont allignés
							if (gomoku.check(int(Xcase), int(Ycase), player))
							{
								winner = player;
								playing = false;

								//definition du gagnant
								if (winner == 1)
								{
									gomokuTittle.setString("Les Pions Blancs gagnent");
									
								}
								if (winner == 2)
								{
									gomokuTittle.setString("Les Pions Noirs gagnent");
								}
								auto u = gomokuTittle.getGlobalBounds();
								gomokuTittle.setOrigin(u.width / 2, u.height / 2);
								gomokuTittle.setPosition(float(size.x / 2), float(size.y / 3));

								//redefinition du message informatif
								info.setString("  Appuyer sur echap pour quitter \nOu cliquez sur l'écran pour recommencer");
								auto t = info.getGlobalBounds();
								info.setOrigin(t.width / 2, t.height / 2);
								info.setPosition(float(window.getSize().x / 2), float(window.getSize().y / 2));

								//réinitialisation de la Map
								gomoku.gameMap.assign(int(nbPt*nbPt), 0);
								gomoku.drawMap();

								points.clear();
								addNode();

							}
							else
							{
								player = player % playerMax + 1;
								updateNode();
							}
							
						}
					}
				}
			}
		}

		display();
		
	}
}

