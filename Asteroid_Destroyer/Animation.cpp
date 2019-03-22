#include "Animation.h"



Animation::Animation(Texture* texture, Vector2u imageCount, float switchTime)
{
	this->imageCount = imageCount;
	this->switchTime = switchTime;
	totalTime = 0;
	currentImage.x = 0;
	isEnd = false;

	uvRect.width = texture->getSize().x / (float)(imageCount.x);
	uvRect.height = texture->getSize().y / (float)(imageCount.y);
}


Animation::~Animation()
{
}

void Animation::Update(int row, float deltaTime)
{
	currentImage.y = row;
	totalTime += deltaTime;

	if (totalTime >= switchTime) // if czas ktory leci jest juz wiekszy niz ten po ktorym chcemy switchnac na nast obrazek
	{
		totalTime -= switchTime; // =0 not smoother
		currentImage.x++;

		if (isEnd == false)
		{
			if (currentImage.x >= imageCount.x)
			{
				currentImage.x = 0;
			}
		}

	}

	uvRect.top = currentImage.y * uvRect.height;

	uvRect.left = currentImage.x * uvRect.width;
	uvRect.width = abs(uvRect.width);


}

bool Animation::isEndOfAnimation()
{
	if (currentImage.x >= imageCount.x)
	{
		return true;
	}
	return false;
}