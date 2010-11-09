/*
 * Blackpyre Engine
 * Copyright (c) 2010 William Riley. All rights reserved.
 * 
 * Source available under the Academic Free License
 * See LICENSE for licensing information
 */

#include "WindowFramework.h"

WindowFramework::WindowFramework(int argc, char **argv){
    timeLast = (uint32_t)0;
}

WindowFramework::~WindowFramework(){

}

int WindowFramework::create(char* title){
	return 0;
}

void WindowFramework::handleKeypress(unsigned char key, int x, int y){

}

uint32_t WindowFramework::getTime(){
    return (uint32_t)0;
}

uint32_t WindowFramework::getTimeSinceLast(){
    uint32_t now = getTime();
    uint32_t last = timeLast;
    timeLast = now;
    return now - last;
}
