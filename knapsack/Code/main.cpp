//
//  main.cpp
//  knapsack
//
//  Created by Derek Peterson on 5/6/15.
//  Copyright (c) 2015 Derek Peterson. All rights reserved.
//

#include "SDL2/SDL.h"
#include "SDL2_Image/SDL_Image.h"
#include <stdio.h>
#include "main.h"

int main( int argc, char* args[] )
{
    g_lastFrame = 0;
    SDL_Init( SDL_INIT_VIDEO );
    SDL_CreateWindowAndRenderer( 640, 480, 0, &g_gameWindow, &g_gameRenderer );
    if( !g_gameWindow )
    {
        printf( "Could not create window: %s\n", SDL_GetError() );
        return 1;
    }
    SDL_SetWindowPosition( g_gameWindow, 0, 0 );
    g_gameSurface = SDL_GetWindowSurface( g_gameWindow );
    
    SDL_SetRenderDrawColor( g_gameRenderer, 0, 0, 0, 255 );
    SDL_RenderClear( g_gameRenderer );
    
    g_player = new Player( new Actor( (char*) "Content/Characters/Avatar/Avatar.png" ) );
    
    loop();
    return 0;
}

void loop()
{
    while( !g_quitTriggered )
    {
        unsigned int pTime = SDL_GetTicks();
        unsigned int delta = pTime - g_lastFrame;
        g_lastFrame = pTime;
        float dt = (float) delta / 1000.0f;
        processInput();
        
        g_player->Update( dt );
        
        render( dt );
    }
}

void render( float dt )
{
    SDL_RenderClear( g_gameRenderer );
    g_player->GetActor()->Draw();
    SDL_RenderPresent( g_gameRenderer );
}

void quit()
{
    SDL_DestroyWindow( g_gameWindow );
    SDL_Quit();
}

void processInput()
{
    while( SDL_PollEvent( &g_event ) != 0 )
    {
        if( g_event.type == SDL_QUIT )
        {
            g_quitTriggered = true;
        }
        else if ( g_event.type == SDL_KEYDOWN )
        {
            switch( g_event.key.keysym.sym )
            {
                case SDLK_ESCAPE:
                    g_quitTriggered = true;
                    break;
                case SDLK_w:
                    g_player->SetUpPressed( true );
                    break;
                case SDLK_s:
                    g_player->SetDownPressed( true );
                    break;
                case SDLK_a:
                    g_player->SetLeftPressed( true );
                    break;
                case SDLK_d:
                    g_player->SetRightPressed( true );
                    break;
            }
        }
        else if ( g_event.type == SDL_KEYUP )
        {
            switch( g_event.key.keysym.sym )
            {
                case SDLK_w:
                    g_player->SetUpPressed( false );
                    break;
                case SDLK_s:
                    g_player->SetDownPressed( false );
                    break;
                case SDLK_a:
                    g_player->SetLeftPressed( false );
                    break;
                case SDLK_d:
                    g_player->SetRightPressed( false );
                    break;
            }
        }
    }
}