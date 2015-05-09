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

class Gadget
{
public:
    char* m_gadgetType;
    
    Gadget();
    
    void Init();
    void Update( float dt );
};

#endif /* defined(__knapsack__Gadget__) */
