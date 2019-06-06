#include "VictoryState.hpp"


VictoryState::VictoryState(GameData& gameData, StateMachine& stateMachine) :
	State(gameData, stateMachine),
	_inputManager(),
	_view(sf::View(sf::FloatRect(0, 0, SCREEN_WIDTH,
		SCREEN_HEIGHT))) {


	sf::Texture VictoryTexture;
	if (!VictoryTexture.loadFromFile("assets/textures/victory.png")) {
		std::cout << "erreur chargement texture Victory !" << std::endl;
		exit(1);
	}
	std::cout << "GG, Score = " << std::endl;
	_victorySprite.setTexture(VictoryTexture);

	_view.reset(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
	_gameData.window.setView(_view);


}

void VictoryState::update() {
	_gameData.window.clear();
	_gameData.window.draw(_victorySprite);
	//getInputs, manage buttons (+ animate Victory screen maybe)
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
	//Reset score, load level according to player's choice
}
