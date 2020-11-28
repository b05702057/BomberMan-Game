//
//  Board.hpp
//  Bomb man
//
//  Created by 涂譽寶 on 2020/1/4.
//  Copyright © 2020 張文毓. All rights reserved.
//

#ifndef Board_hpp
#define Board_hpp

#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>

class Board
{
private:
    sf::RectangleShape body;
    sf::Font font;
//    sf::Text timeCnt; // 倒數計時
//    sf::Clock clock;
    sf::Sprite heart_Player1[3];
    sf::Sprite heart_Player2[3];
    
public:
    Board(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position, sf::Texture* heartTexture);
    ~Board();
    
//    void timeCountDown();
    void Draw_heart(sf::RenderWindow* window, const int lives_player1, const int lives_player2);
    void Draw(sf::RenderWindow* window);
};

#endif /* Board_hpp */
