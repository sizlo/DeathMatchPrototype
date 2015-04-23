//
//  Main.cpp
//  DeathMatchPrototype
//
//  Created by Tim Brier on 08/04/2015.
//  Copyright (c) 2015 tbrier. All rights reserved.
//

#include "CDMGame.hpp"

int main(int argc, char **argv)
{
    CDMGame theGame;
    theGame.Init(kGameLocationDummy);
    int returnCode = theGame.Run();
    theGame.Cleanup();
    
    return returnCode;
}
