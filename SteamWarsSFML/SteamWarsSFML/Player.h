#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

class Player
{
private:
	sf::Sprite sprite;
	sf::Texture texture;

	float movementSpeed;
	//private functions
	void initTexture();
	void initSprite();

public:
	Player();
	virtual ~Player();

	
	//functions
	void move(const float dirX, const float dirY);

	void update();
	void render(sf::RenderTarget& target);
};

