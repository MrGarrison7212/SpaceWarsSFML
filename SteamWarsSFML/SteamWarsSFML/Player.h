#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Player
{
private:
	sf::Sprite sprite;
	sf::Texture texture;

	//private functions
	void initTexture();
	void initSprite();

public:
	Player();
	virtual ~Player();


	//functions
	void update();
	void render(sf::RenderTarget& target);
};

