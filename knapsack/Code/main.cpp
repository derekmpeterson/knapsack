//
//  main.cpp
//  knapsack
//
//  Created by Derek Peterson on 5/6/15.
//  Copyright (c) 2015 Derek Peterson. All rights reserved.
//

#include "SDL2/SDL.h"
#include "SDL2_Image/SDL_Image.h"
#include "SDL2_ttf/SDL_ttf.h"
#include <stdio.h>
#include "Systems/ActorSystem.h"
#include "Systems/CollisionSystem.h"
#include "main.h"
#include <iostream>
#include "DEFINES.H"
#include "Gadgets/CollisionGadget.h"
#include "ext/RotMat.h"

#ifdef DEBUG
#include "Debug/DebugText.h"
#endif

int main( int argc, char* args[] )
{
    g_lastFrame = 0;
    
    SDL_Init( SDL_INIT_VIDEO );
    //SDL_CreateWindowAndRenderer( SCREEN_WIDTH, SCREEN_HEIGHT, 0, &g_gameWindow, &g_gameRenderer );
    g_gameWindow = SDL_CreateWindow("knapsack", -SCREEN_WIDTH, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0 );
    g_gameRenderer = SDL_CreateRenderer( g_gameWindow, 0, SDL_RENDERER_PRESENTVSYNC );
    if( !g_gameWindow )
    {
        printf( "Could not create window: %s\n", SDL_GetError() );
        return 1;
    }
    g_gameSurface = SDL_GetWindowSurface( g_gameWindow );
    
    SDL_SetRenderDrawColor( g_gameRenderer, 0, 0, 0, 255 );
    SDL_RenderClear( g_gameRenderer );
    
    if(TTF_Init()==-1) {
        printf("TTF_Init: %s\n", TTF_GetError());
        exit(2);
    }
    
    ActorSystem::CreateActor( "Background", Vector2d( 96.0f, 0.0f ) );
    
    // create some temporary actors for spatial reference
    //ActorSystem::CreateActor( "Avatar", Vector2d( 40.0f, 0.0f ) );
    ActorSystem::CreateActor( "Tree", Vector2d( 50.0f, 0.0f ) );
    ActorSystem::CreateActor( "Tree", Vector2d( 60.0f, 0.0f ) );
    ActorSystem::CreateActor( "Tree", Vector2d( 70.0f, 0.0f ) );
    
    g_player = new Player( ActorSystem::CreateActor( "Avatar", Vector2d( 25.0f, 20.0f ) ) );
    
    ActorSystem::CreateActor( "Crate", Vector2d( 10.0f, 0.0f ) );
    
    g_camera = new Camera( g_player->GetActor(), RotMat( Vector2d( -1, 0 ), Vector2d( 0, -1 ) ) );
    
    CollisionSystem::Init();

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
        
#ifdef DEBUG
        float frameRate = 1000.0f / (float ) delta;
        char buf[16];
        sprintf( buf, "FPS: %0.2f", frameRate );
        if ( frameRate > 30.0f )
            DebugText::WriteText( buf, DebugText::COLOR_GREEN );
        else if ( frameRate > 20.0f )
            DebugText::WriteText( buf, DebugText::COLOR_YELLOW );
        else
            DebugText::WriteText( buf, DebugText::COLOR_RED );
#endif // DEBUG
        processInput();
        
        g_player->Update( dt );
        for (std::map<ActorHandle,Actor*>::iterator it=ActorSystem::m_actors.begin(); it!=ActorSystem::m_actors.end(); ++it)
            it->second->Update( dt );
        
        
        CollisionSystem::Update( dt );
        g_camera->Update( dt );
        
        render( dt );
    }
}

void render( float dt )
{
    SDL_SetRenderDrawColor( g_gameRenderer, 0, 0, 0, 255 );
    SDL_RenderClear( g_gameRenderer );
    
    for (std::map<ActorHandle,Actor*>::iterator it=ActorSystem::m_actors.begin(); it!=ActorSystem::m_actors.end(); ++it)
        it->second->Draw();
    
    DebugText::Render();
    
    SDL_RenderPresent( g_gameRenderer );
}

void quit()
{
    SDL_DestroyRenderer( g_gameRenderer );
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
                    g_player->SetJumpPressed( true );
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
                    g_player->SetJumpPressed( false );
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