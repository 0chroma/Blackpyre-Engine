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

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#else
#include <GL/gl.h>
#endif
#include <string>


class Entity : public GameObject{
    public:
        Entity(float x, float y, float sx, float sy, float a, std::string sprite);
        ~Entity();

        GLuint texture;
        std::string sprite;

        void render();
        void update();

        void show();
        void hide();

    private:
        int objectmanagerId;
};

#endif // Entity_h
