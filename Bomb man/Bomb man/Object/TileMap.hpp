//
//  TileMap.hpp
//  Bomb man
//
//  Created by 涂譽寶 on 2020/1/3.
//  Copyright © 2020 張文毓. All rights reserved.
//
#ifndef TileMap_hpp
#define TileMap_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <iostream>

class TileMap : public sf::Drawable, public sf::Transformable
{
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const // virtual void can only be specified inside the class definition
    {
        // apply the transform
        states.transform *= getTransform();

        // apply the tileset texture
        states.texture = &m_tileset;

        // draw the vertex array
        target.draw(m_vertices, states);
    }
    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
    int* tiles; // 背景草地圖
    
    int* wallsPosition; // 可炸和不可炸牆壁的位置圖
    const int wall_breakable    = 1;
    const int wall_unbreakable  = 0;
    int wallCnt_breakable;
    int wallCnt_unbreakable;
    
public:
    TileMap(unsigned int WINDOW_WIDTH, unsigned int WINDOW_HEIGHT);
    
    bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);
    
    int* get_wallsPosition() { return wallsPosition; }
    int get_wallCnt_breakable() { return wallCnt_breakable; }
    int get_wallCnt_unbreakable() { return wallCnt_unbreakable; }
};


#endif /* TileMap_hpp */
