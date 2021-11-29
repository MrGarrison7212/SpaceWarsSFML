#include "pch.h"
#include "Game.h"

//privateFUNC

void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "SpaceWars works!", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(144);
	this->window->setVerticalSyncEnabled(false);
}

void Game::initTextures()
{
	this->textures["BULLET"] = new sf::Texture();
	this->textures["BULLET"]->loadFromFile("Data/bullet.png");
}

void Game::initPlayer()
{
	this->player = new Player();

}

void Game::initEnemies()
{
	this->spawnTimerMax = 50.f;
	this->spawnTimer = this->spawnTimerMax;
}

//con/des
Game::Game()
{
	this->initWindow();
	this->initTextures();
	this->initPlayer();
	this->initEnemies();
}


Game::~Game()
{
	delete this->window;
	delete this->player;

	//remove textures, cause of leaks
	for (auto &i : this->textures) {
		delete i.second;
	}
	//deleting bullets
	for (auto *i : this->bullets) {
		delete i;
	}
	//delete all enemies
	for (auto *i : this->enemies) {
		delete i;
	}
}

//functions 
void Game::run()
{
	while (this->window->isOpen()) {
		this->update();
		this->render();
	}

}

void Game::updatePollEvents()
{
	sf::Event e;
	while (this->window->pollEvent(e)) {
		if (e.Event::type == sf::Event::Closed) {
			this->window->close();
		}
		if (e.Event::KeyPressed &&e.Event::key.code == sf::Keyboard::Escape) {
			this->window->close();
		}
	}
}

void Game::updateInputs()
{
	//move Player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
		this->player->move(-1.f, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		this->player->move(1.f, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
		this->player->move(0.f, -1.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
		this->player->move(0.f, 1.f);
	}
	//create bullet
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->player->canAttack()) {
		this->bullets.push_back(new Bullet(this->textures["BULLET"], this->player->getPos().x, this->player->getPos().y, 0.f, -1.f, 5.f));
	}
}

void Game::updateBullets()
{
	unsigned counter = 0;
	for (auto *bullet : this->bullets) {
		bullet->update();

		//bullet culling(top of screen)
		if (bullet->getBounds().top + bullet->getBounds().height < 0.f) {
			//delete bullet
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			--counter;
		}

		++counter;
	}
}

void Game::updateEnemies()
{
	this->spawnTimer += 0.5f;
	if (this->spawnTimer >= this->spawnTimerMax) {
		this->enemies.push_back(new Enemy(rand() % 200, rand() % 200));
		this->spawnTimer = 0.f;
	}
	for (auto *enemy : this->enemies) {
		enemy->update();
	}
}

void Game::update()
{
	this->updatePollEvents();
	this->updateInputs();
	this->player->update();
	this->updateBullets();
	this->updateEnemies();
}

void Game::render()
{
	this->window->clear();

	//drawings
	this->player->render(*this->window);

	for (auto *bullet : this->bullets) {
		bullet->render(this->window);
	}

	for (auto *enemy : this->enemies) {
		enemy->render(this->window);
	}

	this->window->display();
}
