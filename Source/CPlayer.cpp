//
//  CPlayer.cpp
//  DeathMatchPrototype
//
//  Created by Tim Brier on 23/04/2015.
//  Copyright (c) 2015 tbrier. All rights reserved.
//

#include "CPlayer.hpp"
#include "CGlobals.hpp"
#include "CPlatform.hpp"
#include "CDMGame.hpp"
#include "CLevel.hpp"

CVector2f upDir = CVector2f(0.0f, -1.0f);
CVector2f downDir = CVector2f(0.0f, 1.0f);
CVector2f leftDir = CVector2f(-1.0f, 0.0f);
CVector2f rightDir = CVector2f(1.0f, 0.0f);

CPlayer::CPlayer()
:   mInputController(this)
{
    float halfWidth = CGlobals::playerHalfWidth;
    std::list<CVector2f> points;
    points.push_back(CVector2f(-halfWidth, -halfWidth));
    points.push_back(CVector2f(halfWidth, -halfWidth));
    points.push_back(CVector2f(halfWidth, halfWidth));
    points.push_back(CVector2f(-halfWidth, halfWidth));
    mShape  = CConvexShape(points);
    mShape.setFillColor(CColour::Green);
    
    mInitialJumpSpeed = 600.0f;
}

CPlayer::~CPlayer()
{
    
}

void CPlayer::Init(CVector2f startPos)
{
    mShape.setPosition(startPos);
    GroundSelf();
    mGravityVelocity = CVector2f(0.0f, 0.0f);
    mPlayerControlledVelocity = CVector2f(0.0f, 0.0f);
}

void CPlayer::Update(CTime elapsedTime)
{
    mInputController.Update(elapsedTime);
    
    switch (mState)
    {
        case kGrounded:
            if (!IsAboveGround())
            {
                UngroundSelf();
            }
            break;
            
        case kInAir:
            mGravityVelocity += CGlobals::gravity * elapsedTime.asSeconds();
            break;
            
        case kOnWall:
            CVector2f playerDirection = mPlayerControlledVelocity;
            playerDirection.Normalise();
            if ((playerDirection.x < 0 && mJumpDirection.x < 0)
                || (playerDirection.x > 0 && mJumpDirection.x > 0))
            {
                UngroundSelf();
            }
    }
    
    Move(elapsedTime);
}

void CPlayer::Draw(CWindow *theWindow)
{
    theWindow->DrawShape(mShape);
}

void CPlayer::Jump()
{
    if (mState == kGrounded || mState == kOnWall)
    {
        mGravityVelocity += mJumpDirection * mInitialJumpSpeed;
        UngroundSelf();
    }
}

void CPlayer::SetControlledVelocity(CVector2f theVelocity)
{
    mPlayerControlledVelocity = theVelocity;
    if (theVelocity.GetMagnitude() > 1.0f)
    {
        mGravityVelocity.x = 0.0f;
    }
}

void CPlayer::Move(CTime thisUpdateTime)
{
    CVector2f velocity = GetFullVelocity();
    mShape.move(velocity * thisUpdateTime.asSeconds());
}

CConvexShape CPlayer::GetHitbox()
{
    return mShape;
}

void CPlayer::ReactToCollisionWithPlatform(CVector2f correctionVector)
{
    mShape.move(correctionVector);
    
    correctionVector.Normalise();
    
    if (correctionVector == upDir && IsDecending())
    {
        GroundSelf();
    }
    
    if (correctionVector == downDir)
    {
        mGravityVelocity.y = 0;
    }
    
    if (correctionVector == leftDir || correctionVector == rightDir)
    {
        AttachToWall(correctionVector);
    }
}

void CPlayer::GroundSelf()
{
    mGravityVelocity = CVector2f(0.0f, 0.0f);
    mJumpDirection = upDir;
    mState = kGrounded;
}

void CPlayer::UngroundSelf()
{
    mState = kInAir;
}

void CPlayer::AttachToWall(CVector2f directionFromWall)
{
    if (mState == kInAir)
    {
        mState = kOnWall;
        mJumpDirection = directionFromWall + upDir;
        mJumpDirection.Normalise();
        mGravityVelocity = CVector2f(0.0f, 0.0f);
    }
}

bool CPlayer::IsDecending()
{
    return GetFullVelocity().y >= 0.0f;
}

bool CPlayer::IsAboveGround()
{
    bool theResult = false;
    
    // Check for a collision between the platforms and a hitbox 1 unit lower down
    std::list<CVector2f> points;
    points.push_back(CVector2f(-CGlobals::playerHalfWidth, 0.0f));
    points.push_back(CVector2f(CGlobals::playerHalfWidth, 0.0f));
    points.push_back(CVector2f(CGlobals::playerHalfWidth, 1.0f));
    points.push_back(CVector2f(-CGlobals::playerHalfWidth, 1.0f));
    CConvexShape hitbox = CConvexShape(points);
    hitbox.setPosition(mShape.getPosition() + CVector2f(0.0f, CGlobals::playerHalfWidth));
    
    if (CDMGame::Get()->GetCurrentLevel()->IsAPlatformHere(hitbox))
    {
        theResult = true;
    }
    
    return theResult;
}

CVector2f CPlayer::GetFullVelocity()
{
    return mGravityVelocity + mPlayerControlledVelocity;
}