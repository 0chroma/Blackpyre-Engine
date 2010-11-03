/*
 * Blackpyre Engine
 * Copyright (c) 2010 William Riley. All rights reserved.
 * 
 * Source available under the Academic Free License
 * See LICENSE for licensing information
 */

#include "Global.h"
#include "WindowGLUT.h"
#include "GlUtil.h"
#include "ObjectManager.h"
#include "util.h"
//test header
#include "ObjectFrame.h"
#include "Entity.h"

#include <stdio.h>

Global *Global::instance = 0;
GlUtil *Global::glUtil = 0;

WindowFramework *Global::window = 0;
ObjectManager *Global::objectManager = 0;

Global::Global(){
	window = new WindowGLUT();
    objectManager = ObjectManager::getInstance();
    glUtil = new GlUtil();
}

Global::~Global(){

}

Global *Global::getInstance(){
	if(!instance){
		Global::instance = new Global;
	}
	return Global::instance;
}

int Global::init(int argc, char **argv){
    setupPath();

	char title[] = "Blackpyre";
	window->create(title);


	return 0;
}

void Global::setupGame(){
    ObjectFrame *p = new ObjectFrame(15.0f, 15.0f, 50.0f, 50.0f, 0.0f);
    Entity *a = new Entity(300.0f, 200.0f, 100.0f, 100.0f, 0.0f, "testTexture.png");
    Entity *b = new Entity(300.0f, 200.0f, 100.0f, 100.0f, 45.0f, "testTexture.png");
    Entity *c = new Entity(300.0f, 200.0f, 100.0f, 100.0f, 90.0f, "testTexture.png");
    Entity *d = new Entity(300.0f, 200.0f, 100.0f, 100.0f, 135.0f, "testTexture.png");
    Entity *e = new Entity(300.0f, 200.0f, 100.0f, 100.0f, 180.0f, "testTexture.png");
    Entity *f = new Entity(300.0f, 200.0f, 100.0f, 100.0f, 225.0f, "testTexture.png");
    Entity *g = new Entity(300.0f, 200.0f, 100.0f, 100.0f, 270.0f, "testTexture.png");
    Entity *h = new Entity(300.0f, 200.0f, 100.0f, 100.0f, 315.0f, "testTexture.png");
    objectManager->addObject(p);
    objectManager->addObject(a);
    objectManager->addObject(b);
    objectManager->addObject(c);
    objectManager->addObject(d);
    objectManager->addObject(e);
    objectManager->addObject(f); 
    objectManager->addObject(g);
    objectManager->addObject(h); 
}
