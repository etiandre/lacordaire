#pragma once

#include <sstream>
#include "DEFINITIONS.h"
#include "GameOverState.h"
#include <iostream>

GameOverState::GameOverState(GameDataRef data) : _data(data)
{

}

void GameOverState::init()
{
	_data->assets.loadTexture("Game Over Background", GAME_OVER_BACKGROUND_FILEPATH);
	_background.setTexture(_data->assets.getTexture("Game Over Background"));
}

void GameOverState::handleInput()
{
	sf::Event event;

	while (this->_data->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			_data->window.close();
		}
	}
}

void GameOverState::update(float dt)
{

}

void GameOverState::draw(float dt)
{
	_data->window.clear(sf::Color::Red);
	_data->window.draw(_background);
	_data->window.display();
}
