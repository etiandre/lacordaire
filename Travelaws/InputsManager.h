#pragma once

#include "SFML\Graphics.hpp"


class InputsManager
{
public:
	InputsManager() {}
	~InputsManager() {}

	bool isSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow &window);

	sf::Vector2i getMousePosition(sf::RenderWindow &window);
};
