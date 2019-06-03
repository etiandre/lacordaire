#pragma once
#include "pch.h"
#include "InputsManager.h"


bool InputsManager::isSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow &window)
{
	if (sf::Mouse::isButtonPressed(button))
	{
		sf::IntRect playButtonRect(object.getPosition().x, object.getPosition().y, object.getGlobalBounds().width, object.getGlobalBounds().height);

		if (playButtonRect.contains(sf::Mouse::getPosition(window)))
		{
			return true;
		}
	}

	return false;
}

sf::Vector2i InputsManager::getMousePosition(sf::RenderWindow &window)
{
	return sf::Mouse::getPosition(window);
}

