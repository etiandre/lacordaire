#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.hpp"

/*
Classe de base pour un objet dynamique
Une classe enfant devrait au moins implémenter update()
*/
class Actor {
public:
	// Constructeur avec un nom pour le debug
	Actor(const char* name);

	// téléporte l'Actor aux coordonnées spécifiées et reset son vecteur vitesse
	void teleportTo(float x, float y);
	void teleportTo(sf::Vector2f position);

	sf::Vector2f getPosition();
	
	virtual void update(sf::Time dt);

	// dessine l'actor
	void draw(sf::RenderWindow& window);

	// renvoie vrai si l'actor touche rect
	bool collidesWith(sf::FloatRect rect);

	sf::Vector2f velocity; // en pixels/seconde
	sf::Sprite sprite;
	sf::FloatRect hitbox;


protected:
	Animator _anim;
	const char* _name;
};