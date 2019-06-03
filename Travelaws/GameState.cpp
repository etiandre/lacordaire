#pragma once
#include <sstream>
#include "DEFINITIONS.h"
#include "GameState.h"
#include <iostream>

GameState::GameState(GameDataRef data) : _data(data)
{

}

void GameState::init()
{
	_data->assets.loadTexture("Game Background", GAME_BACKGROUND_FILEPATH);
	_background.setTexture(_data->assets.getTexture("Game Background"));
}

void GameState::handleInput()
{
	sf::Event event;

	while (_data->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			_data->window.close();
		}
	}
}

void GameState::update(float dt)
{

}

void GameState::draw(float dt)
{
	_data->window.clear(sf::Color::Red);
	_data->window.draw(_background);
	_data->window.display();
}
