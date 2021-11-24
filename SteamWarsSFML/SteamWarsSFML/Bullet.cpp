#include "pch.h"
#include "Bullet.h"


Bullet::Bullet()
{

}


Bullet::Bullet(sf::Texture & texture, float dir_X, float dir_Y, float movement_speed)
{
	this->shape.setTexture(texture);
	this->direction.x = dir_X;
	this->direction.y = dir_Y;
	this->movementSpeed = movement_speed;
}

Bullet::~Bullet()
{

}

void Bullet::update()
{
	//movement
	this->shape.move(this->movementSpeed * this->direction);
}

void Bullet::render(sf::RenderTarget * target)
{
	target->draw(this->shape);
}
