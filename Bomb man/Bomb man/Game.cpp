#include "Game.hpp"

//Static Functions

//Initializer

void Game:: initWindow()
{
    
    this -> window = new sf::RenderWindow (sf::VideoMode(800, 800), "Bomber Man!", sf::Style::Close | sf::Style::Resize);
    
}

void Game::initStates()
{
    this -> states.push(new MainMenuState (this -> window, &this->states));
}

//Constructor/Destructor
Game::Game( )
{
    this -> initWindow();
    this -> initStates();
    
}
Game::~Game( )
{
    delete this -> window;
    while (!this -> states.empty())
    {
        delete this -> states.top();
        this -> states.pop();
        
    }
    
}

//Function
void Game::UpdateDt()
{
    /*Updates the deltatime with the time it takes to update and render one frame*/
    this -> deltaTime = this -> clock.restart().asSeconds();
}

void Game::UpdateSFMLEvents( )
{
    while(this -> window -> pollEvent(this -> evnt))
    {
        switch(this -> evnt.type)
        {
            case sf::Event::Closed:
                this -> window ->close();
                break;
                
           
            default:
                break;
        }
    }
    
}

void Game::Update()
{
    
    if(!this->states.empty())
    {
        this ->states.top() -> Update(this -> deltaTime);
        if(this ->states.top() -> getQuit())
        {
            this -> states.top() -> EndingState();
            delete this -> states.top();
            this -> states.pop();
        }
    }
    // APP END
    else
    {
        this -> window -> close();
        
    }
}

void Game::Render()
{
    
    
    //Render items
    if(!this->states.empty())
        this ->states.top() -> Render(this -> window);
    this -> window -> display();
    
}

void Game::Run()
{
    while(this -> window -> isOpen())
    {
        this -> UpdateDt();
        this -> UpdateSFMLEvents();
        this -> window -> clear();
        this -> Update();
        this -> Render();
    }

}


