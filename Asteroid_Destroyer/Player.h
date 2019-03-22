#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include  "Animation.h"
#include  "Entity.h"
#include <cmath>

using namespace std;
using namespace sf;

const unsigned max_speed = 1000;
enum Status;

class Player :public Entity
{
private:
	Animation animation;
	unsigned row;
	float vx, vy;
	unsigned lives = 100;
public:
	Player(Texture* texture, Vector2u imageCount, float switchTime, Vector2f speed);
	~Player();
	Vector2f GetPosition() { return body.getPosition(); }
	void ifinwindow();
	void update(float deltaTime, RenderWindow & window);
	void removeLive() { if (lives> 0) lives--; }
	unsigned getLives() { return lives; }

};


