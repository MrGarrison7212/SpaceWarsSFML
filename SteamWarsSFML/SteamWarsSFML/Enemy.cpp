#include "pch.h"
#include "Enemy.h"


void Enemy::initShapes()
{
	this->shape.setRadius(rand() % 20 + 20);
	this->shape.setPointCount(rand() % 20 + 3);
}

void Enemy::initVariables()
{
	this->type = 0;
	this->hp = 0;
	this->hpMax = 10;
	this->damage = 1;
	this->points = 5  ;
}

//functions

void Enemy::update()
{
}

void Enemy::render(sf::RenderTarget * target)
{
	target->draw(this->shape);
}

Enemy::Enemy(float pos_x, float pos_y )
{
	this->initShapes();
	this->initVariables();
	this->shape.setPosition(pos_x, pos_y);

}


Enemy::~Enemy()
{
}
