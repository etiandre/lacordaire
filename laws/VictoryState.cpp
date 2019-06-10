#include "VictoryState.hpp"
#include <algorithm>
#include "DEBUG.h"
#include "TextWriter.h"
#include "TextureManager.h"


// Constructor
VictoryState::VictoryState(GameData& gameData, StateMachine& stateMachine)
    : State(gameData, stateMachine) {
  sf::Texture* texturePtr =
      TextureManager::loadTexture("Victory", "assets/textures/victory.jpg");
  if (!texturePtr) {
    std::cout << "erreur chargement texture Victory !" << std::endl;
    exit(1);
  }
  _victorySprite.setTexture(*texturePtr);
}

// Requests State change at the end of the current frame
void VictoryState::processEvent(sf::Event& event) {
  if (event.type == sf::Event::KeyPressed) _stateMachine.requestState(PreGame);
}

// Victory state's graphics update, displays the content created during onEnter
void VictoryState::update(sf::Time dt) {
  _gameData.window.clear();
  _gameData.window.draw(_victorySprite);
  TextWriter::drawShadowedText(_ggText, _gameData.window);
  TextWriter::drawShadowedText(_timeText, _gameData.window);
  TextWriter::drawShadowedText(_ruleText, _gameData.window);
  TextWriter::drawShadowedText(_totalText, _gameData.window);
}

// Initializes Victory state's content
void VictoryState::onEnter() {
  int timeScore = std::max((int)(50. - _gameData.time.asSeconds()), 0);
  int ruleScore = 0;
  for (const auto& rule : _gameData.rules)
    if (rule.get()->active) ruleScore += rule.get()->getScore();

  sf::View view(sf::View(sf::FloatRect(0, 0, VIEW_WIDTH, VIEW_HEIGHT)));

  _ggText = TextWriter::createText(
      "you win !", sf::Vector2f(VIEW_WIDTH / 2, VIEW_HEIGHT / 5),
      sf::Color(141, 29, 206));
  char buf[255];

  sprintf_s(buf, "%zd rules=%d pts", _gameData.rules.size(), ruleScore);
  _ruleText =
      TextWriter::createText(buf, sf::Vector2f(VIEW_WIDTH / 2, VIEW_HEIGHT / 5 * 2),
                             sf::Color(255, 0, 0), 20);

  sprintf_s(buf, "%.2f s=%d pts", _gameData.time.asSeconds(), timeScore);
  _timeText = TextWriter::createText(
      buf, sf::Vector2f(VIEW_WIDTH / 2, VIEW_HEIGHT / 5 * 3),
      sf::Color(255, 0, 0), 20);

  sprintf_s(buf, "total=%d pts", timeScore + ruleScore);
  _totalText = TextWriter::createText(
      buf, sf::Vector2f(VIEW_WIDTH / 2, VIEW_HEIGHT / 5 * 4), sf::Color(255, 0, 0), 25);

  _gameData.window.setView(view);
}
