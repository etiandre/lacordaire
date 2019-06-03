#include "pch.h"
#include "InputManager.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

void InputManager::manageInputs(Player &player) {

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {

		player.move(-3, 0);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		player.move(3, 0);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		player.move(0, -5);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		player.move(0, 3);
	}

	std::cout << "coords (" << player.getPosition().x << "," << player.getPosition().y << ")" << std::endl;
}

