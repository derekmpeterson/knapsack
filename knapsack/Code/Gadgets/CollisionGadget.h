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
#include "DEFINES.h"
#include "Box2D/Box2D.h"

typedef int ActorHandle;

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
    AABB GetWorldExtents( AABB& i_extents );
    AABB m_groundSensorExtents;
    
    bool m_juggernaut;
#ifdef DEBUG_COLLISON
    bool m_intersecting;
#endif
    bool m_onGround;
    
    b2Body* m_b2Body;
    b2Body* m_groundSensorBody;
    
    void GroundSensorBeginContact( b2Contact* contact );
    void GroundSensorEndContact( b2Contact* contact );
};

#endif /* defined(__knapsack__CollisionGadget__) */
