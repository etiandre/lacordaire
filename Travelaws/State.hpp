#pragma once
#include <thread>
#include "GameData.h"
#include "StateMachine.hpp"
#include "SFML/Audio.hpp"
#include "SoundManager.h"


class StateMachine;

class State {
 public:
  State(GameData& gameData, StateMachine& stateMachine);
  virtual void processEvent(sf::Event& event);
  virtual void update(sf::Time dt);
  virtual void onEnter();
  virtual void onExit();

 protected:
  GameData& _gameData;
  StateMachine& _stateMachine;
};