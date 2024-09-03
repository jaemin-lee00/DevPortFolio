/*
  System.cpp

  GAM100 Prototype2
  Fall 2019
  
 Jaemin Lee wrote this all
 Byeongjun Kim
 Sangjin Lee

  All content © 2019 DigiPen (USA) Corporation, all rights reserved.
*/
#include "System.h"
#include "Enum.h"
#include "Global.h"
#include <doodle/doodle.hpp>
#include <iostream>

void SystemType::ModifyByCollision(SystemType& collision_object)
{

    {
    if (aisMoveUp)
        aPosY -= aSpeed, aisMoveUp = collision_object.aisMoveUp;
    else if (aisMoveDown)
        aPosY += aSpeed, aisMoveDown = collision_object.aisMoveDown;
    else if (aisMoveLeft)
        aPosX += aSpeed, aisMoveLeft = collision_object.aisMoveLeft;
    else if (aisMoveRight)
        aPosX -= aSpeed, aisMoveRight = collision_object.aisMoveRight;
    }
}

void SystemType::PushedBy(SystemType& collision_object)
{
    if (collision_object.aisMoveUp)
    {
        aSpeed = collision_object.GetSpeed();
        aPosY += aSpeed;
        aisMoveUp = collision_object.aisMoveUp;
    }
    if (collision_object.aisMoveDown)
    {
        aSpeed = collision_object.GetSpeed();
        aPosY -= aSpeed;
        aisMoveDown = collision_object.aisMoveDown;
    }
    if (collision_object.aisMoveLeft)
    {
        aSpeed = collision_object.GetSpeed();
        aPosX -= aSpeed;
        aisMoveLeft = collision_object.aisMoveLeft;
    }
    if (collision_object.aisMoveRight)
    {
        aSpeed = collision_object.GetSpeed();
        aPosX += aSpeed;
        aisMoveRight = collision_object.aisMoveRight;
    }

    if (IsCollisionDetectWall())
    {
        ModifyByWall();
        if (collision_object.aObjectKind == OBJECT_KIND::PLAYER)
            collision_object.ModifyByCollision(*this);
    }
}

void SystemType::ModifyByWall()
{
   
    if (aisMoveUp)
        aPosY -= aSpeed, aisMoveUp = false;
    if (aisMoveDown)
        aPosY += aSpeed, aisMoveDown = false;
    if (aisMoveLeft)
        aPosX += aSpeed, aisMoveLeft = false;
    if (aisMoveRight)
        aPosX -= aSpeed, aisMoveRight = false;
}

void SystemType::AddPositionX(float X) { aPosX += X; }
void SystemType::AddPositionY(float Y) { aPosY += Y; }

float SystemType::GetPositionX() { return aPosX; }
float SystemType::GetPositionY() { return aPosY; };

float SystemType::GetSpeed() { return aSpeed; }

float SystemType::GetWidth() { return aWidth; }
float SystemType::GetHeight() { return aHeight; }

bool SystemType::IsCollisionDetect(SystemType& collision_object)
{
    int  a_kind_case         = aObjectKind + collision_object.aObjectKind;
    bool is_collision_detect = false;

    switch (a_kind_case)
    {
        // collision to block from player
        case (OBJECT_KIND::PLAYER + OBJECT_KIND::BLOCK):
            // Collision check to line
            if (aObjectKind == OBJECT_KIND::PLAYER)
            {
                if (aPosY - aRadius / 2 < collision_object.aPosY + collision_object.aHeight / 2 &&
                    aPosY + aRadius / 2 > collision_object.aPosY - collision_object.aHeight / 2)
                    if (aPosX < collision_object.aPosX + collision_object.aWidth / 2 &&
                        aPosX > collision_object.aPosX - collision_object.aWidth / 2)
                        is_collision_detect = true;

                if (aPosX - aRadius / 2 < collision_object.aPosX + collision_object.aWidth / 2 &&
                    aPosX + aRadius / 2 > collision_object.aPosX - collision_object.aWidth / 2)
                    if (aPosY < collision_object.aPosY + collision_object.aHeight / 2 &&
                        aPosY > collision_object.aPosY - collision_object.aHeight / 2)
                        is_collision_detect = true;

                float corner_x = (aPosX < collision_object.aPosX)
                                     ? collision_object.aPosX - collision_object.aWidth / 2
                                     : collision_object.aPosX + collision_object.aWidth / 2;

                float corner_y = (aPosY < collision_object.aPosY)
                                     ? collision_object.aPosY - collision_object.aHeight / 2
                                     : collision_object.aPosY + collision_object.aHeight / 2;

                float dist_x = aPosX - corner_x;
                float dist_y = aPosY - corner_y;

                if (sqrt(dist_x * dist_x + dist_y * dist_y) < aRadius / 2)
                    is_collision_detect = true;
            }
            if (aObjectKind == OBJECT_KIND::BLOCK)
            {
                if (aPosY - aHeight / 2 < collision_object.aPosY + collision_object.aRadius / 2 &&
                    aPosY + aHeight / 2 > collision_object.aPosY - collision_object.aRadius / 2)
                    if (aPosX - aWidth / 2 < collision_object.aPosX && aPosX + aWidth / 2 > collision_object.aPosX)
                        is_collision_detect = true;

                if (aPosX - aWidth / 2 < collision_object.aPosX + collision_object.aRadius / 2 &&
                    aPosX + aWidth / 2 > collision_object.aPosX - collision_object.aRadius / 2)
                    if (aPosY - aHeight / 2 < collision_object.aPosY && aPosY + aHeight / 2 > collision_object.aPosY)
                        is_collision_detect = true;

                // find corner
                float corner_x = (collision_object.aPosX < aPosX) ? aPosX - aWidth / 2 : aPosX + aWidth / 2;
                float corner_y = (collision_object.aPosY < aPosY) ? aPosY - aHeight / 2 : aPosY + aHeight / 2;

                float dist_x = collision_object.aPosX - corner_x;
                float dist_y = collision_object.aPosY - corner_y;

                if (sqrt(dist_x * dist_x + dist_y * dist_y) < collision_object.aRadius / 2)
                    is_collision_detect = true;
            }
            // Collision Check to dot


            break;
        // collision to block to block
        case (OBJECT_KIND::BLOCK + OBJECT_KIND::BLOCK):
            if (aPosY - aHeight / 2 < collision_object.aPosY + collision_object.aHeight / 2 &&
                aPosY + aHeight / 2 > collision_object.aPosY - collision_object.aHeight / 2 &&

                aPosX - aWidth / 2 < collision_object.aPosX + collision_object.aWidth / 2 &&
                aPosX + aWidth / 2 > collision_object.aPosX - collision_object.aWidth / 2)
                is_collision_detect = true;

            break;

        // collision to item to player
        case (OBJECT_KIND::PLAYER + OBJECT_KIND::ITEM):
            float dist_x = aPosX - collision_object.aPosX;
            float dist_y = aPosY - collision_object.aPosY;
            if (sqrt(dist_x * dist_x + dist_y * dist_y) < (aRadius + collision_object.aRadius) / 2)
                is_collision_detect = true;

        break;
    }

    return is_collision_detect;
}

bool SystemType::IsCollisionDetectWall()
{
    // collision to X
    if ((-(Width / 2) > aPosX - (aRadius + aWidth) / 2) || aPosX + (aRadius + aWidth) / 2 > Width / 2)
        return true;

    // collision to Y
    if (-(Height / 2) > aPosY - (aRadius + aHeight) / 2 || aPosY + (aRadius + aWidth) / 2 > Height / 2)
        return true;

    for (BlockType* wall : GLOBAL::WallArray)
        if (IsCollisionDetect(*wall))
            return true;

	for (BlockType* line : GLOBAL::LineArray)
        if (IsCollisionDetect(*line))
            return true;


    return false;
}
