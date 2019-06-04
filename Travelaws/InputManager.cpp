#include "InputManager.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

void InputManager::manageInputs(Player &player) {
  int X = 0;
  int Y = 0;

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
    X = -3;
    player.animator(player.animatorState().x, 0);
    player.animator(player.animatorState().x + 1, player.animatorState().y);
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    X = 30;
    player.animator(player.animatorState().x, 1);
    player.animator(player.animatorState().x + 1, player.animatorState().y);
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
    Y = -5;
    // specific anim ?
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
    Y = 3;
  }

  player.velocity.x = X;
  player.velocity.y = Y;

  // std::cout << "coords (" << player.getPosition().x << "," <<
  // player.getPosition().y << ")" << std::endl;
}
