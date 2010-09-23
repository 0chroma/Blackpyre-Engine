/*
 * Blackpyre Engine
 * Copyright (c) 2010 0chroma. All rights reserved.
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

#include <math.h>
#include <stdint.h>

Entity::Entity(float x, float y, float sx, float sy, float a)
    : GameObject(x,y,sx,sy,a){

}

Entity::~Entity(){

}

void Entity::render(){
    update();
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

void Entity::update(){
    uint32_t time = fabs(sin((timeSinceSpawn()/22.22)*(3.14/180)))*4000;
    angle = (time/10)+initialAngle;
    posX = initialPosX+(time*sin(initialAngle*(3.14/180))/15);
    posY = initialPosY+(time*cos(initialAngle*(3.14/180))/15);
}
