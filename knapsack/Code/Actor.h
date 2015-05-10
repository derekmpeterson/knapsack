//
//  Actor.h
//  knapsack
//
//  Created by Derek Peterson on 5/7/15.
//  Copyright (c) 2015 Derek Peterson. All rights reserved.
//

#ifndef __knapsack__Actor__
#define __knapsack__Actor__

#include <stdio.h>
#include "SDL2/SDL.h"
#include "SDL2_Image/SDL_Image.h"
#include "ext/Vector2d.cpp"
#include <vector>
#include <string>
#include "Gadget.h"
#include "LuaScript.h"

typedef int ActorHandle;

class Actor
{
private:
    Vector2d m_pos;
    Vector2d m_acceleration;
    float m_speed;
    SDL_Texture* m_texture;
    std::string m_name;
    
public:
    Actor( std::string i_name, std::string i_imageName );
    ~Actor() {};
    
    ActorHandle m_actorHandle;
    std::vector<Gadget*> m_gadgets;
    
    void SetPos( Vector2d i_pos ) { m_pos = i_pos; };
    void SetAcceleration( Vector2d i_acceleration ) { m_acceleration = i_acceleration; };
    void SetSpeed( int i_speed ) { m_speed = i_speed; };
    void SetTexture( SDL_Texture* i_texture ) { m_texture = i_texture; };
    
    Vector2d GetPos() { return m_pos; };
    Vector2d GetAcceleration() { return m_acceleration; };
    float GetSpeed() { return m_speed; };
    SDL_Texture* GetTexture() { return m_texture; };
    
    std::string GetName() { return m_name; };
    
    void Update( float dt );
    void Draw();
    
    void AttachGadget( std::string i_gadgetType );
    void AttachGadgetWithDNA( std::string i_gadgetType, LuaScript& i_script );
};

#endif /* defined(__knapsack__Actor__) */
