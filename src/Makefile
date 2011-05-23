CC = g++
CFLAGS = -Wall -g -Wl,-rpath,'./lib' #'${ORIGIN}/lib'
PROG = blackpyre

SRCS = main.cpp Global.cpp WindowFramework.cpp WindowGLUT.cpp GlUtil.cpp ObjectManager.cpp GameObject.cpp ObjectFrame.cpp Entity.cpp util.cpp ResourceManager.cpp Scripting.cpp

INCLUDES =  ../support/glpng/lib/libglpng.a \
            -I../support/v8/include/ \
            -I../support/glpng/include/ \
            -I../support/v8-juice/src/include/

LIBRARY_PATHS = -L../support/v8 \
                -L../support/v8-juice/src/lib/juice/

ifeq ($(shell uname),Darwin)
	LIBS = -framework OpenGL -framework GLUT -framework GLU -framework pthread -framework v8_g
else
    LIBS = -lglut -lGLU -lpthread -lv8_g -lv8-juice
endif

all: $(PROG)

$(PROG):	$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIBS) $(LIBRARY_PATHS) $(INCLUDES)

clean:
	rm -f $(PROG)
