#pragma once
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "Player.h"

using namespace std;
using namespace sf;

class Engine
{
private:

public:
	bool gameOver = false;
	bool menu = false;

	Engine();
	~Engine();
	void runEngine(RenderWindow &window);

	friend class Player;
};

