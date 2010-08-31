CC = g++
CFLAGS = -Wall
PROG = blackpyre

SRCS = main.h main.cpp Global.h Global.cpp WindowFramework.h WindowFramework.cpp WindowGLUT.h WindowGLUT.cpp GlUtil.h GlUtil.cpp ObjectManager.h ObjectManager.cpp GameObject.h GameObject.cpp ObjectFrame.h ObjectFrame.cpp Entity.h Entity.cpp

ifeq ($(shell uname),Darwin)
	LIBS = -framework OpenGL -framework GLUT -framework GLU 
else
	LIBS = -lglut -lGLU
endif

all: $(PROG)

$(PROG):	$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIBS)

clean:
	rm -f $(PROG)
