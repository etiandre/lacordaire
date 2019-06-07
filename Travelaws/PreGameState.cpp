#include "PreGameState.h"
#include "DEFINITIONS.h"
#include "TextWriter.h"

PreGameState::PreGameState(GameData& gameData, StateMachine& stateMachine)
    : State(gameData, stateMachine) {
  _titleText = TextWriter::createText(
      "choix des regles", sf::Vector2f(VIEW_WIDTH / 2, VIEW_HEIGHT / 2));
}

void PreGameState::processEvent(sf::Event& event) {
  if (event.type == sf::Event::KeyPressed) _stateMachine.requestState(InGame);
}

void PreGameState::update(sf::Time dt) {
  _gameData.window.clear();
  TextWriter::drawShadowedText(_titleText, _gameData.window);
}

void PreGameState::onEnter() {}
