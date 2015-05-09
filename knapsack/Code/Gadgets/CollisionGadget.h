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
#include "Gadget.h"

class CollisionGadget : public Gadget
{
public:
    char* m_gadgetType;
    
    CollisionGadget();
    
    void Init();
    void Update( float dt );
};

#endif /* defined(__knapsack__CollisionGadget__) */
