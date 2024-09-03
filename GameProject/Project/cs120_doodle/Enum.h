/*
  Enum.h

  GAM100 Prototype2
  Fall 2019

 Jaemin Lee wrote the object_kind enum
 Byeongjun Kim wrote the enum classes , the phase_screen and functino about overload
 Sangjin Lee

  All content © 2019 DigiPen (USA) Corporation, all rights reserved.
*/

#pragma once
enum class GAME_STATEMENT
{
    console_1D,
    doodle_1phase,
    doodle_2phase,
    doodle_3phase,
    doodle_4phase ,
	doodle_5phase ,
};

constexpr float phase4_screenX = 200;
constexpr float phase4_screenY = 200;

void operator++(GAME_STATEMENT& state);


enum class DIRECTION
{
    NONE,

    LEFT,
    RIGHT,
    UP,
    DOWN
};

 enum OBJECT_KIND : int
{
    PLAYER,
    BLOCK,
    LADDER,
    ITEM
};
