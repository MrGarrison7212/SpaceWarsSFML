#pragma once
#include "Player.h"

class Game
{
private:
	sf::RenderWindow* window;

	//Player
	Player* player;
	//private functions

	void initWindow();
	void initPlayer();

public:
	Game();
	virtual ~Game();

	//functions

	void run();

	void update();
	void render();

};

