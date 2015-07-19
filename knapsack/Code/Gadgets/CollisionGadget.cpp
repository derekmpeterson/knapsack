//
//  CollisionGadget.cpp
//  knapsack
//
//  Created by Derek Peterson on 5/8/15.
//  Copyright (c) 2015 Derek Peterson. All rights reserved.
//

#include "CollisionGadget.h"
#include "SDL2/SDL.h"
#include "SDL2_Image/SDL_Image.h"
#include "../Camera.h"
#include "../Systems/ActorSystem.h"
#include "DEFINES.h"
#include <vector>
#include "../Systems/CollisionSystem.h"

extern SDL_Renderer* g_gameRenderer;
extern Camera* g_camera;
extern b2World g_world;

GadgetRegister<CollisionGadget> CollisionGadget::reg("Collision");

CollisionGadget::CollisionGadget()
{
    m_juggernaut = false;
    m_onGround = false;
}

void CollisionGadget::Init( ActorHandle i_actorHandle )
{
    m_actorHandle = i_actorHandle;
    CollisionSystem::Register( m_actorHandle );
}

void CollisionGadget::DNADataInit( ActorHandle i_actorHandle, LuaScript& script )
{
    Init( i_actorHandle );
    
    std::vector<float> pExtents = script.getFloatVector( "DNA.Gadgets.Collision.Extents" );
    float pFriction = script.get<float>( "DNA.Gadgets.Collision.Friction" );
    ASSERTS( pExtents.size() == 4, "Incorrect extents vector" );
    m_extents.SetMinExtents( Vector2d( pExtents[0], pExtents[1] ) );
    m_extents.SetMaxExtents( Vector2d( pExtents[2], pExtents[3] ) );
    m_juggernaut = script.get<bool>( "DNA.Gadgets.Collision.Juggernaut" );
    
    Actor* pActor = ActorSystem::GetActor( m_actorHandle );
    if ( pActor )
    {
        b2BodyDef bodyDef;
        if ( !m_juggernaut )
            bodyDef.type = b2_dynamicBody;
        bodyDef.position = pActor->GetPos() + m_extents.GetCenter();
        bodyDef.fixedRotation = true;
        m_b2Body = CollisionSystem::m_world.CreateBody( &bodyDef );
        
        Vector2d pHalfLength = m_extents.GetHalfLength();
        b2PolygonShape box;
        box.SetAsBox( pHalfLength.GetX(), pHalfLength.GetY() );
        
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &box;
        fixtureDef.density = 0.25f;
        fixtureDef.friction = pFriction;
        fixtureDef.userData = this;
        
        m_b2Body->CreateFixture( &fixtureDef );
        
        
        if ( !m_juggernaut )
        {
            b2BodyDef groundSensorDef;
            groundSensorDef.type = b2_dynamicBody;
            groundSensorDef.position = pActor->GetPos() + Vector2d( m_extents.GetCenter().GetX(), m_extents.GetMinExtents().GetY() );
            groundSensorDef.fixedRotation = true;
            m_groundSensorBody = CollisionSystem::m_world.CreateBody( &groundSensorDef );
            
            pHalfLength = m_extents.GetHalfLength();
            m_groundSensorExtents.SetMinExtents(
                Vector2d(
                    pHalfLength.GetX() * -0.95f,
                    pHalfLength.GetY() * -0.5f
                )
            );
            m_groundSensorExtents.SetMaxExtents(
                Vector2d(
                    pHalfLength.GetX() * 0.95f,
                    0.01f
                )
            );
            pHalfLength = m_groundSensorExtents.GetHalfLength();
            box.SetAsBox( pHalfLength.GetX(), pHalfLength.GetY() );
            
            b2FixtureDef gsFixtureDef;
            gsFixtureDef.shape = &box;
            gsFixtureDef.isSensor = true;
            gsFixtureDef.userData = this;

            m_groundSensorBody->CreateFixture( &gsFixtureDef );
        }
    }
}

void CollisionGadget::Update( float dt )
{
#ifdef DEBUG_COLLISON
    m_intersecting = false;
#endif
    Actor* pActor = ActorSystem::GetActor( m_actorHandle );
    if ( pActor )
    {
        Vector2d pAcceleration = pActor->GetAcceleration();
        if ( pAcceleration.GetX() != 0.0f )
        {
            float xVel = m_b2Body->GetLinearVelocity().x;
            float xVelChange = pAcceleration.GetX() - xVel;
            float xImpulse = xVelChange * m_b2Body->GetMass();
            
            m_b2Body->ApplyLinearImpulse( Vector2d( xImpulse, 0.0f ), m_b2Body->GetWorldCenter(), true );
        }
        if ( pAcceleration.GetY() != 0.0f )
        {
            float yVel = m_b2Body->GetLinearVelocity().y;
            float yVelChange = pAcceleration.GetY() - yVel;
            float yImpulse = yVelChange * m_b2Body->GetMass();
            
            m_b2Body->ApplyLinearImpulse( Vector2d( 0.0f, yImpulse ), m_b2Body->GetWorldCenter(), true );
        }
    
        Vector2d bodyPos = Vector2d( m_b2Body->GetWorldCenter().x, m_b2Body->GetWorldCenter().y );
        pActor->SetPos( bodyPos - m_extents.GetCenter() );
        
        if ( !m_juggernaut )
        {
            Vector2d groundSensorPos = pActor->GetPos() + Vector2d( m_extents.GetCenter().GetX(), m_extents.GetMinExtents().GetY() );
            m_groundSensorBody->SetTransform( groundSensorPos, 0.0f );
        }
    }
}

void CollisionGadget::Draw()
{
#ifdef DEBUG_COLLISON
    AABB pWorldExtents = GetWorldExtents( m_extents );
    AABB pCameraExtents = g_camera->AABBToCameraSpace( pWorldExtents );
    SDL_Rect r = pCameraExtents.ToRect();
    
    SDL_SetRenderDrawColor( g_gameRenderer, 255, 0, 0, 255 );
    SDL_RenderDrawRect( g_gameRenderer, &r );
    
    if ( !m_juggernaut )
    {
        Vector2d groundSensorPos = Vector2d( m_groundSensorBody->GetWorldCenter().x, m_groundSensorBody->GetWorldCenter().y );
        
        AABB pSensorWorldExtents = GetWorldExtents( m_groundSensorExtents );
        AABB pSensorCameraExtents = g_camera->AABBToCameraSpace( pSensorWorldExtents );
        
        SDL_Rect sensor_rect = pSensorCameraExtents.ToRect();
        SDL_SetRenderDrawBlendMode( g_gameRenderer, SDL_BLENDMODE_BLEND );
        if ( m_onGround )
            SDL_SetRenderDrawColor( g_gameRenderer, 0, 255, 0, 95 );
        else
            SDL_SetRenderDrawColor( g_gameRenderer, 255, 0, 0, 95 );
        SDL_RenderFillRect( g_gameRenderer, &sensor_rect );
    }
    
    if ( m_intersecting )
    {
        SDL_SetRenderDrawBlendMode( g_gameRenderer, SDL_BLENDMODE_BLEND );
        SDL_SetRenderDrawColor( g_gameRenderer, 255, 0, 0, 95 );
        SDL_RenderFillRect( g_gameRenderer, &r );
    }
#endif
}

AABB CollisionGadget::GetWorldExtents( AABB& i_extents)
{
    AABB pWorldExtents = i_extents;
    Actor* pActor = ActorSystem::GetActor( m_actorHandle );
    ASSERTS( pActor, "Missing actor!" );
    if ( pActor )
    {
        pWorldExtents.SetMinExtents( pWorldExtents.GetMinExtents() + pActor->GetPos() );
        pWorldExtents.SetMaxExtents( pWorldExtents.GetMaxExtents() + pActor->GetPos() );
    }
    return pWorldExtents;
}

void CollisionGadget::GroundSensorBeginContact( b2Contact* contact )
{
    m_onGround = true;
}

void CollisionGadget::GroundSensorEndContact( b2Contact* contact )
{
    m_onGround = false;
}