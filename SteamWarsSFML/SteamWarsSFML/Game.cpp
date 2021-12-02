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

void Game::initGUI()
{
	//loadfonts
	if (!this->font.loadFromFile("Data/SpaceMission-rgyw9.otf")) {
		std::cout << "ERROR::GAME::Failed to load font" << "\n";
	};

	//init
	this->pointText.setPosition(615, 20.f);
	this->pointText.setFont(this->font);
	this->pointText.setCharacterSize(25);
	this->pointText.setFillColor(sf::Color::White);
	this->pointText.setString("test");

	//game over
	this->gameOver.setFont(this->font); 
	this->gameOver.setCharacterSize(60);
	this->gameOver.setFillColor(sf::Color::Yellow);
	this->gameOver.setString(" Game Over!");
	this->gameOver.setPosition(this->window->getSize().x / 2.f - this->gameOver.getGlobalBounds().width / 2.f,
							   this->window->getSize().y / 2.f - this->gameOver.getGlobalBounds().height / 2.f);

	//init player GUI
	this->playerHpBar.setSize(sf::Vector2f(300.f, 25.f));
	this->playerHpBar.setFillColor(sf::Color::Green);
	this->playerHpBar.setPosition(sf::Vector2f(20.f, 20.f));

	this->playerHpBarBack = this->playerHpBar;
	this->playerHpBarBack.setFillColor(sf::Color::Red);
}

void Game::initBackground()
{
	if (!this->worldBackground_tex.loadFromFile("Data/background1.jpg")) {
		std::cout << "ERROR::GAME::Failed to load background" << "\n";
	};
	this->worldBackground.setTexture(this->worldBackground_tex);
}

void Game::initSystems()
{
	this->points = 0;
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
	this->initGUI();
	this->initBackground();
	this->initSystems();
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
		this->updatePollEvents();

		if (this->player->getHp() > 0) {
			this->update();
		}
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
		this->bullets.push_back(new Bullet(this->textures["BULLET"], this->player->getPos().x + this->player->getBounds().width/2.f,
			this->player->getPos().y, 0.f, -1.f, 5.f));
	}
}

void Game::updateGUI()
{
	std::stringstream ss;
	ss << "  Points: " << this->points;
	this->pointText.setString(ss.str());

	//update Player GUI
	float hpPercent = static_cast<float>(this->player->getHp()) / this->player->getHpMax();
	this->playerHpBar.setSize(sf::Vector2f(300.f * hpPercent, this->playerHpBar.getSize().y));
}

void Game::updateBackground()
{

}

void Game::updateCollision()
{
	//out of bounds-left
	if (this->player->getBounds().left < 0.f) {
		this->player->setPosition(0.f, this->player->getBounds().top);
	}
	//out of bounds-right
	else if (this->player->getBounds().left + this->player->getBounds().width >= this->window->getSize().x) {
		this->player->setPosition(this->window->getSize().x - this->player->getBounds().width, this->player->getBounds().top);
	}
	//out of bounds-top
	if (this->player->getBounds().top < 0.f) {
		this->player->setPosition(this->player->getBounds().left, 0.f);
	}
	//out of bounds-down
	else if (this->player->getBounds().top + this->player->getBounds().height >= this->window->getSize().y) {
		this->player->setPosition(this->player->getBounds().left, this->window->getSize().y - this->player->getBounds().height);
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

void Game::updateEnemiesAndCombat()
{
	this->spawnTimer += 0.5f;
	if (this->spawnTimer >= this->spawnTimerMax) {
		this->enemies.push_back(new Enemy(rand() % this->window->getSize().x - 20.f, -100.f));
		this->spawnTimer = 0.f;
	}
	for (int i = 0; i < this->enemies.size(); i++) {
		bool enemy_removed = false;
		this->enemies[i]->update();
		//Remove enemy/bullet collision

		for (size_t k = 0; k < this->bullets.size() && !enemy_removed; k++){
			if (this->bullets[k]->getBounds().intersects(this->enemies[i]->getBounds())) {

				this->points += this->enemies[i]->getPoints();

				this->bullets.erase(this->bullets.begin() + k);
				this->enemies.erase(this->enemies.begin() + i);

				enemy_removed = true;
			}
		}
		//Remove enemy at the bottom of the screen
		if (!enemy_removed) {
			if (this->enemies[i]->getBounds().top > this->window->getSize().y) {
				this->enemies.erase(this->enemies.begin() + i);
				enemy_removed = true;
			}
			//player/enemy collision
			else if (this->enemies[i]->getBounds().intersects(this->player->getBounds())) {
				//manage hp lose
				this->player->loseHp(this->enemies[i]->getDamage());

				this->enemies.erase(this->enemies.begin() + i);
				enemy_removed = true;
			}
		}
	}
}

void Game::update()
{
	this->updateInputs();
	this->player->update();
	this->updateCollision();
	this->updateBullets();
	this->updateEnemiesAndCombat();
	this->updateGUI();
	this->updateBackground();
}

void Game::renderGUI()
{
	this->window->draw(this->pointText);
	this->window->draw(this->playerHpBarBack);
	this->window->draw(this->playerHpBar);
}

void Game::renderBackground()
{
	this->window->draw(this->worldBackground);
}

void Game::render()
{
	this->window->clear();
	//background stuff
	this->renderBackground();
	//drawings
	this->player->render(*this->window);

	for (auto *bullet : this->bullets) {
		bullet->render(this->window);
	}

	for (auto *enemy : this->enemies) {
		enemy->render(this->window);
	}

	this->renderGUI();

	//gameOverScreen
	if (this->player->getHp() <= 0) {
		this->window->draw(this->gameOver);
	}

	this->window->display();
}
