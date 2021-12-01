#include "pch.h"
#include "Player.h"


void Player::initVariables()
{
	this->movementSpeed = 3.f;

	this->attackCooldownMax = 10.f;
	this->attackCooldown = this->attackCooldownMax;
	
	this->hpMax = 10;
	this->hp = this->hpMax;

}

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
	this->initVariables();
	this->initTexture();
	this->initSprite();
}


Player::~Player()
{
}

const sf::Vector2f & Player::getPos() const
{
	return this->sprite.getPosition();
}

const sf::FloatRect Player::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

const int & Player::getHp() const
{
	return this->hp;
}

const int & Player::getHpMax() const
{
	return this->hpMax;
}

void Player::setPosition(const sf::Vector2f pos)
{
	this->sprite.setPosition(pos);
}

void Player::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}


void Player::move(const float dirX, const float dirY)
{
	this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}

const bool Player::canAttack()
{
	if (this->attackCooldown >= this->attackCooldownMax) {
		this->attackCooldown = 0.f;
		return true;
	}
	return false;
}

void Player::updateAttack()
{
	if (this->attackCooldown < this->attackCooldownMax) {
		this->attackCooldown += 0.5f;
	}
}

//functions
void Player::update()
{
	this->updateAttack();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
