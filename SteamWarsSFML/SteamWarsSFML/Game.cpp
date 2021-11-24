#include "pch.h"
#include "Game.h"

//privateFUNC

void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "SpaceWars works!", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(144);
	this->window->setVerticalSyncEnabled(false);
}

void Game::initPlayer()
{
	this->player = new Player();
}

//con/des
Game::Game()
{
	this->initWindow();
	this->initPlayer();
}


Game::~Game()
{
	delete this->window;
	delete this->player;
}

//functions 
void Game::run()
{
	while (this->window->isOpen()) {
		this->update();
		this->render();
	}

}

void Game::update()
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
}

void Game::render()
{
	this->window->clear();

	//drawings
	this->player->render(*this->window);

	this->window->display();
}
