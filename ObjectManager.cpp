/*
 * Blackpyre Engine
 * Copyright (c) 2010 William Riley. All rights reserved.
 * 
 * Source available under the Academic Free License
 * See LICENSE for licensing information
 */

#include "ObjectManager.h"

class GameObject;

ObjectManager::ObjectManager(){

}

ObjectManager::~ObjectManager(){

}

ObjectManager *ObjectManager::getInstance(){
	if(!instance){
		ObjectManager::instance = new ObjectManager;
	}
	return ObjectManager::instance;
}

int ObjectManager::addObject(GameObject object){
    objectList.push_back(object);
    return (int) objectList.size()-1;
}

void ObjectManager::removeObject(int id){
    
}

void ObjectManager::renderObjects(){
    int i;
    for(i=objectList.begin(); i!=objectList.end(); ++i){
        objectList[*i]->render();
    }
}
