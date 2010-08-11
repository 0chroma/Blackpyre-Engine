/*
 * Blackpyre Engine
 * Copyright (c) 2010 0chroma. All rights reserved.
 * 
 * Source available under the Academic Free License
 * See LICENSE for licensing information
 */

#include "Global.h"
#include "WindowGLUT.h"

Global::Global(){
	window = new WindowGLUT();
}

Global::~Global(){

}

int Global::init(int argc, char **argv){
	char title="foo";
	window->create(title);
	return 0;
}
