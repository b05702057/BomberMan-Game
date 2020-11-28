
#include "Player.hpp"

//Constructor/Destructor

Player::Player(sf::Texture* texture,sf::Texture* bombTexture, sf::Vector2u imageCount, float switchTime, float speed, sf::Keyboard::Key key[5], int whichPlayer):
animation(texture, imageCount, switchTime)
{
    this -> whichPlayer = whichPlayer;
    this -> speed = speed;
    this -> lives = 3; // 一開始三條命
    this -> texture = texture;
    row = 0;
    faceRight = false;
    
    body.setSize(sf::Vector2f(32.0f, 32.0f));
    if(whichPlayer == 1)
        body.setPosition(48.0f, 400.0f);
    else if(whichPlayer == 2)
        body.setPosition(752.0f, 400.0f);
    body.setTexture(texture);
    body.setOrigin(body.getSize()/2.0f);
    quota = 2;
    strongness = 1;
    numOfBombDroped = 0;
    ifAlive = 1;
    
    this -> Up = key[0];
    this -> Down = key[1];
    this -> Left = key[2];
    this -> Right = key[3];
    this -> bombKey = key[4];
    for(int i = 0; i < this -> quota; i++)
    {
        vbomb[i] = new Bomb(bombTexture,sf::Vector2u(7,6),0.2f);
    }
    playerBombTexture = *bombTexture;
}

Player::~Player()
{
    
}


//Functions
int Player::chooseBomb()
{
    for(int i = 0; i < quota; i++)
    {
        if(ifSetBomb[i] == 0)
        {
            return i;
        }
    }
    return -1;
}

//update anime
void Player::Update(float deltaTime)
{
    sf::Vector2f movement(0.0f,0.0f);
    if(ifAlive)
    {
        if(whichPlayer == 1)
        {
            if(sf::Keyboard::isKeyPressed(this -> Left))
            {
                movement.x -= speed *deltaTime;
                row = 2;
            }
            if(sf::Keyboard::isKeyPressed(this -> Right))
            {
                movement.x += speed *deltaTime;
                row = 3;
            }
            if(sf::Keyboard::isKeyPressed(this -> Up))
            {
                movement.y -= speed *deltaTime;
                row = 0;
            }
            if(sf::Keyboard::isKeyPressed(this -> Down))
            {
                movement.y += speed *deltaTime;
                row = 1;
            }
            if(movement.x == 0.0f && movement.y == 0.0f)
            {
                row = 4;
            }
            if(sf::Keyboard::isKeyPressed(this -> bombKey))
            {
                SetBomb();
            }
        }
        else if(whichPlayer == 2)
        {
            if(sf::Keyboard::isKeyPressed(this -> Left))
            {
                movement.x -= speed *deltaTime;
                row = 2;
            }
            if(sf::Keyboard::isKeyPressed(this -> Right))
            {
                movement.x += speed *deltaTime;
                row = 3;
            }
            if(sf::Keyboard::isKeyPressed(this -> Up))
            {
                movement.y -= speed *deltaTime;
                row = 0;
            }
            if(sf::Keyboard::isKeyPressed(this -> Down))
            {
                movement.y += speed *deltaTime;
                row = 1;
            }
            if(movement.x == 0.0f && movement.y == 0.0f)
            {
                row = 4;
            }
            if(sf::Keyboard::isKeyPressed(this -> bombKey))
            {
                SetBomb();
            }
        }
        animation.UpdatePlayer(row, deltaTime);
        body.setTextureRect(animation.uvRect);
        body.move(movement);
    }
    
}
void Player::deathAnime(float deltaTime,sf::RenderWindow *window)
{
    row = 5;
    ifAnimeDone = animation.UpdatePlayer(row, deltaTime);
    body.setTextureRect(animation.uvRect);
    Draw(window);
}
void Player::BackToLive()
{
    ifAlive = true;
    ifAnimeDone = false;
    body.setTexture(this -> texture);
    if(whichPlayer == 1)
        body.setPosition(48.0f, 400.0f);
    else if(whichPlayer == 2)
        body.setPosition(752.0f, 400.0f);
}

void Player::Draw(sf::RenderWindow *window)
{
    window -> draw(body);
}

void Player::SetBomb()
{
//    std::cout << numOfBombDroped <<std::endl;
    if(numOfBombDroped < quota)
    {
        int index = chooseBomb();
        if(index != -1)
        {
            if((numOfBombDroped != 0 && vbomb[lastBombset] -> ifPlayerleft) || numOfBombDroped == 0)
            {
                vbomb[index] ->setup(getLoc());
                numOfBombDroped++;
                setUnavailable(index);
                lastBombset = index;
            }
        }
    }
}

void Player::quotaUp()
{
    quota += 1;
    vbomb[quota-1] = new Bomb(&playerBombTexture,sf::Vector2u(7,6),0.2f);
}
