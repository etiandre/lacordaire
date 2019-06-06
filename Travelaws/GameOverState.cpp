#include "GameOverState.hpp"
#include "TextureManager.h"

GameOverState::GameOverState(GameData& gameData, StateMachine& stateMachine)
    : State(gameData, stateMachine), _inputManager() {
  sf::Texture* texturePtr =
      TextureManager::loadTexture("GameOver", "assets/textures/gameover.png");
  if (!texturePtr) {
    std::cout << "erreur chargement texture gameOver !" << std::endl;
    exit(1);
  }
  std::cout << "GG, Score = " << std::endl;
  _gameOverSprite.setTexture(*texturePtr);
}

void GameOverState::processEvent(sf::Event& event) {
  if (event.type == sf::Event::KeyPressed) _stateMachine.requestState(InGame);
}

void GameOverState::update() {
  _gameData.window.clear();
  _gameData.window.draw(_gameOverSprite);
  // getInputs, manage buttons (+ animate gameOver screen maybe)
}

void GameOverState::onEnter() {
  sf::View view(sf::View(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT)));
  // Instantiate Buttons

  view.reset(sf::FloatRect(0, 0, SCREEN_WIDTH / SCALE_FACTOR,
                           SCREEN_HEIGHT / SCALE_FACTOR));
  _gameData.window.setView(view);
}
