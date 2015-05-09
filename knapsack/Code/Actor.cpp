//
//  Actor.cpp
//  knapsack
//
//  Created by Derek Peterson on 5/7/15.
//  Copyright (c) 2015 Derek Peterson. All rights reserved.
//

#include "Actor.h"
#include "Systems/ActorSystem.h"
#include "Systems/GadgetSystem.h"
#include "Camera.h"
#include "DEFINES.h"

extern SDL_Renderer* g_gameRenderer;
extern ActorSystem* g_actorSystem;
extern Camera* g_camera;

Actor::Actor( std::string i_imageName ) : m_speed( 200 )
{
    i_imageName = "Content/" + i_imageName;
    m_texture = IMG_LoadTexture( g_gameRenderer, i_imageName.c_str() );
    SDL_SetTextureBlendMode( m_texture, SDL_BLENDMODE_BLEND );
}

void Actor::Update( float dt )
{
    for (std::vector<Gadget*>::iterator it = m_gadgets.begin() ; it != m_gadgets.end(); ++it)
    {
        Gadget* pGadget = *it;
        if ( pGadget )
            pGadget->Update( dt );
    }
    m_pos += m_acceleration * dt;
}

void Actor::Draw()
{
    SDL_Texture* pTexture = this->GetTexture();
    SDL_SetTextureBlendMode( pTexture, SDL_BLENDMODE_BLEND );
    
    if( pTexture )
    {
        int pWidth = 0;
        int pHeight = 0;
        SDL_QueryTexture( pTexture, NULL, NULL, &pWidth, &pHeight );
        
        Vector2d pActorPos = this->GetPos();
        Vector2d pLocalPos = g_camera->ToCameraCoords( pActorPos );
        pLocalPos.SetX( pLocalPos.GetX() - ( 0.5f * pWidth ) );
        pLocalPos.SetY( pLocalPos.GetY() - ( 0.5f * pHeight ) );
        SDL_Rect Rect = { (int) pLocalPos.GetX(), (int) pLocalPos.GetY(), pWidth, pHeight };
        SDL_RenderCopy( g_gameRenderer, pTexture, NULL, &Rect );
    }
    
    for (std::vector<Gadget*>::iterator it = m_gadgets.begin() ; it != m_gadgets.end(); ++it)
    {
        Gadget* pGadget = *it;
        if ( pGadget )
            pGadget->Draw();
    }
}

void Actor::AttachGadget( std::string i_gadgetType )
{
    Gadget* gadget = GadgetSystem::CreateInstance( i_gadgetType );
    ASSERTS( gadget, "Attempting to attach invalid gadget type '"+i_gadgetType+"'" );
    gadget->m_actorHandle = m_actorHandle;
    m_gadgets.push_back( gadget );
}