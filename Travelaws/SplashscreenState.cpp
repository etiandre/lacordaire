#include "SplashscreenState.hpp"
#include "TextureManager.h"
#include "FontManager.hpp"


SplashscreenState::SplashscreenState(GameData& gameData, StateMachine& stateMachine) :
	State(gameData, stateMachine),
	_inputManager() {

	//   BACKGROUND
	sf::Texture* texturePtr =
		TextureManager::loadTexture("Splashscreen", "assets/textures/splashscreen.jpg");
	if (!texturePtr) {
		std::cout << "erreur chargement Texture splashscreen !" << std::endl;
		exit(-1);
	}
	_splashscreenSprite.setTexture(*texturePtr);

	sf::Font* fontPtr =
		FontManager::loadFont("8bitfont", "assets/8bitfont.ttf");
	if (!fontPtr)
	{
		std::cout << "erreur chargement font !" << std::endl;
		exit(-1);
	}

	_text.setFont(*fontPtr);
}


void SplashscreenState::processEvent(sf::Event& event) {
	if (event.type == sf::Event::KeyPressed) _stateMachine.requestState(InGame);
}

void SplashscreenState::update() {

	_gameData.window.clear();
	_gameData.window.draw(_splashscreenSprite);

	//     TEXT 
	_text.setString("L A W S");
	_text.setCharacterSize(36);
	_text.setPosition(sf::Vector2f(SCREEN_WIDTH / SCALE_FACTOR / 8, SCREEN_HEIGHT / SCALE_FACTOR / 8));
	_text.setFillColor(sf::Color(35, 4, 129));
	_text.setStyle(sf::Text::Bold | sf::Text::Underlined);
	_gameData.window.draw(_text);
	_text.setFillColor(sf::Color(141, 29, 206));
	_text.setPosition(sf::Vector2f(SCREEN_WIDTH / SCALE_FACTOR / 8 + 2, SCREEN_HEIGHT / SCALE_FACTOR / 8 - 2));
	_gameData.window.draw(_text);

	//(+animate screen maybe)
}

void SplashscreenState::onEnter() {
	sf::View view(sf::View(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT)));
	// _text and buttons Buttons

	view.reset(sf::FloatRect(0, 0, SCREEN_WIDTH / SCALE_FACTOR,
		SCREEN_HEIGHT / SCALE_FACTOR));
	_gameData.window.setView(view);
}

