//
//  MainMenuState.cpp
//  Bomb man
//
//  Created by 張文毓 on 2019/12/28.
//  Copyright © 2019 張文毓. All rights reserved.
//

#include "MainMenuState.hpp"

//Constructor/Destructor

MainMenuState::MainMenuState(sf::RenderWindow* window, std::stack<State*> * states):
State(window, states)
{
    initFont();
    initButton();
    initBackGround();
    menuMusic.play();
}
MainMenuState:: ~MainMenuState()
{
    auto iterator  = this -> buttons.begin();
    for(iterator = this -> buttons.begin(); iterator != buttons.end(); iterator++)
    {
        delete iterator-> second;
    }
    
}
//Initializer
void MainMenuState::initFont()
{
    if(!this -> font.loadFromFile("/Users/lijicheng/Downloads/程式設計/PD_期末/Final Demo/Bomb man/Bomb man/Fonts/The Army Of God.ttf"))
    {
        throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
    }
    
}


void  MainMenuState::initButton()
{
    float width = this -> window -> getSize().x;
    float height = this -> window -> getSize().y;
    
    this -> buttons["GAME_STATE"] = new Button(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 1 + 75, 150, 50, &this->font, "Start Game",
    sf::Color::White, sf::Color::Blue, sf::Color::Red);
    this -> buttons["EXIT_STATE"] = new Button(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 2 + 75, 150, 50, &this->font, "Quit",
    sf::Color::White, sf::Color::Blue, sf::Color::Red);
    
}
void MainMenuState::initBackGround()
{
    bgtexture.loadFromFile("/Users/lijicheng/Downloads/程式設計/PD_期末/Final Demo/Bomb man/Bomb man/images/MainMenu.png");
    backgroud.setScale(1.315,1.663);
    backgroud.setTexture(bgtexture);
    
}

//Functions

void MainMenuState::UpdateInput(const float& deltatime)
{
    return this -> CheckforQuit();
}
void MainMenuState::EndingState()
{
    std::cout << "Ending this states!!!" << std::endl;
    
    
}

void MainMenuState::Update(const float& deltatime)
{
    this -> UpdateInput(deltatime);
    this -> UpdateMousePosition();
    
    
//    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
//        MoveUp();
//    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
//        MoveDown();
    this -> UpdateButtons();
    
    
    
    
}
void MainMenuState::UpdateButtons()
{
    /*Update the button state and all functionality*/
    for(auto &it : this -> buttons )
    {
        it.second -> Update(this -> mousePosView);
    }

    //New Game
    if(this -> buttons["GAME_STATE"] -> isPressed())
    {
        this -> states -> push(new GameState (this -> window, this->states));
        menuMusic.stop();
        gameStartSound.play();
    }

    //Quit the game
    
    if(this -> buttons["EXIT_STATE"] -> isPressed())
    {
        this -> quit = true;
        
    }
    
    

}
void MainMenuState::RenderButtons(sf::RenderTarget* target)
{
    for(auto &it : this -> buttons )
    {
        it.second -> Render(target);
    }

}
void MainMenuState::Render(sf::RenderTarget* target)
{
    for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
    {
        this -> window -> draw(menu[i]);
    }
    this -> RenderBG();
    this ->RenderButtons(this->window);

}
void MainMenuState::RenderBG()
{
    this -> window -> draw(this -> backgroud);
}

//void MainMenuState::MoveUp()
//{
//    if (selectedItemIndex - 1 >= 0)
//    {
//        menu[selectedItemIndex].setFillColor(sf::Color::White);
//        selectedItemIndex--;
//        menu[selectedItemIndex].setFillColor(sf::Color::Red);
//
//    }
//}
//void MainMenuState::MoveDown()
//{
//    if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
//    {
//        menu[selectedItemIndex].setFillColor(sf::Color::White);
//        selectedItemIndex++;
//        menu[selectedItemIndex].setFillColor(sf::Color::Red);
//
//    }
//}
