#include "Bullet.h"
#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "Animation.h"


using namespace std;
using namespace sf;

Bullet::Bullet(Texture * texture, Vector2u imageCount, float switchTime) :animation(texture, imageCount, switchTime)
{
	name = "bullet";
	body.setTexture(texture);
	row = 0;
	speed.x = 500;
	speed.y = 500;
}

void Bullet::settings(int X, int Y, double Angle, double radius)
{
	x = X;
	y = Y;
	rotation = Angle;

	R = radius;

	body.setPosition(x, y);
	body.setRotation(rotation + 90);
	body.setRadius(R);
	body.setOrigin(Vector2f(body.getRadius(), body.getRadius()));
}

void Bullet::update(float deltaTime, RenderWindow& window)
{
	float vx = sin((rotation * 3.1415) / 180.0f);
	float vy = -cos((rotation * 3.1415) / 180.0f);

	Vector2f movement;
	movement.x = deltaTime * vx * speed.x;
	movement.y = deltaTime * vy * speed.y;

	body.move(movement);
	body.setRotation(rotation);
	animation.Update(row, deltaTime);
	body.setTextureRect(animation.uvRect);
	ifinwindow();

}

void Bullet::ifinwindow()
{
	if (body.getPosition().x >= 1200 + 5 || body.getPosition().x < 0 || body.getPosition().y >= 900 + 5 || body.getPosition().y <= 0 - 5) life = 0;
}

Bullet::~Bullet()
{
}

