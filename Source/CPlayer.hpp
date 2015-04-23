//
//  CPlayer.hpp
//  DeathMatchPrototype
//
//  Created by Tim Brier on 23/04/2015.
//  Copyright (c) 2015 tbrier. All rights reserved.
//

#ifndef __DeathMatchPrototype__CPlayer__
#define __DeathMatchPrototype__CPlayer__

#include "CUpdateable.hpp"
#include "CRenderable.hpp"
#include "CPlayerInputController.hpp"

enum EPlayerState
{
    kGrounded,
    kInAir,
    kOnWall
};

class CPlayer : public CUpdateable, public CRenderable
{
public:
    CPlayer();
    ~CPlayer();
    
    void Init(CVector2f startPos);
    
    void Update(CTime elapsedTime);
    void Draw(CWindow *theWindow);
    
    void Jump();
    void SetControlledVelocity(CVector2f theVelocity);
    void Move(CTime thisUpdateTime);
    
    CConvexShape GetHitbox();
    void ReactToCollisionWithPlatform(CVector2f correctionVector);
    
private:
    void GroundSelf();
    void UngroundSelf();
    void AttachToWall(CVector2f directionFromWall);
    bool IsDecending();
    bool IsAboveGround();
    
    CVector2f GetFullVelocity();
    
    CConvexShape mShape;
    EPlayerState mState;
    CVector2f mGravityVelocity;
    CVector2f mPlayerControlledVelocity;
    float mInitialJumpSpeed;
    CVector2f mJumpDirection;
    
    CPlayerInputController mInputController;
};

#endif /* defined(__DeathMatchPrototype__CPlayer__) */
