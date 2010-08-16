/*
 * Blackpyre Engine
 * Copyright (c) 2010 William Riley. All rights reserved.
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
