/*
 * Blackpyre Engine
 * Copyright (c) 2010 William Riley. All rights reserved.
 * 
 * Source available under the Academic Free License
 * See LICENSE for licensing information
 */


#include "ObjectManager.h"
#include "GameObject.h"

GameObject *ObjectManager::rootObject = 0;
ObjectManager *ObjectManager::instance = 0;
int ObjectManager::idCounter = 0;

ObjectManager::ObjectManager(){
    idCounter = 0;
    rootObject = 0;
}

ObjectManager::~ObjectManager(){

}

ObjectManager *ObjectManager::getInstance(){
	if(!instance){
		ObjectManager::instance = new ObjectManager;
	}
	return ObjectManager::instance;
}

int ObjectManager::addObject(GameObject *object){
    if(!rootObject){
        rootObject = object;
    }else{
        GameObject *listObj = rootObject;
        while(listObj->next){
            listObj = listObj->next;
        }
        listObj->next = object;
        object->prev = listObj;
    }
    object->id = ++idCounter;
    object->setSpawnTime();
    return (int) object->id;
}

void ObjectManager::removeObject(int id){
    GameObject *listObj = rootObject;
    while(listObj->id != id){
        listObj = listObj->next;
    }
    GameObject *prevObj = listObj->prev;
    GameObject *nextObj = listObj->next;
    prevObj->next = nextObj;
    if(nextObj){
        nextObj->prev = prevObj;
    }

}

void ObjectManager::renderObjects(){
    if(!rootObject){
        return;
    }
    GameObject *listObj;
    listObj = rootObject;
    while(listObj){
        listObj->render();
        listObj = listObj->next;
    }
}
