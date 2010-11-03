CC = g++
CFLAGS = -Wall -g
PROG = blackpyre

SRCS = main.h main.cpp Global.h Global.cpp WindowFramework.h WindowFramework.cpp WindowGLUT.h WindowGLUT.cpp GlUtil.h GlUtil.cpp ObjectManager.h ObjectManager.cpp GameObject.h GameObject.cpp ObjectFrame.h ObjectFrame.cpp Entity.h Entity.cpp util.h util.cpp

ifeq ($(shell uname),Darwin)
	LIBS = -framework OpenGL -framework GLUT -framework GLU -framework glpng
else
	LIBS = -lglut -lGLU -lglpng
endif

all: $(PROG)

$(PROG):	$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIBS)

clean:
	rm -f $(PROG)
