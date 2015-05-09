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
#include "Systems/ActorSystem.h"
#include "main.h"
#include <iostream>
#include "DEFINES.H"
#include "Gadgets/CollisionGadget.h"

int main( int argc, char* args[] )
{
    g_lastFrame = 0;
    SDL_Init( SDL_INIT_VIDEO );
    SDL_CreateWindowAndRenderer( SCREEN_WIDTH, SCREEN_HEIGHT, 0, &g_gameWindow, &g_gameRenderer );
    if( !g_gameWindow )
    {
        printf( "Could not create window: %s\n", SDL_GetError() );
        return 1;
    }
    SDL_SetWindowPosition( g_gameWindow, 0, 0 );
    g_gameSurface = SDL_GetWindowSurface( g_gameWindow );
    
    SDL_SetRenderDrawColor( g_gameRenderer, 0, 0, 0, 255 );
    SDL_RenderClear( g_gameRenderer );
    
    Actor* a = ActorSystem::CreateActor( (char*) "Content/Terrain/bg.png" );
    a->SetPos( Vector2d( 960, 240 ) );
    
    g_player = new Player( ActorSystem::CreateActor( (char*) "Content/Characters/Avatar/Avatar.png" ) );
    g_player->GetActor()->SetPos( Vector2d( 250, 428 ) );
    g_player->GetActor()->AttachGadget( new CollisionGadget() );
    
    // create some temporary actors for spatial reference
    Actor* b = ActorSystem::CreateActor( (char*) "Content/Characters/Tree/Tree.png" );
    b->SetPos( Vector2d( 100, 332 ) );
    Actor* c = ActorSystem::CreateActor( (char*) "Content/Characters/Tree/Tree.png" );
    c->SetPos( Vector2d( 300, 332 ) );
    Actor* d = ActorSystem::CreateActor( (char*) "Content/Characters/Tree/Tree.png" );
    d->SetPos( Vector2d( 400, 332 ) );
    Actor* e = ActorSystem::CreateActor( (char*) "Content/Characters/Tree/Tree.png" );
    e->SetPos( Vector2d( 500, 332 ) );
    
    g_camera = new Camera( g_player->GetActor() );
    
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
        std::cout << "FPS: " << frameRate << std::endl;
#endif // DEBUG
        processInput();
        
        g_player->Update( dt );
        g_camera->Update( dt );
        
        render( dt );
    }
}

void render( float dt )
{
    SDL_RenderClear( g_gameRenderer );
    
    for (std::map<ActorHandle,Actor>::iterator it=ActorSystem::m_actors.begin(); it!=ActorSystem::m_actors.end(); ++it)
        it->second.Draw();
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