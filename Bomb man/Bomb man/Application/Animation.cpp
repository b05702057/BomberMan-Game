//
//  Animation.cpp
//  Bomb man
//
//  Created by 張文毓 on 2019/12/21.
//  Copyright © 2019 張文毓. All rights reserved.
//
#include <iostream>
#include "Animation.hpp"

//Constructor / Destructor
Animation::Animation()
{
    
}
Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
{
    this -> imageCount = imageCount;
    this -> switchTime = switchTime;
    
    totalTime = 0.0f;
    currentImage.x = 0;
    
    uvRect.width = texture ->getSize().x / float(imageCount.x);
    uvRect.height= texture ->getSize().y / float(imageCount.y);
}
Animation::~Animation()
{
    
}


//Functions

void Animation::reset()
{
    currentImage.x = 0;
    totalTime = 0.0f;
}


void Animation::UpdateBomb(int row, float deltaTime, bool &ifExplode)
{
   if(!ifExplode)
   {
       
        currentImage.y = row;
        totalTime += deltaTime;
        if(totalTime >= switchTime)
        {
            totalTime -= switchTime;
            currentImage.x ++;
            if(currentImage.x >= imageCount.x)
            {
                ifExplode = true;
                currentImage.y = 4;
                totalTime = 0.0f;
            }
        }
       
    }
    uvRect.left = currentImage.x * uvRect.width;
    uvRect.top = currentImage.y * uvRect.height;
}

void Animation::UpdateExplosion(int column,float deltaTime ,bool& Exploded)
{
    static int count = 0;
    if(!Exploded)
    {
        currentImage.x = column;
        totalTime += deltaTime;
        if(totalTime >= switchTime)
        {
            totalTime -= switchTime;
            currentImage.y --;
            count++;
            
            if(currentImage.y < 1)
            {
                Exploded = true;
                totalTime = 0.0f;
                
            }
        }
    }
    
    
    uvRect.left = currentImage.x * uvRect.width;
    uvRect.top = currentImage.y * uvRect.height;
    
}


bool Animation::UpdatePlayer(int row, float deltaTime)
{
    currentImage.y = row;
    totalTime += deltaTime;
    if(totalTime >= switchTime)
    {
        totalTime -= switchTime;
        currentImage.x ++;
        if(currentImage.x >= imageCount.x && row != 5)
        {
            currentImage.x = 0;
        }
        else if(currentImage.x >= imageCount.x && row == 5)
        {
            return true;
        }
        
    }
    uvRect.top = currentImage.y * uvRect.height;
    
    
    uvRect.left = currentImage.x * uvRect.width;
    return false;
}



