/*
  Item.cpp

  GAM100 Prototype2
  Fall 2019
  
 Jaemin Lee wrote this all
 Byeongjun Kim
 Sangjin Lee 

  All content © 2019 DigiPen (USA) Corporation, all rights reserved.
*/
#include "Item.h"
#include <doodle/drawing.hpp>
#include "Global.h"

ItemType::ItemType(float positionX, float positionY, float radius)
    : SystemType(positionX, positionY, radius){}

void ItemType::Draw()
{
    doodle::set_rectangle_mode(doodle::RectMode::Center);
    doodle::set_fill_color(GLOBAL::LADDER_COLOR);
    doodle::draw_ellipse(aPosX, aPosY, aRadius, aRadius);
}



