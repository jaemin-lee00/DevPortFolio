/*
  Ladder.h

  GAM100 Prototype2
  Fall 2019

 Jaemin Lee wrote this all
 Byeongjun Kim
 Sangjin Lee

  All content © 2019 DigiPen (USA) Corporation, all rights reserved.
*/
#pragma once
#include "System.h"
#include <doodle/color.hpp>


class LadderType : virtual public SystemType
{
private:
    doodle::HexColor aLadderColor;

public:

    LadderType(float positionX, float positionY, float width, float height, doodle::HexColor ladderColor);


    void Draw();
};