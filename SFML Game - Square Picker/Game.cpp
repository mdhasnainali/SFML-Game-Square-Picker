#include "Game.h"

//Privet Functions
void Game::initializeVariables()
{
	this->window = nullptr;

	//Game Logic
	this->endGame = false;
	this->points = 0;
	this->health = 10;
	this->enemySpawnTimerMax = 10.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 12;
	this->mouseHeld = false;
}

void Game::initializeWindow()
{
	this->videoMode.width = 1000;
	this->videoMode.height = 600;
	this->window = new RenderWindow(videoMode, "Game 1");
	this->window->setFramerateLimit(60);
}

void Game::initializeEnemy()
{
	//this->enemy.setPosition(Vector2f(400, 100));
	this->enemy.setSize(Vector2f(200.f, 200.f));
	this->enemy.setScale(Vector2f(.50f, .50f));
	this->enemy.setFillColor(Color::Red);
	//this->enemy.setOutlineThickness(3.0f);
	//this->enemy.setOutlineColor(Color::Green);
}

void Game::initializeFont()
{
	this->font.loadFromFile("Font/Hack-Regular.ttf");
}

void Game::initializeText()
{
	this->uiText.setFont(this->font);
	this->uiText.setCharacterSize(24);
	this->uiText.setFillColor(Color::White);
	this->uiText.setString("NONE");
}

//Constructors & Destructors
Game::Game()
{
	this->initializeVariables();
	this->initializeWindow();
	this->initializeFont();
	this->initializeText();
	this->initializeEnemy();
}

Game::~Game()
{
	delete this->window;
}


//Accessors
const bool Game::running() const
{
	return this->window->isOpen();
}

const bool Game::getGameEnd() const
{
	return endGame;
}


// Functions:

void Game::spawnEnemy()
{
	/*
		@return void

		Spawn enemies and sets their colors, types and positions
		- Sets random positions
		- Sets random color
		- Add enemy to the vector
	*/

	this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
		//static_cast<float>(rand() % static_cast<int>(this->window->getSize().y - this->enemy.getSize().y))
		0.f
	);

	//Randomize enemy type
	int type = rand() % 5;

	switch (type)
	{
	case 0:
		this->enemy.setSize(Vector2f(30.f, 30.f));
		this->enemy.setFillColor(Color::Magenta);
		break;
	case 1:
		this->enemy.setSize(Vector2f(50.f, 50.f));
		this->enemy.setFillColor(Color::Blue);
		break;
	case 2:
		this->enemy.setSize(Vector2f(70.f, 70.f));
		this->enemy.setFillColor(Color::Cyan);
		break;
	case 3:
		this->enemy.setSize(Vector2f(100.f, 100.f));
		this->enemy.setFillColor(Color::Red);
		break;
	case 4:
		this->enemy.setSize(Vector2f(150.f, 150.f));
		this->enemy.setFillColor(Color::Yellow);
		break;

	default:
		this->enemy.setSize(Vector2f(170.f, 170.f));
		this->enemy.setFillColor(Color::Green);
		break;
	}


	//Spwan the enemy
	this->enemies.push_back(this->enemy);

}

void Game::updatePollEvents()
{
	//Update Events
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case Event::Closed:
			window->close();
			break;
		}
	}
}

void Game::updateMousePositions()
{
	/*
		@return void

		Update the Mouse Positions:
		- Mouse positions relative to window
		- Mouse Position relative to Full Screen
	*/

	this->mousePositionWindow = Mouse::getPosition(*this->window);
	//this->mousePositionFullScreen = Mouse::getPosition();
	this->mousePositionFullinFloat = window->mapPixelToCoords(this->mousePositionWindow);

	cout << mousePositionFullinFloat.x << endl;
}

void Game::updateText()
{
	stringstream ss;
	ss << "Points: " << this->points << " Health: " << this->health << endl;
	this->uiText.setString(ss.str());
}

void Game::updateEnemies()
{
	/*
		@return void

		- Updates the enemy spawn timer and spawn enemies
		  when the total amount of enemies is smaller than the maximum.
		- Moves enemies downwards
		- Removes the enemies at the edge of the screen. //ToDo

	*/

	//Updating the timer for enemy spawning
	if (this->enemies.size() < this->maxEnemies)
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			//Spwan the enemy and reset the timer
			this->spawnEnemy();
			this->enemySpawnTimer = 0.f;
		}
		else
			this->enemySpawnTimer += 1.f;
	}

	//Moving and updating enemies
	for (int i = 0; i < this->enemies.size(); i++)
	{

		this->enemies[i].move(0.f, 5.f);

		//If the enemy is past the bottom of the screen
		if (this->enemies[i].getPosition().y > this->window->getSize().y)
		{
			this->enemies.erase(this->enemies.begin() + i);
			this->health -= 1;
		}
	}


	//Check if clicked upon
	if (Mouse::isButtonPressed(Mouse::Left))
	{
		if (this->mouseHeld == false)
		{
			this->mouseHeld = true;
			bool deleted = false;

			for (size_t i = 0; i < this->enemies.size() && deleted == false; i++)
			{
				if (this->enemies[i].getGlobalBounds().contains(this->mousePositionFullinFloat))
				{
					//Delete the enemy
					deleted = true;
					this->enemies.erase(this->enemies.begin() + i);

					//Gain Points:
					this->points += 1;
				}
			}
		}
		else
		{
			this->mouseHeld = false;
		}
	}

}

void Game::update()
{
	this->updatePollEvents();

	if (this->endGame == false)
	{
		//Update Mouse Position
		this->updateMousePositions();

		this->updateText();

		this->updateEnemies();
	}

	//End Game Condition
	if (this->health <= 0)
	{
		endGame = true;
	}
}

void Game::renderText()
{
	this->window->draw(uiText);
}

void Game::renderEnemies()
{
	for (auto& e : this->enemies)
	{
		this->window->draw(e);
	}
}

void Game::render()
{
	/*
		@return void

		Render the game objects:
		- clear old frame
		- render new objects
		- display frame in window
	*/

	this->window->clear();

	//Draw game objects
	this->renderText();

	this->renderEnemies();

	this->window->display();
}
