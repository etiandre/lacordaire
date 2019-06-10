#pragma once
#include "GameData.h"
#include "State.hpp"

enum StateName { None, Splash, PreGame, InGame, GameOver, Victory };

class State;

/*
Classe impl�mentant une machine � �tats
Est initialis�e avec une r�f�rence � gameData qui doit donc avoir �t� cr�� au
pr�alable.
Aucun �tat n'est d�truit apr�s sa cr�ation, seulement d�sactiv�.
*/
class StateMachine {
 public:
  StateMachine(GameData& gameData);

  // ajoute un �tat � la liste interne
  void addState(StateName stateName, std::unique_ptr<State> state);
  // demande le basculement sur un �tat d�j� ajout� � la liste interne
  void requestState(StateName stateName);

  // update() et processEvent() appellent les fonctions idoines du State actif
  void update(sf::Time dt);
  void processEvent(sf::Event& event);

  // s'il y a un changement d'�tat en attente:
  // - appelle onExit() de l'�tat actuel
  // - change l'�tat actuel vers le nouveau
  // - appelle onEnter() de ce nouvel �tat
  void processStateSwitch();

 private:
  GameData& _gameData;
  std::map<StateName, std::unique_ptr<State>> _states;
  void _switchState(StateName stateName);
  StateName _currentState;
  StateName _nextState;
};