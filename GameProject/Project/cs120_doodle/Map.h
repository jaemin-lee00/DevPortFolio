/*
  Map.h

  GAM100 Prototype2
  Fall 2019

 Jaemin Lee
 Byeongjun Kim wrote this all
 Sangjin Lee

  All content © 2019 DigiPen (USA) Corporation, all rights reserved.
*/
#pragma once
#include "Enum.h"
#include <doodle/doodle.hpp>
using namespace doodle;

class MapType
{
private:
    float aMapPosX = -(Width / 2.0f) + 50.0f;
    float aMapPosY = 0;
    float MapSize{300.0f}; 

public:
    void MapFollow();
    void MapExtend();
    void MapFollow2();
    void MapEnd();
    void SetExtendAble(const DIRECTION& dir, const bool& TorF);
};

void FitMapX(float multi);
void FitMapY(float multi);
