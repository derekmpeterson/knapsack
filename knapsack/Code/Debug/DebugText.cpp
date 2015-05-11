//
//  DebugText.cpp
//  knapsack
//
//  Created by Derek Peterson on 5/11/15.
//  Copyright (c) 2015 Derek Peterson. All rights reserved.
//

#include "DebugText.h"
#include "DEFINES.h"
#include "SDL2/SDL.h"
#include "SDL2_ttf/SDL_ttf.h"

extern SDL_Renderer* g_gameRenderer;

std::vector<DebugTextDraw> DebugText::m_drawBuffer;

void DebugText::WriteText( std::string i_text, int i_color )
{
    DebugTextDraw dtd = DebugTextDraw( i_text, i_color, 0, 0 );
    m_drawBuffer.push_back( dtd );
}

void DebugText::Render()
{
    for(std::vector<DebugTextDraw>::iterator it = m_drawBuffer.begin(); it != m_drawBuffer.end(); ++it) {
        DebugTextDraw* dtd = &*it;
        
        SDL_Color textColor;
        if ( dtd->m_color == COLOR_RED )
            textColor = { 255, 0, 0, 255 };
        if ( dtd->m_color == COLOR_GREEN )
            textColor = { 0, 160, 0, 255 };
        if ( dtd->m_color == COLOR_YELLOW )
            textColor = { 255, 255, 0, 255 };
        if ( dtd->m_color == COLOR_WHITE )
            textColor = { 255, 255, 255, 255 };
        
        TTF_Font* font = TTF_OpenFont( "Content/Fonts/PressStart2P.ttf", 12 ); //this opens a font style and sets a size
        if ( font )
        {
            SDL_Surface* textSurface = TTF_RenderText_Solid( font, dtd->m_text.c_str(), textColor );
            SDL_Texture* text = SDL_CreateTextureFromSurface( g_gameRenderer, textSurface );
            int text_width = textSurface->w;
            int text_height = textSurface->h;
            SDL_FreeSurface( textSurface );
            SDL_Rect renderQuad = { dtd->m_x, dtd->m_y, text_width, text_height };
            SDL_RenderCopy( g_gameRenderer, text, NULL, &renderQuad );
            SDL_DestroyTexture( text );
        }
    }
    m_drawBuffer.clear();
}