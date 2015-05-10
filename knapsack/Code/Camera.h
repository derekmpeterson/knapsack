//
//  Camera.h
//  knapsack
//
//  Created by Derek Peterson on 5/8/15.
//  Copyright (c) 2015 Derek Peterson. All rights reserved.
//

#ifndef __knapsack__Camera__
#define __knapsack__Camera__

#include <stdio.h>
#include "Actor.h"
#include "ext/Vector2d.h"
#include "ext/RotMat.h"
#include "ext/AABB.h"

class Camera
{
private:
    Vector2d m_centerPoint;
    RotMat m_orient;
    Actor* m_focusActor;
public:
    Camera( Actor* i_focusActor, RotMat i_orient );
    ~Camera();
    
    void Update( float dt );

    Vector2d GetCenterPoint() { return m_centerPoint; };
    Vector2d VectorToCameraSpace( Vector2d i_pos );
    AABB AABBToCameraSpace( AABB i_extents );
    
    RotMat GetOrient() { return m_orient; };
};

#endif /* defined(__knapsack__Camera__) */
