/*
 * Blackpyre Engine
 * Copyright (c) 2010 William Riley. All rights reserved.
 * 
 * Source available under the Academic Free License
 * See LICENSE for licensing information
 */


#include "Global.h"

#include <stdio.h>

int main(int argc, char **argv){
    fprintf(stdout, "game starting");
	Global *game = Global::getInstance();
	game->init();
	return 0;
}
