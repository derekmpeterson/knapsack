//
//  CollisionSystem.h
//  knapsack
//
//  Created by Derek Peterson on 5/9/15.
//  Copyright (c) 2015 Derek Peterson. All rights reserved.
//

#ifndef __knapsack__CollisionSystem__
#define __knapsack__CollisionSystem__

#include <stdio.h>
#include <vector>
#include "../ext/Vector2d.h"
#include "Box2D/Box2D.h"

typedef int ActorHandle;

class ContactListener : public b2ContactListener
{
private:
    ActorHandle m_actorHandle;
public:
    ContactListener(){};
    void BeginContact( b2Contact *contact );
    void EndContact( b2Contact *contact );
};

class CollisionSystem
{
public:
    static std::vector<ActorHandle> m_activeActors;
    
    static void Update( float dt );
    
    static void Register( ActorHandle i_actorHandle );
    static void Unregister( ActorHandle i_actorHandle );
    
    static void Init();
    
    static Vector2d m_gravity;
    static b2World m_world;
    static ContactListener m_contactListener;
    
    static float32 m_timeStep;
    static int32 m_velocityIterations;
    static int32 m_positionIterations;
    static float32 m_accumulator;
};

#endif /* defined(__knapsack__CollisionSystem__) */