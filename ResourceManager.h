/*
 * Blackpyre Engine
 * Copyright (c) 2010 William Riley. All rights reserved.
 * 
 * Source available under the Academic Free License
 * See LICENSE for licensing information
 */

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#else
#include <GL/gl.h>
#endif

#include <string.h>

#ifndef ResourceManager_h
#define ResourceManager_h

class ResourceManagerObject;
class ResourceManagerTextureObject;

class ResourceManager {
	public:
        ResourceManager();
        ~ResourceManager();

        static ResourceManager *getInstance();
        
        GLuint loadTexture(const char *filename);
        void unloadTexture(GLuint id);
    private:
        static ResourceManagerTextureObject *rootTextureObject;
        static ResourceManager *instance;
        static int idCounter;
};

class ResourceManagerObject {
    private:
        int id;
        char path[256];
        ResourceManagerObject *next;
        ResourceManagerObject *prev;
    friend class ResourceManager;
};

class ResourceManagerTextureObject : public ResourceManagerObject {
    private:
        GLuint textureId;
        ResourceManagerTextureObject *next;
        ResourceManagerTextureObject *prev;
    friend class ResourceManager;
};
#endif // ResourceManager_h 
