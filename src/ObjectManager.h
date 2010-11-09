/*
 * Blackpyre Engine
 * Copyright (c) 2010 William Riley. All rights reserved.
 * 
 * Source available under the Academic Free License
 * See LICENSE for licensing information
 */

#ifndef ObjectManager_h
#define ObjectManager_h

//class GameObject;

#include "GameObject.h"

class ObjectManager {
	public:
        ObjectManager();
        ~ObjectManager();

        static ObjectManager *getInstance();
        
        void renderObjects();
        int addObject(GameObject *object);
        void removeObject(int id);
    private:
        static GameObject *rootObject;
        static ObjectManager *instance;
        static int idCounter;
};

#endif // ObjectManager_h 
