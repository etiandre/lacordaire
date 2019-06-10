#include "Animation.hpp"
#include <iostream>

Animator::Animator() {}

void Animator::playAnimation(int animationID, sf::Time dt) {
  _currentFrame.y = animationID;
  _currentTime += dt;

  if (_currentTime >= _timePerFrame) {
    _currentTime -= _timePerFrame;
    _currentFrame.x++;

    if (_currentFrame.x >= _frameCount.x) {
      _currentFrame.x -= _frameCount.x;
    }

    textureRect.left = _currentFrame.x * textureRect.width;
    textureRect.top = _currentFrame.y * textureRect.height;
  }
}

void Animator::setAnimationTexture(sf::Texture* texture,
                                    sf::Vector2i frameCount,
                                    sf::Time timePerFrame) {
  _frameCount = frameCount;
  _timePerFrame = timePerFrame;
  _currentTime = sf::Time();
  _currentFrame.x = 0;

  textureRect.width = texture->getSize().x / ((float)frameCount.x);
  textureRect.height = texture->getSize().y / ((float)frameCount.y);
}
