//
//  CPlatform.cpp
//  DeathMatchPrototype
//
//  Created by Tim Brier on 23/04/2015.
//  Copyright (c) 2015 tbrier. All rights reserved.
//

#include "CPlatform.hpp"

CPlatform::CPlatform(CVector2f topLeft, float width, float height)
{
    std::list<CVector2f> points;
    points.push_back(topLeft);
    points.push_back(topLeft + CVector2f(width, 0.0f));
    points.push_back(topLeft + CVector2f(width, height));
    points.push_back(topLeft + CVector2f(0.0f, height));
    mShape = CConvexShape(points);
    mShape.setFillColor(CColour::Blue);
}

CPlatform::~CPlatform()
{
    
}

void CPlatform::Draw(CWindow *theWindow)
{
    theWindow->DrawShape(mShape);
}

CConvexShape CPlatform::GetHitbox()
{
    return mShape;
}
