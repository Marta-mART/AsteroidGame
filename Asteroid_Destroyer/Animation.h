#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

class Animation
{
private:
	Vector2u imageCount;
	Vector2u currentImage;
	bool isEnd;
	float totalTime;
	float switchTime;

public:
	IntRect uvRect;
	Animation() {}
	Animation(Texture* texture, Vector2u imageCount, float switchTime);
	~Animation();
	void Update(int row, float deltaTime);
	void setEnd() { isEnd = true; }
	bool isEndOfAnimation();
};

