/*
 * Blackpyre Engine
 * Copyright (c) 2010 0chroma. All rights reserved.
 * 
 * Source available under the Academic Free License
 * See LICENSE for licensing information
 */

#ifndef Entity_h
#define Entity_h

#include "GameObject.h"

class Entity : public GameObject{
    public:
        Entity(float x, float y, float sx, float sy);
        ~Entity();

        void render();

    private:
        float posX;
        float posY;
        float sizeX;
        float sizeY;
        float angle;
};

#endif // Entity_h
