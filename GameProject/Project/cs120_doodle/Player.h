/*
  Player.h

  GAM100 Prototype2
  Fall 2019

 Jaemin Lee wrote the initial struct and the physics related collision
 Byeongjun Kim wrote about moving
 Sangjin Lee

  All content © 2019 DigiPen (USA) Corporation, all rights reserved.
*/
#pragma once
#include "System.h"
#include "Enum.h"
#include "Ladder.h"
#include <doodle/doodle.hpp>
using namespace doodle;

class PlayerType : virtual public SystemType
{
private:

    bool aisAbleMoveLeft  = true;
    bool aisAbleMoveRight = true;
    bool aisAbleMoveUp    = false;
    bool aisAbleMoveDown  = false;

	int phase_number = 0;

    float aHoldDistance;
    float aHoldLadder;


    bool IsCheckOnLadder(LadderType* ladder);
    bool IsCheckOnChecker(LadderType* stagechecker);
    void ClimbLadder();


public:
    bool aisJumping = false;
    bool aisEffectedGravity = false;
    
     bool aisGetKeyInteraction = false;

     PlayerType(float positionX, float positionY, float radius, float speed);

    
    void Draw();
    void Update();
    void Moving();

    float GetRadius();
    float GetSpeed();
    void SetSpeed(float input);

    bool GetAbleMoveLeft();
    bool GetAbleMoveRight();
    bool GetAbleMoveUp();
    bool GetAbleMoveDown();

    void SetMoveAble(const DIRECTION& dir, const bool& true_or_false);
};