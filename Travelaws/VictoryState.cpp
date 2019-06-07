#include "VictoryState.hpp"
#include "TextWriter.h"
#include "TextureManager.h"

VictoryState::VictoryState(GameData& gameData, StateMachine& stateMachine)
    : State(gameData, stateMachine) {
  sf::Texture* texturePtr =
      TextureManager::loadTexture("Victory", "assets/textures/victory.png");
  if (!texturePtr) {
    std::cout << "erreur chargement texture Victory !" << std::endl;
    exit(1);
  }
  std::cout << "GG, Score = " << std::endl;
  _victorySprite.setTexture(*texturePtr);
  _ggText =
      TextWriter::createText("gg you win",
                             sf::Vector2f(SCREEN_WIDTH / SCALE_FACTOR / 2,
                                          SCREEN_HEIGHT / SCALE_FACTOR / 4),
                             sf::Color(141, 29, 206));
}

void VictoryState::processEvent(sf::Event& event) {
  if (event.type == sf::Event::KeyPressed) _stateMachine.requestState(InGame);
}

void VictoryState::update(sf::Time dt) {
  _gameData.window.clear();
  _gameData.window.draw(_victorySprite);
  TextWriter::drawShadowedText(_ggText, _gameData.window);
  TextWriter::drawShadowedText(_scoreText, _gameData.window);
}

void VictoryState::onEnter() {
  sf::View view(sf::View(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT)));
  char buf[255];
  sprintf_s(buf, "%.2f s", _gameData.time.asSeconds());
  _scoreText = TextWriter::createText(
      buf, sf::Vector2f(SCREEN_WIDTH / SCALE_FACTOR / 2,
                        SCREEN_HEIGHT / SCALE_FACTOR / 4 * 3));
  view.reset(sf::FloatRect(0, 0, SCREEN_WIDTH / SCALE_FACTOR,
                           SCREEN_HEIGHT / SCALE_FACTOR));
  _gameData.window.setView(view);
}
