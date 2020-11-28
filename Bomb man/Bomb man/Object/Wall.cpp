//
//  Wall.cpp
//  Bomb man
//
//  Created by 涂譽寶 on 2020/1/3.
//  Copyright © 2020 張文毓. All rights reserved.
//

#include "Wall.hpp"


Wall::Wall(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position, bool isBreakable, bool isBroken)
{
    this->isBreakable = isBreakable;
    this->isBroken = isBroken;
    body.setSize(size);
    body.setOrigin(size / 2.0f);
    body.setTexture(texture);
    body.setPosition(position);
    
}

Wall::~Wall()
{
}

void Wall::Draw(sf::RenderWindow* window)
{
    if(!isBroken)
        window->draw(body);
//        window.draw(body);
}
