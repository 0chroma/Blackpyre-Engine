CC = g++
CFLAGS = -Wall -g -Wl,-rpath,'./lib' #'${ORIGIN}/lib'
PROG = blackpyre

SRCS = main.h main.cpp Global.h Global.cpp WindowFramework.h WindowFramework.cpp WindowGLUT.h WindowGLUT.cpp GlUtil.h GlUtil.cpp ObjectManager.h ObjectManager.cpp GameObject.h GameObject.cpp ObjectFrame.h ObjectFrame.cpp Entity.h Entity.cpp util.h util.cpp ResourceManager.h ResourceManager.cpp Scripting.h Scripting.cpp

INCLUDES =  ../support/glpng/lib/libglpng.a \
            -I../support/v8/include/ \
            -I../support/glpng/include/ \
            -I../support/v8-juice/src/include/

LIBRARY_PATHS = -L../support/v8 \
                -L../support/v8-juice/src/lib/juice/

ifeq ($(shell uname),Darwin)
	LIBS = -framework OpenGL -framework GLUT -framework GLU -framework pthread -framework v8
else
    LIBS = -lglut -lGLU -lpthread -lv8 -lv8-juice
endif

all: $(PROG)

$(PROG):	$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIBS) $(LIBRARY_PATHS) $(INCLUDES)

clean:
	rm -f $(PROG)
