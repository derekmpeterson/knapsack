//
//  ActorSystem.cpp
//  knapsack
//
//  Created by Derek Peterson on 5/8/15.
//  Copyright (c) 2015 Derek Peterson. All rights reserved.
//

#include "ActorSystem.h"
#include <random>
#include "../ext/LuaScript.h"
#include "DEFINES.h"

std::map<ActorHandle,Actor*> ActorSystem::m_actors;

Actor* ActorSystem::CreateActor( std::string i_name )
{
    ActorHandle newHandle = rand() % 1000000000;
    while ( ActorSystem::m_actors.count( newHandle ) != 0 )
        newHandle = rand() % 1000000000;
    
    LuaScript script( "Content/Characters/"+i_name+".dna" );
    std::string name = script.get<std::string>("DNA.Name");
    std::string imagePath = script.get<std::string>("DNA.ImagePath");
    
    Actor* newActor = new Actor( name, imagePath );
    newActor->m_actorHandle = newHandle;
    
    
    std::vector<std::string> keys = script.getTableKeys("DNA");
    if ( std::find(keys.begin(), keys.end(), "Gadgets") != keys.end() )
    {
        // Gadgets table exists!
        keys = script.getTableKeys("DNA.Gadgets");
        for(std::vector<std::string>::iterator it = keys.begin(); it != keys.end(); it++) {
            std::string gadgetName = *it;
            newActor->AttachGadgetWithDNA( gadgetName, script );
        }
    }
    
    ActorSystem::m_actors.insert( std::make_pair( newHandle, newActor ) );
    return ActorSystem::GetActor( newHandle );
}

void ActorSystem::DeleteActor( ActorHandle i_actorHandle )
{
    delete ActorSystem::GetActor( i_actorHandle );
    ActorSystem::m_actors.erase( i_actorHandle );
}

Actor* ActorSystem::GetActor( ActorHandle i_actorHandle )
{
    ASSERTS( ActorSystem::m_actors.find( i_actorHandle ) != ActorSystem::m_actors.end(), "Trying to get invalid ActorHandle" );
    if ( ActorSystem::m_actors.find( i_actorHandle ) != ActorSystem::m_actors.end() )
        return ActorSystem::m_actors.at( i_actorHandle );
    else
        return NULL;
}