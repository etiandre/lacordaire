#pragma once
#include <thread>
#include "GameData.h"
#include "SFML/Audio.hpp"
#include "SoundManager.h"
#include "StateMachine.hpp"

class StateMachine;
/*
Classe abstraite repr�sentant le concept d'�tat. Est g�r� par une StateMachine
On l'initialise avec une r�f�rence � gameData et � la stateMachine -> ceux-ci
doivent avoir �t� cr��s au pr�alable.

Une classe enfant devrait au moins impl�menter update() pour servir � quelque chose
*/
class State {
 public:
  State(GameData& gameData, StateMachine& stateMachine);
	// doit g�rer les �ventuels events
  virtual void processEvent(sf::Event& event);
	// doit impl�menter la mise � jour des objets de jeu et leur dessin
  virtual void update(sf::Time dt);
	// est appel� lors de l'entr�e dans ce state
  virtual void onEnter();
	// est appel� lors de la sortie du state
  virtual void onExit();

 protected:
  GameData& _gameData;
  StateMachine& _stateMachine;
};