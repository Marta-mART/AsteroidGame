#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Windows.h>



using namespace std;
using namespace sf;

const int MAX_NUMBER_OF_ITEMS = 3;

class Game
{
private:
	SoundBuffer buff;
	Sound clickSound;
	Font font;
	Text menu[MAX_NUMBER_OF_ITEMS];

protected:
	enum GameState { MENU, INFO, GAME, GAME_OVER, END };
	GameState state;
public:
	Game();
	void gra(RenderWindow &window);
	void ShowMenu(RenderWindow& window);
	void ShowInfo(RenderWindow& window);
	void runGame(RenderWindow& window);
	void GameOver(RenderWindow& window);
};

