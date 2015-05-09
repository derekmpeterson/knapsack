//
//  Vector2d.h
//  knapsack
//
//  Created by Derek Peterson on 5/7/15.
//  Copyright (c) 2015 Derek Peterson. All rights reserved.
//

#ifndef __knapsack__Vector2d__
#define __knapsack__Vector2d__

#include <stdio.h>
#include <cmath>

class Vector2d
{
private:
    float m_x;
    float m_y;
public:
    Vector2d() : m_x( 0.0 ), m_y( 0.0 ) {};
    Vector2d( float i_x, float i_y ) : m_x( i_x ), m_y( i_y ) {};
    ~Vector2d() {};
    
    void SetX( float i_x ) { m_x = i_x; };
    void SetY( float i_y ) { m_y = i_y; };
    
    float GetX() const { return m_x; };
    float GetY() const { return m_y; };
    
    float Length() { return sqrt( pow( m_x, 2 ) + pow( m_y, 2 ) ); };
    float LengthSquared() { return ( pow( m_x, 2 ) + pow( m_y, 2 ) ); };
    
    Vector2d& operator+=( const Vector2d& other ) // compound assignment (does not need to be a member,
    {                           // but often is, to modify the private members)
        this->SetX( this->GetX() + other.GetX() );
        this->SetY( this->GetY() + other.GetY() );
        return *this; // return the result by reference
    }
    
    Vector2d& operator+( const Vector2d& other ) // compound assignment (does not need to be a member,
    {                           // but often is, to modify the private members)
        this->SetX( this->GetX() + other.GetX() );
        this->SetY( this->GetY() + other.GetY() );
        return *this; // return the result by reference
    }
    
    Vector2d& operator-=( const Vector2d& other ) // compound assignment (does not need to be a member,
    {                           // but often is, to modify the private members)
        this->SetX( this->GetX() - other.GetX() );
        this->SetY( this->GetY() - other.GetY() );
        return *this; // return the result by reference
    }
    
    Vector2d& operator-( const Vector2d& other ) // compound assignment (does not need to be a member,
    {                           // but often is, to modify the private members)
        this->SetX( this->GetX() - other.GetX() );
        this->SetY( this->GetY() - other.GetY() );
        return *this; // return the result by reference
    }
    
    Vector2d& operator*=( const float scalar )
    {
        this->SetX( this->GetX() * scalar );
        this->SetY( this->GetY() * scalar );
        return *this;
    }
    
    Vector2d operator* ( float scalar )
    {
        Vector2d newVector = *this;
        newVector *= scalar;
        
        return newVector;
    }
};

#endif /* defined(__knapsack__Vector2d__) */