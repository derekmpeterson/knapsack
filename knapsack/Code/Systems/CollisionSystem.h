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

typedef int ActorHandle;

class CollisionSystem
{
public:
    static std::vector<ActorHandle> m_activeActors;
    
    static void Update( float dt );
    
    static void Register( ActorHandle i_actorHandle );
    static void Unregister( ActorHandle i_actorHandle );
};

#endif /* defined(__knapsack__CollisionSystem__) */