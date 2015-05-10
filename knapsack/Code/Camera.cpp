//
//  Camera.cpp
//  knapsack
//
//  Created by Derek Peterson on 5/8/15.
//  Copyright (c) 2015 Derek Peterson. All rights reserved.
//

#include "Camera.h"
#include "DEFINES.h"
#include <cmath>

Camera::Camera( Actor* i_focusActor, RotMat i_orient )
{
    m_focusActor = i_focusActor;
    m_orient = i_orient;
}

void Camera::Update( float dt )
{
    Vector2d pFocusPos = m_focusActor->GetPos();
    m_centerPoint = pFocusPos;
}

Vector2d Camera::VectorToCameraSpace( Vector2d i_pos )
{
    i_pos -= m_centerPoint;
    i_pos = m_orient * i_pos;
    
    i_pos.SetX( i_pos.GetX() + ( 0.5f * SCREEN_WIDTH ) );
    i_pos.SetY( i_pos.GetY() + ( 0.5f * SCREEN_HEIGHT ) );

    return i_pos;
}

AABB Camera::AABBToCameraSpace( AABB i_extents )
{
    Vector2d a = i_extents.GetMinExtents();
    a = VectorToCameraSpace( a );
    Vector2d b = i_extents.GetMaxExtents();
    b = VectorToCameraSpace( b );
    
    
    
    /*Vector2d minExtents = a;
    if ( b.GetX() < a.GetX() )
        minExtents.SetX( b.GetX() );
    if ( b.GetY() < a.GetY() )
        minExtents.SetY( b.GetY() );
    Vector2d maxExtents = b;
    if ( a.GetX() > b.GetX() )
        maxExtents.SetX( a.GetX() );
    if ( a.GetY() > b.GetY() )
        maxExtents.SetY( a.GetY() );*/
    
    return AABB( a, b );

}