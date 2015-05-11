//
//  GravityGadget.cpp
//  knapsack
//
//  Created by Derek Peterson on 5/10/15.
//  Copyright (c) 2015 Derek Peterson. All rights reserved.
//

#include "GravityGadget.h"

//GadgetRegister<GravityGadget> GravityGadget::reg("Gravity");

GravityGadget::GravityGadget()
{
    
}

void GravityGadget::Init( ActorHandle i_actorHandle )
{
    m_actorHandle = i_actorHandle;
}

void GravityGadget::DNADataInit( ActorHandle i_actorHandle, LuaScript& i_script )
{
    Init( i_actorHandle );
}

void GravityGadget::Update( float dt )
{
    
}

void GravityGadget::Draw()
{
    
}