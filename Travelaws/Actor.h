#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.hpp"

class Actor {
public:
	Actor(const char* name);
	void teleportTo(float x, float y);
	void teleportTo(sf::Vector2f position);
	sf::Vector2f getPosition();
	virtual void update(sf::Time dt);

	void draw(sf::RenderWindow& window);
	bool collidesWith(sf::FloatRect rect);

	sf::Vector2f velocity;
	sf::Sprite sprite;
	sf::FloatRect hitbox;


protected:
	Animation _anim;
	float _inertia;
	const char* _name;
};