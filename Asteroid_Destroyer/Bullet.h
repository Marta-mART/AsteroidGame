#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Entity.h"

using namespace std;
using namespace sf;


class Bullet :public Entity
{
private:
	Clock timer;
	Time frequency;
	Animation animation;
	unsigned row;

public:
	Bullet(Texture* texture, Vector2u imageCount, float switchTime);
	~Bullet();
	void ifinwindow();
	void settings(int X, int Y, double Angle = 0, double radius = 10);
	void update(float deltaTime, RenderWindow& window);

};

