/*
 * Blackpyre Engine
 * Copyright (c) 2010 William Riley. All rights reserved.
 * 
 * Source available under the Academic Free License
 * See LICENSE for licensing information
 */
 
#ifndef WindowGLUT_h
#define WindowGLUT_h

#include "WindowFramework.h"

class WindowGLUT : public WindowFramework{
    public:
        WindowGLUT(int argc = 0, char **argv = 0);
        ~WindowGLUT();

        int create(char* title);
        static void handleKeypress(unsigned char key, int x, int y);
        void swapBuffers();
	void postRedisplay();
};

#endif // WindowGLUT_h
