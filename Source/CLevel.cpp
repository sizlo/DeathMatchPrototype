//
//  CLevel.cpp
//  DeathMatchPrototype
//
//  Created by Tim Brier on 23/04/2015.
//  Copyright (c) 2015 tbrier. All rights reserved.
//

#include "CLevel.hpp"
#include "CDMGame.hpp"
#include "CGlobals.hpp"

CLevel::CLevel()
{
    mPlatforms.push_back(new CPlatform(CVector2f(0.0f, 0.0f),
                                       50.0f,
                                       GameOptions::viewHeight));
    mPlatforms.push_back(new CPlatform(CVector2f(GameOptions::viewWidth - 50.0f, 0.0f),
                                       50.0f,
                                       GameOptions::viewHeight));
    mPlatforms.push_back(new CPlatform(CVector2f(0.0f, GameOptions::viewHeight - 50.0f),
                                       GameOptions::viewWidth,
                                       50.0f));
    mPlatforms.push_back(new CPlatform(CVector2f(0.0f, 0.0f),
                                       GameOptions::viewWidth,
                                       50.0f));
    mPlatforms.push_back(new CPlatform(CVector2f(200.0f, GameOptions::viewHeight - 250.0f),
                                       300.0f,
                                       50.0f));
    mPlatforms.push_back(new CPlatform(CVector2f(600.0f, GameOptions::viewHeight - 400.0f),
                                       300.0f,
                                       50.0f));
    mPlatforms.push_back(new CPlatform(CVector2f(200.0f, GameOptions::viewHeight - 550.0f),
                                       300.0f,
                                       50.0f));
}

CLevel::~CLevel()
{
    FREE_LIST_CONTENTS(mPlatforms);
}

void CLevel::Enter()
{
    CDMGame::Get()->RegisterUpdateable(this);
    CDMGame::Get()->RegisterRenderable(this);
    
    CDMGame::Get()->SetGameState(kGameStateInGame);
    
    StartLevel();
}

void CLevel::Exit()
{
    CDMGame::Get()->UnregisterUpdateable(this);
    CDMGame::Get()->UnregisterRenderable(this);
    
    CDMGame::Get()->UnsetGameState(kGameStateInGame);
}

void CLevel::StartLevel()
{
    mPlayer.Init(CVector2f(800.0f, GameOptions::viewHeight - (50.0f + CGlobals::playerHalfWidth)));
}

void CLevel::Update(CTime elapsedTime)
{
    mPlayer.Update(elapsedTime);
    HandleCollisions();
}

void CLevel::Draw(CWindow *theWindow)
{
    for (CPlatform *p: mPlatforms)
    {
        p->Draw(theWindow);
    }
    
    mPlayer.Draw(theWindow);
}

bool CLevel::IsAPlatformHere(CConvexShape hitbox,
                             CVector2f *correctionVector /* = NULL */)
{
    bool theResult = false;
    
    for (CPlatform *p: mPlatforms)
    {
        CVector2f cv;
        if (p->GetHitbox().IsCollidingWith(hitbox, &cv))
        {
            if (correctionVector != NULL)
            {
                correctionVector->x = cv.x;
                correctionVector->y = cv.y;
            }
            theResult = true;
            break;
        }
    }
    
    return theResult;
}

void CLevel::HandleCollisions()
{
    // Player vs platforms
    for (CPlatform *p: mPlatforms)
    {
        CConvexShape platformHitbox = p->GetHitbox();
        CVector2f cv;
        if (mPlayer.GetHitbox().IsCollidingWith(platformHitbox, &cv))
        {
            mPlayer.ReactToCollisionWithPlatform(cv);
        }
    }
}