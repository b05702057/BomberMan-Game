#pragma once
#include <SFML/Graphics.hpp>

class Collider
{
public:
    //Constructor / Destructor
    Collider(sf::RectangleShape& body);
    ~Collider();
    
    //Functions
    void Move(float dx, float dy) { body.move(dx,dy); }
    bool checkDestroyed(Collider& other,int strongness, int rangeOfUp, int rangeOfDown, int rangeOfRight, int rangeOfLeft);
    bool checkCollision(Collider& other, float push, bool ifPush);
    bool checkCollision_Wall(Collider& other, float push);
    sf::Vector2f GetPosition() { return body.getPosition(); }
    sf::Vector2f GetHalfSize() { return body.getSize() / 2.0f; }
    
    
private:
    sf::RectangleShape& body;
    
    
    
    
    
    
};
