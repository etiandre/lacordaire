#include "InputManager.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

void InputManager::manageInputs(Player &player) {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
    player.velocity.x = -player.moveSpeed;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    player.velocity.x = player.moveSpeed;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && player.onGround) {
    player.velocity.y = -8;
  }
}
