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
#include "../ext/LuaScript.h"
#include "../Actor.h"
#include "ActorSystem.h"

typedef std::map<std::string, Gadget*(*)()> GadgetMap;
typedef int ActorHandle;

template<typename T> Gadget* createT() { return new T; }

class GadgetSystem
{
public:
    static GadgetMap m_gadgetTypes;
    static Gadget* CreateInstance(std::string const& s, ActorHandle i_actorHandle );
    static Gadget* CreateInstanceWithDNA(std::string const& s, ActorHandle i_actorHandle, LuaScript& i_script);
    
    template<typename GadgetType>
    static GadgetType* GetGadget( ActorHandle i_actorHandle )
    {
        Actor* pActor = ActorSystem::GetActor( i_actorHandle );
        for (std::vector<Gadget*>::iterator it = pActor->m_gadgets.begin() ; it != pActor->m_gadgets.end(); ++it)
        {
            Gadget* pGadget = *it;
            if ( typeid( *pGadget ) == typeid( GadgetType ) )
                return (GadgetType*) pGadget;
        }
        return NULL;
    }
};

template<typename T>
struct GadgetRegister : GadgetSystem {
    GadgetRegister(std::string const& s) {
        GadgetSystem::m_gadgetTypes.insert(std::make_pair(s, &createT<T>));
    }
};

#endif /* defined(__knapsack__GadgetSystem__) */
