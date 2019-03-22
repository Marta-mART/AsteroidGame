#include "Game.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include "Engine.h"
#include "Asteroid.h"
#include "Information.h"

using namespace std;
using namespace sf;

Game::Game()
{

	buff.loadFromFile("sounds\\sfx_zap.ogg");
	clickSound.setBuffer(buff);

	state = END;

	if (!font.loadFromFile("fonts\\game_font_7.ttf"))
	{
		MessageBox(NULL, "Font not found", "ERROR", NULL);
		return;
	}
	state = MENU;
}

void Game::runGame(RenderWindow& window)
{
	while (state != END)
	{
		switch (state)
		{
		case MENU:
			ShowMenu(window);
			break;
		case INFO:
			ShowInfo(window);
			break;
		case GAME:
			cout << "wybrano gre";
			gra(window);
			break;
		case GAME_OVER:
			GameOver(window);
			break;
		}
	}
}

void Game::GameOver(RenderWindow &window)
{
	SoundBuffer buffer;
	buffer.loadFromFile("sounds\\Fail_Sound_Effect.ogg");

	Sound sound;
	sound.setBuffer(buffer);
	sound.play();

	Clock clock;
	float deltaTime = 0;

	const int W = 1200;
	const int H = 900;

	Texture a1;
	a1.loadFromFile("sprity\\rock.png");

	std::list<Entity*> entities;
	for (int i = 0; i<10; i++)
	{
		Asteroid *a = new Asteroid(&a1, Vector2u(16, 1), 0.08);
		a->settings(rand() % W - 5, rand() % H - 5, rand() % 360, 25 + rand() % 30);
		entities.push_back(a);
	}

	Text over("This is over!", font, 120);
	over.setPosition(110, 300);

	Text goBack("Go back", font, 30);
	goBack.setPosition(30, 30);

	Text howManyPoints("You gained:", font, 80);
	howManyPoints.setPosition(360, 500);

	Text points(std::to_string(Information::Npoints), font, 90);
	points.setPosition(howManyPoints.getPosition().x + 600, 500);

	while (state == GAME_OVER)
	{
		deltaTime = clock.restart().asSeconds();
		Vector2f mouse(Mouse::getPosition(window));
		Event event;
		while (window.pollEvent(event))
		{
			//Wciœniêcie ESC lub przycisk X
			if (event.type == Event::Closed || event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
			{
				clickSound.play();
				state = END;
			}

			else if (goBack.getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				clickSound.play();
				state = MENU;
			}
		}

		if (goBack.getGlobalBounds().contains(mouse))
			goBack.setFillColor(Color::Cyan);
		else goBack.setFillColor(Color::White);

		window.clear();
		window.draw(over);
		window.draw(goBack);
		window.draw(howManyPoints);
		window.draw(points);


		for (auto i : entities)
		{
			i->draw(window);
			i->update(deltaTime, window);
		}
		window.display();
	}
	Information::Npoints = 0;

}
void Game::gra(RenderWindow &window)
{
	Engine engine;
	engine.runEngine(window);

	cout << "przed ifami";
	if (engine.menu) state = MENU;
	if (engine.gameOver) state = GAME_OVER;

	cout << "po grze, inna petla";
}


void Game::ShowInfo(RenderWindow & window)
{

	Text title("Opis gry", font, 80);
	title.setPosition(1280 / 2 - title.getGlobalBounds().width / 2, 30);
	title.setStyle(Text::Bold);

	Text information("\nGra polega na strzelaniu\n do asteroid i niszeniu ich!\n Przezyj jak najdluzej i nie pozwol\n sie zdmuchnac asteroidom!\n\n Instrukcja\n\n Spacja - przyspieszenie\n Mysz - sterowanie\n Lewy przycisk myszy - strzal\n", font, 40);
	information.setPosition(1280 / 2 - information.getGlobalBounds().width / 2, 200);

	Text goBack("Go back", font, 30);
	goBack.setPosition(30, 30);

	while (state == INFO)
	{
		Vector2f mouse(Mouse::getPosition(window));
		Event event;
		while (window.pollEvent(event))
		{
			//Wciœniêcie ESC lub przycisk X
			if (event.type == Event::Closed || event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
			{
				clickSound.play();
				state = END;
			}

			else if (goBack.getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				clickSound.play();
				state = MENU;
			}
		}


		if (goBack.getGlobalBounds().contains(mouse))
			goBack.setFillColor(Color::Cyan);
		else goBack.setFillColor(Color::White);

		window.clear();
		window.draw(title);
		window.draw(goBack);
		window.draw(information);
		window.display();

	}
}

void Game::ShowMenu(RenderWindow& window)
{
	RectangleShape background;
	Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("sprity\\inne\\background.jpg"))
	{
		cout << "error background";
	}
	background.setTexture(&backgroundTexture);

	Text title("Asteroid destroyer", font, 80);
	title.setStyle(Text::Bold);

	title.setPosition(1280 / 2 - title.getGlobalBounds().width / 2, 20);

	string str[] = { "Play", "Information", "Exit" };
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		menu[i].setFont(font);
		menu[i].setCharacterSize(55);
		menu[i].setString(str[i]);
		menu[i].setFillColor(Color::White);
		menu[i].setPosition(1280 / 2 - menu[i].getGlobalBounds().width / 2, 250 + i * 120);
	}

	while (state == MENU)
	{
		Vector2f mouse(Mouse::getPosition(window));
		Event event;
		while (window.pollEvent(event))
		{
			//Wciœniêcie ESC lub przycisk X
			if (event.type == Event::Closed || event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
			{
				clickSound.play();
				state = END;
			}
			else if (menu[0].getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				clickSound.play();
				state = GAME;
			}
			else if (menu[1].getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				clickSound.play();
				state = INFO;
			}
			//Wciœniêcie EXIT
			else if (menu[2].getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				clickSound.play();
				state = END;
			}
		}

		for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
		{
			if (menu[i].getGlobalBounds().contains(mouse))
				menu[i].setFillColor(Color::Cyan);
			else menu[i].setFillColor(Color::White);
		}

		window.clear();
		window.draw(background);
		window.draw(title);
		for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
		{
			window.draw(menu[i]);
		}
		window.display();
	}


}
