//
//  CollisionSystem.cpp
//  knapsack
//
//  Created by Derek Peterson on 5/9/15.
//  Copyright (c) 2015 Derek Peterson. All rights reserved.
//

#include "CollisionSystem.h"
#include "../Actor.h"
#include "ActorSystem.h"
#include "GadgetSystem.h"
#include "../Gadgets/CollisionGadget.h"
#include "DEFINES.H"

std::vector<ActorHandle> CollisionSystem::m_activeActors;

void CollisionSystem::Update( float dt )
{
    for(std::vector<ActorHandle>::iterator it = CollisionSystem::m_activeActors.begin(); it != CollisionSystem::m_activeActors.end(); it++)
    {
        ActorHandle pActorHandle = *it;
        CollisionGadget* pCG = GadgetSystem::GetGadget<CollisionGadget>( pActorHandle );
        ASSERTS( pCG, "Active actor in CollisionSystem doesn't have CollisionGadget!" );
        if ( pCG )
        {
            AABB pExtents = pCG->m_extents;
            float safeDistanceSquared = pExtents.SafeDistanceSquared();
            for(std::vector<ActorHandle>::iterator cit = CollisionSystem::m_activeActors.begin(); cit != CollisionSystem::m_activeActors.end(); cit++)
            {
                ActorHandle pOtherActorHandle = *cit;
                if ( pActorHandle == pOtherActorHandle )
                    continue;
                
                Actor* pActor = ActorSystem::GetActor( pActorHandle );
                Actor* pOtherActor = ActorSystem::GetActor( pOtherActorHandle );
                if ( pActor && pOtherActor )
                {
                    CollisionGadget* pOtherCG = GadgetSystem::GetGadget<CollisionGadget>( pOtherActorHandle );
                    ASSERTS( pCG, "Active actor in CollisionSystem doesn't have CollisionGadget!" );
                    if ( pOtherCG )
                    {
                        if ( pCG->m_juggernaut && pOtherCG->m_juggernaut )
                            continue; // we don't need juggernauts wasting time on each other
                        AABB pOtherExtents = pOtherCG->m_extents;
                        Vector2d diff = pActor->GetPos() - pOtherActor->GetPos();
                        float distanceSquared = diff.LengthSquared();
                        float otherSafeDistanceSquared = pOtherExtents.SafeDistanceSquared();
                        if ( distanceSquared < safeDistanceSquared || distanceSquared < otherSafeDistanceSquared )
                        {
                            std::cout << pActor->GetName() << " and " << pOtherActor->GetName() << " colcheck" << std::endl;
                        }
                    }
                }
            }
        }
    }

}

void CollisionSystem::Register( ActorHandle i_actorHandle )
{
    CollisionSystem::m_activeActors.push_back( i_actorHandle );
}

void CollisionSystem::Unregister( ActorHandle i_actorHandle )
{
    CollisionSystem::m_activeActors.erase(std::remove(CollisionSystem::m_activeActors.begin(), CollisionSystem::m_activeActors.end(), i_actorHandle), CollisionSystem::m_activeActors.end());
}