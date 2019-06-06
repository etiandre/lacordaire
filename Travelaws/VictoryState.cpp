#include "VictoryState.hpp"
#include "TextureManager.h"

VictoryState::VictoryState(GameData& gameData, StateMachine& stateMachine) :
	State(gameData, stateMachine),
	_inputManager(),
	_view(sf::View(sf::FloatRect(0, 0, SCREEN_WIDTH,
		SCREEN_HEIGHT))) {

	sf::Texture* texturePtr = TextureManager::loadTexture("Victory", "assets/textures/victory.png");
	if (!texturePtr) {
		std::cout << "erreur chargement texture Victory !" << std::endl;
		exit(1);
	}
	std::cout << "GG, Score = " << std::endl;
	_victorySprite.setTexture(*texturePtr);

	_view.reset(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
	_gameData.window.setView(_view);


}

void VictoryState::processEvent(sf::Event& event) {
  if (event.type == sf::Event::KeyPressed) _stateMachine.requestState(InGame);
}

void VictoryState::update() {
	_gameData.window.clear();
	_gameData.window.draw(_victorySprite);
}

void VictoryState::onEnter() {
	//Instantiate Buttons
	sf::View view(sf::View(sf::FloatRect(0, 0, SCREEN_WIDTH,
		SCREEN_HEIGHT)));
	//Instantiate Buttons

	view.reset(sf::FloatRect(0, 0, SCREEN_WIDTH / SCALE_FACTOR, SCREEN_HEIGHT / SCALE_FACTOR));
	_gameData.window.setView(view);
}

void VictoryState::onExit() {
}
