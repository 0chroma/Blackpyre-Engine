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
    ObjectFrame *p = new ObjectFrame(50.0f, 50.0f, 300.0f, 400.0f);
    objectManager->addObject(p);
    //end test code

	char title[] = "Blackpyre";
	window->create(title);


	return 0;
}
