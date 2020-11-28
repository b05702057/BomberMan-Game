//
//  Board.cpp
//  Bomb man
//
//  Created by 涂譽寶 on 2020/1/4.
//  Copyright © 2020 張文毓. All rights reserved.
//


#include "Board.hpp"


Board::Board(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position, sf::Texture* heartTexture)
{
    body.setSize(size);
    body.setOrigin(size / 2.0f);
    body.setTexture(texture);
    body.setPosition(position);
    
    float heart1_x_axis = 16.0;
    for(int i = 0; i < 3; i++)
    {
        heart_Player1[i].setTexture(*heartTexture); // 不知道為什麼要用*
        heart_Player1[i].setPosition(heart1_x_axis + (i * 80.0), 32.0);
    }
    
    float heart2_x_axis = 720.0;
    for(int i = 0; i < 3; i++)
    {
        heart_Player2[i].setTexture(*heartTexture);
        heart_Player2[i].setPosition(heart2_x_axis - (i * 80.0), 32.0);
    }
}

Board::~Board()
{
}

void Board::Draw_heart(sf::RenderWindow* window, const int lives_player1, const int lives_player2)
{
    for(int i = 0; i < lives_player1; i++)
        window->draw(heart_Player1[i]);
    for(int i = 0; i < lives_player2; i++)
        window->draw(heart_Player2[i]);
}

void Board::Draw(sf::RenderWindow* window)
{
    window->draw(body);
}
