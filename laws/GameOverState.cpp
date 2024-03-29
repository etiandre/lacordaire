#include "GameOverState.hpp"
#include "FontManager.hpp"
#include "TextWriter.h"
#include "TextureManager.h"

GameOverState::GameOverState(GameData& gameData, StateMachine& stateMachine)
    : State(gameData, stateMachine) {
  sf::Texture* texturePtr =
      TextureManager::loadTexture("GameOver", "assets/textures/gameover.png");
  if (!texturePtr) {
    std::cout << "erreur chargement texture gameOver !" << std::endl;
    exit(1);
  }
  _gameOverSprite.setTexture(*texturePtr);
  _gitgudText =
      TextWriter::createText("git gud",
                             sf::Vector2f(VIEW_WIDTH / 2,
                                          VIEW_HEIGHT / 8),
                             sf::Color(141, 29, 206));
}

void GameOverState::processEvent(sf::Event& event) {
  if (event.type == sf::Event::KeyPressed) _stateMachine.requestState(InGame);
}

void GameOverState::update(sf::Time dt) {
  _gameData.window.clear();
  _gameData.window.draw(_gameOverSprite);
  TextWriter::drawShadowedText(_gitgudText, _gameData.window);
}

void GameOverState::onEnter() {
  sf::View view(sf::View(sf::FloatRect(0, 0, VIEW_WIDTH, VIEW_HEIGHT)));
  _gameData.window.setView(view);
  std::thread thread_object(playSound(), "assets/sounds/gameover.wav");
  thread_object.detach();
}
