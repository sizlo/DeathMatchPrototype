//
//  CLevel.cpp
//  DeathMatchPrototype
//
//  Created by Tim Brier on 23/04/2015.
//  Copyright (c) 2015 tbrier. All rights reserved.
//

#include "CLevel.hpp"
#include "CDMGame.hpp"

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
    mPlatforms.push_back(new CPlatform(CVector2f(200.0f, GameOptions::viewHeight - 250.0f),
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
}

void CLevel::Exit()
{
    CDMGame::Get()->UnregisterUpdateable(this);
    CDMGame::Get()->UnregisterRenderable(this);
}

void CLevel::Update(CTime elapsedTime)
{
    
}

void CLevel::Draw(CWindow *theWindow)
{
    for (CPlatform *p: mPlatforms)
    {
        p->Draw(theWindow);
    }
}