/*
  Ladder.cpp

  GAM100 Prototype2
  Fall 2019
  
 Jaemin Lee wrote this all
 Byeongjun Kim
 Sangjin Lee 

  All content © 2019 DigiPen (USA) Corporation, all rights reserved.
*/
#include "Ladder.h"
#include "Global.h"
#include "Enum.h"
#include <doodle/drawing.hpp>

LadderType::LadderType(float positionX, float positionY, float width, float height, doodle::HexColor ladderColor)
    : SystemType(positionX, positionY, width, height, 0, OBJECT_KIND::LADDER), aLadderColor(ladderColor){};


void LadderType::Draw()
{
    doodle::set_rectangle_mode(doodle::RectMode::Center);
    doodle::set_fill_color(aLadderColor);
    doodle::draw_rectangle(aPosX, aPosY, aWidth, aHeight);
}

