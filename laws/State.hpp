#pragma once
#include <thread>
#include "GameData.h"
#include "SFML/Audio.hpp"
#include "SoundManager.h"
#include "StateMachine.hpp"

class StateMachine;
/*
Classe abstraite représentant le concept d'état. Est géré par une StateMachine
On l'initialise avec une référence à gameData et à la stateMachine -> ceux-ci
doivent avoir été créés au préalable.

Une classe enfant devrait au moins implémenter update() pour servir à quelque chose
*/
class State {
 public:
  State(GameData& gameData, StateMachine& stateMachine);
	// doit gérer les éventuels events
  virtual void processEvent(sf::Event& event);
	// doit implémenter la mise à jour des objets de jeu et leur dessin
  virtual void update(sf::Time dt);
	// est appelé lors de l'entrée dans ce state
  virtual void onEnter();
	// est appelé lors de la sortie du state
  virtual void onExit();

 protected:
  GameData& _gameData;
  StateMachine& _stateMachine;
};