//
//  Player.h
//  knapsack
//
//  Created by Derek Peterson on 5/7/15.
//  Copyright (c) 2015 Derek Peterson. All rights reserved.
//

#ifndef __knapsack__Player__
#define __knapsack__Player__

#include <stdio.h>
#include "Actor.h"

class Player
{
private:
    bool m_upPressed;
    bool m_downPressed;
    bool m_leftPressed;
    bool m_rightPressed;
    Actor* m_actor;
public:
    Player( Actor* i_actor ) : m_upPressed( false ), m_downPressed( false ), m_leftPressed( false ), m_rightPressed( false ) {
        m_actor = i_actor;
    };
    ~Player() { delete m_actor; };
    
    Actor* GetActor() { return m_actor; };
    
    void Update( float dt );
    
    void SetUpPressed( bool i_bool ) { m_upPressed = i_bool; };
    void SetDownPressed( bool i_bool ) { m_downPressed = i_bool; };
    void SetLeftPressed( bool i_bool ) { m_leftPressed = i_bool; };
    void SetRightPressed( bool i_bool ) { m_rightPressed = i_bool; };
    
    bool GetUpPressed() { return m_upPressed; };
    bool GetDownPressed() { return m_downPressed; };
    bool GetLeftPressed() { return m_leftPressed; };
    bool GetRightPressed() { return m_rightPressed; };
};

#endif /* defined(__knapsack__Player__) */
