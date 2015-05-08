//
//  Actor.cpp
//  knapsack
//
//  Created by Derek Peterson on 5/7/15.
//  Copyright (c) 2015 Derek Peterson. All rights reserved.
//

#include "Actor.h"

extern SDL_Renderer* g_gameRenderer;

Actor::Actor( char* i_imageName ) : m_speed( 200 )
{
    m_texture = IMG_LoadTexture( g_gameRenderer, i_imageName );
    SDL_SetTextureBlendMode( m_texture, SDL_BLENDMODE_BLEND );
}

void Actor::Update( float dt )
{
    m_pos += m_acceleration * dt;
}

void Actor::Draw()
{
    SDL_Texture* pTexture = this->GetTexture();
    SDL_SetTextureBlendMode( pTexture, SDL_BLENDMODE_BLEND );
    
    if( pTexture )
    {
        Vector2d pActorPos = this->GetPos();
        SDL_Rect Rect = { (int) pActorPos.GetX(), (int) pActorPos.GetY(), 0, 0 };
        SDL_QueryTexture( pTexture, NULL, NULL, &Rect.w, &Rect.h );
        Rect.w *= 4;
        Rect.h *= 4;
        SDL_RenderCopy( g_gameRenderer, pTexture, NULL, &Rect );
    }
}