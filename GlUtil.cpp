/*
 * Blackpyre Engine
 * Copyright (c) 2010 William Riley. All rights reserved.
 * 
 * Source available under the Academic Free License
 * See LICENSE for licensing information
 */

#include "GlUtil.h"
#include "Global.h"
#include "WindowFramework.h"

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#else
#include <GL/gl.h>
#endif

#include <stdio.h>

float _angle = 0.0f;

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
	_angle += 0.05f;
	if(_angle > 360.0f)
		_angle -= 360.0f;

	//Clear information from last draw
	glClearColor(.3, .3, .3, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
	glLoadIdentity(); //Reset the drawing perspective
	
	glPushMatrix();
	glTranslatef(320.0f, 240.0f, 0.0f);
	glRotatef(_angle, 0.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);
    
	glVertex2f(-150.0f, -150.0f);
	glVertex2f(150.0f, -150.0f);
	glVertex2f(150.0f, 150.0f);
	glVertex2f(-150.0f, 150.0f);
	
	glEnd(); // GL_QUADS
	glPopMatrix();

	WindowFramework *window = Global::getInstance()->window;
	window->swapBuffers();
	window->postRedisplay();
}
