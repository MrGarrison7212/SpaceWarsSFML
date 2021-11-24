#pragma once
#include "Player.h"
#include <map>

class Game
{
private:
	sf::RenderWindow* window;

	//resource
	std::map<std::string,sf::Texture> textures;

	//Player
	Player* player;
	//private functions

	void initWindow();
	void initTexture();

	void initPlayer();

public:
	Game();
	virtual ~Game();

	//functions

	void run();

	void updatePollEvents();
	void updateInputs();
	void update();
	void render();

};

