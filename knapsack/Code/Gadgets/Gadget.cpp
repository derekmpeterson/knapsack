//
//  Gadget.cpp
//  knapsack
//
//  Created by Derek Peterson on 5/8/15.
//  Copyright (c) 2015 Derek Peterson. All rights reserved.
//

#include "Gadget.h"
#include "../Systems/GadgetSystem.h"

Gadget::Gadget()
{
    
}

void Gadget::Init( ActorHandle i_actorHandle )
{
    m_actorHandle = i_actorHandle;
}

void Gadget::DNADataInit( ActorHandle i_actorHandle, LuaScript& i_script )
{
    Init( i_actorHandle );
}

void Gadget::Update( float dt )
{
    
}

void Gadget::Draw()
{
    
}