/*
 * Blackpyre Engine
 * Copyright (c) 2010 William Riley. All rights reserved.
 * 
 * Source available under the Academic Free License
 * See LICENSE for licensing information
 */

#include "Entity.h"

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <OpenGL/glpng.h>
#else
#include <GL/gl.h>
#endif

Entity::Entity(float x, float y, float sx, float sy)
    : GameObject(){
    posX = x;
    posY = y;
    sizeX = sx;
    sizeY = sy;
    angle = 0;
}

Entity::~Entity(){

}

void Entity::render(){
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
