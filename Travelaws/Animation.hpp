#pragma once
#include "SFML/Graphics.hpp"

class Animation
{
public:
	Animation();
	void update(int animationSequence, sf::Time delta);
	sf::IntRect textureRect;
	void addAnimation(sf::Texture* texture, sf::Vector2i imageCount, sf::Time switchTime);

private:
	sf::Vector2i _imageCount;
	sf::Vector2i _currentImage;
	sf::Time _currentTime;
	sf::Time _switchTime;
};

