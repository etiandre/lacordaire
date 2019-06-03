// Travelaws.cpp : Ce fichier contient la fonction 'main'
//

#pragma region includes
#include "pch.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Travelaws.h"
#include "DEFINITIONS.h"
#include "SplashState.h"
#pragma endregion includes

/*
Game::Game(int width, int height, std::string title)
{
	//INIT

	run();
}

void Game::run()
{
	
	}

}
int main(int argc, char ** argv) {
	Game(SCREEN_WIDTH, SCREEN_HEIGHT, "Travelaws alpha");

	return EXIT_SUCCESS;
}

*/
#pragma region variables
sf::RenderWindow window;
int windowHeight = 1080;
int windowWidth = 1920;


sf::CircleShape circle;
sf::ConvexShape convex;
int speed = 5;
sf::Vector2i positionSouris;
sf::Texture slimeTexture;
sf::Sprite slimeSprite;
enum Directions { Left, Right };
sf::Vector2i anim(1, Right);
bool updateFPS = true;
int blockSize = 64;
sf::View view;
#pragma endregion variables


void gestion_clavier() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		anim.y = Left;
		slimeSprite.move(-speed, 0);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		anim.y = Right;
		slimeSprite.move(speed, 0);
	}

	if (slimeSprite.getPosition().x <= 0 )
		slimeSprite.setPosition(sf::Vector2f(0, slimeSprite.getPosition().y));
	if (slimeSprite.getPosition().x >= windowWidth)
		slimeSprite.setPosition(sf::Vector2f(windowWidth, slimeSprite.getPosition().y));
	if (slimeSprite.getPosition().y <= 0)
		slimeSprite.setPosition(sf::Vector2f(slimeSprite.getPosition().x, 0));
	if (slimeSprite.getPosition().y >= windowHeight)
		slimeSprite.setPosition(sf::Vector2f(slimeSprite.getPosition().x, windowHeight));

}

void gestion_souris() {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		positionSouris = sf::Mouse::getPosition(window);
		std::cout << "Mouse.x = " << sf::Mouse::getPosition().x << "Mouse.y = " << sf::Mouse::getPosition().y << std::endl;
	}
}


int main(int argc, char ** argv) {

	window.create(sf::VideoMode(windowWidth, windowHeight), "DemGame");
	window.setFramerateLimit(60);
	std::cout << "Lancement du jeu" << std::endl;

	sf::Event event;


	if (!slimeTexture.loadFromFile("textures/slime.png")) {
		std::cout << "erreur chargement slime.png" << std::endl;
	}
	slimeTexture.setSmooth(true); //lisse la texture
	slimeSprite.setTexture(slimeTexture);


	float fpsCount = 0,
		switchFPS = 100,
		fpsSpeed = 500;



	sf::Clock time;

	while (window.isOpen()) {
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::EventType::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
				updateFPS = true;
			else
				updateFPS = false;
		}


		gestion_clavier();
		gestion_souris();

		if (updateFPS)
		{
			if (time.getElapsedTime().asMilliseconds() >= 50)
			{
				anim.x--;
				if (anim.x * blockSize >= slimeTexture.getSize().x)
					anim.x = 2;
				time.restart();
				std::cout << slimeSprite.getPosition().x << "," << slimeSprite.getPosition().y << std::endl;
			}
		}

		slimeSprite.setTextureRect(sf::IntRect(anim.x*blockSize, anim.y*blockSize, blockSize, blockSize));

		//Détection des collisions:

		//Création et gestion de la vue:
		view.reset(sf::FloatRect(0, 0, windowWidth, windowHeight));
		sf::Vector2f position(windowWidth / 2, windowHeight / 2);
		position.x = slimeSprite.getPosition().x + blockSize / 2 - windowWidth/2;
		if (position.x < 0)
			position.x = 0;
		if (position.y < 0)
			position.y = 0;

		view.reset(sf::FloatRect(position.x, 0, windowWidth, windowHeight));
		window.setView(view);

		window.clear();
		window.draw(slimeSprite);
		window.draw(circle);
		window.draw(convex);
		window.display();
	}


}



