/*
 * Blackpyre Engine
 * Copyright (c) 2010 0chroma. All rights reserved.
 * 
 * Source available under the Academic Free License
 * See LICENSE for licensing information
 */

#include "Global.h"
#include "WindowGLUT.h"
#include "GlUtil.h"
#include "ObjectManager.h"
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
    //test code
    fprintf(stdout, "adding objframe");
    ObjectFrame *p = new ObjectFrame(15.0f, 15.0f, 350.0f, 450.0f);
    Entity *s = new Entity(400.0f, 100.0f, 100.0f, 100.0f);
    objectManager->addObject(p);
    objectManager->addObject(s);
    //end test code

	char title[] = "Blackpyre";
	window->create(title);

	return 0;
}
