#include "PreGameState.h"
#include "DEFINITIONS.h"
#include "TextWriter.h"
#include "TextureManager.h"

PreGameState::PreGameState(GameData& gameData, StateMachine& stateMachine)
	: State(gameData, stateMachine) {
	_titleText = TextWriter::createText(
		"Choose your Laws\nPress Space to \nStart", sf::Vector2f(VIEW_WIDTH / 2, VIEW_HEIGHT / 4), sf::Color(221, 207, 60), 32);

	// Create "buttons" to enable or not the rules

	_rule1 = TextWriter::createText(
		"Gravity: ON", sf::Vector2f(VIEW_WIDTH * 1 / 4, VIEW_HEIGHT * 10 / 16), sf::Color::White, 24);
	_rule2 = TextWriter::createText(
		"Wind: ON", sf::Vector2f(VIEW_WIDTH * 3 / 4, VIEW_HEIGHT * 10 / 16), sf::Color::White, 24);
	_rule3 = TextWriter::createText(
		"Vision: ON", sf::Vector2f(VIEW_WIDTH * 1 / 4, VIEW_HEIGHT * 13 / 16), sf::Color::White, 24);
	_rule4 = TextWriter::createText(
		"Collision: ON", sf::Vector2f(VIEW_WIDTH * 3 / 4, VIEW_HEIGHT * 13 / 16), sf::Color::White, 20);


	//Texture manager
	sf::Texture* buttonTexturePtr =
		TextureManager::loadTexture("Button", "assets/textures/button.png");
	if (!buttonTexturePtr) {
		std::cout << "erreur chargement texture Button !" << std::endl;
		exit(1);
	}
	_rule1ButtonImage.setTexture(*buttonTexturePtr);
	_rule2ButtonImage.setTexture(*buttonTexturePtr);
	_rule3ButtonImage.setTexture(*buttonTexturePtr);
	_rule4ButtonImage.setTexture(*buttonTexturePtr);

	float _buttonWidth = _rule1ButtonImage.getLocalBounds().width;
	float _buttonHeight = _rule1ButtonImage.getLocalBounds().height;

	_rule1ButtonImage.setPosition(VIEW_WIDTH / 4.0f - _buttonWidth / 2.0, VIEW_HEIGHT * 10.0f / 16.0f - _buttonHeight / 2.0f);
	_rule2ButtonImage.setPosition(VIEW_WIDTH * 3.0f / 4.0f - _buttonWidth / 2.0, VIEW_HEIGHT * 10.0f / 16.0f - _buttonHeight / 2.0f);
	_rule3ButtonImage.setPosition(VIEW_WIDTH / 4.0f - _buttonWidth / 2.0, VIEW_HEIGHT * 13.0f / 16.0f - _buttonHeight / 2.0f);
	_rule4ButtonImage.setPosition(VIEW_WIDTH * 3.0f / 4.0f - _buttonWidth / 2.0, VIEW_HEIGHT * 13.0f / 16.0f - _buttonHeight / 2.0f);
}

void PreGameState::processEvent(sf::Event& event) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) _stateMachine.requestState(InGame);

	sf::Vector2i mousePos = sf::Mouse::getPosition(_gameData.window);
	sf::Vector2f mouseLocalPosFloat(mousePos.x / SCALE_FACTOR, mousePos.y / SCALE_FACTOR);

	//////// Mouse tracking

	// Checks if mouse is on a button and change its color accordingly
	if (event.type == sf::Event::MouseMoved) {

		if (_rule1ButtonImage.getGlobalBounds().contains(mouseLocalPosFloat))
		{
			_rule1ButtonImage.setColor(sf::Color(41, 163, 126));
		}
		else { _rule1ButtonImage.setColor(sf::Color(255, 255, 255)); }

		if (_rule2ButtonImage.getGlobalBounds().contains(mouseLocalPosFloat))
		{
			_rule2ButtonImage.setColor(sf::Color(41, 163, 126));
		}
		else { _rule2ButtonImage.setColor(sf::Color(255, 255, 255)); }

		if (_rule3ButtonImage.getGlobalBounds().contains(mouseLocalPosFloat))
		{
			_rule3ButtonImage.setColor(sf::Color(41, 163, 126));
		}
		else { _rule3ButtonImage.setColor(sf::Color(255, 255, 255)); }

		if (_rule4ButtonImage.getGlobalBounds().contains(mouseLocalPosFloat))
		{
			_rule4ButtonImage.setColor(sf::Color(41, 163, 126));
		}
		else { _rule4ButtonImage.setColor(sf::Color(255, 255, 255)); }


	}


	//Handles buttons click
	if (event.type == sf::Event::MouseButtonPressed) {
		if (_rule1ButtonImage.getGlobalBounds().contains(mouseLocalPosFloat))
			_gameData.rules[0]->active = !_gameData.rules[0]->active;
		else if (_rule2ButtonImage.getGlobalBounds().contains(mouseLocalPosFloat))
			_gameData.rules[1]->active = !_gameData.rules[1]->active;
		else if (_rule3ButtonImage.getGlobalBounds().contains(mouseLocalPosFloat))
			_gameData.rules[2]->active = !_gameData.rules[2]->active;
		else if (_rule4ButtonImage.getGlobalBounds().contains(mouseLocalPosFloat))
			_gameData.rules[3]->active = !_gameData.rules[3]->active;
	}
	//////////
}

void PreGameState::update(sf::Time dt) {
	_gameData.window.clear();
	sf::RectangleShape background(sf::Vector2f(VIEW_WIDTH, VIEW_HEIGHT));
	background.setFillColor(sf::Color(42, 137, 56));
	_gameData.window.draw(background);

	// Draw "buttons" + Rule's state and points according to processEvent's results

	_gameData.window.draw(_rule1ButtonImage);
	_gameData.window.draw(_rule2ButtonImage);
	_gameData.window.draw(_rule3ButtonImage);
	_gameData.window.draw(_rule4ButtonImage);

	TextWriter::drawShadowedText(_titleText, _gameData.window);
	TextWriter::drawShadowedText(_rule1, _gameData.window);
	TextWriter::drawShadowedText(_rule2, _gameData.window);
	TextWriter::drawShadowedText(_rule3, _gameData.window);
	TextWriter::drawShadowedText(_rule4, _gameData.window);
}

void PreGameState::onEnter() {}