//
//  Item.cpp
//  Bomb man
//
//  Created by 李季澄 on 2020/1/5.
//  Copyright © 2020 張文毓. All rights reserved.
//

#include "Item.hpp"


using namespace std ;

Item::Item(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position)
{
    body.setSize(size) ;
    body.setOrigin(size / 2.0f) ;
    body.setTexture(texture) ;
    body.setPosition(position) ;
    DrawOrNot = 1 ;
}

Item::~Item()
{
}

void Item::Draw(sf::RenderWindow* window)
{
    window -> draw(body) ;
}
