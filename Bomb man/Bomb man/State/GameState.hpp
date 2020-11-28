//

#ifndef GameState_hpp
#define GameState_hpp

#include "EndState.hpp"


class GameState:
    public State
{
public:
    GameState(sf::RenderWindow* window,std::stack<State*> * states);
    virtual ~GameState();
    
    //Functions
    
    void EndingState();
    void UpdateInput(const float& deltatime);
    void CheckTimeOut();
    void CheckWhoWins();
    void Update(const float& deltatime);
    void Render(sf::RenderTarget* target = nullptr);
    void DrawPlayer();
    void UpdatePlayer(float deltatime);
    void ResetBomb();
    void CheckCollideWithBomb__Player1();
    void CheckCollideWithBomb__Player2();
    
//    void CheckCollideWithBomb_Wall_Unbreakable(Player& Bombsetter);
//    void CheckDestroyed_Wall_Breakable(Player& Bombsetter);
    
    void LoadWalls(Wall* walls[], sf::Texture* texture, const int* level, const int tileSelected, const int WINDOW_WIDTH, const int WINDOW_HEIGHT, bool isBreakable, bool isBroken);
    
    void CheckCollideWithWall_Breakable();
    void CheckCollideWithWall_Unbreakable();
    
    void DrawMap();
    void DrawWalls();
    void DrawBoard();
    void DrawGameClock();
    void DrawBomb(float deltatime);
    void CheckDestroyed( Player& BombSetter);
    
    void CheckUsedShoes(Item& item);
    void CheckUsedBag(Item& item);
    void CheckUsedPower(Item& item);

private:
    Player player1;
    Player player2;
    Item shoes1;
    Item shoes2;
    Item shoes3;
    Item shoes4;
    Item bag1;
    Item bag2;
    Item bag3;
    Item bag4;
    Item power1;
    Item power2;
    Item power3;
    Item power4;
    
    int* grass;
    int* wallMap; // level
    
    TileMap map;
    int breakableWallsCnt;
    int unbreakableWallsCnt;
    Wall* breakableWalls[625]; // 先這樣
    Wall* unbreakableWalls[625];
    
    Board board;
    GameClock gameClock; // 遊戲開始的計時器
    
//public:
//    friend void Update(float deltaTime,sf::RenderWindow &window, int strongness, int* level, Wall* breakableWalls[]);
};

#endif /* GameState_hpp */
