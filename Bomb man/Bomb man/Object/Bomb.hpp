#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.hpp"
#include "Collider.hpp"
#include "Wall.hpp"
#include <iostream>
#include <SFML/Audio.hpp>


class Bomb
{
public:
    //Constructor / Destructor
    Bomb();
    Bomb(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
    ~Bomb();
    
    
    //Functions
    void Update(float deltaTime,sf::RenderWindow &window, int strongness, Wall* breakableWalls[], Wall* unbreakableWalls[], const int breakableWallsCnt, const int unbreakableWallsCnt);
    
    void Draw(sf::RenderWindow& window);
    void Draw(sf::RenderWindow &window, sf::RectangleShape up, sf::RectangleShape down, sf::RectangleShape right, sf::RectangleShape left);
    
    void DrawUp(sf::RenderWindow& window, sf::RectangleShape up);
    void DrawDown(sf::RenderWindow& window, sf::RectangleShape down);
    void DrawRight(sf::RenderWindow& window, sf::RectangleShape right);
    void DrawLeft(sf::RenderWindow& window, sf::RectangleShape left);
    
    //setter
    void setup(sf::Vector2f currentloc);
    void reset();
    //getter
    bool getDuringExplosion() { return ifExplode&&Bombing; }
    bool getIfExploded() { return Exploded; }
    
    Collider GetCollider(){ return Collider(body); }
    

    void ExplodeUp(float deltaTime, sf::RenderWindow& window, int strongness, Wall* breakableWalls[], Wall* unbreakableWalls[], int breakableWallsCnt, int unbreakableWallsCnt);
    void ExplodeDown(float deltaTime, sf::RenderWindow& window, int strongness, Wall* breakableWalls[], Wall* unbreakableWalls[], int breakableWallsCnt, int unbreakableWallsCnt);
    void ExplodeRight(float deltaTime, sf::RenderWindow& window, int strongness, Wall* breakableWalls[], Wall* unbreakableWalls[], int breakableWallsCnt, int unbreakableWallsCnt);
    void ExplodeLeft(float deltaTime, sf::RenderWindow& window, int strongness, Wall* breakableWalls[], Wall* unbreakableWalls[], int breakableWallsCnt, int unbreakableWallsCnt);
    
private:
    void Explode(float deltaTime, sf::RenderWindow& window, int strongness);
    
public:
    bool ifSet = false;
    bool ifPlayerleft = false;
    
    int rangeOfUp = 0;
    int rangeOfDown = 0;
    int rangeOfLeft = 0;
    int rangeOfRight = 0;

private:
    bool ifExplode;
    sf::RectangleShape body;
    Animation animation;
    unsigned int row;
    bool Exploded;
    
    bool Bombing = false;
    sf::SoundBuffer explosionBuffer;
    sf::Sound explosionSound;
    
    bool exitUp = false;
    bool exitDown = false;
    bool exitRight = false;
    bool exitLeft = false;
    bool unBreakExitUp = false;
    bool unBreakExitDown = false;
    bool unBreakExitRight = false;
    bool unBreakExitLeft = false;
    
    
    
};
