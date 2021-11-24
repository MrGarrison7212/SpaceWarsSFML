#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Bullet
{

private:
	sf::Sprite shape;

	sf::Vector2f direction;
	float movementSpeed;

public:
	Bullet();
	Bullet(sf::Texture& texture, float dir_X, float dir_Y, float movement_speed);
	virtual ~Bullet();

	void update();
	void render(sf::RenderTarget* target);
};

