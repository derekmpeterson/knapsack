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
Vector2d CollisionSystem::m_gravity;
b2World CollisionSystem::m_world( Vector2d( 0.0f, 0.0f ) );

float32 CollisionSystem::m_timeStep;
int32 CollisionSystem::m_velocityIterations;
int32 CollisionSystem::m_positionIterations;
float32 CollisionSystem::m_accumulator;

ContactListener CollisionSystem::m_contactListener;

void CollisionSystem::Init()
{
    m_timeStep = 1.0f / 60.0f;
    m_velocityIterations = 6;
    m_positionIterations = 2;
    m_accumulator = 0.0f;
    
    m_gravity = Vector2d( 0.0f, -200.0f );
    m_contactListener = ContactListener();
    m_world.SetAllowSleeping(true);
    m_world.SetContinuousPhysics(true);
    m_world.SetContactListener( &m_contactListener );
    m_world.SetGravity( m_gravity );
}
void CollisionSystem::Update( float dt )
{
    m_accumulator += dt;
    while ( m_accumulator > m_timeStep )
    {
        m_accumulator -= m_timeStep;
        m_world.Step( m_timeStep, m_velocityIterations, m_positionIterations );
    }
    /*for(std::vector<ActorHandle>::iterator it = CollisionSystem::m_activeActors.begin(); it != CollisionSystem::m_activeActors.end(); it++)
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
                            //std::cout << pActor->GetName() << " and " << pOtherActor->GetName() << " colcheck" << std::endl;
                            AABB pWorldExtents = pCG->GetWorldExtents();
                            AABB pOtherWorldExtents = pOtherCG->GetWorldExtents();
                            Vector2d proposedResolution;
                            if ( pWorldExtents.Intersects( pOtherWorldExtents, proposedResolution ) )
                            {
                                //std::cout << pActor->GetName() << " -> " << pOtherActor->GetName() << " Intersect!" << std::endl;
                                pCG->m_intersecting = true;
                                if ( !pCG->m_juggernaut && pOtherCG->m_juggernaut )
                                {
                                    pActor->SetPos( pActor->GetPos() + proposedResolution );
                                }
                                else if ( !pCG->m_juggernaut && !pOtherCG->m_juggernaut )
                                {
                                    pActor->SetPos( pActor->GetPos() + ( proposedResolution * 0.5f ) );
                                }
                                
                            }
                        }
                    }
                }
            }
        }
    }*/

}

void CollisionSystem::Register( ActorHandle i_actorHandle )
{
    CollisionSystem::m_activeActors.push_back( i_actorHandle );
}

void CollisionSystem::Unregister( ActorHandle i_actorHandle )
{
    CollisionSystem::m_activeActors.erase(std::remove(CollisionSystem::m_activeActors.begin(), CollisionSystem::m_activeActors.end(), i_actorHandle), CollisionSystem::m_activeActors.end());
}

void ContactListener::BeginContact( b2Contact* contact )
{
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();
    
    //make sure only one of the fixtures was a sensor
    bool sensorA = fixtureA->IsSensor();
    bool sensorB = fixtureB->IsSensor();
    if ( ! (sensorA ^ sensorB) )
        return;
    
    CollisionGadget* pCollisionGadget  = NULL;
    if ( sensorA )
        pCollisionGadget = (CollisionGadget*) fixtureA->GetUserData();
    if ( sensorB )
        pCollisionGadget = (CollisionGadget*) fixtureB->GetUserData();
    
    if ( pCollisionGadget )
    {
        Actor* pActor = ActorSystem::GetActor( pCollisionGadget->m_actorHandle );
        std::cout << pActor->GetName() << " sensor contact!" << std::endl;
        
        pCollisionGadget->GroundSensorBeginContact( contact );
    }
}

void ContactListener::EndContact( b2Contact *contact )
{
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();
    
    //make sure only one of the fixtures was a sensor
    bool sensorA = fixtureA->IsSensor();
    bool sensorB = fixtureB->IsSensor();
    if ( ! (sensorA ^ sensorB) )
        return;
    
    CollisionGadget* pCollisionGadget  = NULL;
    if ( sensorA )
        pCollisionGadget = (CollisionGadget*) fixtureA->GetUserData();
    if ( sensorB )
        pCollisionGadget = (CollisionGadget*) fixtureB->GetUserData();
    
    if ( pCollisionGadget )
    {
        Actor* pActor = ActorSystem::GetActor( pCollisionGadget->m_actorHandle );
        std::cout << pActor->GetName() << " sensor contact end!" << std::endl;
        
        pCollisionGadget->GroundSensorEndContact( contact );
    }
}