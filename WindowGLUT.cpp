/*
 * Blackpyre Engine
 * Copyright (c) 2010 William Riley. All rights reserved.
 * 
 * Source available under the Academic Free License
 * See LICENSE for licensing information
 */

#include <stdio.h>

#include "WindowGLUT.h"

WindowGLUT::WindowGLUT(int argc, char **argv){
	
}

WindowGLUT::~WindowGLUT(){

}

int WindowGLUT::create(const char title){
	fprintf(stdout, title);
	fprintf(stdout, "\n");
	return 0;
}
