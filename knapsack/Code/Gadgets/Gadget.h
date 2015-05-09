//
//  Gadget.h
//  knapsack
//
//  Created by Derek Peterson on 5/8/15.
//  Copyright (c) 2015 Derek Peterson. All rights reserved.
//

#ifndef __knapsack__Gadget__
#define __knapsack__Gadget__

#include <stdio.h>
#include <string>

typedef int ActorHandle;

class Gadget
{
public:
    std::string m_gadgetType;
    
    ActorHandle m_actorHandle;
    
    Gadget();
    
    virtual void Init();
    virtual void Update( float dt );
    virtual void Draw();
};

#endif /* defined(__knapsack__Gadget__) */
