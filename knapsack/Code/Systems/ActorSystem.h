//
//  ActorSystem.h
//  knapsack
//
//  Created by Derek Peterson on 5/8/15.
//  Copyright (c) 2015 Derek Peterson. All rights reserved.
//

#ifndef __knapsack__ActorSystem__
#define __knapsack__ActorSystem__

#include <stdio.h>
#include "Actor.h"
#include <map>

typedef int ActorHandle;

class ActorSystem
{
public:
    static std::map<ActorHandle,Actor> m_actors;
    static Actor* CreateActor( char* i_imageName );
    
    static Actor* GetActor( ActorHandle i_actorHandle );
};

#endif /* defined(__knapsack__ActorSystem__) */
