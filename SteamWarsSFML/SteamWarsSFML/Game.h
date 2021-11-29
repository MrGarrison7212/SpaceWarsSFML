#pragma once
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include <map>

class Game
{
private:
	sf::RenderWindow* window;

	//resource
	std::map<std::string,sf::Texture*> textures;
	std::vector<Bullet*> bullets;

	//Player
	Player* player;
	//Enemies
	float spawnTimer;
	float spawnTimerMax;
	std::vector<Enemy*> enemies;

	//private functions

	void initWindow();
	void initTextures();

	void initPlayer();
	void initEnemies();

public:
	Game();
	virtual ~Game();

	//functions

	void run();

	void updatePollEvents();
	void updateInputs();
	void updateBullets();
	void updateEnemiesAndCombat();
	void update();
	void render();

};

