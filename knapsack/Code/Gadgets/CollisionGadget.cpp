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

GadgetRegister<CollisionGadget> CollisionGadget::reg("Collision");

CollisionGadget::CollisionGadget()
{
    m_juggernaut = false;
}

void CollisionGadget::Init( ActorHandle i_actorHandle )
{
    m_actorHandle = i_actorHandle;
    CollisionSystem::Register( m_actorHandle );
}

void CollisionGadget::DNADataInit( ActorHandle i_actorHandle, LuaScript& script )
{
    Init( i_actorHandle );
    
    std::vector<int> pExtents = script.getIntVector( "DNA.Gadgets.Collision.Extents" );
    ASSERTS( pExtents.size() == 4, "Incorrect extents vector" );
    m_extents.SetMinExtents( Vector2d( pExtents[0], pExtents[1] ) );
    m_extents.SetMaxExtents( Vector2d( pExtents[2], pExtents[3] ) );
    m_juggernaut = script.get<bool>( "DNA.Gadgets.Collision.Juggernaut" );
    std::cout << "Juggernaut: " << m_juggernaut << std::endl;
}

void CollisionGadget::Update( float dt )
{
#ifdef DEBUG_COLLISON
    m_intersecting = false;
#endif
}

void CollisionGadget::Draw()
{
#ifdef DEBUG_COLLISON
    AABB pWorldExtents = GetWorldExtents();
    AABB pCameraExtents = g_camera->AABBToCameraSpace( pWorldExtents );
    SDL_Rect r = pCameraExtents.ToRect();
    
    SDL_SetRenderDrawColor( g_gameRenderer, 255, 0, 0, 255 );
    SDL_RenderDrawRect( g_gameRenderer, &r );
    
    if ( m_intersecting )
    {
        SDL_SetRenderDrawBlendMode( g_gameRenderer, SDL_BLENDMODE_BLEND );
        SDL_SetRenderDrawColor( g_gameRenderer, 255, 0, 0, 95 );
        SDL_RenderFillRect( g_gameRenderer, &r );
    }
#endif
}

AABB CollisionGadget::GetWorldExtents()
{
    AABB pWorldExtents = m_extents;
    Actor* pActor = ActorSystem::GetActor( m_actorHandle );
    ASSERTS( pActor, "Missing actor!" );
    if ( pActor )
    {
        pWorldExtents.SetMinExtents( pWorldExtents.GetMinExtents() + pActor->GetPos() );
        pWorldExtents.SetMaxExtents( pWorldExtents.GetMaxExtents() + pActor->GetPos() );
    }
    return pWorldExtents;
}
