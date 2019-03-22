#include "Player.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cmath>

using namespace std;
using namespace sf;


Player::Player(Texture* texture, Vector2u imageCount, float switchTime, Vector2f speed) :
	animation(texture, imageCount, switchTime)
{
	name = "player";
	this->speed = speed;
	row = 0;
	lives = 10;
	body.setRadius(50);
	body.setPosition(200, 200);
	body.setTexture(texture);
}

Player::~Player()
{
}

void Player::update(float deltaTime, RenderWindow &window)
{
	ifinwindow();

	Vector2f mysz = (Vector2f)Mouse::getPosition(window);
	Vector2f norm = mysz - body.getPosition();

	float angle = atan2(norm.y, norm.x);
	angle = angle*180.f / 3.1415;
	angle += 90;

	float rotation = body.getRotation();
	float vx = sin((rotation * 3.1415) / 180.0f);
	float vy = -cos((rotation * 3.1415) / 180.0f);

	Vector2f movement(0, 0);
	if (Keyboard::isKeyPressed(Keyboard::Space))
	{

		movement.x = deltaTime * vx * speed.x;
		movement.y = deltaTime * vy * speed.y;
		//zabezpieczenie przed wirowaniem
		if (body.getGlobalBounds().contains(mysz))
		{
			movement.x = deltaTime * vx * 0.02;
			movement.y = deltaTime * vy * 0.02;
		}

	}
	else
	{
		movement.x = sin(angle*0.017282) * 0.1;
		movement.y = -cos(angle*0.017282) * 0.1;
	}

	if (movement.x == 0)
	{
		row = 0;
	}
	else
	{
		row = 1;

	}

	body.setRotation(angle);
	animation.Update(row, deltaTime);
	body.setTextureRect(animation.uvRect);
	body.move(movement);
}



void Player::ifinwindow()
{
	if (body.getPosition().x >= 1200 + 5)
		body.setPosition(0, body.getPosition().y);

	else if (body.getPosition().x <= 0 - 5)
		body.setPosition(1200, body.getPosition().y);

	if (body.getPosition().y >= 900 + 5)
		body.setPosition(body.getPosition().x, 0);

	else if (body.getPosition().y <= 0 - 5)
		body.setPosition(body.getPosition().x, 900);
}