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
//test header
#include "ObjectFrame.h"

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
	char title[] = "Blackpyre";
	window->create(title);

    //test code
    ObjectFrame *p = new ObjectFrame(0.0f, 0.0f, 300.0f, 300.0f);
    objectManager->addObject(p);

	return 0;
}
