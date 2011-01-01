/*
 * Blackpyre Engine
 * Copyright (c) 2010 0chroma. All rights reserved.
 * 
 * Source available under the Academic Free License
 * See LICENSE for licensing information
 */

#include "Entity.h"
#include "Global.h"
#include "GlUtil.h"
#include "ResourceManager.h"
#include "ObjectManager.h"

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#else
#include <GL/gl.h>
#endif

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

//Entity::objectmanagerId = 0;

Entity::Entity(float x, float y, float sx, float sy, float a, const char *sp = "")
    : GameObject(x,y,sx,sy,a){
    objectmanagerId = 0;
    sprite = sp;
    if(sp){
        ResourceManager *resourceManager = Global::getInstance()->resourceManager;
        texture = resourceManager->loadTexture(sprite);
    }
}

Entity::~Entity(){

}

void Entity::render(){
    update();
    glPushMatrix();
	glTranslatef(posX+(sizeX/2), posY+(sizeY/2), 0.0f);
	glRotatef(angle, 0.0f, 0.0f, 1.0f);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);

	glBegin(GL_TRIANGLE_STRIP);
    
    glTexCoord2f(1.0f, 0.0f);
	glVertex2f(sizeX/2, sizeY/2);
    glTexCoord2f(0.0f, 0.0f);
	glVertex2f(-sizeX/2, sizeY/2);
    glTexCoord2f(1.0f, 1.0f);
	glVertex2f(sizeX/2, -sizeY/2);
    glTexCoord2f(-0.0f, 1.0f);
	glVertex2f(-sizeX/2, -sizeY/2);

	glEnd(); // GL_QUAD
    
    glDisable(GL_TEXTURE_2D);
	
    glPopMatrix();
}

void Entity::update(){
    //uint32_t time = fabs(sin((timeSinceSpawn()/22.22)*(3.14/180)))*4000;
    uint32_t time = timeSinceSpawn()*2;
    while(time > 6000){
        time -= 6000;
    }
    angle = (timeSinceSpawn()/5)+initialAngle;
//    posX = initialPosX+(time*sin(initialAngle*(3.14/180))/15);
//    posY = initialPosY+(time*cos(initialAngle*(3.14/180))/15);
    posX = initialPosX + (time*sin((initialAngle+(time/10))*(3.14/180))/17);
    posY = initialPosY + (time*cos((initialAngle+(time/10))*(3.14/180))/17);
}

void Entity::show(){
    if(objectmanagerId == 0){
        ObjectManager *objectManager = Global::getInstance()->objectManager;
        objectmanagerId = objectManager->addObject(this);
    }
}

void Entity::hide(){
    if(objectmanagerId != 0){ 
        ObjectManager *objectManager = Global::getInstance()->objectManager;
        objectManager->removeObject(objectmanagerId);
        objectmanagerId = 0;
    }
}
