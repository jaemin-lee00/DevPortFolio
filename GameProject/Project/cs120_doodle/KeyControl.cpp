/*
  KeyControl.cpp

  GAM100 Prototype2
  Fall 2019
  
 Jaemin Lee
 Byeongjun Kim wrote overall without struct
 Sangjin Lee wrtoe this sturct

  All content © 2019 DigiPen (USA) Corporation, all rights reserved.
*/
#include "Enum.h"
#include "Global.h"

using GLOBAL::PageNum;
using GLOBAL::Player;

// When you press the button
void on_key_pressed(KeyboardButtons buttons)
{
    if (buttons == KeyboardButtons::Left && GLOBAL::Player.GetAbleMoveLeft())
    {
        Player.aisMoveLeft = true;
    }
    if (buttons == KeyboardButtons::Right && GLOBAL::Player.GetAbleMoveRight())
    {
        Player.aisMoveRight = true;
    }
    if (buttons == KeyboardButtons::Up && GLOBAL::Player.GetAbleMoveUp())
    {
        Player.aisMoveUp = true;
        Player.aisEffectedGravity = false;
    }
    if (buttons == KeyboardButtons::Down && GLOBAL::Player.GetAbleMoveDown())
    {
        Player.aisMoveDown = true;
        Player.aisEffectedGravity = false;
    }
    if (buttons == KeyboardButtons::Space && GLOBAL::PageNum >= GAME_STATEMENT::doodle_1phase)
    {
        Player.aisGetKeyInteraction = true;
    }
}

// When you release the key
void inline on_key_released(KeyboardButtons buttons)
{
    if (buttons == KeyboardButtons::Left && GLOBAL::PageNum >= GAME_STATEMENT::doodle_1phase)
    {
        Player.aisMoveLeft = false;
    }
    if (buttons == KeyboardButtons::Right && GLOBAL::PageNum >= GAME_STATEMENT::doodle_1phase)
    {
        Player.aisMoveRight = false;
    }
    if (buttons == KeyboardButtons::Up && GLOBAL::PageNum >= GAME_STATEMENT::doodle_2phase)
    {
        Player.aisMoveUp = false;
        Player.aisEffectedGravity = true;
    }
    if (buttons == KeyboardButtons::Down && GLOBAL::PageNum >= GAME_STATEMENT::doodle_2phase)
    {
        Player.aisMoveDown = false;
        Player.aisEffectedGravity = true;
    }
    if (buttons == KeyboardButtons::Space && GLOBAL::PageNum >= GAME_STATEMENT::doodle_1phase)
    {
        Player.aisGetKeyInteraction = false;
    }

    if (buttons == KeyboardButtons::V && PageNum >= GAME_STATEMENT::doodle_3phase)
    {
        if (!GLOBAL::Player.aisJumping) 	// Jump is works only when you are not jumping.
        {
            GLOBAL::Player.aisJumping = true;
            GLOBAL::Player.AddPositionY(GLOBAL::INIT_GAP_PLAYER_BLOCK);
            GLOBAL::velocity.addTo(0, 2.5);
        }
    }

	// Some kind of cheat that you can skip that stage.
    if (buttons == KeyboardButtons::Q)
    {
        ++GLOBAL::PageNum;
    }

	// This are only for debug, but we will leave these functions
    if (buttons == KeyboardButtons::R)
    {
        ShowWindow(GLOBAL::Console, SW_SHOW);
    }
    if (buttons == KeyboardButtons::T)
    {
        ShowWindow(GLOBAL::Console, SW_HIDE);
    }

	// When it ends
    if (buttons == KeyboardButtons::Escape && PageNum == GAME_STATEMENT::doodle_5phase)
    {
        exit(0);
    }
}
