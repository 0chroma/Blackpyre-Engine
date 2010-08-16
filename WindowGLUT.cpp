/*
 * Blackpyre Engine
 * Copyright (c) 2010 0chroma. All rights reserved.
 * 
 * Source available under the Academic Free License
 * See LICENSE for licensing information
 */

#include <stdio.h>
#include <iostream>

#include "WindowGLUT.h"
#include "WindowFramework.h"

WindowGLUT::WindowGLUT(int argc, char **argv) : WindowFramework(argc, argv){
	
}

WindowGLUT::~WindowGLUT(){

}

int WindowGLUT::create(char* title){
	//fprintf(stdout, "%s\n", title);
	std::cout << title;
	return 0;
}
