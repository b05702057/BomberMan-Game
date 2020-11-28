#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <map>
#include <vector>

#include <cstdlib>
#include <ctime>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Animation.hpp"
#include "Bomb.hpp"
#include "Player.hpp"
#include "Collider.hpp"
#include "TileMap.hpp"
#include "Wall.hpp"
#include "Board.hpp"
#include "GameClock.hpp"
#include "Item.hpp"

class State
{
private:
    
    
protected:
    std::stack<State*> * states;
    sf::RenderWindow *window;
    bool quit;
    sf::Vector2i mousePosScreen;
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;
    int winner;
    
    int xarray[23] = {48, 80, 112, 144, 176, 208, 240, 272, 304, 336, 368, 400, 432, 464, 496, 528, 560, 592, 624, 656, 688,
                     720, 752};
    int yarray[11] = {176, 208, 240, 336, 368, 464, 496, 592, 624, 720, 752};
    
    int chosenXindex[12] = {0}; // 12個index(道具數量)
    int chosenYindex[12] = {0};
    
    int cumulativeX = 0;
    int cumulativeY = 0;
    
    bool repeatX = false;
    bool repeatY = false;
    
    int rnx = 0, rny = 0;
    

    
    
     //Resources
    sf::Texture player1Texture,player2Texture;
    sf::Texture bombTexture;
    sf::Texture wallTexture_breakable, wallTexture_unbreakable;
    sf::Texture boardTexture;
    sf::Texture heartTexture;
    sf::Texture shoesTexture;
    sf::Texture bagTexture;
    sf::Texture powerTexture;
    
    sf::SoundBuffer getItemBuffer;
    sf::Sound getItemSound;
    
    sf::SoundBuffer gameStartBuffer;
    sf::Sound gameStartSound;
    
    sf::Music gameMusic;
    sf::Music menuMusic;
    
    //Keyset
    sf::Keyboard::Key P1MoveSet[5];
    sf::Keyboard::Key P2MoveSet[5];
    
    
    
public:
    State(sf::RenderWindow* window,std::stack<State*> * states);
    virtual ~State();
    
    const bool& getQuit() const;
    
    virtual void CheckforQuit();
    virtual void EndingState() = 0;

    virtual void UpdateMousePosition();
    virtual void UpdateInput(const float& deltatime) = 0;
    virtual void Update(const float& deltatime) = 0;
    virtual void Render(sf::RenderTarget* target = nullptr ) = 0;
    
    
    
    
};
