//
//  Player.cpp
//  knapsack
//
//  Created by Derek Peterson on 5/7/15.
//  Copyright (c) 2015 Derek Peterson. All rights reserved.
//

#include "Player.h"
#include "CollisionGadget.h"

void Player::Update( float dt)
{
    Vector2d currentAccel = m_actor->GetAcceleration();
    float x = currentAccel.GetX();
    float y = currentAccel.GetY();
    
    CollisionGadget* pCollisionGadget = GadgetSystem::GetGadget<CollisionGadget>( m_actor->m_actorHandle );
    if ( m_jumpPressed && pCollisionGadget && pCollisionGadget->m_onGround )
    {
        y += m_actor->GetSpeed() * 2.0f;
        pCollisionGadget->m_onGround = false;
    }
    else
        y = 0.0f;
    if ( m_leftPressed )
        x += m_actor->GetSpeed() * 0.1f;
    else if ( !m_rightPressed )
        x = 0.0f;
    if ( m_rightPressed )
        x -= m_actor->GetSpeed() * 0.1f;
    else if ( !m_leftPressed )
        x = 0.0f;
    
    Vector2d accel = Vector2d( x, y );
    accel.ClampX( m_actor->GetSpeed() );
    m_actor->SetAcceleration( accel );
}