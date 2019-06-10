#pragma once
#include "GameData.h"
#include "State.hpp"

enum StateName { None, Splash, PreGame, InGame, GameOver, Victory };

class State;

/*
Classe implémentant une machine à états
Est initialisée avec une référence à gameData qui doit donc avoir été créé au
préalable.
Aucun état n'est détruit après sa création, seulement désactivé.
*/
class StateMachine {
 public:
  StateMachine(GameData& gameData);

  // ajoute un état à la liste interne
  void addState(StateName stateName, std::unique_ptr<State> state);
  // demande le basculement sur un état déjà ajouté à la liste interne
  void requestState(StateName stateName);

  // update() et processEvent() appellent les fonctions idoines du State actif
  void update(sf::Time dt);
  void processEvent(sf::Event& event);

  // s'il y a un changement d'état en attente:
  // - appelle onExit() de l'état actuel
  // - change l'état actuel vers le nouveau
  // - appelle onEnter() de ce nouvel état
  void processStateSwitch();

 private:
  GameData& _gameData;
  std::map<StateName, std::unique_ptr<State>> _states;
  void _switchState(StateName stateName);
  StateName _currentState;
  StateName _nextState;
};