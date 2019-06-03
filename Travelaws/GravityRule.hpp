#pragma once

class GravityRule : public Rule {
 private:
  float gravity = -3;

 public:
  void update(GameData gameData&);
};