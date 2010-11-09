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
#include "GlUtil.h"
#include "Global.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdint.h>

int WindowGLUT::last_time = 0;
int WindowGLUT::now_time = 0;
int WindowGLUT::fps = 0;
int WindowGLUT::frame = 0;

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
	//fprintf(stderr, "%s\n", title);
	glUtil->initRendering();
    
    Global::getInstance()->setupGame();

    glutDisplayFunc(WindowGLUT::nullFunc);
	glutKeyboardFunc(WindowGLUT::handleKeypress);
	glutReshapeFunc(GlUtil::handleResize);
    
    glutTimerFunc(100, WindowGLUT::drawGame, 0);

	glutMainLoop();
	return 0;
}

void WindowGLUT::drawGame(int){
    GlUtil *glUtil = Global::getInstance()->glUtil;
    glutTimerFunc(33, WindowGLUT::drawGame, 0);

    glUtil->drawScene();

    glutPostRedisplay();
}

void WindowGLUT::handleKeypress(unsigned char key, int x, int y){
    //TODO
}

void WindowGLUT::nullFunc(){
    GlUtil *glUtil = Global::getInstance()->glUtil;
    glUtil->drawScene();
    glutSwapBuffers();
    
    frame++;
    if(!(frame%10)){
        now_time = glutGet(GLUT_ELAPSED_TIME);
        if(last_time){
            fps = (10.0/(now_time-last_time))*1000.0;
        }
        last_time = now_time;
        char title[50];
        sprintf(title, "Blackpyre - fps: %i", fps);
        glutSetWindowTitle(title);
    }
}

uint32_t WindowGLUT::getTime(){
    //my CS prof said that doing this would be ok, because I need to absctract with SDL which uses Uint32, so if it's wrong then it's not my fault
    return (uint32_t)glutGet(GLUT_ELAPSED_TIME);
}
