/*
  Item.h

  GAM100 Prototype2
  Fall 2019

 Jaemin Lee wrote this all
 Byeongjun Kim
 Sangjin Lee

  All content © 2019 DigiPen (USA) Corporation, all rights reserved.
*/
#pragma once
#include "System.h"

class ItemType : virtual public SystemType
{
private:

public:
    ItemType(float positionX, float positionY, float radius);
    void Draw();
};
