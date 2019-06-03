#include "pch.h"
#include "InputManager.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

void InputManager::manageInputs(Player &player) {
	int x = 0;
	int y = 0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		x = -3;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		x = 3;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		y = -5;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		y = 3;
	}

	player.move(x, y);

	std::cout << "coords (" << player.getPosition().x << "," << player.getPosition().y << ")" << std::endl;
}

