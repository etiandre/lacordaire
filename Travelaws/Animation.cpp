#include "Animation.hpp"
#include <iostream>

Animation::Animation() : _currentTime(sf::seconds(0)), _switchTime(sf::seconds(1)) {}


void Animation::update(int animationSequence, sf::Time delta) {

	_currentImage.y = animationSequence;
	_currentTime += delta;

	if (_currentTime >= _switchTime) {
		_currentTime -= _switchTime;
		_currentImage.x++;

		if (_currentImage.x >= _imageCount.x) {
			_currentImage.x -= _imageCount.x;
		}

		textureRect.left = _currentImage.x * textureRect.width;
		textureRect.top = _currentImage.y * textureRect.height;

	}
}

void Animation::addAnimation(sf::Texture* texture, sf::Vector2i imageCount, sf::Time switchTime)
{
	_imageCount = imageCount;
	_switchTime = switchTime;
	_currentTime = sf::Time();
	_currentImage.x = 0;

	textureRect.width = texture->getSize().x / ((float)imageCount.x);
	textureRect.height = texture->getSize().y / ((float)imageCount.y);
}
