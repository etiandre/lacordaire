#include "SplashscreenState.hpp"
#include "TextureManager.h"

SplashscreenState::SplashscreenState(GameData& gameData, StateMachine& stateMachine) :
	State(gameData, stateMachine),
	_inputManager() {

	//   BACKGROUND
	sf::Texture* texturePtr =
		TextureManager::loadTexture("Splashscreen", "assets/textures/splashscreen.jpg");
	if (!texturePtr) {
		std::cout << "erreur chargement texture splashscreen !" << std::endl;
		exit(-1);
	}
	_splashscreenSprite.setTexture(*texturePtr);
}


void SplashscreenState::processEvent(sf::Event& event) {
	if (event.type == sf::Event::KeyPressed) _stateMachine.requestState(InGame);
}

void SplashscreenState::update() {
	_gameData.window.clear();
	_gameData.window.draw(_splashscreenSprite);

	// !!!!!!! TEMPORARY - CREATE A FONT MANAGER-like

	sf::Font font;
	if (!font.loadFromFile("assets/8bitfont.ttf"))
	{
		exit(-1);
	}
	sf::Text text;
	text.setFont(font);
	text.setString("Hello world");
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::Red);
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);
	_gameData.window.draw(text);
	//(+animate screen maybe)
}

void SplashscreenState::onEnter() {
	sf::View view(sf::View(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT)));
	// Text and buttons Buttons

	view.reset(sf::FloatRect(0, 0, SCREEN_WIDTH / SCALE_FACTOR,
		SCREEN_HEIGHT / SCALE_FACTOR));
	_gameData.window.setView(view);
}

