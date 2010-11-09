/*
 * Blackpyre Engine
 * Copyright (c) 2010 William Riley. All rights reserved.
 * 
 * Source available under the Academic Free License
 * See LICENSE for licensing information
 */

#include "GlUtil.h"
#include "Global.h"
#include "ObjectManager.h"
#include "WindowFramework.h"
#include "util.h"

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <OpenGL/glpng.h>
#else
#include <GL/gl.h>
#include <GL/glpng.h>
#endif

#include <stdio.h>
#include <string.h>

float _angle = 0.0f;

GlUtil::GlUtil(){

}

GlUtil::~GlUtil(){

}

void GlUtil::initRendering(){
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void GlUtil::handleResize(int w, int h){
    fprintf(stderr, "width is %u, height is %u\n", w, h);

    glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION); //Switch to setting the camera perspective
	
	glLoadIdentity(); //Reset the camera

    glOrtho(0, 640, 480, 0, 0, 1);
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
	
	
    //glTranslatef(0.375, 0.375, 0);
    ObjectManager *objMan = ObjectManager::getInstance();

    objMan->renderObjects();
}

GLuint GlUtil::loadTexture(const char *filename){
	//Note that since this is a 2d game engine, this function doesn't bother with mipmaps.
	//If 3d aspects (eg. backgrounds) are added later, this function needs to be updated.
    GLuint textureId;
    //TODO: support other formats
    pngInfo tmpInfo;
    textureId = pngBind(dataPath(filename), PNG_NOMIPMAPS, PNG_ALPHA, &tmpInfo, GL_CLAMP, GL_NEAREST, GL_NEAREST);
    
    if (textureId != 0) {
           fprintf(stderr, "Loaded %s successfully with textureId of %i\n", dataPath(filename), textureId);
    }
    else {
           fprintf(stderr, "Can't load %s\n", dataPath(filename));
    }
    glDisable(GL_TEXTURE_2D);
    return textureId;
}
