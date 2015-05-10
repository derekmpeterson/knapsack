//
//  Gadget.h
//  knapsack
//
//  Created by Derek Peterson on 5/8/15.
//  Copyright (c) 2015 Derek Peterson. All rights reserved.
//

#ifndef __knapsack__Gadget__
#define __knapsack__Gadget__

#include <stdio.h>
#include <string>
#include "../ext/LuaScript.h"

typedef int ActorHandle;

class Gadget
{
public:
    std::string m_gadgetType;
    
    ActorHandle m_actorHandle;
    
    Gadget();
    
    virtual void Init( ActorHandle i_actorHandle );
    virtual void DNADataInit( ActorHandle i_actorHandle, LuaScript& i_script );
    virtual void Update( float dt );
    virtual void Draw();
};

#endif /* defined(__knapsack__Gadget__) */
