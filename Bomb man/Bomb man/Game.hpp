#ifndef GAME_H
#define GAME_H

#include "GameState.hpp"
#include "MainMenuState.hpp"


class Game
{
    
public:
    Game( );
    virtual ~Game( );
    
    //Functions
    void UpdateDt();
    void UpdateSFMLEvents( );
    void Update();
    void Render();
    void Run();
    
private:
    //Initializer
    void initWindow();
    void initStates();
public:
    
private:
    sf::RenderWindow* window;
    sf::Event evnt;
    sf::Clock clock;
    float deltaTime;
    
    std::stack<State*> states;
    
    
    
    
};

#endif
