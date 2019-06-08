#include "PreGameState.h"
#include "DEFINITIONS.h"
#include "TextWriter.h"

PreGameState::PreGameState(GameData& gameData, StateMachine& stateMachine)
    : State(gameData, stateMachine) {
  _titleText = TextWriter::createText(
      "choix des regles\n Press Space to Start", sf::Vector2f(VIEW_WIDTH / 2, VIEW_HEIGHT / 2));
}

void PreGameState::processEvent(sf::Event& event) {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) _stateMachine.requestState(InGame);
}

void PreGameState::update(sf::Time dt) {
  _gameData.window.clear();
  TextWriter::drawShadowedText(_titleText, _gameData.window);
  // Draw "buttons" + Rule's state and points
}

void PreGameState::onEnter() {
	// Create "buttons" to enable or not the rules
}
