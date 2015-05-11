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
#include "ext/Vector2d.h"
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
    
    Actor* a = ActorSystem::CreateActor( "Background" );
    a->SetPos( Vector2d( 9.6, 0 ) );
    
    // create some temporary actors for spatial reference
    Actor* b = ActorSystem::CreateActor( "Avatar" );
    b->SetPos( Vector2d( 4, 0 ) );
    Actor* c = ActorSystem::CreateActor( "Tree" );
    c->SetPos( Vector2d( 5, 0 ) );
    Actor* d = ActorSystem::CreateActor( "Tree" );
    d->SetPos( Vector2d( 6, 0 ) );
    Actor* e = ActorSystem::CreateActor( "Tree" );
    e->SetPos( Vector2d( 7, 0 ) );
    
    g_player = new Player( ActorSystem::CreateActor( "Avatar" ) );
    g_player->GetActor()->SetPos( Vector2d( 2.5f, 0 ) );
    
    Actor* f = ActorSystem::CreateActor( "Crate" );
    f->SetPos( Vector2d( 1.0f, 0 ) );
    
    g_camera = new Camera( g_player->GetActor(), RotMat( Vector2d( -1, 0 ), Vector2d( 0, -1 ) ) );

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