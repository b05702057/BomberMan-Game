

#ifndef MainMenuState_hpp
#define MainMenuState_hpp

#include "GameState.hpp"
#include "Button.hpp"

class MainMenuState:
    public State
{
public:
    MainMenuState(sf::RenderWindow* window,std::stack<State*> * states);
    virtual ~MainMenuState();
    
    //Functions
    
    void EndingState();
    void UpdateButtons();
    void UpdateInput(const float& deltatime);
    void Update(const float& deltatime);
    void Render(sf::RenderTarget* target = nullptr);
    void RenderButtons(sf::RenderTarget* target = nullptr);
    void RenderBG();
    void MoveUp();
    void MoveDown();
    int GetPressItem() { return selectedItemIndex; }
    
private:
    void initFont();
    void initButton();
    void initBackGround();
private:
    sf::Texture bgtexture;
    int selectedItemIndex;
    sf::Font font;
    sf::Text menu[MAX_NUMBER_OF_ITEMS];
    sf::Sprite backgroud;
    std::map <std::string, Button*> buttons;
    
    
};

#endif /* MainMenuState_hpp */
