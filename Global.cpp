/*
 * Blackpyre Engine
 * Copyright (c) 2010 0chroma. All rights reserved.
 * 
 * Source available under the Academic Free License
 * See LICENSE for licensing information
 */

#include "Global.h"
#include "WindowGLUT.h"

Global *Global::instance = 0;

WindowFramework *Global::window = 0;

Global::Global(){
	window = new WindowGLUT();
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
	char title[] = "bar";
	window->create(title);
	return 0;
}
