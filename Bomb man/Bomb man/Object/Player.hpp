#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.hpp"
#include "Bomb.hpp"
#include "Collider.hpp"

class Player
{
public:
    //Constructor / Destructor
    Player(sf::Texture* texture,sf::Texture* bombTexture, sf::Vector2u imageCount, float switchTime, float speed, sf::Keyboard::Key key[5], int whichPlayer);
    ~Player();
    
    //Functions
    void Update(float deltaTime);
    void deathAnime(float deltaTime,sf::RenderWindow *window);
    void Draw(sf::RenderWindow *window);
    int chooseBomb();
    void BackToLive();
    //setter
    void SetBomb();
    void setAvailable(int index) { ifSetBomb[index] = false; };
    void setUnavailable(int index) { ifSetBomb[index] = true; };
    void setDeath(){ ifAlive = false;lives --; animation.reset(); }
   
    //getter
    sf::Vector2f getLoc() { return body.getPosition(); }
    bool checkAlive() { return ifAlive; }
    int getStrongness() { return strongness; }
    bool getIfAnimeDone() { return ifAnimeDone; }
    Collider GetCollider() { return Collider(body); }
    int getQuota() { return quota; }
    int GetLives(){return lives;}
    
    void speedUp() { speed += 100.0f; } ;
    void quotaUp();
    sf::Texture playerBombTexture;
    void strongnessUp() {strongness += 1; } ;
   
public:
    int whichPlayer;
    int numOfBombDroped;
    int lastBombset;
    Bomb *vbomb[15];
    int lives;
    
private:
    
    sf::Keyboard::Key Up;
    sf::Keyboard::Key Down;
    sf::Keyboard::Key Left;
    sf::Keyboard::Key Right;
    sf::Keyboard::Key bombKey;
    sf::Texture* texture;
    sf::RectangleShape body;
    Animation animation;
    unsigned int row;
    float speed;
    int quota;
    bool faceRight;
    int strongness;
    bool ifSetBomb[15] = {0};
    bool ifAlive;
    bool ifAnimeDone = false;
   

};

