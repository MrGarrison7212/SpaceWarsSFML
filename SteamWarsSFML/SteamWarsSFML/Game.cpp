#include "pch.h"
#include "Game.h"

//privateFUNC

void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "SpaceWars works!", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(144);
	this->window->setVerticalSyncEnabled(false);
}

//con/des
Game::Game()
{
	this->initWindow();
}


Game::~Game()
{
	delete this->window;
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
}

void Game::render()
{
	this->window->clear();
	this->window->display();
}
