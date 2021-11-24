#include "pch.h"
#include "Player.h"


void Player::initTexture()
{
	//load texture from file
	if (!this->texture.loadFromFile("Data/ship.png")) {
		std::cout << "ERROR::PLAYER::INITTEXTURE::Error in loading.";
	}
}

void Player::initSprite()
{
	//Set the texture to te sprite
	this->sprite.setTexture(this->texture);
	//resize the sprite
	this->sprite.scale(0.2f, 0.2f);
}

Player::Player()
{
	this->movementSpeed = 5.f;

	this->initTexture();
	this->initSprite();
}


Player::~Player()
{
}


void Player::move(const float dirX, const float dirY)
{
	this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}

//functions
void Player::update()
{

}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
