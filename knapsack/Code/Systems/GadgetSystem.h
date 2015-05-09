//
//  GadgetSystem.h
//  knapsack
//
//  Created by Derek Peterson on 5/9/15.
//  Copyright (c) 2015 Derek Peterson. All rights reserved.
//

#ifndef __knapsack__GadgetSystem__
#define __knapsack__GadgetSystem__

#include <stdio.h>
#include <vector>
#include <string>
#include <map>
#include "../Gadgets/Gadget.h"

typedef std::map<std::string, Gadget*(*)()> GadgetMap;

template<typename T> Gadget* createT() { return new T; }

class GadgetSystem
{
public:
    static GadgetMap m_gadgetTypes;
    static Gadget* CreateInstance(std::string const& s);
};

template<typename T>
struct GadgetRegister : GadgetSystem {
    GadgetRegister(std::string const& s) {
        GadgetSystem::m_gadgetTypes.insert(std::make_pair(s, &createT<T>));
    }
};

#endif /* defined(__knapsack__GadgetSystem__) */
