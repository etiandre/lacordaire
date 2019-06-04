// Travelaws.cpp : Ce fichier contient la fonction 'main'
//

#pragma region includes
#include "Travelaws.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <tmxlite/Map.hpp>
#include "CollisionRule.h"
#include "DEFINITIONS.h"
#include "GravityRule.hpp"
#include "InputManager.hpp"
#include "Player.h"
#include "SFMLOrthogonalLayer.hpp"
#include "VisionRule.hpp"
#include "WindRule.hpp"
#include "imgui-SFML.h"
#include "imgui.h"
#pragma endregion includes

Game::Game(int width, int height, std::string title) {
	gameData.player = Player();
	gameData.map = tmx::Map();
	gameData.gameState = InGame;
	window.create(sf::VideoMode(width, height),
		"Travelaws 0.0.0.0.1 alpha dx+ TEST RELEASE");
	window.setFramerateLimit(60);
	ImGui::SFML::Init(window);
	loadLevel(1);
	mainLoop();
	ImGui::SFML::Shutdown();
}

void Game::loadLevel(int levelID) {
	if (!gameData.map.load("assets/levels/level" + std::to_string(levelID) +
		".tmx")) {
		std::cout << "cannot load level !" << std::endl;
		exit(1);
	}
}

void Game::mainLoop() {

	sf::Event event;
	InputManager inputManager;

	MapLayer backgroundLayer(gameData.map, 0);
	MapLayer platformsLayer(gameData.map, 2);

  rules.push_back(std::make_unique<GravityRule>());
  //rules.push_back(std::make_unique<WindRule>());
  //rules.push_back(std::make_unique<VisionRule>());
  rules.push_back(std::make_unique<CollisionRule>(
      platformsLayer));  //!\\ Collision has to be last !

	sf::Clock clock;

	while (window.isOpen()) {
		// EVENTS
		while (window.pollEvent(event)) {
			ImGui::SFML::ProcessEvent(event);
			if (event.type == sf::Event::EventType::Closed) window.close();
		}

		ImGui::SFML::Update(window, clock.restart());

		switch (gameData.gameState) {
		case InGame:
		{
			// INPUTS
			inputManager.manageInputs(gameData.player);

			// PHYSICS UPDATE
			for (auto& rule : rules) {
				if (rule.get()->active) rule.get()->update(gameData);
			}

			// POSITION UPDATE
			gameData.player.update();

			// CHECK STATE
			check_state();

			// RULES UPDATE
			for (auto& rule : rules) {
				if (rule.get()->active) rule.get()->update(gameData);
			}

			// VIEW
			view.reset(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
			sf::Vector2f position(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
			position.x =
				gameData.player.getPosition().x + BLOCK_SIZE / 2 - SCREEN_WIDTH / 2;
			if (position.x < 0) position.x = 0;
			if (position.y < 0) position.y = 0;

			view.reset(sf::FloatRect(position.x, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
			window.setView(view);

			// GUI
			ImGui::Begin("Rules");
			for (auto& rule : rules) {
				ImGui::Checkbox(rule.get()->getName(), &rule.get()->active);
			}
			ImGui::End();  // Rules

			ImGui::Begin("Debug");
			ImGui::Text("position : x=%d y=%d", gameData.player.getPosition().x, gameData.player.getPosition().y);
			ImGui::Text("vitesse : x=%0.3f y=%0.3f", gameData.player.velocity.x, gameData.player.velocity.y);
			ImGui::End();  // Debug

			// DRAW
			gameData.player.updateAnimation();
			window.clear();
			window.draw(backgroundLayer);
			window.draw(platformsLayer);
			gameData.player.draw(window);
			// RULES DRAW
			for (auto& rule : rules) {
				if (rule.get()->active)
					rule.get()->draw(window);
			}
		}
		break;
		case Victory:
			victory();
			break;
		case GameOver:
			gameOver();
			break;
		}


		ImGui::SFML::Render(window);
		window.display();
	}
}


void Game::check_state()
{
	// Condition sur x seulement pour le moment, � voir si on change
	if (gameData.player.sprite.getPosition().x >= 6400) {
		gameData.player.sprite.setPosition(6432, gameData.player.sprite.getPosition().y);
		gameData.gameState = Victory;
	}
	else if (gameData.player.sprite.getPosition().y >= 1016) {
		//Kill player
		gameData.gameState = GameOver;
	}

}

void Game::victory()
{
	sf::Sprite victorySprite;
	sf::Texture victoryTexture;
	if (!victoryTexture.loadFromFile("assets/textures/victory.png")) {
		std::cout << "erreur chargement texture victory !" << std::endl;
		exit(1);
	}
	std::cout << "GG, Score = " << std::endl;
	victorySprite.setTexture(victoryTexture);


	view.reset(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
	window.setView(view);
	window.clear();
	window.draw(victorySprite);


}

void Game::gameOver()
{
	sf::Sprite gameOverSprite;
	sf::Texture gameOverTexture;
	if (!gameOverTexture.loadFromFile("assets/textures/gameover.jpg")) {
		std::cout << "erreur chargement texture gameover !" << std::endl;
		exit(1);
	}
	std::cout << "You lose, score = -42 " << std::endl;
	gameOverSprite.setTexture(gameOverTexture);


	view.reset(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
	window.setView(view);
	window.clear();
	window.draw(gameOverSprite);
}




int main(int argc, char** argv) {
	Game(SCREEN_WIDTH, SCREEN_HEIGHT, "Game alpha");
	return EXIT_SUCCESS;
}