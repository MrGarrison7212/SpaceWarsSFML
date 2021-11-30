#include "pch.h"
#include "Enemy.h"


void Enemy::initVariables()
{
	this->pointCount = rand() % 8 + 3;
	this->type = 0;
	this->speed = static_cast<float>(this->pointCount/3);
	this->hpMax = static_cast<int>(this->pointCount);
	this->hp = this->hpMax;
	this->damage = this->pointCount;
	this->points = this->pointCount;
}

void Enemy::initShapes()
{
	this->shape.setRadius(this->pointCount * 3);
	this->shape.setPointCount(this->pointCount);
	this->shape.setFillColor(sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1, 255));
}
//functions

void Enemy::update()
{
	this->shape.move(0.f, this->speed);
}

void Enemy::render(sf::RenderTarget * target)
{
	target->draw(this->shape);
}

Enemy::Enemy(float pos_x, float pos_y )
{
	this->initVariables();
	this->initShapes();
	 
	this->shape.setPosition(pos_x, pos_y);

}


Enemy::~Enemy()
{
}

const sf::FloatRect Enemy::getBounds() const
{
	return this->shape.getGlobalBounds();
}

const int & Enemy::getPoints() const
{
	return this->points;
}