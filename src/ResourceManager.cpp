/*
 * Blackpyre Engine
 * Copyright (c) 2010 0chroma. All rights reserved.
 * 
 * Source available under the Academic Free License
 * See LICENSE for licensing information
 */


#include "ResourceManager.h"
#include "util.h"
#include "Global.h"
#include "GlUtil.h"

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#else
#include <GL/gl.h>
#endif

#include <stdio.h>

ResourceManagerTextureObject *ResourceManager::rootTextureObject = 0;
ResourceManager *ResourceManager::instance = 0;
int ResourceManager::idCounter = 0;

ResourceManager::ResourceManager(){
    idCounter = 0;
    rootTextureObject = 0;
}

ResourceManager::~ResourceManager(){

}

ResourceManager *ResourceManager::getInstance(){
	if(!instance){
		ResourceManager::instance = new ResourceManager;
	}
	return ResourceManager::instance;
}

GLuint ResourceManager::loadTexture(const char *filename){
    //check if we already loaded it
    ResourceManagerTextureObject *listObj = rootTextureObject;
    while(listObj){
        if(strcmp(listObj->path, dataPath(filename)) == 0){
            return listObj->textureId;
        }
        listObj = listObj->next;
    }
    ResourceManagerTextureObject *object = new ResourceManagerTextureObject();
    //add to linked list
    if(!rootTextureObject){
        rootTextureObject = object;
    }else{
        listObj = rootTextureObject;
        while(listObj->next){
            listObj = listObj->next;
        }
        listObj->next = object;
        object->prev = listObj;
        object->next = 0;
    }
    //setup
    GlUtil *glUtil = Global::getInstance()->glUtil;
    object->id = ++idCounter;
    strcpy(object->path, dataPath(filename));
    object->textureId = glUtil->loadTexture(filename);
    return object->textureId;
}

void ResourceManager::unloadTexture(GLuint id){
    ResourceManagerTextureObject *listObj = rootTextureObject;
    while(listObj->textureId != id){
        listObj = listObj->next;
    }
    ResourceManagerTextureObject *prevObj = listObj->prev;
    ResourceManagerTextureObject *nextObj = listObj->next;
    prevObj->next = nextObj;
    if(nextObj){
        nextObj->prev = prevObj;
    }

}
