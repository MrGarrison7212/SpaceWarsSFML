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
	//private functions
	Enemy* enemy;

	void initWindow();
	void initTextures();

	void initPlayer();

public:
	Game();
	virtual ~Game();

	//functions

	void run();

	void updatePollEvents();
	void updateInputs();
	void updateBullets();
	void update();
	void render();

};

