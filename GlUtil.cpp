/*
 * Blackpyre Engine
 * Copyright (c) 2010 0chroma. All rights reserved.
 * 
 * Source available under the Academic Free License
 * See LICENSE for licensing information
 */

#include "GlUtil.h"
#include "Global.h"
#include "WindowFramework.h"

#include <GL/gl.h>
#include <GL/glu.h>

GlUtil::GlUtil(){

}

GlUtil::~GlUtil(){

}

void GlUtil::initRendering(){
    glDisable(GL_DEPTH_TEST);
}

void GlUtil::handleResize(int w, int h){
	glMatrixMode(GL_PROJECTION); //Switch to setting the camera perspective
	
	glLoadIdentity(); //Reset the camera

    glOrtho(0, w, h, 0, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.375, 0.375, 0);
}

void GlUtil::drawScene(){
	//Clear information from last draw
    glClearColor(.3, .3, .3, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
	glLoadIdentity(); //Reset the drawing perspective
	
	glBegin(GL_QUADS);
    
	glVertex2f(20.0f, 20.0f);
	glVertex2f(400.0f, 20.0f);
	glVertex2f(400.0f, 400.0f);
	glVertex2f(20.0f, 400.0f);
	
	glEnd(); // GL_QUADS

    WindowFramework *window = Global::getInstance()->window;
    window->swapBuffers();
}
