//
//  GadgetSystem.cpp
//  knapsack
//
//  Created by Derek Peterson on 5/9/15.
//  Copyright (c) 2015 Derek Peterson. All rights reserved.
//

#include "GadgetSystem.h"

GadgetMap GadgetSystem::m_gadgetTypes;

Gadget* GadgetSystem::CreateInstance(std::string const& s, ActorHandle i_actorHandle ) {
    GadgetMap::iterator it = GadgetSystem::m_gadgetTypes.find(s);
    if(it == GadgetSystem::m_gadgetTypes.end())
        return 0;
    Gadget* gadget = it->second();
    gadget->Init( i_actorHandle );
    return gadget;
}

Gadget* GadgetSystem::CreateInstanceWithDNA(std::string const& s, ActorHandle i_actorHandle, LuaScript& i_script) {
    GadgetMap::iterator it = GadgetSystem::m_gadgetTypes.find(s);
    if(it == GadgetSystem::m_gadgetTypes.end())
        return 0;
    Gadget* gadget = it->second();
    gadget->DNADataInit( i_actorHandle, i_script );
    return gadget;
}