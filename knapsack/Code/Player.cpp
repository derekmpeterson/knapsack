//
//  Player.cpp
//  knapsack
//
//  Created by Derek Peterson on 5/7/15.
//  Copyright (c) 2015 Derek Peterson. All rights reserved.
//

#include "Player.h"

void Player::Update( float dt)
{
    int x = 0;
    int y = 0;
    if ( m_upPressed )
        y += 1;
    if ( m_downPressed )
        y -= 1;
    if ( m_leftPressed )
        x += 1;
    if ( m_rightPressed )
        x -= 1;
    
    Vector2d accel = Vector2d( x, y );
    accel *= m_actor->GetSpeed();
    m_actor->SetAcceleration( accel );
}