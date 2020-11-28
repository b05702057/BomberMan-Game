//
//  GameClock.hpp
//  Bomb man
//
//  Created by 涂譽寶 on 2020/1/4.
//  Copyright © 2020 張文毓. All rights reserved.
//

#ifndef GameClock_hpp
#define GameClock_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>

class GameClock
{
private:
    sf::Clock clock;
    sf::Text text;
    sf::Font font;
    sf::Time time;
    int countDown;
    int checkSecond;
    
    sf::SoundBuffer countDownBuffer;
    sf::Sound countDownSound;
public:
    GameClock();
    ~GameClock();
    
    void restart();
    void CntTime();
    void timeCountDown();
    void Draw(sf::RenderWindow* window);
    int GetCntDown(){return countDown;}
};

#endif /* GameClock_hpp */
