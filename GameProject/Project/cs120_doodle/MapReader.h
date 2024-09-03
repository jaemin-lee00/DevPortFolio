/*
  MapReader.h

  GAM100 Prototype2
  Fall 2019
  
 Jaemin Lee
 Byeongjun Kim wrote this all
 Sangjin Lee

  All content © 2019 DigiPen (USA) Corporation, all rights reserved.
*/

#pragma once
#include <vector>

namespace MAP_READING
{
    constexpr unsigned BLOCK_GREEN   = 0x00FF00FF;
    constexpr unsigned LADDER_SKY    = 0x00FFFFFF;
    constexpr unsigned WALL_YELLOW   = 0xFFFF00FF;
    constexpr unsigned WALL_RED      = 0xFF0000FF;
    constexpr unsigned WALL_PURPLE   = 0xFF00FFFF;
    constexpr unsigned WALL_BLACK    = 0x000000FF;
    constexpr unsigned CHECKER_COLOR = 0x999999ff;
    constexpr unsigned WALL_GREY = 0x888888ff;

    void Map_Load();
    struct Map
    {
        int              width  = 0;
        int              height = 0;
        std::vector<unsigned> tiles{};
    };

	   extern Map map;
}

