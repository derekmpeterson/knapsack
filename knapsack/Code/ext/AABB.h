//
//  AABB.h
//  knapsack
//
//  Created by Derek Peterson on 5/9/15.
//  Copyright (c) 2015 Derek Peterson. All rights reserved.
//

#ifndef __knapsack__AABB__
#define __knapsack__AABB__

#include <stdio.h>
#include "Vector2d.h"
#include "RotMat.h"
#include "SDL2/SDL.h"

struct AABB
{
private:
    Vector2d m_minExtents;
    Vector2d m_maxExtents;
public:
    AABB( Vector2d i_minExtents, Vector2d i_maxExtents ) : m_minExtents( i_minExtents ), m_maxExtents( i_maxExtents ) {};
    AABB() : m_minExtents( Vector2d( 0.0f, 0.0f ) ), m_maxExtents( Vector2d( 0.0f, 0.0f ) ) {};
    ~AABB() {};
    
    void SetMinExtents( Vector2d i_minExtents ) { m_minExtents = i_minExtents; };
    void SetMaxExtents( Vector2d i_maxExtents ) { m_maxExtents = i_maxExtents; };
    
    Vector2d GetMinExtents() { return m_minExtents; };
    Vector2d GetMaxExtents() { return m_maxExtents; };
    void CorrectValues();
    
    SDL_Rect ToRect();
 
    Vector2d GetCenter();
    Vector2d GetHalfLength();
};

#endif /* defined(__knapsack__AABB__) */
