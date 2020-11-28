
#include "Bomb.hpp"


// Constructor/Destructor
Bomb::Bomb()
{
    
}
Bomb::Bomb(sf::Texture* texture, sf::Vector2u imageCount, float switchTime):
animation(texture, imageCount, switchTime)
{
    row = 5;
    ifExplode = false;
    body.setSize(sf::Vector2f(32.0f, 32.0f));
    body.setTexture(texture);
    body.setOrigin(body.getSize()/2.0f);
    Exploded = false;
    explosionBuffer.loadFromFile("/Users/lijicheng/Downloads/程式設計/PD_期末/Final Demo/Bomb man/Bomb man/Sound/Explosion.wav");
    explosionSound.setBuffer(explosionBuffer);
}

Bomb::~Bomb()
{
}



//Functions
void Bomb::Update(float deltaTime,sf::RenderWindow &window, int strongness, Wall* breakableWalls[], Wall* unbreakableWalls[], const int breakableWallsCnt, const int unbreakableWallsCnt)
{
    if(ifExplode)
    {
        if (Bombing == false)
        {
            explosionSound.play();
            Bombing = true;
        }
//        Explode(deltaTime, window,strongness);
        ExplodeUp(deltaTime, window, strongness, breakableWalls, unbreakableWalls, breakableWallsCnt, unbreakableWallsCnt);
        ExplodeDown(deltaTime, window, strongness, breakableWalls, unbreakableWalls, breakableWallsCnt, unbreakableWallsCnt);
        ExplodeRight(deltaTime, window, strongness, breakableWalls, unbreakableWalls, breakableWallsCnt, unbreakableWallsCnt);
        ExplodeLeft(deltaTime, window, strongness, breakableWalls, unbreakableWalls, breakableWallsCnt, unbreakableWallsCnt);
    }
    else
    {
        Bombing = false;
        animation.UpdateBomb(row, deltaTime, ifExplode);
        body.setTextureRect(animation.uvRect);
        Draw(window);
    }
    
}
//void Bomb::Explode(float deltaTime, sf::RenderWindow &window, int strongness)
//{
//    animation.UpdateExplosion(0, deltaTime, Exploded);
//    body.setTextureRect(animation.uvRect);
//    sf::IntRect tmp_uvrect(animation.uvRect);
//    for(float i = 1.0f; i <= strongness; i++)
//    {
//
//        sf::RectangleShape up(body);
//        sf::RectangleShape down(body);
//        sf::RectangleShape right(body);
//        sf::RectangleShape left(body);
//
//        up.setPosition(body.getPosition().x,body.getPosition().y + i * body.getSize().y);
//        down.setPosition(body.getPosition().x, body.getPosition().y - i * body.getSize().y);
//        right.setPosition(body.getPosition().x - i * body.getSize().x,body.getPosition().y);
//        left.setPosition(body.getPosition().x + i * body.getSize().x,body.getPosition().y);
//
//
//        tmp_uvrect.left = 1 * tmp_uvrect.width;
//        up.setTextureRect(tmp_uvrect);
//        down.setTextureRect(tmp_uvrect);
//
//        tmp_uvrect.left = 2 * tmp_uvrect.width;
//        right.setTextureRect(tmp_uvrect);
//        left.setTextureRect(tmp_uvrect);
//
//
//        if(!Exploded)
//            Draw(window,up,down,right,left);
//        else
//             ifExplode = false;
//
//
//    }
//}

void Bomb::ExplodeUp(float deltaTime, sf::RenderWindow& window, int strongness, Wall* breakableWalls[], Wall* unbreakableWalls[], int breakableWallsCnt, int unbreakableWallsCnt)
{
    animation.UpdateExplosion(0, deltaTime, Exploded);
    body.setTextureRect(animation.uvRect);
    sf::IntRect tmp_uvrect(animation.uvRect);
    

    for(int i = 0; i <= strongness; i++)
    {
        if((this -> exitUp || this -> unBreakExitUp)  && i > rangeOfUp)
            break;
        sf::RectangleShape up(body);
        up.setSize(sf::Vector2f(body.getSize().x - 0.1f, body.getSize().y - 0.1f));
        up.setPosition(body.getPosition().x,body.getPosition().y - i * body.getSize().y);
        tmp_uvrect.left = 1 * tmp_uvrect.width;
        up.setTextureRect(tmp_uvrect);
        Collider tmp = Collider(up);
        
        for(int j = 0; j < breakableWallsCnt; j++) // 還不知道怎麼傳breakableWalls 的數量
        {
            if(breakableWalls[j]->GetCollider().checkCollision_Wall(tmp, 1.0f) && !(breakableWalls[j]->get_wall_condition()))
            {
                breakableWalls[j]->change_Wall_condition(); // 木塊消失
                this -> exitUp = true;
                this -> rangeOfUp = i;
                break; // 外面沒break到
            }
        }
        for(int j = 0; j < unbreakableWallsCnt; j++)
        {
            if(unbreakableWalls[j]->GetCollider().checkCollision_Wall(tmp, 1.0f))
            {
                this -> unBreakExitUp = true;
                this -> rangeOfUp = i;
                break;
            }
        }
        
//        std:: cout << "上面停止位置： " << this -> rangeOfUp << "\n";
        if (!Exploded  && (i <  this -> rangeOfUp || !this -> unBreakExitUp))
            DrawUp(window, up);
        if(Exploded)
        {
            ifExplode = false;
        }
    
    }
}

void Bomb::ExplodeDown(float deltaTime, sf::RenderWindow& window, int strongness, Wall* breakableWalls[], Wall* unbreakableWalls[], int breakableWallsCnt, int unbreakableWallsCnt)
{
    animation.UpdateExplosion(0, deltaTime, Exploded);
    body.setTextureRect(animation.uvRect);
    sf::IntRect tmp_uvrect(animation.uvRect);
    

    for(int i = 0; i <= strongness; i++)
    {
        if((this -> exitDown || this -> unBreakExitDown) && i > rangeOfDown)
            break;
        sf::RectangleShape down(body);
        down.setSize(sf::Vector2f(body.getSize().x - 0.1f, body.getSize().y - 0.1f));
        down.setPosition(body.getPosition().x,body.getPosition().y + i * body.getSize().y);
        tmp_uvrect.left = 1 * tmp_uvrect.width;
        down.setTextureRect(tmp_uvrect);
        Collider tmp = Collider(down);
        
        for(int j = 0; j < breakableWallsCnt; j++) // 還不知道怎麼傳breakableWalls 的數量
        {
            if(breakableWalls[j]->GetCollider().checkCollision_Wall(tmp, 1.0f) && !(breakableWalls[j]->get_wall_condition()))
            {
                breakableWalls[j]->change_Wall_condition(); // 不再往下炸下去
                this -> exitDown = true;
                this -> rangeOfDown = i;
                break; // 外面沒break到
            }
        }
        for(int j = 0; j < unbreakableWallsCnt; j++)
        {
            if(unbreakableWalls[j]->GetCollider().checkCollision_Wall(tmp, 1.0f))
            {
                this -> unBreakExitDown = true;
                this -> rangeOfDown = i;
                break;
            }
        }
//        std:: cout << "下面停止位置： " << this -> rangeOfDown << "\n";
        if (!Exploded && (i <  this -> rangeOfDown || !this -> unBreakExitDown))
            DrawDown(window, down);
        if(Exploded)
        {
            ifExplode = false;
        }
        
    }
}

void Bomb::ExplodeRight(float deltaTime, sf::RenderWindow& window, int strongness, Wall* breakableWalls[], Wall* unbreakableWalls[], int breakableWallsCnt, int unbreakableWallsCnt)
{
    
    animation.UpdateExplosion(0, deltaTime, Exploded);
    body.setTextureRect(animation.uvRect);
    sf::IntRect tmp_uvrect(animation.uvRect);
    

    for(int i = 0; i <= strongness; i++)
    {
        if((this -> exitRight || this -> unBreakExitRight)&& i > rangeOfRight)
            break;
        sf::RectangleShape right(body);
        right.setSize(sf::Vector2f(body.getSize().x - 0.1f, body.getSize().y - 0.1f));
        right.setPosition(body.getPosition().x + i * body.getSize().x, body.getPosition().y);
        tmp_uvrect.left = 2 * tmp_uvrect.width;
        right.setTextureRect(tmp_uvrect);
        Collider tmp = Collider(right);
        
        for(int j = 0; j < breakableWallsCnt; j++) // 還不知道怎麼傳breakableWalls 的數量
        {
            if(breakableWalls[j]->GetCollider().checkCollision_Wall(tmp, 1.0f) && !(breakableWalls[j]->get_wall_condition()))
            {
                breakableWalls[j]->change_Wall_condition(); // 不再往下炸下去
                this -> exitRight = true;
                this -> rangeOfRight = i ;
                break; // 外面沒break到
            }
        }
        for(int j = 0; j < unbreakableWallsCnt; j++)
        {
            if(unbreakableWalls[j]->GetCollider().checkCollision_Wall(tmp, 1.0f))
            {
                this -> unBreakExitRight = true;
                this -> rangeOfRight = i;
                break;
            }
        }
//        std:: cout << "右邊停止位置： " << this -> rangeOfRight << "\n";
        if (!Exploded && (i <  this -> rangeOfRight || !this -> unBreakExitRight))
            DrawRight(window, right);
        if(Exploded)
        {
            ifExplode = false;
        }
        
    }
}
void Bomb::ExplodeLeft(float deltaTime, sf::RenderWindow& window, int strongness, Wall* breakableWalls[], Wall* unbreakableWalls[], int breakableWallsCnt, int unbreakableWallsCnt)
{
    animation.UpdateExplosion(0, deltaTime, Exploded);
    body.setTextureRect(animation.uvRect);
    sf::IntRect tmp_uvrect(animation.uvRect);
    
    for(int i = 0; i <= strongness; i++)
    {
        if((this -> exitLeft  || this -> unBreakExitLeft) && i > rangeOfLeft)
            break;
        sf::RectangleShape left(body);
        left.setSize(sf::Vector2f(body.getSize().x - 0.1f, body.getSize().y - 0.1f));
        left.setPosition(body.getPosition().x - i * body.getSize().x, body.getPosition().y);
        tmp_uvrect.left = 2 * tmp_uvrect.width;
        left.setTextureRect(tmp_uvrect);
        Collider tmp = Collider(left);
        
        for(int j = 0; j < breakableWallsCnt; j++) // 還不知道怎麼傳breakableWalls 的數量
        {
            if(breakableWalls[j]->GetCollider().checkCollision_Wall(tmp, 1.0f) && !(breakableWalls[j]->get_wall_condition()))
            {
                breakableWalls[j]->change_Wall_condition(); // 不再往下炸下去
                this -> exitLeft = true;
                this -> rangeOfLeft = i;
                break; // 外面沒break到
            }
        }
        for(int j = 0; j < unbreakableWallsCnt; j++)
        {
            if(unbreakableWalls[j]->GetCollider().checkCollision_Wall(tmp, 1.0f))
            {
                this -> unBreakExitLeft = true;
                this -> rangeOfLeft = i;
                break;
            }
        }
//        std:: cout << "左邊停止位置： " << this -> rangeOfLeft << "\n";
        if (!Exploded && (!this -> unBreakExitLeft || i < this -> rangeOfLeft))
            DrawUp(window, left);
        if(Exploded)
        {
            ifExplode = false;
        }
        
    }
}
void Bomb::setup(sf::Vector2f currentloc)
{
    float x_cor = currentloc.x;
    float y_cor = currentloc.y;
    int multiplier_x = 0;
    int multiplier_y = 0;
    while(true)
    {
        x_cor -= 16.0f;
        if(x_cor < 0)
        {
            x_cor +=16.0f;
            break;
        }
        multiplier_x++;
    }
    while(true)
    {
        y_cor -= 16.0f;
        if(y_cor < 0)
        {
            y_cor +=16.0f;
            break;
        }
        multiplier_y++;
    }
    if(x_cor >= 8 && multiplier_x % 2 == 0)
        multiplier_x ++;
    else if(x_cor < 8 && multiplier_x % 2 == 0)
        multiplier_x ++;
    if(y_cor >= 8 && multiplier_y % 2 == 0)
        multiplier_y ++;
    else if(y_cor < 8 && multiplier_y % 2 == 0)
        multiplier_y ++;
//    std::cout << "炸彈位置： "<< 16.0f * multiplier_x << " " <<16.0f*multiplier_y << "\n";
//    std::cout << "人物位置： "<< currentloc.x << " " << currentloc.y << "\n";
    body.setPosition(sf::Vector2f(16.0f * multiplier_x, 16.0f*multiplier_y));
    ifSet = true;
    rangeOfUp = 0;
    rangeOfDown = 0;
    rangeOfLeft = 0;
    rangeOfRight = 0;
    
}



void Bomb::reset()
{
    ifSet = false;
    Exploded = false;
    animation.reset();
    ifPlayerleft = false;
    exitUp = false;
    exitDown = false;
    exitRight = false;
    exitLeft = false;
    unBreakExitUp = false;
    unBreakExitDown = false;
    unBreakExitRight = false;
    unBreakExitLeft = false;
    

}


void Bomb::Draw(sf::RenderWindow &window)
{
    window.draw(body);
}

void Bomb::Draw(sf::RenderWindow &window, sf::RectangleShape up, sf::RectangleShape down, sf::RectangleShape right, sf::RectangleShape left)
{
    window.draw(body);
    window.draw(up);
    window.draw(down);
    window.draw(right);
    window.draw(left);
}

void Bomb::DrawUp(sf::RenderWindow& window, sf::RectangleShape up)
{
    window.draw(body);
    window.draw(up);
}

void Bomb::DrawDown(sf::RenderWindow& window, sf::RectangleShape down)
{
    window.draw(body);
    window.draw(down);
}

void Bomb::DrawRight(sf::RenderWindow& window, sf::RectangleShape right)
{
    window.draw(body);
    window.draw(right);
}

void Bomb::DrawLeft(sf::RenderWindow& window, sf::RectangleShape left)
{
    window.draw(body);
    window.draw(left);
}
