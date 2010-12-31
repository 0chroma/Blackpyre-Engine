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
#else
#include <GL/gl.h>
#endif

ObjectFrame::ObjectFrame(float x, float y, float sx, float sy, float a)
    : GameObject(x,y,sx,sy,a){
}

ObjectFrame::~ObjectFrame(){

}

void ObjectFrame::update(){
    
}

void ObjectFrame::render(){
    update();
    glPushMatrix();
	glTranslatef(posX, posY, 0.0f);
	glRotatef(angle*(180/3.14), 0.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);
    
	glVertex2f(0.0f, 0.0f);
	glVertex2f(sizeX, 0.0f);
	glVertex2f(sizeX, sizeY);
	glVertex2f(0.0f, sizeY);
	
	glEnd(); // GL_QUADS
	glPopMatrix();
}
