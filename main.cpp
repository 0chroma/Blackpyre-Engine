/*
 * Blackpyre Engine
 * Copyright (c) 2010 0chroma. All rights reserved.
 * 
 * Source available under the Academic Free License
 * See LICENSE for licensing information
 */


#include "Global.h" 



int main(int argc, char **argv){
	Global *game = Global::getInstance();
	game->init();
	return 0;
}
