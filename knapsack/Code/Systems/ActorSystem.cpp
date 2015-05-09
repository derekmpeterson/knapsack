//
//  ActorSystem.cpp
//  knapsack
//
//  Created by Derek Peterson on 5/8/15.
//  Copyright (c) 2015 Derek Peterson. All rights reserved.
//

#include "ActorSystem.h"
#include <random>

std::map<ActorHandle,Actor> ActorSystem::m_actors;

Actor* ActorSystem::CreateActor( char* i_imageName )
{
    ActorHandle newHandle = rand() % 1000000000;
    while ( ActorSystem::m_actors.count( newHandle ) != 0 )
        newHandle = rand() % 1000000000;
    Actor newActor = Actor( i_imageName );
    newActor.m_actorHandle = newHandle;
    
    ActorSystem::m_actors.insert( std::make_pair( newHandle, newActor ) );
    return ActorSystem::GetActor( newHandle );
}

Actor* ActorSystem::GetActor( ActorHandle i_actorHandle )
{
    return &ActorSystem::m_actors.at( i_actorHandle );
}