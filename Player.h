#ifndef PLAYER_H
#define PLAYER_H

#include <Bullet.h>

class Player
{
private:
    sf::Texture *texture;
    sf::Sprite sprite;

    sf::Vector2f Velocity;
    sf::Vector2f Direction;
    float maxVelocity = 10.f;

    int LVL;
    int Exp;
    int ExpNext;
    int HP;
    int HPmax;
    int DMG;
    int DMGMax;
    int Points;

    int Armor;
    int cooling;


    float HitTime;
    float HitTimeMax;

public:
    Player(sf::Texture *texture, float pos_x, float pos_y);
    virtual ~Player();

    inline const sf::FloatRect getGlobalBounds()const{return this->sprite.getGlobalBounds();}
    inline const sf::Vector2f getPosition()const{return this->sprite.getPosition();}
    inline const std::string getHpString() const{return std::to_string(this->HP)+"/"+ std::to_string(this->HPmax);}
    inline const float& getVelocity()const {return this->maxVelocity;}
    inline const int& getHP()const {return this->HP;}
    inline const int& getHPmax()const {return this->HPmax;}
    inline const int& getLVL()const {return this->LVL;}
    inline const int& getExp()const {return this->Exp;}
    inline const int& getExpNext()const {return this->ExpNext;}
    inline void gainExp(int Exp){this->Exp += Exp; this->UpdateLvL();};
    inline const int& getPoints()const{return this->Points;}
    inline const int& getCooling()const{return this->cooling;}


    int getDmg();
    bool dead();
    bool ColorChange(){return this->HitTime < this->HitTimeMax;};
    void getHit(int DMG);
    void PointsUp();
    void UpdateLvL();
    void DmgColor();
    void erase(){this->sprite.setScale(0,0);}
    void Movement();
    void WindowBounds(sf::RenderTarget &target);
    void Update(sf::RenderTarget &target);
    void Draw(sf::RenderTarget &target);

};

#endif // PLAYER_H
