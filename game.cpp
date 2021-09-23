#include "Game.h"

Game::Game(sf::RenderWindow *window)
{
    this->window = window;
    this->window->setFramerateLimit(60);


    this->BackgroundT.loadFromFile("Textures/background.jpg");
    this->shipT.loadFromFile("Textures/ship.png");
    this->bulletT.loadFromFile("Textures/fire_blue.png");
    this->enemyT.loadFromFile("Textures/enemy.png");
    this->enemy1T.loadFromFile("Textures/rock1.png");
    this->font.loadFromFile("Textures/Dosis-Light.ttf");
    this->BackgroundS.setTexture(this->BackgroundT);

    this->player = new Player(&this->shipT ,this->window->getSize().x, this->window->getSize().y);

    this->shootTimeMax = 20;
    this->spawnTimeMax = 60;
    InitUi();
}

Game::~Game()
{
    delete player;
    for (auto *i : this->bullets)
    {
        delete i;
    }
    for (auto *i : this->enemies)
    {
        delete i;
    }
}

void Game::initVariables()
{
    this->shootTimeMax = 20;
    this->spawnTimeMax = 60;
}

void Game::InitUi()
{
    sf::Text PlayerText;
    this->PlayerText.setFont(font);
    this->PlayerText.setCharacterSize(14);
    this->PlayerText.setFillColor(sf::Color::White);

    sf::Text PlayerStaticText;
    this->PlayerStaticText.setFont(font);
    this->PlayerStaticText.setCharacterSize(40);
    this->PlayerStaticText.setFillColor(sf::Color::White);


    this->enemyText.setFont(this->font);
    this->enemyText.setCharacterSize(14);
    this->enemyText.setFillColor(sf::Color::White);

    this->GameOverText.setFont(this->font);
    this->GameOverText.setCharacterSize(100);
    this->GameOverText.setFillColor(sf::Color::Red);
    this->GameOverText.setString("GAME OVER!");
    this->GameOverText.setOrigin(GameOverText.getGlobalBounds().width/2,GameOverText.getGlobalBounds().height/2);
    this->GameOverText.setPosition(window->getSize().x/2,window->getSize().y/2);

    this->ExpBar.setSize(sf::Vector2f(20.f,90.f));
    this->ExpBar.setFillColor(sf::Color(0.f, 255.f, 77.f, 98.f));

    this->HpBar.setSize(sf::Vector2f(70.f,20.f));
    this->HpBar.setFillColor(sf::Color(255.f, 52.f, 35.f, 220.f));
}

void Game::CombatUpdate()
{   
    for (size_t j = 0; j < this->bullets.size();j++)
    {
        for(size_t i =0; i<this->enemies.size();i++)
        {
            if(this->bullets[j]->getGlobalBounds().intersects(this->enemies[i]->getGlobalBounds()))
            {
                this->bullets.erase(this->bullets.begin() + j);
                if(this->enemies[i]->getHP() > 0)
                {
                    this->enemies[i]->takeDMG(this->player->getDmg());
                }
                if(this->enemies[i]->getHP() <= 0)
                {
                    this->player->gainExp(this->enemies[i]->getHPmax()*5);
                    this->enemies.erase(this->enemies.begin()+i);
                    this->player->PointsUp();
                }
                return;
            }
        }
    }
}


void Game::Update()
{
    if(this->player->dead() == false) //GAME OVER
    {
        //Bullets
        if(this->shootTime  < this->shootTimeMax)
        {
            this->shootTime ++;
            this->shootTimeMax-=this->player->getCooling();
        }


        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && this->shootTime >= this->shootTimeMax )
        {
            this->bullets.push_back(new Bullet(&bulletT, this->player->getPosition().x, this->player->getPosition().y ));
            this->shootTime = 0;
        }

        for (size_t i = 0; i < this->bullets.size(); i++)
        {
            this->bullets[i]->Update();

            if (bullets[i]->getGlobalBounds().top  < 0.f)
            {
                this->bullets.erase(this->bullets.begin() + i);
                break;
            }

        }

        //Enemies
        if(this->spawnTime < this->spawnTimeMax)
        {
            this->spawnTime ++;
            //std::cout<<spawnTime<<" : "<<spawnTimeMax<<"\n";
        }
        if (this->spawnTime >= this->spawnTimeMax )
        {
            this->enemies.push_back( new Enemy(&this->enemyT,this->window->getSize(),sf::Vector2f(0.1f,0.1f),
                                               sf::Vector2f(0.f,0.4f),sf::Vector2f(0.1f,0.1f),
                                               rand()%2, rand()%3+1, 2, 1
                                               ));
            this->enemies.push_back( new Enemy(&this->enemy1T,this->window->getSize(),sf::Vector2f(1.f,1.f),
                                               sf::Vector2f(0.f,0.3f),sf::Vector2f(0.1f,0.1f),
                                               0, 1, 1, 1
                                               ));
            this->spawnTime = 0;
        }


        for(size_t i=0; i < this->enemies.size(); i++)
        {
            this->enemies[i]->Update(this->player->getPosition());

            if(this->player->getGlobalBounds().intersects(this->enemies[i]->getGlobalBounds())
                    && !this->player->ColorChange())
            {

                this->player->getHit(this->enemies[i]->getDMG());
                this->enemies.erase(this->enemies.begin() +i);
            }
            else if(enemies[i]->getGlobalBounds().top > this->window->getSize().y)
            {
                this->enemies.erase(this->enemies.begin() +i);
            }
        }


        this->initVariables();
        this->player->Update(*this->window);
        this->CombatUpdate();
        this->UIUpdate();
    }

    if(this->player->dead())//Game Over
    {
        this->player->erase();
        this->PlayerText.setScale(0,0);
        this->ExpBar.setScale(0,0);
        this->HpBar.setScale(0,0);
    }
}

void Game::UIUpdate()
{
    this->PlayerText.setPosition(this->player->getPosition().x - 20.f,this->player->getPosition().y);
    this->PlayerText.setString(std::string("Lvl:")+""+std::to_string(this->player->getLVL()));
    this->ExpBar.setPosition(this->player->getPosition().x + this->player->getGlobalBounds().width,
                             this->player->getPosition().y);
    this->HpBar.setPosition(this->player->getPosition().x,
                            this->player->getPosition().y +
                            this->player->getGlobalBounds().height);

    this->ExpBar.setScale(1.f,
                          static_cast<float>(this->player->getExp())/
                          static_cast<float>(this->player->getExpNext()));

    this->HpBar.setScale(static_cast<float>(this->player->getHP()/
                                            static_cast<float>(this->player->getHPmax())),
                         1.f);
    this->PlayerStaticText.setPosition(0,0);
    this->PlayerStaticText.setString(std::string("Score:")+" "+std::to_string(this->player->getPoints()));


}

void Game::UIDraw()
{
    this->window->draw(this->PlayerText);
    this->window->draw(this->PlayerStaticText);
    this->window->draw(this->ExpBar);
    this->window->draw(this->HpBar);

    for(size_t i= 0; i <this->enemies.size(); i++)
    {
        this->enemyText.setPosition(this->enemies[i]->getPosition());
        this->enemyText.setString(std::to_string(this->enemies[i]->getHP())+"/"+
                                  std::to_string(this->enemies[i]->getHPmax()));

        this->enemies[i]->Draw(*this->window);
        this->window->draw(this->enemyText);
    }


    if(this->player->dead() == true)
    {
        this->window->draw(this->GameOverText);
    }
}

void Game::Draw()
{
    this->window->clear();
    this->window->draw(this->BackgroundS);
    this->player->Draw(*this->window);
    for (auto *bullet : this->bullets)
    {
        bullet->Draw(*this->window);
    }

    for (auto *enemy : this->enemies)
    {
        enemy->Draw(*this->window);

    }
    this->UIDraw();
    this->window->display();
}
