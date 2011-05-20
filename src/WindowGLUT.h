/*
 * Blackpyre Engine
 * Copyright (c) 2010 0chroma. All rights reserved.
 * 
 * Source available under the Academic Free License
 * See LICENSE for licensing information
 */
 
#ifndef WindowGLUT_h
#define WindowGLUT_h

#include "WindowFramework.h"

#include <stdint.h>

class WindowGLUT : public WindowFramework{
    public:
        WindowGLUT(int argc = 0, char **argv = 0);
        ~WindowGLUT();
        
        static bool charStates[256];
        static bool keyStates[256];
        
        int create(char* title);
        static void handleKeyUp(int key, int x, int y);
        static void handleKeyDown(int key, int x, int y);
        static void handleCharUp(unsigned char key, int x, int y);
        static void handleCharDown(unsigned char key, int x, int y);
        static void nullFunc();
        static void drawGame(int);
        uint32_t getTime();
        static int fps;
        static int frame;
    private:
        static int last_time;
        static int now_time;
};

#endif // WindowGLUT_h
