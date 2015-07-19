//
//  RotMat.h
//  knapsack
//
//  Created by Derek Peterson on 5/10/15.
//  Copyright (c) 2015 Derek Peterson. All rights reserved.
//

#ifndef __knapsack__RotMat__
#define __knapsack__RotMat__

#include <stdio.h>
#include "Vector2d.h"

class RotMat
{
private:
    Vector2d m_xAxis;
    Vector2d m_yAxis;
public:
    RotMat( Vector2d i_xAxis, Vector2d i_yAxis ) : m_xAxis( i_xAxis ), m_yAxis( i_yAxis ) {};
    RotMat() : m_xAxis( Vector2d( 1, 0 ) ), m_yAxis( Vector2d( 0, 1 ) ) {};
    
    void SetXAxis( Vector2d i_xAxis ) { m_xAxis = i_xAxis; };
    void SetYAxis( Vector2d i_yAxis ) { m_yAxis = i_yAxis; };
    
    Vector2d GetXAxis() { return m_xAxis; };
    Vector2d GetYAxis() { return m_yAxis; };
    
    
    Vector2d operator* ( Vector2d i_vector )
    {
        //RXX RXY   X     X*RXX + Y*RXY
        //RYX RYY   Y     X*RYX + Y*RYY
        Vector2d newVector;
        newVector.SetX(
                      i_vector.GetX() * this->GetXAxis().GetX() +
                      i_vector.GetY() * this->GetXAxis().GetY()
                      );
        newVector.SetY(
                      i_vector.GetX() * this->GetYAxis().GetX() +
                      i_vector.GetY() * this->GetYAxis().GetY()
                      );
        
        return newVector;
    }
};

#endif /* defined(__knapsack__RotMat__) */
