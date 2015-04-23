//
//  CPlatform.hpp
//  DeathMatchPrototype
//
//  Created by Tim Brier on 23/04/2015.
//  Copyright (c) 2015 tbrier. All rights reserved.
//

#ifndef __DeathMatchPrototype__CPlatform__
#define __DeathMatchPrototype__CPlatform__

#include "CRenderable.hpp"

class CPlatform : public CRenderable
{
public:
    CPlatform(CVector2f topLeft, float width, float height);
    ~CPlatform();
    
    void Draw(CWindow *theWindow);
    
private:
    CConvexShape mShape;
};

#endif /* defined(__DeathMatchPrototype__CPlatform__) */
