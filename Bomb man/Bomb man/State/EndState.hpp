
#ifndef EndState_hpp
#define EndState_hpp

#include "State.hpp"
#include "Button.hpp"

#define MAX_NUMBER_OF_ITEMS 2
class EndState:
    public State
{
public:
    EndState(sf::RenderWindow* window,std::stack<State*> * states, int winner);
    virtual ~EndState();
    
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
    void ChangeBG();

    
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


#endif /* EndState_hpp */
