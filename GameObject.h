/*
 * Blackpyre Engine
 * Copyright (c) 2010 0chroma. All rights reserved.
 * 
 * Source available under the Academic Free License
 * See LICENSE for licensing information
 */

#ifndef GameObject_h
#define GameObject_h

class GameObject {
	public:
        GameObject();
        ~GameObject();

        virtual void render();
    protected:
        int id;
        GameObject *next;
        GameObject *prev;

    friend class ObjectManager;
};

#endif // GameObject_h 
