#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Bullet.h"
#include <iostream>
using namespace std;
using namespace sf;

int main()
{
	RenderWindow okno(sf::VideoMode(1200, 900), "MENU");

	Game game;
	game.runGame(okno);

	return 0;
}