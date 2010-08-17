/*
 * Blackpyre Engine
 * Copyright (c) 2010 William Riley. All rights reserved.
 * 
 * Source available under the Academic Free License
 * See LICENSE for licensing information
 */

#ifndef GlUtil_h
#define GlUtil_h

class GlUtil {
	public:
        GlUtil();
        ~GlUtil();
        
        void initRendering();
        static void handleResize(int w, int h);
        static void drawScene();
};

#endif // GlUtil_h 
