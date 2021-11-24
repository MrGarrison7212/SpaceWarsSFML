#pragma once
#include "Player.h"

class Game
{
private:
	sf::RenderWindow* window;

	//private functions

	void initWindow();

public:
	Game();
	virtual ~Game();

	//functions

	void run();

	void update();
	void render();

};

