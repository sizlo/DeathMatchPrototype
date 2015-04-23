//
//  CLevel.hpp
//  DeathMatchPrototype
//
//  Created by Tim Brier on 23/04/2015.
//  Copyright (c) 2015 tbrier. All rights reserved.
//

#ifndef __DeathMatchPrototype__CLevel__
#define __DeathMatchPrototype__CLevel__

#include "CUpdateable.hpp"
#include "CRenderable.hpp"
#include "CGameLocation.hpp"
#include "CPlatform.hpp"

class CLevel : public CUpdateable, public CRenderable, public CGameLocation
{
public:
    CLevel();
    ~CLevel();
    
    void Update (CTime elapsedTime);
    void Draw (CWindow *theWindow);
    void Enter();
    void Exit();
    
private:
    std::list<CPlatform *> mPlatforms;
};

#endif /* defined(__DeathMatchPrototype__CLevel__) */
