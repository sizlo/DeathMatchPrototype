//
//  CDMGame.hpp
//  DeathMatchPrototype
//
//  Created by Tim Brier on 08/04/2015.
//  Copyright (c) 2015 tbrier. All rights reserved.
//

#ifndef __DeathMatchPrototype__CDMGame__
#define __DeathMatchPrototype__CDMGame__

#include "CGame.hpp"

class CLevel;

enum EDMGameLocation
{
    kGameLocationLevel = kGameLocationDummy + 1
};

class CDMGame : public CGame
{
public:
    static CDMGame * Get();
    
    CDMGame();
    
    void InitialiseOptions();
    void GoToLocation(int theLocation, std::string filename);
    CLevel * GetCurrentLevel();

};

#endif /* defined(__DeathMatchPrototype__CDMGame__) */
