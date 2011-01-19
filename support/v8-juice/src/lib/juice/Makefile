include toc2.make

HEADERS = 

OBJECTS = $(addsuffix .o,\
	PathFinder \
	PathFinder-cw \
	cleanup \
	plugin \
	juice \
	JSClassCreator \
	JuiceShell \
	whprintf \
	jssprintf \
	time \
	mutex \
	StringTokenizer \
	)
#	PathFinder-js

########################################################################
# Build DLL...
c-dlls.list := libv8-juice
#libv8-juice.DLL.VERSION := $(V8JUICE_VERSION_DOTTED)
libv8-juice.DLL.OBJECTS = $(OBJECTS)
libv8-juice.DLL.LDADD = $(LDADD_DL)
#ifeq (1,$(v8juice_CONFIG_ENABLE_PLUGINS))
#  libv8-juice.DLL.OBJECTS += plugin/plugin.o plugin/path_finder.o
#endif
include $(toc2.dirs.makefiles)/c-dlls.make
# end DLL rules
########################################################################

libv8-juice.LIB.OBJECTS := $(libv8-juice.DLL.OBJECTS)
$(eval $(call toc2.eval.rules.c-lib,libv8-juice))

all: $(libv8-juice.LIB)
all: $(libv8-juice.DLL)
