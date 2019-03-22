#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <time.h>
#include <list>
#include "Engine.h"
#include "Entity.h"
#include "Bullet.h"
#include "Asteroid.h"
#include "string"
#include "Information.h"

using namespace std;
using namespace sf;

bool checkCollision(Entity *a, Entity *b)
{

	Vector2f thisPosition = a->GetPosition();
	Vector2f otherPosition = b->GetPosition();
	int thisRadius = a->body.getRadius();
	int otherRadius = b->body.getRadius();

	float deltaX = otherPosition.x - thisPosition.x;
	float deltaY = otherPosition.y - thisPosition.y;

	return (deltaX)*(deltaX)+
		(deltaY)*(deltaY)<
		(thisRadius + otherRadius)*(thisRadius + otherRadius);

}

Engine::Engine()
{

}


Engine::~Engine()
{
}

void Engine::runEngine(RenderWindow &window)
{
	unsigned points = 0;
	Clock clock;
	float deltaTime = 0;

	Font font;
	Texture a0, a1, a2, a3, a4, tE, tE2, backgroundTexture, b1, b2, s1;
	Texture playerTexture;
	RectangleShape background;

	font.loadFromFile("fonts\\game_font_7.ttf");

	a0.loadFromFile("sprity\\rock.png");
	a1.loadFromFile("sprity\\rock_small.png");
	tE.loadFromFile("sprity\\explosions\\type_B.png");
	tE2.loadFromFile("sprity\\explosions\\type_C.png");
	b1.loadFromFile("sprity\\bullet.png");
	b2.loadFromFile("sprity\\inne\\fire_blue.png");
	backgroundTexture.loadFromFile("sprity\\background.jpg");
	playerTexture.loadFromFile("sprity\\your_blue_ship2.png");
	s1.loadFromFile("sprity\\life.png");

	background.setTexture(&backgroundTexture);
	background.setSize(Vector2f(1920, 1200));

	playerTexture.setSmooth(true);
	backgroundTexture.setSmooth(true);

	SoundBuffer buffer1, buffer2, buffer3;
	buffer1.loadFromFile("sounds\\sfx_laser2.ogg");
	buffer2.loadFromFile("sounds\\scuxi.ogg");

	Music music;
	music.openFromFile("sounds\\bensound-scifi.ogg");
	music.play();
	music.setVolume(30);

	Sound shoot, explosion;
	shoot.setBuffer(buffer1);
	explosion.setBuffer(buffer2);
	explosion.setVolume(10);

	Text pointText("Points: ", font, 30);
	pointText.setPosition(80 - pointText.getGlobalBounds().width / 2, 40);

	std::list<Entity*> entities;
	for (int i = 0; i<17; i++)
	{
		Asteroid *a = new Asteroid(&a0, Vector2u(16, 1), 0.04);
		a->settings(rand() % Information::W - 5, rand() % Information::H - 5, rand() % 360, 25 + rand() % 30);
		entities.push_back(a);
		cout << "stworzono asteroide\n";
	}

	Player *p = new Player(&playerTexture, Vector2u(4, 2), 0.3, Vector2f(200, 200));
	p->settings(Information::H / 2, Information::W / 2, 0, 50);
	entities.push_back(p);


	while (!menu && !gameOver)
	{
		deltaTime = clock.restart().asSeconds();

		Event event;

		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyReleased && event.key.code == Keyboard::Escape)
				menu = true;

			if (event.type == Event::MouseButtonPressed && event.key.code == Mouse::Button::Left)
			{
				Bullet *b = new Bullet(&b2, Vector2u(16, 1), 0.3);
				b->settings(p->body.getPosition().x, p->body.getPosition().y, p->body.getRotation(), 20);
				std::cout << p->body.getRotation();
				entities.push_back(b);
				std::cout << "bullet" << endl;
				shoot.play();
			}

			switch (event.type)
			{
			case Event::Closed:
				menu = true;
				break;
			}

		}

		if (p->getLives() == 0)
		{
			gameOver = true;
			cout << "game over";
		}


		Time time = clock.getElapsedTime();
		clock.restart().asMilliseconds();


		for (auto a : entities)
			for (auto b : entities)
			{
				if (a->name == "asteroid" && b->name == "player")
					if (checkCollision(a, b))
					{
						a->life = false;

						Entity *e = new Entity(&tE, Vector2u(64, 1), 0.03, Vector2f(0, 0), 0, 20);
						e->settings(a->body.getPosition().x, a->body.getPosition().y, 0, 70);
						e->name = "explosion";
						entities.push_back(e);

						explosion.play();

						p->settings(Information::W / 2, Information::H / 2, 0, 50);
						p->removeLive();

						cout << "Lives: " << p->getLives() << endl;
					}
				if (a->name == "asteroid" && b->name == "bullet")
					if (checkCollision(a, b))
					{
						a->life = false;
						b->life = false;

						Entity *e = new Entity(&tE2, Vector2u(48, 1), 0.005, Vector2f(0, 0), 0, 20);
						e->settings(a->body.getPosition().x, a->body.getPosition().y, 0, 70);
						e->name = "explosion";
						entities.push_back(e);

						explosion.play();
						Information::Npoints++;

						for (int i = 0; i<2; i++)
						{
							if (a->R == 24) continue;
							Entity *e = new Asteroid(&a1, Vector2u(16, 1), 0.08);
							e->settings(a->body.getPosition().x, a->body.getPosition().y, rand() % 360, 24);
							entities.push_back(e);
						}
					}
			}

		if (rand() % 150 == 0)
		{
			Asteroid *a = new Asteroid(&a0, Vector2u(16, 1), 0.08);
			a->settings(0, rand() % Information::H, rand() % 360, rand() % 20 + 20);
			entities.push_back(a);
			cout << "PRODUKCJA ASTEROIDY" << endl;
		}

		for (auto e : entities)
			if (e->name == "explosion")
				if (e->anim.isEndOfAnimation()) {
					e->life = 0; cout << "usunieto EKSPLOZJE";
				}

		for (auto i = entities.begin(); i != entities.end();)
		{
			Entity *e = *i;

			e->update(deltaTime, window);

			if (e->life == 0) { cout << "usunieto " << e->name << endl; delete e; i = entities.erase(i); }
			else i++;
		}

		Text pointTextNo(std::to_string(Information::Npoints), font, 30);
		pointTextNo.setPosition(220 - pointText.getGlobalBounds().width / 2, 40);

		//------------------draw-------------------

		window.draw(background);
		for (auto i : entities)
		{
			i->draw(window);
			window.draw(pointText);
			window.draw(pointTextNo);
		}

		Sprite s;
		s.setTexture(s1);
		for (int i = 0; i < p->getLives(); i++)
		{
			s.setPosition(20 + 20 * i, 20);
			window.draw(s);
		}

		window.display();

	}

}