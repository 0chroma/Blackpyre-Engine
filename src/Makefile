CC = g++
CFLAGS = -Wall -g
PROG = blackpyre

SRCS = main.h main.cpp Global.h Global.cpp WindowFramework.h WindowFramework.cpp WindowGLUT.h WindowGLUT.cpp GlUtil.h GlUtil.cpp ObjectManager.h ObjectManager.cpp GameObject.h GameObject.cpp ObjectFrame.h ObjectFrame.cpp Entity.h Entity.cpp util.h util.cpp ResourceManager.h ResourceManager.cpp Scripting.h Scripting.cpp

ifeq ($(shell uname),Darwin)
	LIBS = -framework OpenGL -framework GLUT -framework GLU -framework pthread 
else
    LIBS = -lglut -lGLU -lpthread
endif

all: $(PROG)

$(PROG):	$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIBS) -L../support/v8/ -L../support/v8-juice/src/lib/juice/ ../support/glpng/lib/libglpng.a -I../support/v8/include/ -I../support/glpng/include/ -I../support/v8-juice/src/include/

clean:
	rm -f $(PROG)
