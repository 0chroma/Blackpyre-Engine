CC = g++
CFLAGS = -Wall
PROG = blackpyre

SRCS = main.h main.cpp Global.h Global.cpp WindowFramework.h WindowFramework.cpp WindowGLUT.h WindowGLUT.cpp

ifeq ($(shell uname),Darwin)
	LIBS = -framework OpenGL -framework GLUT
else
	LIBS = -lglut
endif

all: $(PROG)

$(PROG):	$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIBS)

clean:
	rm -f $(PROG)
