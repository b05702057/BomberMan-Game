#include <cmath>
#include <iostream>
#include "Collider.hpp"
using namespace std;

//Constructor/ Destructor
Collider::Collider(sf::RectangleShape& body):
body(body)
{
    
}
Collider::~Collider()
{
    
}

//Functions

bool Collider::checkDestroyed(Collider& other,int strongness, int rangeOfUp, int rangeOfDown, int rangeOfRight, int rangeOfLeft)
{
    sf::Vector2f otherPosition = other.GetPosition();
    sf::Vector2f otherHalfSize = other.GetHalfSize();
    sf::Vector2f thisPosition = GetPosition();
    sf::Vector2f thisHalfSize = GetHalfSize();
    
    float deltaX = otherPosition.x - thisPosition.x;
    float deltaY = otherPosition.y - thisPosition.y;
    
    float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
    float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);
    if (rangeOfUp == 0)
        rangeOfUp = strongness;
    if (rangeOfDown == 0)
        rangeOfDown = strongness;
    if (rangeOfRight == 0)
        rangeOfRight = strongness;
    if (rangeOfLeft == 0)
        rangeOfLeft = strongness;
    
    
    if(deltaY <= 0 &&intersectX < 0.0f && abs(deltaY) < (thisHalfSize.y- 0.1f) * (2 * (rangeOfUp + 1)))
    {
        std::cout << "dead form up: " << rangeOfUp << "\n";
        return true;
    }
    if(deltaX <= 0 && intersectY < 0.0f && abs(deltaX) < (thisHalfSize.x- 0.1f) * (2 * (rangeOfLeft + 1)))
    {
        std::cout << "dead form left: " << rangeOfLeft << "\n";
        return true;
    }
    if(deltaY > 0 &&intersectX < 0.0f && abs(deltaY) < (thisHalfSize.y - 0.1f) * (2 * (rangeOfDown + 1)))
    {
        std::cout << "dead form down: " << rangeOfDown << "\n";
        return true;
    }
    if(deltaX > 0 && intersectY < 0.0f && abs(deltaX) < (thisHalfSize.x- 0.1f) * (2 * (rangeOfRight + 1)))
    {
        std::cout << "dead form right: " << rangeOfRight << "\n";
        return true;
    }
    
    
    return false;

}

bool Collider::checkCollision(Collider& other, float push, bool ifPush)
{
    sf::Vector2f otherPosition = other.GetPosition();
    sf::Vector2f otherHalfSize = other.GetHalfSize();
    sf::Vector2f thisPosition = GetPosition();
    sf::Vector2f thisHalfSize = GetHalfSize();
    
    float deltaX = otherPosition.x - thisPosition.x;
    float deltaY = otherPosition.y - thisPosition.y;
    
    float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
    float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);
    
    if(intersectX < 0.0f && intersectY < 0.0f )
    {
        push  = min(max(0.0f,push), 1.0f);
        
        if(ifPush)
        {
            if(abs(intersectX) < abs(intersectY))
            {
                if(deltaX > 0.0f)
                {
                    Move(intersectX * (1.0f - push), 0.0f);
                    other.Move(-intersectX * push, 0.0f);
                }
                else
                {
                    Move(-intersectX * (1.0f - push), 0.0f);
                    other.Move(intersectX * push, 0.0f);
                }
            }
            else
            {
                if(deltaY > 0.0f)
                {
                    Move(0.0f, intersectY * (1.0f - push));
                    other.Move(0.0f, -intersectY * push);
                }
                else
                {
                    Move(0.0f, -intersectY * (1.0f - push));
                    other.Move(0.0f, intersectY * push);
                }
                
            }
        }
        return true;
    }
    return false;
}


bool Collider::checkCollision_Wall(Collider& other, float push)
{
    sf::Vector2f otherPosition = other.GetPosition();
    sf::Vector2f otherHalfSize = other.GetHalfSize();
    sf::Vector2f thisPosition = GetPosition();
    sf::Vector2f thisHalfSize = GetHalfSize();
    
    float deltaX = otherPosition.x - thisPosition.x;
    float deltaY = otherPosition.y - thisPosition.y;
    
    float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
    float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

    if(intersectX < 0.0f && intersectY < 0.0f)
    {
        return true;
    }
    
    return false;
}
