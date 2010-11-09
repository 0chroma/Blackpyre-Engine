/*
 * Blackpyre Engine
 * Copyright (c) 2010 0chroma. All rights reserved.
 * 
 * Source available under the Academic Free License
 * See LICENSE for licensing information
 */


#include "Global.h"

#include <stdio.h>

int main(int argc, char **argv){
    fprintf(stderr, "game starting...\n");
	Global *game = Global::getInstance();
	game->init();
	return 0;
}
