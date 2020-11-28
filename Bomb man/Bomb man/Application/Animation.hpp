#pragma once
#include <SFML/Graphics.hpp>

class Animation
{
public:
    //Constructor / Destructor
    Animation();
    Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchtime);
    ~Animation();
    
    //Functions
    void UpdateBomb(int row, float deltaTime, bool &ifExploded);
    void UpdateExplosion(int column,float deltaTime, bool& Exploded);
    bool UpdatePlayer(int row, float deltaTime);
    void reset();
    
public:
    sf::IntRect uvRect;
    
private:
    sf::Vector2u imageCount;
    sf::Vector2u currentImage;
    
    
    float totalTime;
    float switchTime;
    
    
    
    
};
