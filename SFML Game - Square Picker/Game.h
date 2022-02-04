#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

using namespace sf;
using namespace std;

/*
	Class that act as a game engine.
	Wrapper class.
*/


class Game
{
private:
	//Variables
	//Window:
	RenderWindow* window;
	VideoMode videoMode;
	Event ev;

	//Game Logic
	bool endGame;
	unsigned points;
	int health;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	bool mouseHeld;

	//Game Objects
	RectangleShape enemy;
	vector <RectangleShape> enemies;

	//Game Resourse
	Font font;

	//Text
	Text uiText;

	//Window Mouse Position
	Vector2i mousePositionWindow;
	//Vector2i mousePositionFullScreen;
	Vector2f mousePositionFullinFloat;

	//Privet Functions:
	void initializeVariables();
	void initializeWindow();
	void initializeFont();
	void initializeText();
	void initializeEnemy();

public:
	//Constructors & Destructors
	Game();
	virtual ~Game();

	//Accessors
	const bool running() const;
	const bool getGameEnd() const;

	//Functions
	void spawnEnemy();

	void updatePollEvents();
	void updateMousePositions();
	void updateText();
	void updateEnemies();
	void update();

	void renderText();
	void renderEnemies();
	void render();
};

