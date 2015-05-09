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

class Camera
{
private:
    Vector2d m_centerPoint;
    Actor* m_focusActor;
public:
    Camera( Actor* i_focusActor ){ m_focusActor = i_focusActor; };
    ~Camera();
    
    void Update( float dt );

    Vector2d GetCenterPoint() { return m_centerPoint; };
    Vector2d ToCameraCoords( Vector2d i_pos );
};

#endif /* defined(__knapsack__Camera__) */
