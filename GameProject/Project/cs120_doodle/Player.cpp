/*
  Player.cpp

  GAM100 Prototype2
  Fall 2019

 Jaemin Lee wrote the initial struct and the physics related collision
 Byeongjun Kim wrote about moving and game statement
 Sangjin Lee

  All content © 2019 DigiPen (USA) Corporation, all rights reserved.
*/
#include "Player.h"
#include "Global.h"


using GLOBAL::Map;
using GLOBAL::PageNum;
using GLOBAL::Player;

PlayerType::PlayerType(float positionX, float positionY, float radius, float speed)
    : SystemType(positionX, positionY, radius, speed), aHoldDistance(GLOBAL::INIT_PLAYER_HOLD_DISTANCE),
      aHoldLadder(GLOBAL::INIT_PLAYER_HOLD_LADDER){};

bool PlayerType::IsCheckOnLadder(LadderType* ladder)
{
    if (aPosY - aRadius / 2 < ladder->GetPositionY() + ladder->GetHeight() / 2 &&
        aPosY + aRadius / 2 > ladder->GetPositionY() - ladder->GetHeight() / 2)
        if (aPosX < ladder->GetPositionX() + ladder->GetWidth() / 2 &&
            aPosX > ladder->GetPositionX() - ladder->GetWidth() / 2)
            return true;

    return false;
}

// check whether the player is in the checker(to progress the map)
bool PlayerType::IsCheckOnChecker(LadderType* stagechecker)
{
    if (aPosY - aRadius / 2 < stagechecker->GetPositionY() + stagechecker->GetHeight() / 2 &&
        aPosY + aRadius / 2 > stagechecker->GetPositionY() - stagechecker->GetHeight() / 2)
        if (aPosX < stagechecker->GetPositionX() + stagechecker->GetWidth() / 2 &&
            aPosX > stagechecker->GetPositionX() - stagechecker->GetWidth() / 2)
        {
            return true;
        }
    return false;
}

void PlayerType::Draw()
{
    set_fill_color(HexColor{GLOBAL::PLAYER_COLOR});
    draw_ellipse(aPosX, aPosY, aRadius, aRadius);
}

void PlayerType::Update()
{
    Moving();

    std::vector<ItemType*>::iterator erase_item = GLOBAL::ItemArray.begin();

	//collision about item
    for (ItemType* item : GLOBAL::ItemArray)
    {
        if (IsCollisionDetect(*item))
        {
            // check player is collied by item when player down the key Getinteract
            if (aisGetKeyInteraction)
            {
                GLOBAL::ItemArray.erase(erase_item);

                for (std::vector<BlockType*>::iterator erase_line = GLOBAL::LineArray.begin();
                     erase_line < GLOBAL::LineArray.end();)
                {
                    if ((*erase_line)->GetColor() == GLOBAL::LINE_YELLOW.rgba && phase_number == 0)
                        GLOBAL::LineArray.erase(erase_line);
                    else if ((*erase_line)->GetColor() == GLOBAL::LINE_GREY.rgba && phase_number == 1)
                        GLOBAL::LineArray.erase(erase_line);
                    else
                        erase_line++;
                }
                phase_number++;
            }
            else
                ModifyByCollision(*item);
        }

        erase_item++;
    }
	//colllision aobut wall
    for (BlockType* wall : GLOBAL::WallArray)
    {
        if (IsCollisionDetect(*wall))
        {
            ModifyByCollision(*wall);
        }

        // When the collision is detected,
        if (IsCollisionDetect(*wall))
        {
            // When the player is jumping
            if (GLOBAL::Player.aisJumping)
            {
                // If player is falling
                if (GLOBAL::velocity.getY() < 0)
                {
                    GLOBAL::velocity.initialization(0, 0);
                    if (absolute(aPosY - wall->GetPositionY()) > wall->GetHeight() / 2)
                    {
                        aPosY += aRadius / 2 -
                                 absolute(absolute(aPosY - wall->GetPositionY()) - wall->GetHeight() / 2) +
                                 GLOBAL::INIT_GAP_PLAYER_BLOCK;
                    }
                    else
                    {
                        aPosY += aRadius / 2 +
                                 absolute(absolute(aPosY - wall->GetPositionY()) - wall->GetHeight() / 2) +
                                 GLOBAL::INIT_GAP_PLAYER_BLOCK;
                    }
                }
                else
                {
                    if (absolute(aPosY - wall->GetPositionY()) > wall->GetHeight() / 2)
                    {
                        aPosY -= aRadius / 2 -
                                 absolute(absolute(aPosY - wall->GetPositionY()) - wall->GetHeight() / 2) +
                                 GLOBAL::INIT_GAP_PLAYER_BLOCK * 2;
                    }
                    else
                    {
                        aPosY -= aRadius / 2 +
                                 absolute(absolute(aPosY - wall->GetPositionY()) - wall->GetHeight() / 2) +
                                 GLOBAL::INIT_GAP_PLAYER_BLOCK * 2;
                    }
                }
            }
        }
    }
	//collision about line
    for (BlockType* line : GLOBAL::LineArray)
    {
        if (IsCollisionDetect(*line))
        {
            ModifyByCollision(*line);
        }

        // When the collision is detected,
        if (IsCollisionDetect(*line))
        {
            // When the player is jumping
            if (GLOBAL::Player.aisJumping)
            {
                // If player is falling
                if (GLOBAL::velocity.getY() < 0)
                {
                    GLOBAL::velocity.initialization(0, 0);
                    if (absolute(aPosY - line->GetPositionY()) > line->GetHeight() / 2)
                    {
                        aPosY += aRadius / 2 -
                                 absolute(absolute(aPosY - line->GetPositionY()) - line->GetHeight() / 2) +
                                 GLOBAL::INIT_GAP_PLAYER_BLOCK;
                    }
                    else
                    {
                        aPosY += aRadius / 2 +
                                 absolute(absolute(aPosY - line->GetPositionY()) - line->GetHeight() / 2) +
                                 GLOBAL::INIT_GAP_PLAYER_BLOCK;
                    }
                }
                else
                {
                    if (absolute(aPosY - line->GetPositionY()) > line->GetHeight() / 2)
                    {
                        aPosY -= aRadius / 2 -
                                 absolute(absolute(aPosY - line->GetPositionY()) - line->GetHeight() / 2) +
                                 GLOBAL::INIT_GAP_PLAYER_BLOCK * 2;
                    }
                    else
                    {
                        aPosY -= aRadius / 2 +
                                 absolute(absolute(aPosY - line->GetPositionY()) - line->GetHeight() / 2) +
                                 GLOBAL::INIT_GAP_PLAYER_BLOCK * 2;
                    }
                }
            }
        }
    }

    // When player collisioned to checker block
    int CheckerSize = GLOBAL::StageCheckerArray.size();
    for (int i = 0; i < CheckerSize; i++)
    {
        LadderType* CheckerCounterTemp = GLOBAL::StageCheckerArray[i];
        if (IsCheckOnChecker(CheckerCounterTemp))
        {
            ++GLOBAL::PageNum;
            GLOBAL::StageCheckerArray.erase(GLOBAL::StageCheckerArray.begin() + i);
        }
    }

    // To check whether the player is on the ladder or not
    if (GLOBAL::PageNum == GAME_STATEMENT::doodle_3phase)
    {
        Player.aisEffectedGravity = true;
        // OnLadder is false in default
        bool OnLadder = false;
        for (LadderType* ladder : GLOBAL::LadderArray)
        {
            // If player is in the ladder
            if (IsCheckOnLadder(ladder))
            {
                OnLadder = true;
            }
        }
        if (OnLadder)
        {
            GLOBAL::Player.SetMoveAble(DIRECTION::UP, true);
            GLOBAL::Player.SetMoveAble(DIRECTION::DOWN, true);
            Player.aisEffectedGravity = false;
        }
        else
        {
            GLOBAL::Player.SetMoveAble(DIRECTION::UP, false);
            GLOBAL::Player.SetMoveAble(DIRECTION::DOWN, false);
        }
    }

    GLOBAL::Player_Collision_Helper.aPosX = GLOBAL::Player.aPosX;
    GLOBAL::Player_Collision_Helper.aPosY = GLOBAL::Player.aPosY - GLOBAL::INIT_GAP_PLAYER_BLOCK;

    // When player collisioned to wall
    if (GLOBAL::PageNum == GAME_STATEMENT::doodle_3phase)
    {
        for (BlockType* wall : GLOBAL::WallArray)
        {
            if (GLOBAL::Player_Collision_Helper.IsCollisionDetect(*wall))
            {
                Player.aisEffectedGravity = false;
                GLOBAL::Player.aisJumping = false;
                GLOBAL::velocity.initialization(0, 0);
            }
        }

        for (BlockType* line : GLOBAL::LineArray)
        {
            if (GLOBAL::Player_Collision_Helper.IsCollisionDetect(*line))
            {
                Player.aisEffectedGravity = false;
                GLOBAL::Player.aisJumping = false;
                GLOBAL::velocity.initialization(0, 0);
            }
        }

        // When the velocity is lower than specific value, that means that player is falling.
        if (GLOBAL::velocity.getY() < -GLOBAL::INIT_GAP_PLAYER_BLOCK)
        {
            GLOBAL::Player.aisJumping = true;
        }
    }
}

// To move the player
void PlayerType::Moving()
{
    if (Player.aisMoveLeft)
    {
        aPosX -= aSpeed;
    }
    if (Player.aisMoveRight)
    {
        aPosX += aSpeed;
    }
    if (Player.aisMoveUp)
    {
        aPosY += aSpeed;
    }
    if (Player.aisMoveDown)
    {
        aPosY -= aSpeed;
    }

    // When the phase is 1, map will follow
    if (PageNum == GAME_STATEMENT::doodle_1phase)
    {
        Map.MapFollow();
    }
    // At 4, map follow(2)
    else if (PageNum == GAME_STATEMENT::doodle_4phase)
    {
        Map.MapFollow2();
    }

    // When the phase is 2 or 3,
    else if (PageNum >= GAME_STATEMENT::doodle_2phase)
    {
        Map.MapExtend();
        if (PageNum == GAME_STATEMENT::doodle_3phase)
        {
            if (aisEffectedGravity)
            {
                AddPositionX(GLOBAL::velocity.getX());
                AddPositionY(GLOBAL::velocity.getY());
                GLOBAL::velocity.add(GLOBAL::gravity);
            }
        }
    }

    // When the player is out of the screen
    if (aPosX < -Width / 2 + aRadius / 4)
    {
        aPosX += aSpeed;
    }
    if (aPosX > Width / 2 - aRadius / 4)
    {
        aPosX -= aSpeed;
    }
    if (aPosY > Height / 2 - aRadius / 4)
    {
        aPosY -= aSpeed;
    }
    if (aPosY < -Height / 2 + aRadius / 4)
    {
        aPosY += aSpeed;
    }
}


float PlayerType::GetRadius() { return aRadius; }

float PlayerType::GetSpeed() { return aSpeed; }

void PlayerType::SetSpeed(float input) { aSpeed = input; }

void PlayerType::SetMoveAble(const DIRECTION& dir, const bool& true_or_false)
{
    switch (dir)
    {
        case DIRECTION::LEFT:
        {
            aisAbleMoveLeft = true_or_false;
            break;
        }
        case DIRECTION::RIGHT:
        {
            aisAbleMoveRight = true_or_false;
            break;
        }
        case DIRECTION::UP:
        {
            aisAbleMoveUp = true_or_false;
            break;
        }
        case DIRECTION::DOWN:
        {
            aisAbleMoveDown = true_or_false;
            break;
        }
    }
}

bool PlayerType::GetAbleMoveLeft() { return aisAbleMoveLeft; }

bool PlayerType::GetAbleMoveRight() { return aisAbleMoveRight; }

bool PlayerType::GetAbleMoveUp() { return aisAbleMoveUp; }

bool PlayerType::GetAbleMoveDown() { return aisAbleMoveDown; }