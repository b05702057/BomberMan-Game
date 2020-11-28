//
//  GameState.cpp
//  Bomb man
//
//  Created by 張文毓 on 2019/12/27.
//  Copyright © 2019 張文毓. All rights reserved.
//


#include "GameState.hpp"
// Constructor/Destructor
GameState::GameState(sf::RenderWindow* window,std::stack<State*> * states):
State(window, states),
player1(&player1Texture,&bombTexture, sf::Vector2u(8,6),0.3f,200.0f, this -> P1MoveSet, 1),
player2(&player2Texture,&bombTexture, sf::Vector2u(8,6),0.3f,200.0f, this -> P2MoveSet, 2),
shoes1(&shoesTexture, sf::Vector2f(31.5f, 31.5f), sf::Vector2f(xarray[chosenXindex[0]], yarray[chosenYindex[0]])),
shoes2(&shoesTexture, sf::Vector2f(31.5f, 31.5f), sf::Vector2f(xarray[chosenXindex[1]], yarray[chosenYindex[1]])),
shoes3(&shoesTexture, sf::Vector2f(31.5f, 31.5f), sf::Vector2f(xarray[chosenXindex[2]], yarray[chosenYindex[2]])),
shoes4(&shoesTexture, sf::Vector2f(31.5f, 31.5f), sf::Vector2f(xarray[chosenXindex[3]], yarray[chosenYindex[3]])),
bag1(&bagTexture, sf::Vector2f(31.5f, 31.5f), sf::Vector2f(xarray[chosenXindex[4]], yarray[chosenYindex[4]])),
bag2(&bagTexture, sf::Vector2f(31.5f, 31.5f), sf::Vector2f(xarray[chosenXindex[5]], yarray[chosenYindex[5]])),
bag3(&bagTexture, sf::Vector2f(31.5f, 31.5f), sf::Vector2f(xarray[chosenXindex[6]], yarray[chosenYindex[6]])),
bag4(&bagTexture, sf::Vector2f(31.5f, 31.5f), sf::Vector2f(xarray[chosenXindex[7]], yarray[chosenYindex[7]])),
power1(&powerTexture, sf::Vector2f(31.5f, 31.5f), sf::Vector2f(xarray[chosenXindex[8]], yarray[chosenYindex[8]])),
power2(&powerTexture, sf::Vector2f(31.5f, 31.5f), sf::Vector2f(xarray[chosenXindex[9]], yarray[chosenYindex[9]])),
power3(&powerTexture, sf::Vector2f(31.5f, 31.5f), sf::Vector2f(xarray[chosenXindex[10]], yarray[chosenYindex[10]])),
power4(&powerTexture, sf::Vector2f(31.5f, 31.5f), sf::Vector2f(xarray[chosenXindex[11]], yarray[chosenYindex[11]])),

map(800, 800),
board(&boardTexture, sf::Vector2f(800.0, 96.0), sf::Vector2f(400.0, 48.0), &heartTexture)
{
    grass = new int[25*25];     // 背景草地圖
    wallMap = new int[25*25];   // 牆壁位置圖
    for(int i = 0; i < 25*25; i++)
        grass[i] = 2;
    
    map.load("tileset.png", sf::Vector2u(32, 32), grass, 25, 25);
    
    for(int i = 0; i < 25*25; i++)
        wallMap[i] = map.get_wallsPosition()[i]; // 這樣可以知道原始的石牆在哪，wallMap可以在遊戲中變動

    const int wall_breakable_num    = 1;
    const int wall_unbreakable_num  = 0;
    
    breakableWallsCnt = map.get_wallCnt_breakable();
    unbreakableWallsCnt = map.get_wallCnt_unbreakable();
    
    LoadWalls(this->breakableWalls, &wallTexture_breakable, this->wallMap, wall_breakable_num, 800, 800, true, false);
    LoadWalls(this->unbreakableWalls, &wallTexture_unbreakable, this->wallMap, wall_unbreakable_num, 800, 800, false, false);
    gameMusic.play();
    
    
}
 GameState::~GameState()
{
}
   
   //Functions
void GameState::UpdateInput(const float& deltatime)
{
    return this -> CheckforQuit();
}

void GameState::EndingState()
{
}

void GameState::Update(const float& deltatime)
{
    this -> UpdateInput(deltatime);
    this -> UpdateMousePosition();
    this -> CheckTimeOut();
    if(gameClock.GetCntDown() >= 0)
        this -> CheckWhoWins();
    
    gameClock.CntTime(); // 更新遊戲時鐘
    DrawMap();
    CheckUsedShoes(shoes1);
    CheckUsedShoes(shoes2);
    CheckUsedShoes(shoes3);
    CheckUsedShoes(shoes4);
    CheckUsedBag(bag1);
    CheckUsedBag(bag2);
    CheckUsedBag(bag3);
    CheckUsedBag(bag4);
    CheckUsedPower(power1);
    CheckUsedPower(power2);
    CheckUsedPower(power3);
    CheckUsedPower(power4);
    DrawWalls();
    UpdatePlayer(deltatime);
    CheckCollideWithBomb__Player1();
    CheckCollideWithBomb__Player2();
    CheckCollideWithWall_Breakable();
    CheckCollideWithWall_Unbreakable();
    
//    CheckCollideWithBomb_Wall_Breakable();
    
    DrawBomb(deltatime);
//    CheckDestroyed_Wall_Breakable(player1);
//    CheckDestroyed_Wall_Breakable(player2);
    CheckDestroyed(player1);
    CheckDestroyed(player2);
    ResetBomb();
//    board.Draw_heart(this->window, player1.lives, player2.lives);
    
}
void GameState::CheckWhoWins()
{
    if(player1.GetLives() == 0 && player1.getIfAnimeDone())
    {
        this -> states -> push(new class EndState(this -> window, this->states, 2));
        gameMusic.stop();
    }
    if(player2.GetLives() == 0 && player2.getIfAnimeDone())
    {
        this -> states -> push(new class EndState(this -> window, this->states, 1));
        gameMusic.stop();
    }
        
}
void GameState::CheckTimeOut()
{
    if(this -> gameClock.GetCntDown() == 0)
    {
        if(player1.GetLives() > player2.GetLives())
        {
            this -> winner = 1;

        }
        else if(player1.GetLives() < player2.GetLives())
        {
            this -> winner = 2;
            
        }
        else
        {
            this -> winner = 3;
        }
        
        
    }
    else if (this -> gameClock.GetCntDown() == -3)
    {
        this -> states -> push(new class EndState(this -> window, this->states, this -> winner));
        gameMusic.stop();
    }
        
}
void GameState::Render(sf::RenderTarget* target)
{
//    DrawMap(); // 沒有出來
//    DrawWalls();
    DrawBoard();
    
    board.Draw_heart(this->window, player1.lives, player2.lives); // 放在render是不是不會更新？
    DrawGameClock();
    DrawPlayer();
}

void GameState::UpdatePlayer(float deltatime)
{
    //Update Player1
    
    if(this -> player1.checkAlive())
        this -> player1.Update(deltatime);
    else if(!this -> player1.getIfAnimeDone())
        this -> player1.deathAnime(deltatime, this -> window);
    else if(this -> player1.getIfAnimeDone() && this -> player1.GetLives() > 0)
        this -> player1.BackToLive();
        
    //Update Player2
    if(this -> player2.checkAlive())
        this -> player2.Update(deltatime);
    else if(!this -> player2.getIfAnimeDone())
        this -> player2.deathAnime(deltatime, this -> window);
    else if(this -> player2.getIfAnimeDone() && this -> player2.GetLives() > 0)
        this -> player2.BackToLive();
    
}
void GameState::ResetBomb()
{
    for(int i = 0; i < player1.getQuota(); i++)
    {
        if(player1.vbomb[i] -> ifSet)
        {
            //check if bomb is exploded
            if(player1.vbomb[i] -> getIfExploded())
            {
                player1.vbomb[i]->reset();
                player1.numOfBombDroped--;
                player1.setAvailable(i);
            }
            
        }
    }
    for(int i = 0; i < player2.getQuota(); i++)
    {
        if(player2.vbomb[i] -> ifSet)
        {
            //check if bomb is exploded
            if(player2.vbomb[i] -> getIfExploded())
            {
                player2.vbomb[i]->reset();
                player2.numOfBombDroped--;
                player2.setAvailable(i);
            }
            
        }
    }
    
}

void GameState::DrawBomb(float deltatime)
{
    //Player1's Bomb
    for(int i = 0; i < player1.getQuota(); i++)
    {
        if(player1.vbomb[i] -> ifSet)
        {
            //bomb anime
            player1.vbomb[i] -> Update(deltatime, *window, player1.getStrongness(), this->breakableWalls, this->unbreakableWalls, this->breakableWallsCnt, this->unbreakableWallsCnt);
            
//            //check if bomb is exploded
//            if(player1.vbomb[i] -> getIfExploded())
//            {
//                player1.vbomb[i]->reset();
//                player1.numOfBombDroped--;
//                player1.setAvailable(i);
//            }
            
        }
    
        
    }
    //Player2's Bomb
    for(int i = 0; i < player2.getQuota(); i++)
    {
        if(player2.vbomb[i] -> ifSet)
        {
            //bomb anime
            player2.vbomb[i] -> Update(deltatime, *window, player2.getStrongness(), this->breakableWalls, this->unbreakableWalls, this->breakableWallsCnt, this->unbreakableWallsCnt);
            
//            //check if bomb is exploded
//            if(player2.vbomb[i] -> getIfExploded())
//            {
//                player2.vbomb[i]->reset();
//                player2.numOfBombDroped--;
//                player2.setAvailable(i);
//            }
            
        }
    }
}
    
void GameState::CheckDestroyed( Player& BombSetter)
{
    //Destryed Player1
    for(int i = 0; i < BombSetter.getQuota(); i++)
    {
        if(BombSetter.vbomb[i] -> getDuringExplosion())
        {
            Collider tmp = player1.GetCollider();
            if(BombSetter.vbomb[i] -> GetCollider().checkDestroyed(tmp,BombSetter.getStrongness() , BombSetter.vbomb[i] -> rangeOfUp, BombSetter.vbomb[i] -> rangeOfDown, BombSetter.vbomb[i] -> rangeOfRight, BombSetter.vbomb[i] -> rangeOfLeft)&& player1.checkAlive())
            {
                player1.setDeath();
            }
        }
    }
    //Destryed Player2
    for(int i = 0; i < BombSetter.getQuota(); i++)
    {
        if(BombSetter.vbomb[i] -> getDuringExplosion())
        {
            Collider tmp = player2.GetCollider();
            if(BombSetter.vbomb[i] -> GetCollider().checkDestroyed(tmp,BombSetter.getStrongness(), BombSetter.vbomb[i] -> rangeOfUp, BombSetter.vbomb[i] -> rangeOfDown, BombSetter.vbomb[i] -> rangeOfRight, BombSetter.vbomb[i] -> rangeOfLeft)&& player2.checkAlive())
            {
                player2.setDeath();
            }
        }
    }
}
    
void GameState::DrawPlayer()
{
    //Draw Player1
    if(this -> player1.checkAlive())
        this -> player1.Draw(this -> window);
    
    //Draw Player2
    if(this -> player2.checkAlive())
        this -> player2.Draw(this -> window);
    
}

void GameState::CheckCollideWithBomb__Player1()
{
    for(int i = 0; i < player1.getQuota(); i++)
    {
        if(player1.vbomb[i] -> ifSet && !(player1.vbomb[i] -> getIfExploded()))
        {
            Collider tmp = player1.GetCollider();
            bool ifcollide = player1.vbomb[i] ->GetCollider().checkCollision(tmp, 1.0f, player1.vbomb[i] ->ifPlayerleft);
            if(!ifcollide)
                player1.vbomb[i] ->ifPlayerleft = true;
        }
            
    }
}

void GameState::CheckCollideWithBomb__Player2()
{
    for(int i = 0; i < player2.getQuota(); i++)
    {
        if(player2.vbomb[i] -> ifSet && !(player2.vbomb[i] -> getIfExploded()))
        {
            Collider tmp = player2.GetCollider();
            bool ifcollide = player2.vbomb[i] ->GetCollider().checkCollision(tmp, 1.0f, player2.vbomb[i] ->ifPlayerleft);
            if(!ifcollide)
                player2.vbomb[i] ->ifPlayerleft = true;
        }
            
    }
}

//void GameState::CheckDestroyed_Wall_Breakable(Player& Bombsetter)
//{
//    for(int i = 0; i < Bombsetter.quota; i++)
//    {
//        if(Bombsetter.vbomb[i] -> getDuringExplosion())
//        {
//            for(int j = 0; j < breakableWallsCnt; j++)
//            {
//                Collider tmp = breakableWalls[j] -> GetCollider();
//                if(Bombsetter.vbomb[i] -> GetCollider().checkDestroyed(tmp, Bombsetter.getStrongness()))
//                    breakableWalls[j]->change_Wall_condition();
//            }
//        }
//    }
//}


void GameState::DrawWalls()
{
    for(int i = 0; i < map.get_wallCnt_breakable(); i++) // Draw裡就有判斷
        breakableWalls[i]->Draw(this->window);

    for(int i = 0; i < map.get_wallCnt_unbreakable(); i++)
        unbreakableWalls[i]->Draw(this->window);
}

void GameState::DrawMap()
{
    (this->window)->draw(map); // 沒有
}

void GameState::DrawBoard()
{
    this->board.Draw(this->window);
}

void GameState::DrawGameClock()
{
    this->gameClock.Draw(this->window);
}

void GameState::LoadWalls(Wall* walls[], sf::Texture* texture, const int* level, const int tileSelected, const int WINDOW_WIDTH, const int WINDOW_HEIGHT, bool isBreakable, bool isBroken)
{
    int brickAdded = 0;
    int width  = (WINDOW_WIDTH / 32); // 幾格
    int height = (WINDOW_HEIGHT / 32);
    for(int i = 0; i < width; i++)
    {
        float x_axis = 16.0;
        x_axis += static_cast<float>(32.0 * i);
        for(int j = 0; j < height; j++)
        {
            float y_axis = 16.0;
            y_axis += static_cast<float>(32.0 * j);
            if((level[i + j * width]) == tileSelected)
            {
                walls[brickAdded] = new Wall(texture, sf::Vector2f(32.0f, 32.0f), sf::Vector2f(x_axis, y_axis), isBreakable, isBroken);
                brickAdded++;
            }
        }
    }
}


void GameState::CheckCollideWithWall_Breakable()
{
    Collider temp1 = player1.GetCollider(); // to avoid temp error
    Collider temp3 = player2.GetCollider(); // to avoid temp error
    for(int i = 0; i < map.get_wallCnt_breakable(); i++)
    {
        if(!breakableWalls[i]->get_wall_condition()) // 還沒被炸掉才CheckCollision
        {
            breakableWalls[i]->GetCollider().checkCollision(temp1, 1.0f, 1.0f); // 明天問ifPush
            breakableWalls[i]->GetCollider().checkCollision(temp3, 1.0f, 1.0f);
        }
    }

}

void GameState::CheckCollideWithWall_Unbreakable()
{
    Collider temp1 = player1.GetCollider(); // to avoid temp error
    Collider temp3 = player2.GetCollider(); // to avoid temp error
    for(int i = 0; i < map.get_wallCnt_unbreakable(); i++)
    {
        if(!unbreakableWalls[i]->get_wall_condition())
        {
            unbreakableWalls[i]->GetCollider().checkCollision(temp1, 1.0f, 1.0f);
            unbreakableWalls[i]->GetCollider().checkCollision(temp3, 1.0f, 1.0f);
        }
    }
}

void GameState::CheckUsedShoes(Item& item) // 道具是否被使用過
{
    Collider tmp1 = player1.GetCollider();
    Collider tmp2 = player2.GetCollider();
    
    if (item.GetCollider().checkCollision(tmp1, 0.0f, false) == true and item.GetDrawOrNot() == 1) // 玩家一
    {
        item.SetDrawOrNot() ;
        player1.speedUp() ; 
        getItemSound.play();
    }
    if (item.GetCollider().checkCollision(tmp2, 0.0f, false) == true and item.GetDrawOrNot() == 1) // 玩家二
    {
        item.SetDrawOrNot() ;
        player2.speedUp() ;
        getItemSound.play();
    }
    if (item.GetDrawOrNot() == 1)
        item.Draw(this -> window) ;
}

void GameState::CheckUsedBag(Item& item) // 道具是否被使用過
{
    Collider tmp3 = player1.GetCollider();
    Collider tmp4 = player2.GetCollider();
    
    if (item.GetCollider().checkCollision(tmp3, 0.0f, false) == true and item.GetDrawOrNot() == 1) // 玩家一
    {
        item.SetDrawOrNot() ;
        player1.quotaUp() ;
        getItemSound.play();
    }
    if (item.GetCollider().checkCollision(tmp4, 0.0f, false) == true and item.GetDrawOrNot() == 1) // 玩家二
    {
        item.SetDrawOrNot() ;
        player2.quotaUp() ;
        getItemSound.play();
    }
    if (item.GetDrawOrNot() == 1)
        item.Draw(this -> window) ;
}

void GameState::CheckUsedPower(Item& item) // 道具是否被使用過 
{
    Collider tmp3 = player1.GetCollider();
    Collider tmp4 = player2.GetCollider();
    
    if (item.GetCollider().checkCollision(tmp3, 0.0f, false) == true and item.GetDrawOrNot() == 1) // 玩家一
    {
        item.SetDrawOrNot() ;
        player1.strongnessUp() ;
        getItemSound.play();
    }
    if (item.GetCollider().checkCollision(tmp4, 0.0f, false) == true and item.GetDrawOrNot() == 1) // 玩家二
    {
        item.SetDrawOrNot() ;
        player2.strongnessUp() ;
        getItemSound.play();
    }
    if (item.GetDrawOrNot() == 1)
        item.Draw(this -> window) ;
}
