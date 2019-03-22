#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Animation.h"

using namespace std;
using namespace sf;

class Entity
{
public:

	double rotation, R, x, y;
	string name;
	bool life;
	Vector2f speed;

public:
	CircleShape body;
	Animation anim;

	Entity() { name = "entity";	life = 1; }
	Entity(Texture* texture, Vector2u imageCount, float switchTime, Vector2f speed, double Angle = 0, double radius = 10);
	virtual void settings(int X, int Y, double Angle = 0, double radius = 10);
	Vector2f GetPosition() { return body.getPosition(); }
	virtual void update(float deltaTime, RenderWindow& window);
	void draw(RenderWindow &window) { window.draw(body); }
	virtual ~Entity();
};



