/*
 * Blackpyre Engine
 * Copyright (c) 2010 0chroma. All rights reserved.
 * 
 * Source available under the Academic Free License
 * See LICENSE for licensing information
 */

#include "GameObject.h"
#include "WindowFramework.h"
#include "Global.h"
#include <stdint.h>

GameObject::GameObject(){
    next = 0;
    prev = 0;
    parent = 0;
    spawnTime = (uint32_t)0;
}

GameObject::~GameObject(){

}

void GameObject::render(){
    
}

void GameObject::setSpawnTime(){
    spawnTime = Global::getInstance()->window->getTime();
}

uint32_t GameObject::timeSinceSpawn(){
    return Global::getInstance()->window->getTime() - spawnTime;
}
