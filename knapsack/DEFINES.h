//
//  DEFINES.h
//  knapsack
//
//  Created by Derek Peterson on 5/8/15.
//  Copyright (c) 2015 Derek Peterson. All rights reserved.
//

#ifndef knapsack_DEFINES_h
#define knapsack_DEFINES_h

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 670

#define DEBUG 1
#ifdef DEBUG
    #define DEBUG_COLLISON

    #include <cassert>
    #include <iostream>
    #define ASSERTS( condition, message )                                            \
    {                                                                               \
        if(!(condition))                                                            \
        {                                                                           \
            std::cerr << "Assertion failed at " << __FILE__ << ":" << __LINE__;     \
            std::cerr << " inside " << __FUNCTION__ << std::endl;                   \
            std::cerr << "Condition: " << #condition << std::endl;                  \
            std::cerr << "Message: " << message << std::endl;                       \
            abort();                                                                \
        }                                                                           \
    }
    #define ASSERT( condition )                                                    \
    {                                                                               \
        if(!(condition))                                                            \
        {                                                                           \
            std::cerr << "Assertion failed at " << __FILE__ << ":" << __LINE__;     \
            std::cerr << " inside " << __FUNCTION__ << std::endl;                   \
            std::cerr << "Condition: " << #condition << std::endl;                  \
            abort();                                                                \
        }                                                                           \
    }
#else
    #define ASSERTS( condition, message ) ( condition, message )
    #define ASSERT( condition ) ( condition )
#endif

#endif
