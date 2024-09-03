/*
  MapReader.cpp

  GAM100 Prototype2
  Fall 2019
  
 Jaemin Lee
 Byeongjun Kim wrote this all
 Sangjin Lee

  All content © 2019 DigiPen (USA) Corporation, all rights reserved.
*/

#include "Global.h"
#include <Windows.h>
#include <fstream>
#include <vector>

using namespace std;

namespace MAP_READING
{
    Map map;

    void error(const string& s) { throw runtime_error(s); }

    // To read the map.txt
    int HexDigitToDec(char hexDigit)
    {
        char return_temp = 0;

        if ('a' <= hexDigit)
        {
            return_temp = (hexDigit - '7' - char(32));
        }
        else if ('A' <= hexDigit)
        {
            return_temp = (hexDigit - '7');
        }
        else if ('0' <= hexDigit)
        {
            return_temp = (hexDigit - '0');
        }

        return return_temp;
    }

    // To read the map.txt
    int ConvertHexToDec(string hexString)
    {
        int result = 0;
        int len    = static_cast<int>(hexString.length()) - 1;
        while (len != -1)
        {
            result = HexDigitToDec(hexString[len]) * static_cast<int>(pow(16, len)) + result;
            len--;
        }
        return result;
    }

    // To read the map
    istream& operator>>(istream& input, Map& maap)
    {
        maap.tiles = {};
        string trash;
        char   get_char = '0';
        input >> trash >> maap.width >> trash >> maap.height;
        for (int y = 0; y < maap.height; y++)
        {
            for (int x = 0; x < maap.width; x++)
            {
                string value;
                while (1)
                {
                    input >> get_char;
                    if (get_char == ',')
                        break;
                    value = value + get_char;
                }
                int result = ConvertHexToDec(value);
                maap.tiles.push_back(result);
            }
        }
        return input;
    }

    // This function helps to load
    void Load(ifstream& fin)
    {
        if (!fin)
        {
            error("Failed to read");
        }
        fin.exceptions(fin.exceptions() | ios_base::badbit);
        fin >> map;
    }

    // This function will be called to load the map
    void Map_Load()
    {
        ifstream fin{"map.txt"};
        Load(fin);
        const float blockwidth  = GetSystemMetrics(SM_CXSCREEN) / map.width;
        const float blockheight = (GetSystemMetrics(SM_CYFULLSCREEN) - GetSystemMetrics(SM_CYCAPTION)) / map.height;
        for (int i = 0; i < map.width * map.height; i++)
        {
            // this is the block, the block's color is green
            if (MAP_READING::map.tiles[i] == BLOCK_GREEN)
            {
                GLOBAL::BlockArray.push_back(
                    new BlockType((i + 1) * blockwidth - GLOBAL::INIT_MAP_WIDTH / 2 -
                                      (blockwidth * MAP_READING::map.width) * (i / map.width),
                                  GLOBAL::INIT_MAP_HEIGHT / 2 - (blockheight * (1.5 + (i / map.width))), blockwidth,
                                  blockheight, false, MAP_READING::map.tiles[i]));
            }

            // this is the block, the block's color is sky
            else if (MAP_READING::map.tiles[i] == LADDER_SKY)
            {
                GLOBAL::LadderArray.push_back(
                    new LadderType((i + 1) * blockwidth - GLOBAL::INIT_MAP_WIDTH / 2 -
                                       (blockwidth * MAP_READING::map.width) * (i / map.width),
                                   GLOBAL::INIT_MAP_HEIGHT / 2 - (blockheight * (1.5 + (i / map.width))), blockwidth,
                                   blockheight, MAP_READING::map.tiles[i]));
            }
            else if (MAP_READING::map.tiles[i] == WALL_RED || MAP_READING::map.tiles[i] == WALL_PURPLE ||
                     MAP_READING::map.tiles[i] == WALL_BLACK)
            {
                GLOBAL::WallArray.push_back(
                    new BlockType((i + 1) * blockwidth - GLOBAL::INIT_MAP_WIDTH / 2 -
                                      (blockwidth * MAP_READING::map.width) * (i / map.width),
                                  GLOBAL::INIT_MAP_HEIGHT / 2 - (blockheight * (1.5 + (i / map.width))), blockwidth,
                                  blockheight, false, MAP_READING::map.tiles[i]));
            }
            else if (MAP_READING::map.tiles[i] == WALL_YELLOW || MAP_READING::map.tiles[i] == WALL_GREY)
            {
                GLOBAL::LineArray.push_back(
                    new BlockType((i + 1) * blockwidth - GLOBAL::INIT_MAP_WIDTH / 2 -
                                      (blockwidth * MAP_READING::map.width) * (i / map.width),
                                  GLOBAL::INIT_MAP_HEIGHT / 2 - (blockheight * (1.5 + (i / map.width))), blockwidth,
                                  blockheight, false, MAP_READING::map.tiles[i]));
            }
            else if (MAP_READING::map.tiles[i] == CHECKER_COLOR)
            {
                GLOBAL::StageCheckerArray.push_back(new LadderType(
                    (i + 1) * blockwidth - GLOBAL::INIT_MAP_WIDTH / 2 -
                        (blockwidth * MAP_READING::map.width) * (i / map.width),
                    GLOBAL::INIT_MAP_HEIGHT / 2 - (blockheight * (1.5 + (i / map.width))), blockwidth, blockheight, 0));
            }
        }
    }
}
