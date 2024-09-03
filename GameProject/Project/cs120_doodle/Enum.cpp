/*
  Enum.cpp

  GAM100 Prototype2
  Fall 2019
  
 Jaemin Lee
 Byeongjun Kim wrote this all
 Sangjin Lee

  All content © 2019 DigiPen (USA) Corporation, all rights reserved.
*/
#include "Enum.h"
#include "Global.h"
#include "iostream"

// To upper the phase.
// When it detect the phase update, it changes some settings
void operator++(GAME_STATEMENT& state)
{
    state = static_cast<GAME_STATEMENT>((static_cast<int>(state)) + 1);
    std::cout << "Now Game Statement is "<< (static_cast<int>(state)) << '\n';
    float tempX;
    float tempY;
    switch (state)
    {
        case GAME_STATEMENT::doodle_1phase: break;
        case GAME_STATEMENT::doodle_2phase:
            FitMapX(GLOBAL::NewPlaceX);
            GLOBAL::Player.AddPositionX(GLOBAL::NewPlaceX);
            GLOBAL::NewPlaceX = 0;
            GLOBAL::NewPlaceY = 0;
            GLOBAL::Player.SetMoveAble(DIRECTION::UP, true);
            GLOBAL::Player.SetMoveAble(DIRECTION::DOWN, true);
            break;
        case GAME_STATEMENT::doodle_3phase: GLOBAL::MaxWidth = GetSystemMetrics(SM_CXSCREEN) / 3 * 2;
            GLOBAL::Player.SetMoveAble(DIRECTION::UP, false);
            GLOBAL::Player.SetMoveAble(DIRECTION::DOWN, false);
			break;
        case GAME_STATEMENT::doodle_4phase:
            GLOBAL::MaxWidth = GetSystemMetrics(SM_CXSCREEN);
            GLOBAL::Player.SetMoveAble(DIRECTION::UP, true);
            GLOBAL::Player.SetMoveAble(DIRECTION::DOWN, true);
            tempX = GLOBAL::Player.GetPositionX();
            tempY = GLOBAL::Player.GetPositionY();
            GLOBAL::Player.AddPositionX(-GLOBAL::Player.GetPositionX());
            GLOBAL::Player.AddPositionY(-GLOBAL::Player.GetPositionY());
            FitMapX(-tempX);
            FitMapY(-tempY);
            GLOBAL::NewPlaceX = tempX + GLOBAL::NewWidth / 2 - phase4_screenX / 2;
            GLOBAL::NewPlaceY = -tempY + GLOBAL::NewHeight / 2 - phase4_screenY / 2;
            GLOBAL::NewWidth  = phase4_screenX;
            GLOBAL::NewHeight = phase4_screenY;
			break; 
        case GAME_STATEMENT::doodle_5phase: break;
    }
}