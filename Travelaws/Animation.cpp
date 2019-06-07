#include "Animation.hpp"
#include <iostream>

Animation::Animation() {}

void Animation::playAnimation(int animationID, sf::Time dt) {
  _currentImage.y = animationID;
  _currentTime += dt;

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

void Animation::setAnimationTexture(sf::Texture* texture,
                                    sf::Vector2i frameCount,
                                    sf::Time timePerFrame) {
  _imageCount = frameCount;
  _switchTime = timePerFrame;
  _currentTime = sf::Time();
  _currentImage.x = 0;

  textureRect.width = texture->getSize().x / ((float)frameCount.x);
  textureRect.height = texture->getSize().y / ((float)frameCount.y);
}
