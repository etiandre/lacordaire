#include "GameOverState.hpp"
#include "TextureManager.h"
#include "FontManager.hpp"

GameOverState::GameOverState(GameData& gameData, StateMachine& stateMachine) : 
	State(gameData, stateMachine),
	_inputManager() {

	sf::Texture* texturePtr =
		TextureManager::loadTexture("GameOver", "assets/textures/gameover.png");
	if (!texturePtr) {
		std::cout << "erreur chargement texture gameOver !" << std::endl;
		exit(1);
	}
	std::cout << "GG, Score = " << std::endl;
	_gameOverSprite.setTexture(*texturePtr);

	sf::Font* fontPtr =
		FontManager::loadFont("font", "assets/font.ttf");
	if (!fontPtr)
	{
		std::cout << "erreur chargement font !" << std::endl;
		exit(-1);
	}

	_text.setFont(*fontPtr);
}

void GameOverState::processEvent(sf::Event& event) {
	if (event.type == sf::Event::KeyPressed) _stateMachine.requestState(InGame);
}

void GameOverState::update(sf::Time dt) {
	_gameData.window.clear();
	_gameData.window.draw(_gameOverSprite);
	//(+ animate gameOver screen maybe)
	
		//     TEXT 
	_text.setString(" Ahah\n Try to do \n better");
	_text.setCharacterSize(36);
	_text.setPosition(sf::Vector2f(SCREEN_WIDTH / SCALE_FACTOR / 8, SCREEN_HEIGHT / SCALE_FACTOR / 8));
	_text.setFillColor(sf::Color(35, 4, 129));
	_gameData.window.draw(_text);
	_text.setFillColor(sf::Color(141, 29, 206));
	_text.setPosition(sf::Vector2f(SCREEN_WIDTH / SCALE_FACTOR / 8 + 2, SCREEN_HEIGHT / SCALE_FACTOR / 8 - 2));
	_gameData.window.draw(_text);
}

void GameOverState::onEnter() {
	sf::View view(sf::View(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT)));
	// Instantiate Buttons

	view.reset(sf::FloatRect(0, 0, SCREEN_WIDTH / SCALE_FACTOR,
		SCREEN_HEIGHT / SCALE_FACTOR));
	_gameData.window.setView(view);
}
