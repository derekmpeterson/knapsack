//
//  CollisionGadget.h
//  knapsack
//
//  Created by Derek Peterson on 5/8/15.
//  Copyright (c) 2015 Derek Peterson. All rights reserved.
//

#ifndef __knapsack__CollisionGadget__
#define __knapsack__CollisionGadget__

#include <stdio.h>
#include <string>
#include "Gadget.h"
#include "../Systems/GadgetSystem.h"

class CollisionGadget : public Gadget
{
public:
    CollisionGadget();
    
    virtual void Init();
    virtual void Update( float dt );
    virtual void Draw();
    
    static GadgetRegister<CollisionGadget> reg;
};

#endif /* defined(__knapsack__CollisionGadget__) */
