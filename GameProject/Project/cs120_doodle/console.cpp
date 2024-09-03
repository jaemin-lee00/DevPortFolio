/*
  console.cpp

  GAM100 Prototype2
  Fall 2019
  
 Jaemin Lee wrote overall this without Logo , how to play and game menu
 Byeongjun Kim
 Sangjin Lee wrote the functinos about logo , how to play and game menu

  All content © 2019 DigiPen (USA) Corporation, all rights reserved.
*/
#include "console.h"


namespace CONSOLE
{
    bool isUpKeyDown    = false;
    bool isDownKeyDown  = false;
    bool isLeftKeyDown  = false;
    bool isRightKeyDown = false;

    bool isGetKeyDown = false;
    bool isESCKeyDown = false;

    bool isGoToDoodle = false;

    bool isStart     = false;
    bool isHowToPlay = false;
    bool isMenu      = false;

    int PlayerPosY = 0;
    int PlayerPosX = 0;

    int PlayerDirection = 0;
    int DoodleCount     = 0;

    std::vector<char> Map(WIDTH* HEIGHT);
    std::vector<char> DoodleCallStack = {'d', 'o', 'o', 'd', 'l', 'e'};
    std::vector<int>  DoodlePositions(6);
}

void CONSOLE::draw_logo()
{
    /* NOT USE NOW
    fstream logoInput("logo.txt");
    string logo;
    logoInput >> logo;
    cout << logo;
    */
    go_to_position(0, 0);

    cout << "                  ZZZ ZZZZZZZZEBw          ZEEEEEEEEE9Bj                                                "
            "ZZZZZZZZZZZZEBw                                         ";
    cout << "                  ZZZ ZZZZZZZZZZZZZZ       ZZZZZZZZZZZZZZZZE      BZZZZZZW                    zZZZZZZ   "
            "ZZZZZZZZZZZZZZZZZZ                                      ";
    cout << "                  ZZZ ZZZZZZZZZZZZZZZ      ZZZZZZZZZZZZZZZZZZz    ZZZZZZZ8                    ZZZZZZZy  "
            "ZZZZZZZZZZZZZZZZZZZ                                     ";
    cout << "                  ZZZ ZZZZZZZZZZZZZZZZ     ZZZZZZZZZZZZZZZZZZZZ    BWWWWD                      BWWWWB   "
            "ZZZZZZZ wwWZZZZZZZZZ                                    ";
    cout << "                  ZZZ ZZZZZZZZZZZZZZZZZ    ZZZZZZE ,,w9ZZZZZZZZZ  y9wwwWZ,      BZZZZZZZZZZZ  y9wwwWZ   "
            "ZZZZZZZ      ZZZZZZZ    ZZZZZZZZZ,    WZZZZZZZZZZZZZZZ  ";
    cout << "                  ZZZ ZZZZZZZZZZZZZZZZZ    ZZZZZZ9      WZZZZZZZ  ZZZZZZZD    ZZZZZZZZZZZZZZ  ZZZZZZZ   "
            "ZZZZZZZ      ZZZZZZZ  ZZZZZZZZZZZZZ    ZZZZZZZZZZZZZZZZ ";
    cout << "                  ZZZ ZZZZZZZZZZZZZZZZZ    ZZZZZZZ       9ZZZZZZZ 8ZZZZZZj  DZZZZZZZZZZZZZZZ  8ZZZZZZ   "
            "ZZZZZZZ    5ZZZZZZZZ ZZZZZZZ   ZZZZZ   ZZZZZZZZZZZZZZZZZ";
    cout << "                  ZZZ ZZZZZZZZZZZZZZZZ9    ZZZZZZZ       5ZZZZZZZ 8ZZZZZZj  ZZZZZZZ   ZZZZZZ  8ZZZZZZ   "
            "ZZZZZZZZZZZZZZZZZZZ ZZZZZZZ     ZZZZZ  ZZZZZZZ   ZZZZZZZ";
    cout << "                  ZZZ ZZZZZZZZZZZZZZZZ     ZZZZZZZ       ZZZZZZZW 8ZZZZZZj 9ZZZZZB    ZZZZZZ  8ZZZZZZ   "
            "ZZZZZZZZZZZZZZZZZZ  ZZZZZZZZZZZZZZZZZ  ZZZZZZ9   ZZZZZZZ";
    cout << "                  ZZZ ZZZZZZZZZZZZZZZ      ZZZZZZD     9ZZZZZZZZ  8ZZZZZZj ZZZZZZZ    ZZZZZZ  8ZZZZZZ   "
            "ZZZZZZZZZZZZZZZ5    ZZZZZZZZZZZZZZZZZ  ZZZZZZZ   ZZZZZZZ";
    cout << "                  ZZZ ZZZZZZZZZZZZE        ZZZZZZZZZZZZZZZZZZZZ   8ZZZZZZj  ZZZZZZZZ9WZZZZZZ  8ZZZZZZ   "
            "ZZZZZZE             ZZZZZZZ            ZZZZZZZ   ZZZZZZZ";
    cout << "        WyyyyyyyZ ZZZ ZBBBBBBzD            ZZZZZZZZZZZZZZZZZZZ    8ZZZZZZj  ZZZZZZZZZZZZZZZZ  8ZZZZZZ   "
            "ZZZZZZZ              ZZZZZZZ5Wjjjy8Z   ZZZZZZZ   ZZZZZZZ";
    cout << "    DZZZZZZZZZZZZ ZZZ                      ZZZZZZZZZZZZZZZZZ8     8ZZZZZZj   yZZZZZZZZZZZZZZ  8ZZZZZZ   "
            "ZZZZZZZ               ZZZZZZZZZZZZZD   ZZZZZZZ   ZZZZZZZ";
    cout << "  BZZZZZZZZZZZZZZ ZZZ                      ZZZZZZZZZZZZZZZ        ZZZZZZZ9     wZZZZZZZZZZZZ  ZZZZZZZW  "
            "ZZZZZZZ                 ZZZZZZZZZ     wZZZZZZZ   ZZZZZZZ";
    cout << " ZZZZZZZZZZZZZZZZ ZZZ                      y                            ,            ZZZZZZZ        W   j "
            "    w                                W         j      ";
    cout << " ZZZZZZZZZZZZZZZZ ZZZ                                                         ZZZZEZZZZZZZZZ              "
            "                                                      ";
    cout << "EZZZZZZZZZZZZZZZZ ZZZ                                                         ZZZZZZZZZZZZZ               "
            "                                                      ";
    cout << "ZZZZZZZZZZZZZZZZZ ZZZ                                                         ZZZZZZZZZZZW                "
            "                                                      ";
    cout << "BZZZZZZZZZZZZZZZZ ZZZ                                                         ZZZZZZZZy                   "
            "                                                      ";
    cout << " ZZZZZZZZZZZZZZZZ ZZZ                      W Z    w  w, y   w W y  ,  ,     ,              y    ,,W  w,  "
            "y   y    y   W         ,    j    W     ,W      y  ,   ,";
    cout << " WZZZZZZZZZZZZZZZ ZZZ                      Z BZD  Z ZwZ EWZWD Z ZjZjj Z  ZE DZZE Zzj,    ZZzZZ ,Z W  "
            "5yZzE Z D  ZZ8Zz Z  yZ ZZ  Z  ZZzZZ  Z   BZE9ZZ jZ9yZ  ZyZB";
    cout << "   ZZZZZZZZZZZZZZ ZZZ                      Z j9yZ Z  ZZ   Z   Z   Z   Z  ZB  Z   ZE9w   ZB   Z  Z9Z    Z  "
            " ZWZ ZE     Z9ZZZ Z ZWZ  Z   DZ Z   Z    Z Z   Z   Z  ";
    cout << "      j9ZZZZZZZZZ ZZZ                      Z yE  ZZ EwZ   Z   Z   Z   Z88Z   Z,  ZBDW    ZZEZZ  Z      Z  "
            " Zwz  ZZEZD Z   9 Z   Z  ZZEZZ  Z5Z  ZZZZ5  ZEyZ   Z  ";
}

void CONSOLE::draw_menu()
{
    go_to_position(0, 0);
    cout << "           #########       #         #     ##      #    #########    #########    #########    ##      #  "
            "                                                      ";
    cout << "           #        #      #         #     # #     #   #         #   #           #         #   # #     #  "
            "                                                      ";
    cout << "           #         #     #         #     #  #    #   #         #   #           #         #   #  #    #  "
            "                                                      ";
    cout << "           #          #    #         #     #   #   #   #             #########   #         #   #   #   #  "
            "                                                      ";
    cout << "           #          #    #         #     #    #  #   #      ####   #           #         #   #    #  #  "
            "                                                      ";
    cout << "           #         #     #         #     #     # #   #         #   #           #         #   #     # #  "
            "                                                      ";
    cout << "           #        #      #         #     #      ##   #         #   #           #         #   #      ##  "
            "                                                      ";
    cout << "           #########        #########      #       #    #########    #########    #########    #       #  "
            "                                                      ";
    cout << "                                                        ##       ##         ##       #      #     "
            "########    #########                                         ";
    cout << "                                                        # #     # #        #  #      #    #       #       "
            "    #        #                                        ";
    cout << "                                                        #  #   #  #       #    #     #  #         #       "
            "    #        #                                        ";
    cout << "                                                        #   # #   #      ########    ##           "
            "########    ####### #                                         ";
    cout << "                                                        #    #    #     #        #   #  #         #       "
            "    #      #                                          ";
    cout << "                                                        #         #     #        #   #    #       #       "
            "    #       #                                         ";
    cout << "                                                        #         #     #        #   #      #     #       "
            "    #        #                                        ";
    cout << "                                                        #         #     #        #   #        #   "
            "########    #         #                                       ";
    cout << "                                                                                                          "
            "                                                      ";
    cout << "                                                                                                          "
            "                                                      ";
    cout << "                                     -----------------------------------------------------------          "
            "                                                      ";
    cout << "                                     -                Press 'i' to how to play                 -          "
            "                                                      ";
    cout << "                                     -                Press 'p' to start game                  -          "
            "                                                      ";
    cout << "                                     -----------------------------------------------------------          "
            "                                                      ";
    cout << "                                                                                                          "
            "                                                      ";
}

void CONSOLE::draw_howtoplay()
{
    go_to_position(0, 0);
    cout << "                                                                                                          "
            "                                                      ";
    cout << "                        w         w              u   u ppp                                                "
            "                                                      ";
    cout << "                         w   w   w     ====      u   u p  p                              sssss   ppppp    "
            "  a       cccccc eeeeee                               ";
    cout << "                          w w w w      ====      u   u ppp                              s        p    p   "
            " a a     c       e                                    ";
    cout << "                           w   w                  uuu  p                                 sssss   ppppp    "
            "aaaaa    c       eeeeee                               ";
    cout << "                                                                                              s  p       "
            "a     a   c       e                                    ";
    cout << "                            sssss                ddd      oo    w       w n   n          sssss   p      a "
            "      a   cccccc eeeeee                               ";
    cout << "                           s           ====      d  d    o  o   w       w nn  n                           "
            "                                                      ";
    cout << "                            sssss      ====      d   d   o  o   w   w   w n n n                           "
            "                                                      ";
    cout << "                                 s               d  d    o  o    w w w w  n  nn                 >      "
            "ccccc  oooo  l     l     eeeee   ccccc  ttttt            ";
    cout << "                            sssss                ddd      oo      w   w   n   n                  >    c   "
            "   o    o l     l     e      c         t              ";
    cout << "                                                                                            ------>   c   "
            "   o    o l     l     eeeee  c         t              ";
    cout << "                              a                 l     eeee   ffff ttttt                          >    c   "
            "   o    o l     l     e      c         t              ";
    cout << "                             a a       ====     l     e      f      t                           >      "
            "ccccc  oooo  lllll lllll eeeee   ccccc    t              ";
    cout << "                            aaaaa      ====     l     eeee   ffff   t                                     "
            "                                                      ";
    cout << "                           a     a              l     e      f      t                                     "
            "                                                      ";
    cout << "                          a       a             lllll eeee   f      t                                     "
            "                                                      ";
    cout << "                                                                                              "
            "------------------------                                          ";
    cout << "                          dddddd                rrrrr   iii   ggggg   h    h   ttttt          - press 'm' "
            "to go menu -                                          ";
    cout << "                          d     d      ====     r    r   i   g        h    h     t            -  press "
            "'p' to start  -                                          ";
    cout << "                          d      d     ====     rrrrr    i   g   ggg  hhhhhh     t            "
            "------------------------                                          ";
    cout << "                          d     d               r   r    i   g    g   h    h     t                        "
            "                                                      ";
    cout << "                          dddddd                r    r  iii   gggg    h    h     t                        "
            "                                                      ";
}

void CONSOLE::make_line()
{
    for (int x = 0; x < WIDTH; x++)
    {
        Map[x] = '#';
    }


    for (int x = 0; x < WIDTH; x++)
    {
        Map[x + WIDTH * (HEIGHT - 1)] = '#';
    }


    for (int y = 0; y < HEIGHT; y++)
    {
        Map[y * WIDTH]             = '#';
        Map[y * WIDTH + WIDTH - 1] = '#';
    }
}

void CONSOLE::draw_map()
{
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            cout << Map[y * WIDTH + x];
        }
    }
}

void CONSOLE::set_textcolor(int color_number)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_number);
}

void CONSOLE::console_initial()
{
    system("mode con cols=160 lines=45");

    HANDLE              console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO console_cursor;
    console_cursor.bVisible = 0;
    console_cursor.dwSize   = 1;

    SetConsoleCursorInfo(console_handle, &console_cursor);

    // set random map index pos
    srand(time(NULL));

    int map_index[7];

    for (int i = 0; i < 7; i++)
    {
        map_index[i] = rand() % ((WIDTH - WALLOFFSET) * (HEIGHT - WALLOFFSET));
        for (int sub_i = 0; sub_i < i; sub_i++)
        {
            if (map_index[i] == map_index[sub_i])
            {
                i--;
                break;
            }
        }
    }

    for (int i = 0; i < 6; i++)
    {
        DoodlePositions[i] = map_index[i];
    }

    PlayerPosX = map_index[6] % (WIDTH - WALLOFFSET);
    PlayerPosY = map_index[6] / (WIDTH - WALLOFFSET);

    PlayerDirection = RIGHT;
};

void CONSOLE::player_move()
{
    if (isUpKeyDown)
        PlayerDirection = UP, PlayerPosY--;
    else if (isDownKeyDown)
        PlayerDirection = DOWN, PlayerPosY++;
    else if (isLeftKeyDown)
        PlayerDirection = LEFT, PlayerPosX--;
    else if (isRightKeyDown)
        PlayerDirection = RIGHT, PlayerPosX++;


    // collision to wall
    if (PlayerPosX <= 0 || WIDTH - 2 <= PlayerPosX || PlayerPosY <= 0 || HEIGHT - 1 <= PlayerPosY)
    {
        if (isUpKeyDown)
            PlayerDirection = UP, PlayerPosY++;
        else if (isDownKeyDown)
            PlayerDirection = DOWN, PlayerPosY--;
        else if (isLeftKeyDown)
            PlayerDirection = LEFT, PlayerPosX++;
        else if (isRightKeyDown)
            PlayerDirection = RIGHT, PlayerPosX--;
    }
    // collision to item

    for (int pos : DoodlePositions)
    {
        if (pos == (PlayerPosX - 1) + (PlayerPosY - 1) * (WIDTH - WALLOFFSET))
        {
            if (isUpKeyDown)
                PlayerDirection = UP, PlayerPosY++;
            else if (isDownKeyDown)
                PlayerDirection = DOWN, PlayerPosY--;
            else if (isLeftKeyDown)
                PlayerDirection = LEFT, PlayerPosX++;
            else if (isRightKeyDown)
                PlayerDirection = RIGHT, PlayerPosX--;
        }

		if (pos == (PlayerPosX) + (PlayerPosY - 1) * (WIDTH - WALLOFFSET))
        {
            if (isUpKeyDown)
                PlayerDirection = UP, PlayerPosY++;
            else if (isDownKeyDown)
                PlayerDirection = DOWN, PlayerPosY--;
            else if (isLeftKeyDown)
                PlayerDirection = LEFT, PlayerPosX++;
            else if (isRightKeyDown)
                PlayerDirection = RIGHT, PlayerPosX--;
        }
    }
};

void CONSOLE::get_doodle()
{
    int dest_x = PlayerPosX;
    int dest_y = PlayerPosY;


    if (PlayerDirection == UP)
        dest_y--;
    if (PlayerDirection == DOWN)
        dest_y++;
    if (PlayerDirection == LEFT)
        dest_x--;
    if (PlayerDirection == RIGHT)
        dest_x++;

    for (int i = 0; i < 6; i++)
    {
        if (DoodlePositions[i] == (dest_x - 1) + (dest_y - 1) * (WIDTH - WALLOFFSET) && isGetKeyDown)
        {
            DoodlePositions[i] = i + (WIDTH - WALLOFFSET) * (HEIGHT - 1);
            DoodleCount++;
        };

		
        if (DoodlePositions[i] == (dest_x) + (dest_y - 1) * (WIDTH - WALLOFFSET) && isGetKeyDown)
        {
            DoodlePositions[i] = i + (WIDTH - WALLOFFSET) * (HEIGHT - 1);
            DoodleCount++;
        };
    }
}

void CONSOLE::get_color(){};

void CONSOLE::go_to_position(int x, int y)
{
    HANDLE console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD  pos;
    pos.X = x;
    pos.Y = y;

    SetConsoleCursorPosition(console_handle, pos);
}

void CONSOLE::draw_doodle()
{
    for (int i = 0; i < 6; i++)
    {
        int x = DoodlePositions[i] % (WIDTH - WALLOFFSET) + 1;
        int y = DoodlePositions[i] / (WIDTH - WALLOFFSET) + 1;

        go_to_position(x, y);

        set_textcolor(i * 2 + 1);

        _setmode(_fileno(stdout), _O_TEXT);
        cout << DoodleCallStack[i];
    }
};

void CONSOLE::draw_player()
{
    _setmode(_fileno(stdout), _O_U8TEXT);
    go_to_position(PlayerPosX, PlayerPosY);
    set_textcolor(10);

    switch (PlayerDirection)
    {
        case UP: wcout << L"↑"; break;
        case DOWN: wcout << L"↓"; break;
        case LEFT: wcout << L"←"; break;
        case RIGHT: wcout << L"→"; break;
    };


    _setmode(_fileno(stdout), _O_TEXT);

    go_to_position(0, HEIGHT);
};

void CONSOLE::set_key_control()
{
    if (_getch() == 224)
        return;

    char temp = _getch();


    if (temp == 'w' || temp == 'W')
        isUpKeyDown = true;
    else if (temp == 's' || temp == 'S')
        isDownKeyDown = true;
    else if (temp == 'a' || temp == 'A')
        isLeftKeyDown = true;
    else if (temp == 'd' || temp == 'D')
        isRightKeyDown = true;
    else if (temp == ' ')
        isGetKeyDown = true;
    else if (temp == ESC)
        isESCKeyDown = true;
    else if (temp == 'p' || temp == 'P')
        isStart = true;
    else if (temp == 'i' || temp == 'I')
    {
        isHowToPlay = true;
        isMenu      = false;
    }
    else if (temp == 'm' || temp == 'M')
    {
        isHowToPlay = false;
        isMenu      = true;
    }
    else if (temp == 'q' || temp == 'Q')
    {
        CONSOLE::isGoToDoodle = true;
    }
}

void CONSOLE::set_past_time()
{
    _setmode(_fileno(stdout), _O_U8TEXT);
    go_to_position(PlayerPosX, PlayerPosY);

    wcout << " ";

    for (int i = 0; i < 6; i++)
    {
        int x = DoodlePositions[i] % (WIDTH - WALLOFFSET) + 1;
        int y = DoodlePositions[i] / (WIDTH - WALLOFFSET) + 1;

        go_to_position(x, y);

        _setmode(_fileno(stdout), _O_TEXT);
        cout << " ";
    }
}

void CONSOLE::set_time()
{
    isUpKeyDown    = false;
    isDownKeyDown  = false;
    isLeftKeyDown  = false;
    isRightKeyDown = false;

    isGetKeyDown = false;
}

void CONSOLE::go_to_doodle()
{
    if (DoodleCount == 6)
        isGoToDoodle = true;
}

void play_console()
{
    CONSOLE::console_initial();

    CONSOLE::draw_logo();

    Sleep(2000);

    CONSOLE::isMenu = true;

    while (!CONSOLE::isStart)
    {
        if (CONSOLE::isHowToPlay)
        {
            CONSOLE::draw_howtoplay();
        }
        else
        {
            CONSOLE::draw_menu();
        }
        CONSOLE::set_key_control();
    }

    CONSOLE::go_to_position(0, 0);

    CONSOLE::set_textcolor(10);
    CONSOLE::make_line();
    CONSOLE::draw_map();

    CONSOLE::draw_doodle();
    CONSOLE::draw_player();


    do
    {
        CONSOLE::set_key_control();


        CONSOLE::set_past_time();

        CONSOLE::player_move();
        CONSOLE::get_doodle();

        CONSOLE::draw_doodle();
        CONSOLE::draw_player();

        CONSOLE::set_time();

        CONSOLE::go_to_doodle();
    } while (CONSOLE::isGoToDoodle == false);


    CONSOLE::go_to_position(0, CONSOLE::HEIGHT);
}
