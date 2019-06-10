#pragma once
#include "SFML/Graphics.hpp"

class Animator {
 public:
  Animator();
  void playAnimation(int animationID, sf::Time dt);
  sf::IntRect textureRect;
  void setAnimationTexture(sf::Texture* texture, sf::Vector2i frameCount,
                           sf::Time timePerFrame);

 private:
  sf::Vector2i _frameCount;
  sf::Vector2i _currentFrame;
  sf::Time _currentTime;
  sf::Time _timePerFrame;
};
