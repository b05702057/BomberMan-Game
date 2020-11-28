//
//  Button.cpp
//  Bomb man
//
//  Created by 張文毓 on 2019/12/28.
//  Copyright © 2019 張文毓. All rights reserved.
//

#include "Button.hpp"

//Constructor/Destructor
Button::Button(float x, float y, float width, float height,sf::Font* font, std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
{
    this -> buttonState = BTN_IDLE;
    this -> shape.setPosition(x,y);
    this -> shape.setSize(sf::Vector2f(width,height));
    
    this -> font = font;
    this -> text.setFont(*this->font);
    this -> text.setString(text);
    this -> text.setFillColor(sf::Color::White);
    this -> text.setCharacterSize(24);
    this -> text.setPosition(x,y);
    
    this -> idleColor = idleColor;
    this -> hoverColor = hoverColor;
    this -> activeColor = activeColor;
    this -> shape.setFillColor(sf::Color::Transparent);
    
    mouseMovingBuffer.loadFromFile("/Users/lijicheng/Downloads/程式設計/PD_期末/Final Demo/Bomb man/Bomb man/Sound/MouseMoving.wav");
    mouseMovingSound.setBuffer(mouseMovingBuffer);
}



Button::~Button()
{
    
}

//Accessors

const bool Button::isPressed() const
{
    if(this -> buttonState == BTN_ACTIVE)
        return true;
    
    return false;

}

//Functions

void Button::Update(const sf::Vector2f mousePos)
{
    /* Update the bool for hover and press*/
    
    //Idle
    this -> buttonState = BTN_IDLE;
    
    // Hover
    if(this -> shape.getGlobalBounds().contains(mousePos))
    {
        this -> buttonState = BTN_HOVER;
        
        //Pressed
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            this ->buttonState = BTN_ACTIVE;
        }
    }
    
    switch(buttonState)
    {
        default:
            this -> text.setFillColor(sf::Color::Red);
            break;
        case BTN_IDLE:
            this->text.setFillColor(this -> idleColor);
            hovering = false;
            break;
        
        case BTN_HOVER:
            this->text.setFillColor(this -> hoverColor);
            if (hovering == false)
            {
                hovering = true;
                mouseMovingSound.play();
            }
            break;
            
        case BTN_ACTIVE:
            this->text.setFillColor(this -> activeColor);
            break;
    }
}

void Button::Render(sf::RenderTarget* target)
{
    target -> draw(this -> shape);
    target -> draw(this -> text);
}
