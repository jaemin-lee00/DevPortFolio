/*
  doodle.cpp

  GAM100 Prototype2
  Fall 2019
  
 Jaemin Lee wrote overall struct ,pipe line and initial window system
 Byeongjun Kim wrote about overall window system
 Sangjin Lee wrote initial struct

  All content © 2019 DigiPen (USA) Corporation, all rights reserved.
  */
#include "Variable.h"
#include "console.h"
#include <SFML/Audio.hpp>
#include <doodle/doodle.hpp>
#include <iostream>
#include <string>


using namespace doodle;
using GLOBAL::BlockArray;
using GLOBAL::ItemArray;
using GLOBAL::LadderArray;
using GLOBAL::LineArray;
using GLOBAL::Map;
using GLOBAL::PageNum;
using GLOBAL::Player;
using GLOBAL::StageCheckerArray;
using GLOBAL::WallArray;

// This function will called when you start the game.
void GameStart() // When the game is started, reset the game setting.
{
    ShowWindow(GLOBAL::Console, SW_SHOW); // Show the console (unhide the console)
    play_console();
    system("cls");

    // Set the first window's place.
    GLOBAL::NewWidth  = GLOBAL::INIT_MAP_WIDTH;
    GLOBAL::NewHeight = GLOBAL::INIT_MAP_HEIGHT;
    GLOBAL::MaxWidth  = GetSystemMetrics(SM_CXSCREEN) / 3;
    GLOBAL::MaxHeight = GetSystemMetrics(SM_CYFULLSCREEN);

    // To manage gravity, set the default values
    GLOBAL::velocity.initialization(0, 0);
    GLOBAL::gravity.initialization(0, -0.1);

    // Set the map.
    MAP_READING::Map_Load();
    const float blockwidth = GetSystemMetrics(SM_CXSCREEN) / MAP_READING::map.width;
    const float blockheight =
        (GetSystemMetrics(SM_CYFULLSCREEN) - GetSystemMetrics(SM_CYCAPTION)) / MAP_READING::map.height;
    GLOBAL::StageCheckerArray.push_back(new LadderType(-blockwidth * 4, 0, blockwidth, blockheight, 0));

    // After the console game, hide the console
    ShowWindow(GLOBAL::Console, SW_HIDE); // hide console(bat)
    create_window();
    set_window_title(GLOBAL::GameName);
    GLOBAL::GameWindow = ::FindWindow(NULL, ("DunMe"));

    // Move the new window's place
    GLOBAL::NewPlaceX = GLOBAL::INIT_MAP_POS_X;
    GLOBAL::NewPlaceY = GLOBAL::INIT_MAP_POS_Y;
    FitMapX(-GLOBAL::INIT_MAP_POS_X); // also move the blocks place.

    // This function set the window's size and place.
    ::SetWindowPos(GLOBAL::GameWindow, HWND_BOTTOM, 0, 0, GLOBAL::NewWidth, GLOBAL::NewHeight,
                   SWP_NOOWNERZORDER | SWP_NOZORDER);

}

void DrawGuide(GAME_STATEMENT state)
{
    set_font_size(14);
    switch (state)
    {
        case GAME_STATEMENT::doodle_1phase: draw_text("Go to left", -Width / 2 + 20, 50); break;
        case GAME_STATEMENT::doodle_2phase:
            draw_text("Great!\nNow you can move up/down\nYou can also pull green blocks.", -Width / 2 + 40, 60);
            break;
        case GAME_STATEMENT::doodle_3phase: draw_text("Press \'V\' to jump.", -Width / 2 + 20, 50); break;
    }
}

int main(void)
{
    GameStart();
    GLOBAL::PageNum = GAME_STATEMENT::doodle_1phase;
    ::SetFocus(GLOBAL::GameWindow);
	while (!is_window_closed() && GLOBAL::PageNum != GAME_STATEMENT::doodle_5phase)
    {
        clear_background(HexColor{GLOBAL::BACKGROUND_COLOR});

        // To compute the game, below functions are needed
        Player.Update();
        for (BlockType* block : BlockArray)
            block->Update();
        for (BlockType* block : BlockArray)
            block->Draw();
        for (LadderType* ladder : LadderArray)
            ladder->Draw();
        for (LadderType* checker : StageCheckerArray)
            checker->Draw();
        for (BlockType* wall : WallArray)
            wall->Draw();
        for (BlockType* line : LineArray)
            line->Draw();
        for (ItemType* item : ItemArray)
            item->Draw();
        Player.Draw();
        for (BlockType* block : BlockArray)
            block->UpdateTime();

        DrawGuide(GLOBAL::PageNum);

        update_window();
    }

    // At 5, the game will end
    while (!is_window_closed())
    {
        update_window();
        Map.MapEnd();
    }

    return 0;
}

void on_mouse_pressed() {}
void on_mouse_released() {}

// To prevent when you try to resize/lengthen the window.
void on_window_resized(int new_width, int new_height)
{
    new_width += 0;  // useless
    new_height += 0; // useless
    if (GLOBAL::NewWidth > GetSystemMetrics(SM_CXSCREEN))
    {
        GLOBAL::NewWidth = GetSystemMetrics(SM_CXSCREEN);
    }
    if (GLOBAL::NewHeight > GetSystemMetrics(SM_CYSCREEN))
    {
        GLOBAL::NewHeight = GetSystemMetrics(SM_CYSCREEN);
    }


    ::SetWindowPos(GLOBAL::GameWindow, 0, GLOBAL::NewPlaceX, GLOBAL::NewPlaceY, GLOBAL::NewWidth, GLOBAL::NewHeight,
                   SWP_NOOWNERZORDER | SWP_NOZORDER);
}
