#include "VictoryState.hpp"


VictoryState::VictoryState(GameData& gameData, StateMachine& stateMachine) :
	State(gameData, stateMachine),
	_inputManager(),
	_view(sf::View(sf::FloatRect(0, 0, SCREEN_WIDTH,
		SCREEN_HEIGHT))) {


	sf::Texture VictoryTexture;
	if (!VictoryTexture.loadFromFile("assets/textures/Victory.jpg")) {
		std::cout << "erreur chargement texture Victory !" << std::endl;
		exit(1);
	}
	std::cout << "GG, Score = " << std::endl;
	_victorySprite.setTexture(VictoryTexture);

	_view.reset(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
	_gameData.window.setView(_view);


}

void VictoryState::update() {
	//getInputs, manage buttons (+ animate Victory screen maybe)
}

void VictoryState::onEnter() {
	_gameData.window.clear();
	_gameData.window.draw(_victorySprite);
	//Instantiate Buttons
}

void VictoryState::onExit() {
	//Reset score, load level according to player's choice
}
