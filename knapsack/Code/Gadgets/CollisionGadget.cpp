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

extern SDL_Renderer* g_gameRenderer;
extern Camera* g_camera;

GadgetRegister<CollisionGadget> CollisionGadget::reg("Collision");

CollisionGadget::CollisionGadget()
{
}

void CollisionGadget::Init()
{
    
}

void CollisionGadget::Update( float dt )
{
    
}

void CollisionGadget::Draw()
{
    Actor* pActor = ActorSystem::GetActor( m_actorHandle );
    ASSERTS( pActor, "Missing actor!" );
    if ( pActor )
    {
        Vector2d pos = pActor->GetPos();
        Vector2d localPos = g_camera->ToCameraCoords( pos );
        SDL_Rect r;
        r.x = localPos.GetX();
        r.y = localPos.GetY();
        r.w = 50;
        r.h = 50;
        SDL_SetRenderDrawColor( g_gameRenderer, 255, 0, 0, 255 );
        SDL_RenderFillRect( g_gameRenderer, &r );
    }
}