/*
  console.h

  GAM100 Prototype2
  Fall 2019
  
 Jaemin Lee wrote overall this without Logo , how to play and game menu
 Byeongjun Kim
 Sangjin Lee wrote the functinos about logo , how to play and game menu

  All content © 2019 DigiPen (USA) Corporation, all rights reserved.
*/
#pragma once
#include <Windows.h>
#include <conio.h>
#include <ctime>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <string>
#include <vector>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;


namespace CONSOLE
{
    enum
    {
        UP    = 0,
        DOWN  = 1,
        LEFT  = 2,
        RIGHT = 3
    };

    constexpr int ESC= 27;
   
    constexpr int WIDTH = 160;
    constexpr int HEIGHT = 45 -1;
    constexpr int WALLOFFSET = 2;

    extern bool isUpKeyDown;
    extern bool isDownKeyDown;
    extern bool isLeftKeyDown;
    extern bool isRightKeyDown;
    
    extern bool isGetKeyDown;
    extern bool isESCKeyDown;
    
    extern bool isGoToDoodle;

    extern bool isStart;
    extern bool isHowToPlay;
    extern bool isMenu;

    extern int PlayerPosY;
    extern int PlayerPosX;

    extern int PlayerDirection;
    extern int DoodleCount;


    extern std::vector<char> Map;
    extern vector<char>      DoodleCallStack;
    extern vector<int>  DoodlePositions;


    void draw_map();

    void make_line();

    void set_textcolor(int);

    void console_initial();


    void player_move();


    void get_doodle();

    void get_color();


    void go_to_position(int, int);
    void go_to_doodle();


    void draw_doodle();

    void draw_player();

    void set_key_control();


    void set_time();

    void set_past_time();

    void draw_menu();

    void draw_logo();

    void draw_howtoplay();
}

void play_console();
