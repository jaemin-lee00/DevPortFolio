/*
  Varialbe.h

  GAM100 Prototype2
  Fall 2019
  
 Jaemin Lee wrote class about object
 Byeongjun Kim wrote the initial struct and about map, window system, game statement and color
 Sangjin Lee

  All content © 2019 DigiPen (USA) Corporation, all rights reserved.
*/

#pragma once
#include <Windows.h>
#include "Global.h"
#include <vector>


namespace GLOBAL
{
    //it's about our custom Type
    MapType        Map;
    PlayerType     Player{INIT_PLAYER_POS_X, INIT_PLAYER_POS_Y, INIT_PLAYER_RADIUS, INIT_PLAYER_SPEED};
    PlayerType Player_Collision_Helper{INIT_PLAYER_POS_X, INIT_PLAYER_POS_Y - INIT_GAP_PLAYER_BLOCK, INIT_PLAYER_RADIUS,
                                       INIT_PLAYER_SPEED};
   
    GAME_STATEMENT PageNum;
     Vector_2D            velocity;
     Vector_2D            gravity;
     Vector_2D            acceleration;
    std::vector<BlockType*>		BlockArray;
    std::vector<LadderType*>	LadderArray;
    std::vector<BlockType*>     WallArray;
	std::vector<BlockType*>		LineArray;
    std::vector<ItemType*>      ItemArray;
    std::vector<LadderType*> StageCheckerArray;


    //it's about window system
    std::string    GameName = "DunMe";
    HWND           GameWindow;
    HWND           Console = GetConsoleWindow();

    //it's about Position and Volume
    int            NewWidth;
    int            NewHeight;
    int            NewPlaceX;
    int            NewPlaceY;
    int            MaxWidth;
    int            MaxHeight;


    int INIT_MAP_POS_X = GetSystemMetrics(SM_CXSCREEN) / 3 - GLOBAL::INIT_MAP_WIDTH;
}

