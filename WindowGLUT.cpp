/*
 * Blackpyre Engine
 * Copyright (c) 2010 William Riley. All rights reserved.
 * 
 * Source available under the Academic Free License
 * See LICENSE for licensing information
 */

#include <stdio.h>

#include "WindowGLUT.h"
#include "WindowFramework.h"
#include "GlUtil.h"
#include "Global.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

WindowGLUT::WindowGLUT(int argc, char **argv) : WindowFramework(argc, argv){
	glutInit(&argc, argv);
}

WindowGLUT::~WindowGLUT(){

}

int WindowGLUT::create(char* title){
    GlUtil *glUtil = Global::getInstance()->glUtil;
    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(640, 480);
	
	glutCreateWindow(title);
	//fprintf(stdout, "%s\n", title);
	glUtil->initRendering();
    
    glutDisplayFunc(GlUtil::drawScene);
	glutKeyboardFunc(WindowGLUT::handleKeypress);
	glutReshapeFunc(GlUtil::handleResize);

	glutMainLoop();
	return 0;
}

void WindowGLUT::handleKeypress(unsigned char key, int x, int y){
    //noop
}

void WindowGLUT::swapBuffers(){
    glutSwapBuffers();
}

void WindowGLUT::postRedisplay(){
	glutPostRedisplay();
}
