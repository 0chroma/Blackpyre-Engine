/*
 * Blackpyre Engine
 * Copyright (c) 2010 William Riley. All rights reserved.
 * 
 * Source available under the Academic Free License
 * See LICENSE for licensing information
 */

#ifndef WindowFramework_h
#define WindowFramework_h

class WindowFramework {
    public:
        WindowFramework(int argc = 0, char **argv = 0);
        virtual ~WindowFramework();

        virtual int create(char* title);
};

#endif // WindowFramework_h
