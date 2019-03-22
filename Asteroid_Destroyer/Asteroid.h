#pragma once
#include <iostream>
#include <ctime>
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Entity.h"

using namespace std;
using namespace sf;


class Asteroid :public Entity
{
private:
	Animation animation;

public:
	Asteroid(Texture* texture, Vector2u imageCount, float switchTime);
	void ifinwindow();
	void update(float deltaTime, RenderWindow& window);
};
