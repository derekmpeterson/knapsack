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
    
}

void CollisionGadget::Draw()
{
    AABB pWorldExtents = GetWorldExtents();
    AABB pCameraExtents = g_camera->AABBToCameraSpace( pWorldExtents );
    SDL_Rect r = pCameraExtents.ToRect();
    
    SDL_SetRenderDrawColor( g_gameRenderer, 255, 0, 0, 255 );
    SDL_RenderDrawRect( g_gameRenderer, &r );
    
    Actor* pActor = ActorSystem::GetActor( m_actorHandle );
    if ( pActor )
    {
        Vector2d localPos = g_camera->VectorToCameraSpace( pActor->GetPos() );
        r.x = localPos.GetX() - 3.0f;
        r.y = localPos.GetY() - 3.0f;
        r.w = localPos.GetX() + 3.0f - r.x;
        r.h = localPos.GetY() + 3.0f - r.y;
        SDL_SetRenderDrawColor( g_gameRenderer, 0, 255, 0, 255 );
        SDL_RenderFillRect( g_gameRenderer, &r );
    }
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
