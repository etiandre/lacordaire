#include "GameOverState.hpp"

GameOverState::GameOverState(GameData& gameData, StateMachine& stateMachine)
    : State(gameData, stateMachine),
      _inputManager(),
      _view(sf::View(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT))) {
  sf::Texture gameOverTexture;
  if (!gameOverTexture.loadFromFile("assets/textures/gameover.jpg")) {
    std::cout << "erreur chargement texture gameOver !" << std::endl;
    exit(1);
  }
  std::cout << "GG, Score = " << std::endl;
  _gameOverSprite.setTexture(gameOverTexture);

  _view.reset(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
  _gameData.window.setView(_view);
}

void GameOverState::update() {
  // getInputs, manage buttons (+ animate gameOver screen maybe)
  std::cout << "update" << std::endl;
}

void GameOverState::onEnter() {
  _gameData.window.clear();
  _gameData.window.draw(_gameOverSprite);
  // Instantiate Buttons
}
