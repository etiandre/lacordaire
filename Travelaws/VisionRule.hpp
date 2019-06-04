#pragma once
#include "Rule.h"

class VisionRule : public Rule {

public:
	void draw(sf::RenderWindow& window) override;
	void update(GameData& gameData);
	VisionRule();
	sf::Sprite filter;
	bool filterIsActive=true;
private:
	sf::RectangleShape _rect1;
	sf::RectangleShape _rect2;
};
