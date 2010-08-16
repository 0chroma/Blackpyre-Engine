/*
 * Blackpyre Engine
 * Copyright (c) 2010 0chroma. All rights reserved.
 * 
 * Source available under the Academic Free License
 * See LICENSE for licensing information
 */

#include <stdio.h>

#include "WindowGLUT.h"
#include "WindowFramework.h"

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
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
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	
	glutCreateWindow(title);
	//fprintf(stdout, "%s\n", title);
	

	glutMainLoop();
	return 0;
}
