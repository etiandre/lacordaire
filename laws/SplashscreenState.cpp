#include "SplashscreenState.hpp"
#include "TextWriter.h"
#include "TextureManager.h"

SplashscreenState::SplashscreenState(GameData& gameData,
                                     StateMachine& stateMachine)
    : State(gameData, stateMachine) {
  //   BACKGROUND
  sf::Texture* texturePtr = TextureManager::loadTexture(
      "Splashscreen", "assets/textures/splashscreen.jpg");
  if (!texturePtr) {
    std::cout << "erreur chargement Texture splashscreen !" << std::endl;
    exit(-1);
  }
  _splashscreenSprite.setTexture(*texturePtr);

  _titleText =
      TextWriter::createText("L.A.W.S.",
                             sf::Vector2f(VIEW_WIDTH / 4,
                                          VIEW_HEIGHT / 4),
                             sf::Color(141, 29, 206));
}

void SplashscreenState::processEvent(sf::Event& event) {
  if (event.type == sf::Event::KeyPressed) _stateMachine.requestState(PreGame);
}

void SplashscreenState::update(sf::Time dt) {
  _gameData.window.clear();
  _gameData.window.draw(_splashscreenSprite);

  TextWriter::drawShadowedText(_titleText, _gameData.window);
  //(+animate screen maybe)
}

void SplashscreenState::onEnter() {
  sf::View view(sf::View(sf::FloatRect(0, 0, VIEW_WIDTH, VIEW_HEIGHT)));
  _gameData.window.setView(view);
}
