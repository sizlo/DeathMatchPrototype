//
//  CDMGame.cpp
//  DeathMatchPrototype
//
//  Created by Tim Brier on 08/04/2015.
//  Copyright (c) 2015 tbrier. All rights reserved.
//

#include "CDMGame.hpp"
#include "CLevel.hpp"

CDMGame * CDMGame::Get()
{
    return static_cast<CDMGame *>(CGame::Get());
}

CDMGame::CDMGame() : CGame("DeathMatchGame")
{
    mClearColour = CColour::White;
}

void CDMGame::InitialiseOptions()
{
    GameOptions::viewHeight = GameOptions::windowHeight;
    GameOptions::viewWidth = GameOptions::windowWidth;
}

void CDMGame::GoToLocation(int theLocation, std::string filename)
{
    // If we're already in a location leave it
    if (mCurrentLocation != NULL)
    {
        mCurrentLocation->Exit();
        SAFE_DELETE(mCurrentLocation);
    }
    
    switch (theLocation)
    {
        case kGameLocationLevel:
            DEBUG_LOG("Level requested");
            mCurrentLocation = new CLevel();
            break;
            
        default:
            DEBUG_LOG("Unimplemented game location - going to dummy location");
            mCurrentLocation = new CDummyGameLocation();
            break;
    }
    
    mCurrentLocation->Enter();
}