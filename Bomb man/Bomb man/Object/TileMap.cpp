//
//  TileMap.cpp
//  Bomb man
//
//  Created by 涂譽寶 on 2020/1/3.
//  Copyright © 2020 張文毓. All rights reserved.
//

#include "TileMap.hpp"

TileMap::TileMap(unsigned int WINDOW_WIDTH, unsigned int WINDOW_HEIGHT)
{
    // 2是草皮
    tiles = new int[(WINDOW_WIDTH / 32) * (WINDOW_HEIGHT / 32)];
    for(int i = 0; i < WINDOW_WIDTH / 32 * WINDOW_HEIGHT / 32; i++)
        tiles[i] = 2;
    
    wallsPosition = new int[(WINDOW_WIDTH / 32) * (WINDOW_HEIGHT / 32)];
    
    int level[] =
    {
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1,3,3,3,1,1,3,3,3,3,1,1,3,3,3,1,1,3,3,3,1,1,3,3,1,
        1,3,3,3,1,1,3,3,3,3,1,1,3,3,3,1,1,3,3,3,1,1,3,3,1,
        1,3,3,3,2,2,3,3,3,3,2,2,3,3,3,2,2,3,3,3,2,2,3,3,1,
        1,3,3,3,2,2,3,3,3,3,2,2,3,3,3,2,2,3,3,3,2,2,3,3,1,
        1,3,3,3,2,2,3,3,3,3,2,2,3,3,3,2,2,3,3,3,2,2,3,3,1,
        1,3,3,3,1,1,3,3,3,3,1,1,3,3,3,1,1,3,3,3,1,1,3,3,1,
        1,3,3,3,1,1,3,3,3,3,1,1,3,3,3,1,1,3,3,3,1,1,3,3,1,
        1,3,3,3,2,2,3,3,3,3,2,2,3,3,3,2,2,3,3,3,2,2,3,3,1,
        1,3,3,3,2,2,3,3,3,3,2,2,3,3,3,2,2,3,3,3,2,2,3,3,1,
        1,3,3,3,1,1,3,3,3,3,1,1,3,3,3,1,1,3,3,3,1,1,3,3,1,
        1,3,3,3,1,1,3,3,3,3,1,1,3,3,3,1,1,3,3,3,1,1,3,3,1,
        1,3,3,3,2,2,3,3,3,3,2,2,3,3,3,2,2,3,3,3,2,2,3,3,1,
        1,3,3,3,2,2,3,3,3,3,2,2,3,3,3,2,2,3,3,3,2,2,3,3,1,
        1,3,3,3,1,1,3,3,3,3,1,1,3,3,3,1,1,3,3,3,1,1,3,3,1,
        1,3,3,3,1,1,3,3,3,3,1,1,3,3,3,1,1,3,3,3,1,1,3,3,1,
        1,3,3,3,2,2,3,3,3,3,2,2,3,3,3,2,2,3,3,3,2,2,3,3,1,
        1,3,3,3,2,2,3,3,3,3,2,2,3,3,3,2,2,3,3,3,2,2,3,3,1,
        1,3,3,3,1,1,3,3,3,3,1,1,3,3,3,1,1,3,3,3,1,1,3,3,1,
        1,3,3,3,1,1,3,3,3,3,1,1,3,3,3,1,1,3,3,3,1,1,3,3,1,
        1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,
        1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
    };
    
    // tileMap文字檔tile的index不知道為什麼跑掉
    for(int i = 0; i < (WINDOW_WIDTH / 32) * (WINDOW_HEIGHT / 32); i++)
        level[i] -= 1;
    
    wallCnt_breakable   = 0;
    wallCnt_unbreakable = 0;
    for(int i = 0; i < (WINDOW_WIDTH / 32) * (WINDOW_HEIGHT / 32); i++)
    {
        wallsPosition[i] = level[i];
        if(level[i] == wall_breakable)
            wallCnt_breakable++;
        else if(level[i] == wall_unbreakable)
            wallCnt_unbreakable++;
    }
}

// public function
bool TileMap::load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height)
{
    // tileSize 每片瓦 幾＊幾
    
    // load the tileset texture
      if (!m_tileset.loadFromFile("/Users/lijicheng/Downloads/程式設計/PD_期末/Final Demo/Bomb man/Bomb man/images/merge_tileset.jpg"))
      {
          std::cout << "TileMap fail on load" << std::endl;
          return false;
      }


      // resize the vertex array to fit the level size
      m_vertices.setPrimitiveType(sf::Quads);
      m_vertices.resize(width * height * 4);

      // populate the vertex array, with one quad per tile
      for (unsigned int i = 0; i < width; ++i)
          for (unsigned int j = 0; j < height; ++j)
          {
              // get the current tile number
              int tileNumber = tiles[i + j * width]; // 第幾片瓦

              // find its position in the tileset texture
              int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
              int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

              // get a pointer to the current tile's quad
              sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

              // define its 4 corners
              quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
              quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
              quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
              quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

              // define its 4 texture coordinates
              quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
              quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
              quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
              quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
          }

      return true;
}
