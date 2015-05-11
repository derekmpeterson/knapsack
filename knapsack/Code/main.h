//
//  main.h
//  knapsack
//
//  Created by Derek Peterson on 5/6/15.
//  Copyright (c) 2015 Derek Peterson. All rights reserved.
//

#ifndef knapsack_main_h
#define knapsack_main_h

#include "Player.h"
#include "Actor.h"
#include "Camera.h"
#include "DEFINES.h"

SDL_Window* g_gameWindow;
SDL_Renderer* g_gameRenderer;
SDL_Surface* g_gameSurface;
SDL_Event g_event;
bool g_quitTriggered = false;

void loop();
void processInput();
void quit();
void render( float dt );

Player* g_player;
Camera* g_camera;

unsigned int g_lastFrame;

#endif
