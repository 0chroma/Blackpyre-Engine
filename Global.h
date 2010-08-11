/*
 * Blackpyre Engine
 * Copyright (c) 2010 William Riley. All rights reserved.
 * 
 * Source available under the Academic Free License
 * See LICENSE for licensing information
 */

#ifndef Global_h
#define Global_h

#include "WindowGLUT.h"

class Global {
    public:
	Global();
	~Global();

        static int init(int argc = 0, char **argv = 0);
	static WindowFramework *window;
	
};

#endif // Global_h
