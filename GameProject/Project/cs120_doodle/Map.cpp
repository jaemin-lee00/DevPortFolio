/*
  Map.cpp

  GAM100 Prototype2
  Fall 2019
  
 Jaemin Lee
 Byeongjun Kim wrote this all
 Sangjin Lee

  All content © 2019 DigiPen (USA) Corporation, all rights reserved.
*/
#include "Map.h"
#include "Global.h"


using GLOBAL::Map;
using GLOBAL::PageNum;
using GLOBAL::Player;


// To fit the blocks place(X)
void FitMapX(float value)
{
    const int BlockSize = GLOBAL::BlockArray.size();
    for (int i = 0; i < BlockSize; i++)
    {
        GLOBAL::BlockArray[i]->AddPositionX(value);
    }
    const int LadderSize = GLOBAL::LadderArray.size();
    for (int i = 0; i < LadderSize; i++)
    {
        GLOBAL::LadderArray[i]->AddPositionX(value);
    }
    const int WallSize = GLOBAL::WallArray.size();
    for (int i = 0; i < WallSize; i++)
    {
        GLOBAL::WallArray[i]->AddPositionX(value);
    }
    const int LineSize = GLOBAL::LineArray.size();
    for (int i = 0; i < LineSize; i++)
    {
        GLOBAL::LineArray[i]->AddPositionX(value);
    }
    const int ItemSize = GLOBAL::ItemArray.size();
    for (int i = 0; i < ItemSize; i++)
    {
        GLOBAL::ItemArray[i]->AddPositionX(value);
    }
    const int CheckerSize = GLOBAL::StageCheckerArray.size();
    for (int i = 0; i < CheckerSize; i++)
    {
        GLOBAL::StageCheckerArray[i]->AddPositionX(value);
    }
}

// To fit the blocks place(Y)
void FitMapY(float value)
{
    const int BlockSize = GLOBAL::BlockArray.size();
    for (int i = 0; i < BlockSize; i++)
    {
        GLOBAL::BlockArray[i]->AddPositionY(value);
    }
    const int LadderSize = GLOBAL::LadderArray.size();
    for (int i = 0; i < LadderSize; i++)
    {
        GLOBAL::LadderArray[i]->AddPositionY(value);
    }
    const int LineSize = GLOBAL::LineArray.size();
    for (int i = 0; i < LineSize; i++)
    {
        GLOBAL::LineArray[i]->AddPositionY(value);
    }
    const int WallSize = GLOBAL::WallArray.size();
    for (int i = 0; i < WallSize; i++)
    {
        GLOBAL::WallArray[i]->AddPositionY(value);
    }
    const int ItemSize = GLOBAL::ItemArray.size();
    for (int i = 0; i < ItemSize; i++)
    {
        GLOBAL::ItemArray[i]->AddPositionY(value);
    }
    const int CheckerSize = GLOBAL::StageCheckerArray.size();
    for (int i = 0; i < CheckerSize; i++)
    {
        GLOBAL::StageCheckerArray[i]->AddPositionY(value);
    }
}

// When the phase 1, to make the map to follow the player.
void MapType::MapFollow()
{
    if (Player.GetPositionX() < -Width / 2 + Player.GetRadius() / 2)
    {
        GLOBAL::NewPlaceX -= Player.GetSpeed();
        Player.AddPositionX(Player.GetSpeed());
        FitMapX(Player.GetSpeed() * 1);
    }
    if (Player.GetPositionX() > Width / 2 - Player.GetRadius() / 2)
    {
        GLOBAL::NewPlaceX += Player.GetSpeed();
        Player.AddPositionX(-Player.GetSpeed());
        FitMapX(Player.GetSpeed() * -1);
    }
    if (GLOBAL::NewPlaceX < 0)
    {
        GLOBAL::NewPlaceX = 0;
        FitMapX(Player.GetSpeed() * -1);
    }

    if (GLOBAL::NewPlaceX > GLOBAL::MaxWidth / 2)
    {
        GLOBAL::NewPlaceX = GLOBAL::MaxWidth / 2;
        FitMapX(Player.GetSpeed() * 1);
    }

    ::SetWindowPos(GLOBAL::GameWindow, 0, GLOBAL::NewPlaceX, GLOBAL::NewPlaceY, GLOBAL::NewWidth, GLOBAL::NewHeight,
                   SWP_NOOWNERZORDER | SWP_NOZORDER);
}

// When the phase 4, to make the map to follow the player.
// But at this time, the screen's size is fixed
void MapType::MapFollow2()
{
    if (Player.GetPositionX() < Player.GetRadius() / 2)
    {
        GLOBAL::NewPlaceX -= Player.GetSpeed();
        Player.AddPositionX(Player.GetSpeed());
        FitMapX(Player.GetSpeed() * 1);
    }
    if (Player.GetPositionX() > -Player.GetRadius() / 2)
    {
        GLOBAL::NewPlaceX += Player.GetSpeed();
        Player.AddPositionX(-Player.GetSpeed());
        FitMapX(Player.GetSpeed() * -1);
    }
    if (Player.GetPositionY() < Player.GetRadius() / 2)
    {
        GLOBAL::NewPlaceY += Player.GetSpeed();
        Player.AddPositionY(Player.GetSpeed());
        FitMapY(Player.GetSpeed() * 1);
    }
    if (Player.GetPositionY() > -Player.GetRadius() / 2)
    {
        GLOBAL::NewPlaceY -= Player.GetSpeed();
        Player.AddPositionY(-Player.GetSpeed());
        FitMapY(Player.GetSpeed() * -1);
    }

    ::SetWindowPos(GLOBAL::GameWindow, 0, GLOBAL::NewPlaceX, GLOBAL::NewPlaceY, GLOBAL::NewWidth, GLOBAL::NewHeight,
                   SWP_NOOWNERZORDER | SWP_NOZORDER);
}

// When the phase 2, to make the map to extend by player.
void MapType::MapExtend()
{
    if (Player.GetPositionX() > Width / 2 - Player.GetRadius() / 2)
    {
        GLOBAL::NewWidth += Player.GetSpeed();
        Player.AddPositionX(-Player.GetSpeed() / 2);
        FitMapX(-Player.GetSpeed() / 2);
        if (GLOBAL::NewWidth > GLOBAL::MaxWidth)
        {
            GLOBAL::NewWidth = GLOBAL::MaxWidth;
            FitMapX(Player.GetSpeed() / 2);
        }
    }

    if (Player.GetPositionY() < -Height / 2 + Player.GetRadius() / 2)
    {
        GLOBAL::NewHeight += Player.GetSpeed();
        Player.AddPositionY(Player.GetSpeed() / 2);
        FitMapY(Player.GetSpeed() / 2);

        if (GLOBAL::NewHeight > GLOBAL::MaxHeight)
        {
            GLOBAL::NewHeight = GLOBAL::MaxHeight;
            FitMapY(-Player.GetSpeed() / 2);
        }
    }

    ::SetWindowPos(GLOBAL::GameWindow, 0, GLOBAL::NewPlaceX, GLOBAL::NewPlaceY, GLOBAL::NewWidth, GLOBAL::NewHeight,
                   SWP_NOOWNERZORDER | SWP_NOZORDER);
}

// When the game end.
void MapType::MapEnd()
{
        GLOBAL::NewPlaceX = 0;
        GLOBAL::NewPlaceY = 0;

        GLOBAL::NewWidth = GetSystemMetrics(SM_CXFULLSCREEN);
        GLOBAL::NewHeight = GetSystemMetrics(SM_CYFULLSCREEN);

        ::SetWindowPos(GLOBAL::GameWindow, 0, GLOBAL::NewPlaceX, GLOBAL::NewPlaceY, GLOBAL::NewWidth, GLOBAL::NewHeight,
                       SWP_NOOWNERZORDER | SWP_NOZORDER);

		//clear_background(HexColor{GLOBAL::BACKGROUND_COLOR});

        set_fill_color(HexColor(0x87CEEBFF));
        set_font_size(35);
        draw_text("Made by Team Dungeon_Maker\n\n", -Width / 2, Height / 2.5);
        set_fill_color(255);
        set_font_size(25);
        draw_text("Jaemin Lee        : Physics programmer, main programmer\n\n Byeongjun Kim : "
                  "Play Programmer, Game Management\n\n Sangjin Lee       : Producer, Designer, Sub Programmer",
                  -Width / 2, Height / 3);
        set_font_size(60);
        set_fill_color(HexColor(0xFFFF00FF));
        draw_text("Congratulation~!", -Width / 4, 0);
        set_font_size(20);
        set_fill_color(255);
        draw_text("Press ESC to exit.", -Width / 8, -80);
}
