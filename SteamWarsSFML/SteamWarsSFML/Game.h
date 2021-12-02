#pragma once
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include <map>
#include <string>
#include <sstream>

class Game
{
private:
	sf::RenderWindow* window;

	//resource
	std::map<std::string,sf::Texture*> textures;
	std::vector<Bullet*> bullets;

	//GUI
	sf::Font font;
	sf::Text pointText;

	sf::Text gameOver;

	//World
	sf::Texture worldBackground_tex;
	sf::Sprite worldBackground;
	//Systems
	unsigned points;
	//Player
	Player* player;

	//PlayerGUI
	sf::RectangleShape playerHpBar;
	sf::RectangleShape playerHpBarBack;

	//Enemies
	float spawnTimer;
	float spawnTimerMax;
	std::vector<Enemy*> enemies;



	//private functions

	void initWindow();
	void initTextures();
	void initGUI();
	void initBackground();
	void initSystems();
	void initPlayer();
	void initEnemies();

public:
	Game();
	virtual ~Game();

	//functions

	void run();

	void updatePollEvents();
	void updateInputs();
	void updateGUI();
	void updateBackground();
	void updateCollision();
	void updateBullets();
	void updateEnemiesAndCombat(); 
	void update();
	void renderGUI();
	void renderBackground();
	void render();

};

