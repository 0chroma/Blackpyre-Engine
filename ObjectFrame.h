/*
 * Blackpyre Engine
 * Copyright (c) 2010 William Riley. All rights reserved.
 * 
 * Source available under the Academic Free License
 * See LICENSE for licensing information
 */

#ifndef ObjectFrame_h
#define ObjectFrame_h

#include "GameObject.h"

class ObjectFrame : public GameObject{
    public:
        ObjectFrame(float x, float y, float sx, float sy);
        ~ObjectFrame();

        void render();

    private:
        float posX;
        float posY;
        float sizeX;
        float sizeY;
        float angle;

        GameObject *objectList[];
};

#endif // ObjectFrame_h
