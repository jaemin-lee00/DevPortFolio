/*
  Global.h

  GAM100 Prototype2
  Fall 2019
  
 Jaemin Lee wrote the initial struct, the initial_value, and external class about object
 Byeongjun Kim wrote about map, window system, game statement and color
 Sangjin Lee

  All content © 2019 DigiPen (USA) Corporation, all rights reserved.
*/

#pragma once
#include <Windows.h>
#include <WinUser.h>
#include "Map.h"
#include "Player.h"
#include "Enum.h"
#include "Block.h"
#include "Ladder.h"
#include "MapReader.h"
#include "vector2D.hpp"
#include "Item.h"
#include <vector>

#include <iostream>
using std::cout;

namespace GLOBAL
{
    //it's about our custom Type
    extern MapType        Map;
    extern PlayerType     Player;
    extern PlayerType Player_Collision_Helper;
    extern GAME_STATEMENT PageNum;
    extern Vector_2D                    velocity;
    extern Vector_2D                    gravity;
    extern Vector_2D                    acceleration;
    extern std::vector<BlockType*>		BlockArray;
    extern std::vector<LadderType*>		LadderArray;
    extern std::vector<BlockType*>		WallArray;
    extern std::vector<BlockType*>      LineArray;
    extern std::vector<ItemType*>       ItemArray;
    extern std::vector<LadderType*>     StageCheckerArray;

    //it's about window system
    extern HWND Console;
    extern HWND GameWindow;

    //it's about Position and Volume
    extern int  NewPlaceX;
    extern int  NewPlaceY;
    extern int NewWidth;
    extern int NewHeight;
    extern int  MaxWidth;
    extern int  MaxHeight;

    // it's about Map
    extern int INIT_MAP_POS_X;
    constexpr int INIT_MAP_POS_Y = 0;

    constexpr int INIT_MAP_WIDTH = 300;
    constexpr int INIT_MAP_HEIGHT = 300;

    constexpr float INIT_MAP_SIZE = 0;
	

    // it's about player
    constexpr float INIT_PLAYER_RADIUS = 15.0f;
    constexpr float    INIT_PLAYER_SPEED = 3.0f;
    constexpr float INIT_PLAYER_POS_X  = INIT_MAP_WIDTH / 2 - INIT_PLAYER_RADIUS * 3;
    constexpr float INIT_PLAYER_POS_Y  = 0;
    constexpr float INIT_GAP_PLAYER_BLOCK      = 0.5;


    //it's about distance
    constexpr float INIT_PLAYER_HOLD_DISTANCE = 0;
    constexpr float INIT_PLAYER_HOLD_LADDER   = 0;
    constexpr float INIT_BLOCK_COMBINE_DISTANCE = 1;


    // it's about color

    constexpr HexColor PLAYER_COLOR     = 0xFF00FFFF;
    constexpr HexColor BACKGROUND_COLOR = 0xFFFFFFFF;
    constexpr HexColor BLOCK_COLOR      = 0x00FF00FF;
    constexpr HexColor LADDER_COLOR     = 0xFF0000FF;
    constexpr HexColor WALL_COLOR       = 0x0000FFFF;
    constexpr HexColor INVISIBLE_COLOR  = 0xFFFFFFFF;

	constexpr HexColor LINE_YELLOW   = 0xFFFF00FF;
    constexpr HexColor LINE_GREY     = 0x888888ff;
}
