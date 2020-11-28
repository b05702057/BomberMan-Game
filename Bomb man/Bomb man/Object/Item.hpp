//
//  Item.hpp
//  Bomb man
//
//  Created by 李季澄 on 2020/1/5.
//  Copyright © 2020 張文毓. All rights reserved.
//

#ifndef Item_hpp
#define Item_hpp

#pragma once
#include <stdio.h>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include"Collider.hpp"
#include"Player.hpp"
using namespace std ;

class Item
{
public:
    Item(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position) ;
    ~Item() ;
    void Draw(sf::RenderWindow* window) ;
    int GetDrawOrNot(){return DrawOrNot ;} ;
    void SetDrawOrNot(){DrawOrNot = 0 ;} ;
    Collider GetCollider(){return Collider(body) ;}
    void Shoes(Collider temp, Player& player, sf::RenderWindow& window, sf::Sound& sound) ;
    void Bag(Collider temp, Player& player, sf::RenderWindow& window, sf::Sound& sound) ;
    void Magic(Collider temp, Player& player, sf::RenderWindow& window, sf::Sound& sound) ;
private:
    sf::RectangleShape body ;
    int DrawOrNot ;
};

#endif
