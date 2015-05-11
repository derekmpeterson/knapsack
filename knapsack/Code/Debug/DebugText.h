//
//  DebugText.h
//  knapsack
//
//  Created by Derek Peterson on 5/11/15.
//  Copyright (c) 2015 Derek Peterson. All rights reserved.
//

#ifndef __knapsack__DebugText__
#define __knapsack__DebugText__

#include <stdio.h>
#include <string>
#include <vector>

struct DebugTextDraw
{
    std::string m_text;
    int m_color;
    int m_x;
    int m_y;
    
    DebugTextDraw( std::string i_text, int i_color, int i_x, int i_y ) : m_text( i_text ), m_color( i_color ), m_x( i_x ), m_y( i_y ) {};
};
class DebugText
{
    static std::vector<DebugTextDraw> m_drawBuffer;
public:
    enum {
        COLOR_RED,
        COLOR_GREEN,
        COLOR_YELLOW,
        COLOR_WHITE
    };
    static void WriteText( std::string i_text, int i_color );
    static void Render();
};

#endif /* defined(__knapsack__DebugText__) */
