//
//  CPlayerInputController.cpp
//  DeathMatchPrototype
//
//  Created by Tim Brier on 23/04/2015.
//  Copyright (c) 2015 tbrier. All rights reserved.
//

#include "CPlayerInputController.hpp"
#include "CPlayer.hpp"
#include "CMessageBroadcaster.hpp"
#include "CGlobals.hpp"

int CPlayerInputController::smNextControllerIndex = 0;

CPlayerInputController::CPlayerInputController(CPlayer *controlledPlayer)
{
    mControlledPlayer = controlledPlayer;
    mControllerIndex = smNextControllerIndex;
    smNextControllerIndex++;
    
    CMessageBroadcaster<CEvent>::Subscribe(this);
}

CPlayerInputController::~CPlayerInputController()
{
    CMessageBroadcaster<CEvent>::Unsubscribe(this);
}

bool CPlayerInputController::HandleMessage(CEvent theEvent)
{
    bool eatMessage = false;
    
    if (theEvent.type == CEvent::JoystickButtonPressed &&
        theEvent.joystickButton.joystickId == mControllerIndex)
    {
        if (theEvent.joystickButton.button == 0)
        {
            mControlledPlayer->Jump();
        }
    }
    
    return eatMessage;
}

void CPlayerInputController::Update(CTime elapsedTime)
{
    float stickValue = CJoystick::getAxisPosition(mControllerIndex,
                                                  CJoystick::X);

    CVector2f velocity = CVector2f(0.0f, 0.0f);

    if (stickValue < -50.0f)
    {
        velocity.x = -CGlobals::playerControlledSpeed;
    }
    else if (stickValue > 50.0f)
    {
        velocity.x = CGlobals::playerControlledSpeed;
    }
    
    mControlledPlayer->SetControlledVelocity(velocity);
}