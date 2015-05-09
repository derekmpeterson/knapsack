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
#include <string>

typedef int ActorHandle;

class ActorSystem
{
public:
    static std::map<ActorHandle,Actor*> m_actors;
    static Actor* CreateActor( std::string i_name );
    static void DeleteActor( ActorHandle i_actorHandle );
    
    static Actor* GetActor( ActorHandle i_actorHandle );
};

#endif /* defined(__knapsack__ActorSystem__) */
