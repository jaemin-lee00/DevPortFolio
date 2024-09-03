/*
  System.h

  GAM100 Prototype2
  Fall 2019

 Jaemin Lee wrote this all
 Byeongjun Kim
 Sangjin Lee

  All content © 2019 DigiPen (USA) Corporation, all rights reserved.
*/
#pragma once
#include "Enum.h"

class SystemType
{
protected:
    SystemType();
    int aObjectKind;

    /// member varibale about Position
    float aPosX;
    float aPosY;

    // it's about volume
    float aRadius = 0;
    float aWidth = 0;
    float aHeight = 0;


    float aSpeed = 0;

    bool IsCollisionDetect(SystemType&);
    bool IsCollisionDetectWall();
    void PushedBy(SystemType&);
    void ModifyByCollision(SystemType&);
    void ModifyByWall();


public:
    bool aisMoveLeft{false};
    bool aisMoveRight{false};
    bool aisMoveUp{false};
    bool aisMoveDown{false};

    SystemType(float positionX = 0, float positionY = 0, float radius = 0)
        : aPosX(positionX), aPosY(positionY), aRadius(radius), aObjectKind(OBJECT_KIND::ITEM), aSpeed(0) {};

    SystemType(float positionX , float positionY , float radius , float speed )
        : aSpeed(speed), aObjectKind(OBJECT_KIND::PLAYER), aPosX(positionX), aPosY(positionY), aRadius(radius){};

    SystemType(float positionX, float positionY, float width, float height, float speed)
        : aSpeed(speed), aObjectKind(OBJECT_KIND::BLOCK), aPosX(positionX), aPosY(positionY), aWidth(width),aHeight(height){};

    SystemType(float positionX, float positionY, float width, float height, float speed, int object_kind)
        : aSpeed(speed), aObjectKind(object_kind), aPosX(positionX), aPosY(positionY), aWidth(width), aHeight(height){};

	void AddPositionX(float X);
    void AddPositionY(float Y);

    float GetPositionX();
    float GetPositionY();

    float GetWidth();
    float GetHeight();

    float GetSpeed();

    float SystemUpdate();
};