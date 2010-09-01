/*
 * Blackpyre Engine
 * Copyright (c) 2010 0chroma. All rights reserved.
 * 
 * Source available under the Academic Free License
 * See LICENSE for licensing information
 */

#include "ObjectFrame.h"

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <OpenGL/glpng.h>
#else
#include <GL/gl.h>
#include <GL/glpng.h>
#endif

ObjectFrame::ObjectFrame(float x, float y, float sx, float sy){
    posX = x;
    posY = y;
    sizeX = sx;
    sizeY = sy;
    angle = 0;
}

ObjectFrame::~ObjectFrame(){

}

void ObjectFrame::render(){
    glPushMatrix();
	glTranslatef(posX, posY, 0.0f);
	glRotatef(angle, 0.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);
    
	glVertex2f(0.0f, 0.0f);
	glVertex2f(sizeX, 0.0f);
	glVertex2f(sizeX, sizeY);
	glVertex2f(0.0f, sizeY);
	
	glEnd(); // GL_QUADS
	glPopMatrix();
}
