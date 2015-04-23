//
//  CPlayerInputController.hpp
//  DeathMatchPrototype
//
//  Created by Tim Brier on 23/04/2015.
//  Copyright (c) 2015 tbrier. All rights reserved.
//

#ifndef __DeathMatchPrototype__CPlayerInputController__
#define __DeathMatchPrototype__CPlayerInputController__

#include "CMessageListener.hpp"
#include "CUpdateable.hpp"
#include "SFMLIntegration/SFMLIntegration.hpp"

class CPlayer;

class CPlayerInputController :  public CMessageListener<CEvent>,
                                public CUpdateable
{
public:
    CPlayerInputController(CPlayer *controlledPlayer);
    ~CPlayerInputController();
    
    bool HandleMessage(CEvent theEvent);
    void Update(CTime elapsedTime);
    
private:
    CPlayer *mControlledPlayer;
    int mControllerIndex;
    
    static int smNextControllerIndex;
};

#endif /* defined(__DeathMatchPrototype__CPlayerInputController__) */
