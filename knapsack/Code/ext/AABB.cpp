//
//  AABB.cpp
//  knapsack
//
//  Created by Derek Peterson on 5/9/15.
//  Copyright (c) 2015 Derek Peterson. All rights reserved.
//

#include "AABB.h"

/*AABB AABB::ToBasis( RotMat i_orient )
{
    AABB pExtents = *this;
    Vector2d a = pExtents.m_minExtents;
    Vector2d b = pExtents.m_maxExtents;
    a = i_orient * a;
    b = i_orient * b;
    
    Vector2d minExtents = a;
    if ( b.GetX() < a.GetX() )
        minExtents.SetX( b.GetX() );
    if ( b.GetY() < a.GetY() )
        minExtents.SetY( b.GetY() );
    Vector2d maxExtents = b;
    if ( a.GetX() > b.GetX() )
        maxExtents.SetX( a.GetX() );
    if ( a.GetY() > b.GetY() )
        maxExtents.SetY( a.GetY() );
    
    return pExtents;
}*/

void AABB::CorrectValues()
{
    Vector2d a = m_minExtents;
    Vector2d b = m_maxExtents;
    
    Vector2d minExtents = a;
    if ( b.GetX() < a.GetX() )
        minExtents.SetX( b.GetX() );
    if ( b.GetY() < a.GetY() )
        minExtents.SetY( b.GetY() );
    Vector2d maxExtents = b;
    if ( a.GetX() > b.GetX() )
        maxExtents.SetX( a.GetX() );
    if ( a.GetY() > b.GetY() )
        maxExtents.SetY( a.GetY() );
    
    m_minExtents = minExtents;
    m_maxExtents = maxExtents;
}

SDL_Rect AABB::ToRect()
{
    SDL_Rect r;
    r.x = GetMinExtents().GetX();
    r.y = GetMinExtents().GetY();
    r.w = GetMaxExtents().GetX() - r.x;
    r.h = GetMaxExtents().GetY() - r.y;
    return r;
}

float AABB::SafeDistanceSquared()
{
    float minLength = m_minExtents.LengthSquared();
    Vector2d diag = m_maxExtents - m_minExtents;
    return minLength + diag.LengthSquared();
}