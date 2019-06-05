#include "InputManager.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

void InputManager::manageInputs(Player &player) {
  int X = 0;
  int Y = 0;

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
    player.velocity.x = -player.moveSpeed;
    player.animator(player.animatorState().x, 0);
    player.animator(player.animatorState().x + 1, player.animatorState().y);
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    player.velocity.x = player.moveSpeed;
    player.animator(player.animatorState().x, 1);
    player.animator(player.animatorState().x + 1, player.animatorState().y);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && player.onGround) {
    player.velocity.y = -20;
  }
}
