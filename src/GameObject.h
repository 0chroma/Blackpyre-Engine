/*
 * Blackpyre Engine
 * Copyright (c) 2010 William Riley. All rights reserved.
 * 
 * Source available under the Academic Free License
 * See LICENSE for licensing information
 */

#ifndef GameObject_h
#define GameObject_h

#include <stdint.h>

class GameObject {
	public:
        GameObject(float x, float y, float sx, float sy, float a);
        ~GameObject();

        virtual void render();
        void setSpawnTime();
        uint32_t timeSinceSpawn();
        virtual void update();
    protected:
        int id;
        GameObject *next;
        GameObject *prev;
        GameObject *parent;
        uint32_t spawnTime;
 
        float posX;
        float posY;
        float initialPosX;
        float initialPosY;
        float sizeX;
        float sizeY;
        float initialSizeX;
        float initialSizeY;
        float angle;
        float initialAngle;

    friend class ObjectManager;
    friend class Scripting;
};

#endif // GameObject_h 
