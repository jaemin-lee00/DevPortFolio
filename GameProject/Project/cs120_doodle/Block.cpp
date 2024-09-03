/*
  Block.cpp

  GAM100 Prototype2
  Fall 2019
  
 Jaemin Lee wrote overall this jumping and invisible block
 Byeongjun Kim wrote aobut jumping
 Sangjin Lee wrote invisible block

  All content © 2019 DigiPen (USA) Corporation, all rights reserved.
*/
#include "Block.h"
#include "Global.h"
#include <doodle/doodle.hpp>
#include <iostream>
#include <vector>

using GLOBAL::BlockArray;
using GLOBAL::Player;

BlockType::BlockType(float positionX, float positionY, float width, float height, bool objectHp, HexColor blockColor)
    : SystemType(positionX, positionY, width, height, 0), aBlockColor(blockColor), aisPushed(objectHp)
{
}

void BlockType::Update()
{
    if (IsCollisionDetect(Player))
    {
        if (IsInvisible)
        {
            aBlockColor = GLOBAL::BLOCK_COLOR;
        }
        PushedBy(Player);
        CollisionCheckBlocksBy();
    }
    for (std::vector<BlockType*>::iterator it = BlockArray.begin(); it != BlockArray.end();)
    {
        if (this != *it && IsCombineCheck(*it))
        {
            // add new item
            CombineBlock();
            // erase two component
            // erase it
            it = BlockArray.erase(it);
            // esrase this
            it = BlockArray.begin();
            while (this != *it)
                it++;

            it = BlockArray.erase(it);
        }
        else
            it++;
    }
    if (IsCollisionDetect(GLOBAL::Player_Collision_Helper)) // To check whether the Helper is collisioned.
    {
        Player.aisJumping = true;
    }
}

void BlockType::CollisionCheckBlocksBy()
{
    for (BlockType* block : BlockArray)
    {
        if (this != block && block->aisPushed == false && block->IsCheckCollisionBy(this))
        {
            block->PushedBy(*this);
            block->CollisionCheckBlocksBy();
        }
    }
}

void BlockType::CombineBlock()
{
    GLOBAL::ItemArray.push_back(new ItemType(aPosX, aPosY, (aHeight < aWidth) ? aHeight : aWidth));
}


bool BlockType::IsCheckCollisionBy(BlockType* block)
{
    if (this != block && IsCollisionDetect(*block))
    {
        if (block->aisMoveUp || block->aisMoveDown || block->aisMoveLeft || block->aisMoveRight)
        {
            aisPushed = true;
            return true;
        }
    }

    return false;
}

bool BlockType::IsCombineCheck(BlockType* collision_object)
{
    float dist_x = aPosX - collision_object->aPosX;
    float dist_y = aPosY - collision_object->aPosY;

    if (sqrt(dist_x * dist_x + dist_y * dist_y) <= GLOBAL::INIT_BLOCK_COMBINE_DISTANCE)
        return true;

    return false;
}


bool operator==(const HexColor& lhs, const HexColor& rhs)
{
    if (lhs.rgba == rhs.rgba)
    {
        return true;
    }
    return false;
};

unsigned int BlockType::GetColor() 
{
	return aBlockColor.rgba;
}

void BlockType::Draw()
{
    doodle::set_rectangle_mode(doodle::RectMode::Center);
    push_settings();
    if (aBlockColor == GLOBAL::INVISIBLE_COLOR)
        IsInvisible = true;
    if (IsInvisible)
    {
        set_outline_color(doodle::HexColor(aBlockColor));
        // if (IsCollisionDetect(Player))
        //{
        //    printf("attached");
        //    aBlockColor = 0x00FF00FF;
        //}
    }
    doodle::set_fill_color(doodle::HexColor(aBlockColor));
    doodle::draw_rectangle(aPosX, aPosY, aWidth, aHeight);
    pop_settings();
}

void BlockType::UpdateTime()
{
    aSpeed = 0;

    aisMoveUp    = false;
    aisMoveDown  = false;
    aisMoveLeft  = false;
    aisMoveRight = false;

    aisPushed = false;
}