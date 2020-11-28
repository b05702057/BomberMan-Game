//
//  Game State.cpp
//  Bomb man
//
//  Created by 張文毓 on 2019/12/25.
//  Copyright © 2019 張文毓. All rights reserved.
//

#include "State.hpp"

//Constructor/Destructor
State::State(sf::RenderWindow* window,std::stack<State*> * states)
{
    this -> window = window;
    this -> states = states;
    this -> quit = 0; // 加進去的
    this -> winner = 0;
    player1Texture.loadFromFile("/Users/lijicheng/Downloads/程式設計/PD_期末/Final Demo/Bomb man/Bomb man/images/Bomberman.png");
    player2Texture.loadFromFile("/Users/lijicheng/Downloads/程式設計/PD_期末/Final Demo/Bomb man/Bomb man/images/Bomberdog.png");
    bombTexture.loadFromFile("/Users/lijicheng/Downloads/程式設計/PD_期末/Final Demo/Bomb man/Bomb man/images/Bomb.png");
    shoesTexture.loadFromFile("/Users/lijicheng/Downloads/程式設計/PD_期末/Final Demo/Bomb man/Bomb man/images/shoes.png");
    bagTexture.loadFromFile("/Users/lijicheng/Downloads/程式設計/PD_期末/Final Demo/Bomb man/Bomb man/images/bag.png");
    powerTexture.loadFromFile("/Users/lijicheng/Downloads/程式設計/PD_期末/Final Demo/Bomb man/Bomb man/images/power.png");
    
    getItemBuffer.loadFromFile("/Users/lijicheng/Downloads/程式設計/PD_期末/Final Demo/Bomb man/Bomb man/Sound/GetItem.ogg");
    getItemSound.setBuffer(getItemBuffer);
    
    gameStartBuffer.loadFromFile("/Users/lijicheng/Downloads/程式設計/PD_期末/Final Demo/Bomb man/Bomb man/Sound/GameStart.wav");
    gameStartSound.setBuffer(gameStartBuffer);
    
    gameMusic.openFromFile("/Users/lijicheng/Desktop/BomberMan-Game/Bomb man/Bomb man/Sound/GameMusic.ogg");
    menuMusic.openFromFile("/Users/lijicheng/Desktop/BomberMan-Game/Bomb man/Bomb man/Sound/MenuMusic.ogg");
    
    this -> P1MoveSet[0] = sf::Keyboard::W;
    this -> P1MoveSet[1] = sf::Keyboard::S;
    this -> P1MoveSet[2] = sf::Keyboard::A;
    this -> P1MoveSet[3] = sf::Keyboard::D;
    this -> P1MoveSet[4] = sf::Keyboard::Space;
    
    
    this -> P2MoveSet[0] = sf::Keyboard::Up;
    this -> P2MoveSet[1] = sf::Keyboard::Down;
    this -> P2MoveSet[2] = sf::Keyboard::Left;
    this -> P2MoveSet[3] = sf::Keyboard::Right;
    this -> P2MoveSet[4] = sf::Keyboard::M;
    
    wallTexture_breakable.loadFromFile("/Users/lijicheng/Downloads/程式設計/PD_期末/Final Demo/Bomb man/Bomb man/images/wall_breakable.png");
    wallTexture_unbreakable.loadFromFile("/Users/lijicheng/Downloads/程式設計/PD_期末/Final Demo/Bomb man/Bomb man/images/wall_unbreakable.png");
    boardTexture.loadFromFile("/Users/lijicheng/Downloads/程式設計/PD_期末/Final Demo/Bomb man/Bomb man/images/board_texture.jpg");
    
    heartTexture.loadFromFile("/Users/lijicheng/Downloads/程式設計/PD_期末/Final Demo/Bomb man/Bomb man/images/heart.png");
    
    srand(static_cast<unsigned int>(time(nullptr)));
    
    for(int i = 0; i < 100000; i++)
    {
        rnx = rand() % 23;
        repeatX = false;
        if (i == 0)
            chosenXindex[0] = rnx;
        else if (i != 0 )
        {
            for(int j = 0; j < i-cumulativeX; j++)
            {
                if (rnx == chosenXindex[j])
                {
                    cumulativeX++;
                    repeatX = true;
                    break;
                }
            }
            if (repeatX == false)
                chosenXindex[i-cumulativeX] = rnx;
            if (i - cumulativeX == 11 and repeatX == false)
                break;
        }
    }
    
    for(int i = 0; i < 100000; i++)
    {
        rny = rand() % 11;
        repeatY = false;
        if (i == 0)
            chosenYindex[0] = rny;
        else if (i != 0 )
        {
            for(int j = 0; j < i-cumulativeY; j++)
            {
                if (rny == chosenYindex[j])
                {
                    cumulativeY++;
                    repeatY = true;
                    break;
                }
            }
            if (repeatY == false)
                chosenYindex[i-cumulativeY] = rny;
            if (i-cumulativeY == 11 and repeatY == false)
                break;
        }
    }

}

State::~State()
{
}

// Functions
void State::UpdateInput(const float& deltatime)
{
    this -> CheckforQuit();
}
const bool& State::getQuit() const
{
    return this -> quit;
}

void State::CheckforQuit()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        this -> quit = true;
    }
}

void State::UpdateMousePosition()
{
    this -> mousePosScreen = sf::Mouse::getPosition();
    this -> mousePosWindow = sf::Mouse::getPosition(*(this -> window));
    this -> mousePosView = this -> window -> mapPixelToCoords(sf::Mouse::getPosition(*(this -> window)));
}

