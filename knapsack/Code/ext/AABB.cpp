//
//  AABB.cpp
//  knapsack
//
//  Created by Derek Peterson on 5/9/15.
//  Copyright (c) 2015 Derek Peterson. All rights reserved.
//

#include "AABB.h"
#include "limits.h"

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

bool AABB::Intersects( AABB i_aabb, Vector2d& o_proposedResolution )
{
    bool xMinIntersect = m_minExtents.GetX() >= i_aabb.GetMinExtents().GetX() &&
                         m_minExtents.GetX() <= i_aabb.GetMaxExtents().GetX();
    bool yMinIntersect = m_minExtents.GetY() >= i_aabb.GetMinExtents().GetY() &&
                         m_minExtents.GetY() <= i_aabb.GetMaxExtents().GetY();
    bool xMaxIntersect = m_maxExtents.GetX() >= i_aabb.GetMinExtents().GetX() &&
                         m_maxExtents.GetX() <= i_aabb.GetMaxExtents().GetX();
    bool yMaxIntersect = m_maxExtents.GetY() >= i_aabb.GetMinExtents().GetY() &&
                         m_maxExtents.GetY() <= i_aabb.GetMaxExtents().GetY();
    
    bool xIntersect = xMinIntersect || xMaxIntersect;
    bool yIntersect = yMinIntersect || yMaxIntersect;
    
    if ( xIntersect && yIntersect )
    {
        float firstResolution = INT_MAX;
        bool firstIsX = false;
        // check abs value for which is the smallest displacement, and maybe tha'ts a win?
        float xMinMinDepth = i_aabb.GetMinExtents().GetX() - m_minExtents.GetX();
        if ( xMinMinDepth != 0.0f && std::abs( xMinMinDepth ) < std::abs( firstResolution ) )
        {
            firstResolution = xMinMinDepth;
            firstIsX = true;
        }
        float xMinMaxDepth = i_aabb.GetMaxExtents().GetX() - m_minExtents.GetX();
        if ( xMinMaxDepth != 0.0f && std::abs( xMinMaxDepth ) < std::abs( firstResolution ) )
        {
            firstResolution = xMinMaxDepth;
            firstIsX = true;
        }
        float xMaxMinDepth = i_aabb.GetMinExtents().GetX() - m_maxExtents.GetX();
        if ( xMaxMinDepth != 0.0f && std::abs( xMaxMinDepth ) < std::abs( firstResolution ) )
        {
            firstResolution = xMaxMinDepth;
            firstIsX = true;
        }
        float xMaxMaxDepth = i_aabb.GetMaxExtents().GetX() - m_maxExtents.GetX();
        if ( xMaxMaxDepth != 0.0f && std::abs( xMaxMaxDepth ) < std::abs( firstResolution ) )
        {
            firstResolution = xMaxMaxDepth;
            firstIsX = true;
        }
        
        float yMinMinDepth = i_aabb.GetMinExtents().GetY() - m_minExtents.GetY();
        if ( yMinMinDepth != 0.0f && std::abs( yMinMinDepth ) < std::abs( firstResolution ) )
        {
            firstResolution = yMinMinDepth;
            firstIsX = false;
        }
        float yMinMaxDepth = i_aabb.GetMaxExtents().GetY() - m_minExtents.GetY();
        if ( yMinMaxDepth != 0.0f && std::abs( yMinMaxDepth ) < std::abs( firstResolution ) )
        {
            firstResolution = yMinMaxDepth;
            firstIsX = false;
        }
        float yMaxMinDepth = i_aabb.GetMinExtents().GetY() - m_maxExtents.GetY();
        if ( yMaxMinDepth != 0.0f && std::abs( yMaxMinDepth ) < std::abs( firstResolution ) )
        {
            firstResolution = yMaxMinDepth;
            firstIsX = false;
        }
        float yMaxMaxDepth = i_aabb.GetMaxExtents().GetY() - m_maxExtents.GetY();
        if ( yMaxMaxDepth != 0.0f && std::abs( yMaxMaxDepth ) < std::abs( firstResolution ) )
        {
            firstResolution = yMaxMaxDepth;
            firstIsX = false;
        }
        
        if ( firstResolution == INT_MAX )
        {
            o_proposedResolution = Vector2d( 0.0f, 0.0f );
            return true;
        }
        
        if ( firstIsX )
            o_proposedResolution = Vector2d( firstResolution * 1.01f, 0.0f );
        else
            o_proposedResolution = Vector2d( 0.0f, firstResolution * 1.01f );
        
        return true;
    }
    
    // None of my corners are intersecting him... Maybe his are intersecting me?
    
    bool otherXMinIntersect = i_aabb.GetMinExtents().GetX() >= m_minExtents.GetX() &&
                    i_aabb.GetMinExtents().GetX() <= m_maxExtents.GetX();
    bool otherYMinIntersect = i_aabb.GetMinExtents().GetY() >= m_minExtents.GetY() &&
                    i_aabb.GetMinExtents().GetY() <= m_maxExtents.GetY();
    bool otherXMaxIntersect = i_aabb.GetMaxExtents().GetX() >= m_minExtents.GetX() &&
                    i_aabb.GetMaxExtents().GetX() <= m_maxExtents.GetX();
    bool otherYMaxIntersect = i_aabb.GetMaxExtents().GetY() >= m_minExtents.GetY() &&
                    i_aabb.GetMaxExtents().GetY() <= m_maxExtents.GetY();
    
    xIntersect = xIntersect || otherXMinIntersect || otherXMaxIntersect;
    yIntersect = yIntersect || otherYMinIntersect || otherYMaxIntersect;
    if ( xIntersect && yIntersect )
    {
        float firstResolution = INT_MAX;
        bool firstIsX = false;
        
        float otherXMinMinDepth = m_minExtents.GetX() - i_aabb.GetMinExtents().GetX();
        if ( otherXMinMinDepth != 0.0f && std::abs( otherXMinMinDepth ) < std::abs( firstResolution ) )
        {
            firstResolution = otherXMinMinDepth;
            firstIsX = true;
        }
        float otherXMinMaxDepth = m_minExtents.GetX() - i_aabb.GetMaxExtents().GetX();
        if ( otherXMinMaxDepth != 0.0f && std::abs( otherXMinMaxDepth ) < std::abs( firstResolution ) )
        {
            firstResolution = otherXMinMaxDepth;
            firstIsX = true;
        }
        float otherXMaxMinDepth = m_maxExtents.GetX() - i_aabb.GetMinExtents().GetX();
        if ( otherXMaxMinDepth != 0.0f && std::abs( otherXMaxMinDepth ) < std::abs( firstResolution ) )
        {
            firstResolution = otherXMaxMinDepth;
            firstIsX = true;
        }
        float otherXMaxMaxDepth = m_maxExtents.GetX() - i_aabb.GetMaxExtents().GetX();
        if ( otherXMaxMaxDepth != 0.0f && std::abs( otherXMaxMaxDepth ) < std::abs( firstResolution ) )
        {
            firstResolution = otherXMaxMaxDepth;
            firstIsX = true;
        }
        float otherYMinMinDepth = m_minExtents.GetY() - i_aabb.GetMinExtents().GetY();
        if ( otherYMinMinDepth != 0.0f && std::abs( otherYMinMinDepth ) < std::abs( firstResolution ) )
        {
            firstResolution = otherYMinMinDepth;
            firstIsX = false;
        }
        float otherYMinMaxDepth = m_minExtents.GetY() - i_aabb.GetMaxExtents().GetY();
        if ( otherYMinMaxDepth != 0.0f && std::abs( otherYMinMaxDepth ) < std::abs( firstResolution ) )
        {
            firstResolution = otherYMinMaxDepth;
            firstIsX = false;
        }
        float otherYMaxMinDepth = m_maxExtents.GetY() - i_aabb.GetMinExtents().GetY();
        if ( otherYMaxMinDepth != 0.0f && std::abs( otherYMaxMinDepth ) < std::abs( firstResolution ) )
        {
            firstResolution = otherYMaxMinDepth;
            firstIsX = false;
        }
        float otherYMaxMaxDepth = m_maxExtents.GetY() - i_aabb.GetMaxExtents().GetY();
        if ( otherYMaxMaxDepth != 0.0f && std::abs( otherYMaxMaxDepth ) < std::abs( firstResolution ) )
        {
            firstResolution = otherYMaxMaxDepth;
            firstIsX = false;
        }
        
        if ( firstResolution == INT_MAX )
        {
            o_proposedResolution = Vector2d( 0.0f, 0.0f );
            return true;
        }
        
        if ( firstIsX )
            o_proposedResolution = Vector2d( firstResolution * 1.01f, 0.0f );
        else
            o_proposedResolution = Vector2d( 0.0f, firstResolution * 1.01f );
        
        return true;
    }
    
    return false;
}
