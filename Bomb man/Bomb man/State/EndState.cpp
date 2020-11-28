//
//  EndState.cpp
//  Bomb man
//
//  Created by 張文毓 on 2020/1/4.
//  Copyright © 2020 張文毓. All rights reserved.
//

#include "EndState.hpp"


//Constructor/Destructor

EndState::EndState(sf::RenderWindow* window, std::stack<State*> * states, int winner):
State(window, states)
{
    this -> winner = winner;
    initFont();
    
    initButton();

    initBackGround();

}
EndState:: ~EndState()
{
    auto iterator  = this -> buttons.begin();
    for(iterator = this -> buttons.begin(); iterator != buttons.end(); iterator++)
    {
        delete iterator-> second;
    }
    
}
//Initializer

void EndState::initFont()
{
    if(!this -> font.loadFromFile("/Users/lijicheng/Downloads/程式設計/PD_期末/Final Demo/Bomb man/Bomb man/Fonts/The Army Of God.ttf"))
    {
        throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
    }
    
}


void  EndState::initButton()
{
    float width = this -> window -> getSize().x;
    float height = this -> window -> getSize().y;
    
    this -> buttons["MAIN_MENU_STATE"] = new Button(width / 2 - 75 , height / (MAX_NUMBER_OF_ITEMS + 1) * 1 + 150, 150, 50, &this->font, "Back to Main Menu",
    sf::Color::White, sf::Color::Black, sf::Color::Red);
    this -> buttons["EXIT_STATE"] = new Button(width / 2 - 75, height / (MAX_NUMBER_OF_ITEMS + 1) * 2 + 75, 150, 50, &this->font, "Quit",
    sf::Color::White, sf::Color::Black, sf::Color::Red);
    
}


void EndState::initBackGround()
{
    if(this -> winner == 1)
    {
        bgtexture.loadFromFile("/Users/lijicheng/Downloads/程式設計/PD_期末/Final Demo/Bomb man/Bomb man/images/player1wins.png");
    }
    else if(this -> winner == 2)
    {
        bgtexture.loadFromFile("/Users/lijicheng/Downloads/程式設計/PD_期末/Final Demo/Bomb man/Bomb man/images/player2wins.png");
    }
    else if(this -> winner == 3)
    {
        bgtexture.loadFromFile("/Users/lijicheng/Downloads/程式設計/PD_期末/Final Demo/Bomb man/Bomb man/images/drawscreen.png");
    }
    backgroud.setScale(1.315,1.663);
    backgroud.setTexture(bgtexture);
    
}
//Functions
void EndState::EndingState()
{
    
}

void EndState::UpdateInput(const float& deltatime)
{
    return this -> CheckforQuit();
}



void EndState::Update(const float& deltatime)
{
    this -> UpdateInput(deltatime);
    this -> UpdateMousePosition();
    
//    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
//        MoveUp();
//    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
//        MoveDown();
    this -> UpdateButtons();
    
    
    
    
}
void EndState::UpdateButtons()
{
    /*Update the button state and all functionality*/
    for(auto &it : this -> buttons )
    {
        it.second -> Update(this -> mousePosView);
    }

    //New Game
    if(this -> buttons["MAIN_MENU_STATE"] -> isPressed())
    {
        states -> pop();
        states -> pop();
    }

    //Quit the game
    
    if(this -> buttons["EXIT_STATE"] -> isPressed())
    {
        this -> window ->close();
        
    }
    
    

}
void EndState::RenderButtons(sf::RenderTarget* target)
{
    for(auto &it : this -> buttons )
    {
        it.second -> Render(target);
    }

}
void EndState::RenderBG()
{
    this -> window -> draw(this -> backgroud);
}
void EndState::Render(sf::RenderTarget* target)
{
    for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
    {
        this -> window -> draw(menu[i]);
    }
    this -> RenderBG();
    this ->RenderButtons(this->window);

}
