//
//  Wall.hpp
//  Bomb man
//
//  Created by 涂譽寶 on 2020/1/3.
//  Copyright © 2020 張文毓. All rights reserved.
//

#ifndef Wall_hpp
#define Wall_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "Collider.hpp"

class Wall
{
public:
    Wall();
    Wall(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position, bool isBreakable, bool isBroken);
    ~Wall();
    void Draw(sf::RenderWindow* window);
    Collider GetCollider() {return Collider(body);}
    bool get_wall_condition() { return isBroken; } // getter
    
    void change_Wall_condition() { isBroken = true; }
//    friend void ExplodeUp(float deltaTime, sf::RenderWindow& window, int strongness, int* level, Wall* breakableWalls[]);

private:
    bool isBreakable;
    bool isBroken;   // 被炸掉沒
    sf::RectangleShape body;
    
};

#endif /* Wall_hpp */
