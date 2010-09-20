/*
 * Blackpyre Engine
 * Copyright (c) 2010 0chroma. All rights reserved.
 * 
 * Source available under the Academic Free License
 * See LICENSE for licensing information
 */

#ifndef GameObject_h
#define GameObject_h

#include <stdint.h>

class GameObject {
	public:
        GameObject();
        ~GameObject();

        virtual void render();
        void setSpawnTime();
        uint32_t timeSinceSpawn();
    protected:
        int id;
        GameObject *next;
        GameObject *prev;
        GameObject *parent;
        uint32_t spawnTime;

    friend class ObjectManager;
};

#endif // GameObject_h 
