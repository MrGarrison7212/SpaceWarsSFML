#pragma once
#include <SFML/Graphics.hpp>


class Enemy
{
private:
	sf::CircleShape shape;
	int type;
	float speed;
	int hp;
	int hpMax;
	int damage;
	int points;

	void initShapes();
	void initVariables();


public:
	Enemy(float pos_x, float pos_y);
	virtual ~Enemy();

	//accessors
	const sf::FloatRect getBounds() const;

	//functions
	void update();
	void render(sf::RenderTarget* target);
};

