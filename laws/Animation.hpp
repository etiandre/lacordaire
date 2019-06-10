#pragma once
#include "SFML/Graphics.hpp"

class Animation
{
public:
	Animation();
	void playAnimation(int animationSequence, sf::Time delta);
	sf::IntRect textureRect;
	void setAnimationTexture(sf::Texture* texture, sf::Vector2i imageCount, sf::Time switchTime);

private:
	sf::Vector2i _imageCount;
	sf::Vector2i _currentImage;
	sf::Time _currentTime;
	sf::Time _switchTime;
};

