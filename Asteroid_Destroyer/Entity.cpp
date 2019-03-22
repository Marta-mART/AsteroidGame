#include "Entity.h"


Entity::~Entity()
{
}

Entity::Entity(Texture* texture, Vector2u imageCount, float switchTime, Vector2f speed, double Angle, double radius) : anim(texture, imageCount, switchTime)
{
	name = "entity";	life = 1; rotation = Angle; this->speed = speed; R = radius;
	anim.setEnd();
	body.setTexture(texture);
	body.setRadius(R);
	body.setRotation(rotation);
}

void Entity::settings(int X, int Y, double Angle, double radius)
{
	x = X; y = Y;
	rotation = Angle;
	R = radius;

	body.setPosition(x, y);
	body.setRotation(rotation + 90);
	body.setRadius(R);
	body.setOrigin(Vector2f(R, R));
}

void Entity::update(float deltaTime, RenderWindow& window) {
	anim.Update(0, deltaTime);
	body.setTextureRect(anim.uvRect);
};