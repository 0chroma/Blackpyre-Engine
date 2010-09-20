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
    angle = timeSinceSpawn()/10;
    glPushMatrix();
	glTranslatef(posX+(sizeX/2), posY+(sizeY/2), 0.0f);
	glRotatef(angle, 0.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);
    
	glVertex2f(-sizeX/2, -sizeY/2);
	glVertex2f(sizeX/2, -sizeY/2);
	glVertex2f(sizeX/2, sizeY/2);
	glVertex2f(-sizeX/2, sizeY/2);
	
	glEnd(); // GL_QUADS
	glPopMatrix();
}
