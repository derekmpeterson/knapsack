//
//  GravityGadget.h
//  knapsack
//
//  Created by Derek Peterson on 5/10/15.
//  Copyright (c) 2015 Derek Peterson. All rights reserved.
//

#ifndef __knapsack__GravityGadget__
#define __knapsack__GravityGadget__

#include <stdio.h>
#include "../ext/LuaScript.h"
#include "../Systems/GadgetSystem.h"
#include "Gadget.h"
#include "DEFINES.h"

class GravityGadget : public Gadget
{
public:
    GravityGadget();
    
    virtual void Init( ActorHandle i_actorHandle );
    virtual void DNADataInit( ActorHandle i_actorHandle, LuaScript& i_script );
    virtual void Update( float dt );
    virtual void Draw();
    
    static GadgetRegister<GravityGadget> reg;
};

#endif /* defined(__knapsack__GravityGadget__) */
