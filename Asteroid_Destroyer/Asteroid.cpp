#include "Asteroid.h"
#include <cmath>

Asteroid::Asteroid(Texture* texture, Vector2u imageCount, float switchTime) : animation(texture, imageCount, switchTime)
{
	body.setTexture(texture);
	body.setRadius(40);
	body.setOrigin(Vector2f(body.getRadius(), body.getRadius()));
	body.setRotation(rotation);

	name = "asteroid";

	float Alpha = (rand() % 360) / 180.0 *3.14159;
	float zmienna = rand() % 12 / 10.0 + 0.07;

	speed.x = zmienna*cos(Alpha);
	speed.y = zmienna*sin(Alpha);
}


void Asteroid::update(float deltaTime, RenderWindow& window)
{
	ifinwindow();
	body.setRotation(rotation);
	animation.Update(0, deltaTime);
	body.setTextureRect(animation.uvRect);
	body.move(speed.x, speed.y);

}


void Asteroid::ifinwindow()
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