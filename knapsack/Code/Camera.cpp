//
//  Camera.cpp
//  knapsack
//
//  Created by Derek Peterson on 5/8/15.
//  Copyright (c) 2015 Derek Peterson. All rights reserved.
//

#include "Camera.h"
#include "DEFINES.h"

void Camera::Update( float dt )
{
    m_centerPoint = m_focusActor->GetPos();
}

Vector2d Camera::ToCameraCoords( Vector2d i_pos )
{
    i_pos.SetX( i_pos.GetX() + ( 0.5f * SCREEN_WIDTH ) - m_centerPoint.GetX() );
    i_pos.SetY( i_pos.GetY() + ( 0.5f * SCREEN_HEIGHT ) - m_centerPoint.GetY() );

    return i_pos;
}