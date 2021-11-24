#include "pch.h"
#include "Player.h"


void Player::initTexture()
{
	//load texture from file
}

void Player::initSprite()
{
	//Set the texture to te sprite
	this->sprite.setTexture(this->texture);
}

Player::Player()
{
	this->initTexture();
	this->initSprite();
}


Player::~Player()
{
}


//functions
void Player::update()
{

}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
