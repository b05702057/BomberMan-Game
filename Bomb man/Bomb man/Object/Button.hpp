//
//  Button.hpp
//  Bomb man
//
//  Created by 張文毓 on 2019/12/28.
//  Copyright © 2019 張文毓. All rights reserved.
//

#ifndef Button_hpp
#define Button_hpp

#include <iostream>
#include <fstream>
#include <sstream>


#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>



enum button_states{BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE};

class Button
{
private:
    short unsigned buttonState;
    
    sf::RectangleShape shape;
    sf::Font* font;
    sf::Text text;
    
    sf::Color idleColor;
    sf::Color hoverColor;
    sf::Color activeColor;
    
    sf::SoundBuffer mouseMovingBuffer;
    sf::Sound mouseMovingSound;
    
    bool hovering = false;
    
    
public:
    Button(float x, float y, float width, float height,sf::Font* font, std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
    ~Button();
    //Accessors

    const bool isPressed() const;
    
    //Functions
    
    void Update(const sf::Vector2f mousePos);
    void Render(sf::RenderTarget* target);




}; 

#endif /* Button_hpp */
