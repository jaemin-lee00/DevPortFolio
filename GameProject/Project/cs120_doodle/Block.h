/*
  Block.h

  GAM100 Prototype2
  Fall 2019

 Jaemin Lee wrote this all
 Byeongjun Kim 
 Sangjin Lee

  All content © 2019 DigiPen (USA) Corporation, all rights reserved.
*/
#pragma once
#include "System.h"
#include <doodle/color.hpp>

class BlockType : public SystemType
{
private:
    //Hp must lower than 3
    bool aisPushed = false;
    doodle::HexColor aBlockColor;

    bool IsInvisible = false;

    void CollisionCheckBlocksBy();
    void CombineBlock();
    bool IsCombineCheck(BlockType *);
    bool IsCheckCollisionBy(BlockType *);

public:
    BlockType(float positionX, float positionY, float width, float height, bool objectHp, doodle::HexColor blockColor);

	unsigned int GetColor();

    void Draw();
    void Update();
    void WallUpdate();
    void UpdateTime();
};
bool operator==(const doodle::HexColor& lhs, const unsigned& rhs);