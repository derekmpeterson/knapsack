//
//  CollisionGadget.h
//  knapsack
//
//  Created by Derek Peterson on 5/8/15.
//  Copyright (c) 2015 Derek Peterson. All rights reserved.
//

#ifndef __knapsack__CollisionGadget__
#define __knapsack__CollisionGadget__

#include <stdio.h>
#include <string>
#include "Gadget.h"
#include "../Systems/GadgetSystem.h"
#include "../ext/AABB.h"

class CollisionGadget : public Gadget
{
public:
    CollisionGadget();
    
    virtual void Init( ActorHandle i_actorHandle );
    virtual void DNADataInit( ActorHandle i_actorHandle, LuaScript& script );
    virtual void Update( float dt );
    virtual void Draw();
    
    static GadgetRegister<CollisionGadget> reg;
    
    AABB m_extents;
    AABB GetWorldExtents();
    
    bool m_juggernaut;
};

#endif /* defined(__knapsack__CollisionGadget__) */
