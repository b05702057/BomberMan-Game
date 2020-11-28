//
//  GameClock.cpp
//  Bomb man
//
//  Created by 涂譽寶 on 2020/1/4.
//  Copyright © 2020 張文毓. All rights reserved.
//

#include "GameClock.hpp"


GameClock::GameClock()
{
    if(! font.loadFromFile("/Users/lijicheng/Downloads/程式設計/PD_期末/Final Demo/Bomb man/Bomb man/Fonts/The Army Of God.ttf"))
    {
        std::cout << "Error Loading font file in GameLock.cpp" << std::endl;
        system("pause");
    }
    if (!countDownBuffer.loadFromFile("/Users/lijicheng/Downloads/程式設計/PD_期末/Final Demo/Bomb man/Bomb man/Sound/CountDown.wav"))
    {
        std::cout << "Error Loading music in GameLock.cpp" << std::endl;
        system("pause");
    }
    countDownSound.setBuffer(countDownBuffer);
    
    text.setFont(font);
//    text.setString("3:00");
    countDown = 0.1 * 1200; // 秒數
    checkSecond = 0;
    text.setCharacterSize(48);
    text.setFillColor(sf::Color::Black);
    text.setPosition(sf::Vector2f(325.0, 24.0)); // 不知道怎麼過改成position / 2
     // 倒數計時
}

GameClock::~GameClock()
{
}

void GameClock::CntTime()
{
    time += clock.restart();
    const unsigned int seconds = static_cast<unsigned int>(time.asSeconds());
    if(checkSecond!=seconds)
    {
        checkSecond = seconds;
        countDown -= 1;
        std::cout << checkSecond << std::endl;
        if (countDown <= 3)
            countDownSound.play();
    }

//    countDown -= seconds;
    std::string timeDisplay;
    if(countDown > 0)
    {
        timeDisplay += std::to_string(countDown/60);
        timeDisplay += ":";
    }
    
    if(countDown == 0)
    {
        timeDisplay += "Time out!";
//        text.setCharacterSize(60);
    }
    else if(countDown % 60 == 0)
    {
        timeDisplay += "0";
        timeDisplay += std::to_string(countDown%60);
    }
    else if(countDown % 60 > 0 && countDown % 60 < 10) // 倒數10秒
    {
        timeDisplay += "0";
        timeDisplay += std::to_string(countDown%60);
        text.setFillColor(sf::Color::Red);
    }
    else
        timeDisplay += std::to_string(countDown%60); // 個位數的也要補
    if(countDown >= 0)
        text.setString(timeDisplay);
    
//    text.setString(std::to_string(countDown));
//    text.setString(std::to_string(static_cast<unsigned int>(time.asSeconds())));
}


void GameClock::timeCountDown()
{
    sf::Time elapsed = clock.getElapsedTime();
    std::cout << elapsed.asSeconds() << std::endl;
}

void GameClock::Draw(sf::RenderWindow* window)
{
    window->draw(text);
}
