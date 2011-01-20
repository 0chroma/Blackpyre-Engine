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
#include "ResourceManager.h"
#include "util.h"
#include "Scripting.h"
//test header
#include "ObjectFrame.h"
#include "Entity.h"

#include <stdio.h>
#include <stdlib.h>

Global *Global::instance = 0;
GlUtil *Global::glUtil = 0;

WindowFramework *Global::window = 0;
ObjectManager *Global::objectManager = 0;
ResourceManager *Global::resourceManager = 0;
Scripting *Global::scripting = 0;

Global::Global(){
	window = new WindowGLUT();
    objectManager = ObjectManager::getInstance();
    resourceManager = ResourceManager::getInstance();
    scripting = Scripting::getInstance();
    glUtil = new GlUtil();
}

Global::~Global(){
    quitGame();
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
    scripting->init();
    scripting->run("game/main.js");
    ObjectFrame *p = new ObjectFrame(15.0f, 15.0f, 50.0f, 50.0f, 0.0f);
    objectManager->addObject(p);
}

void Global::quitGame(){
    exit(1);
}
