#package.subdirs := js
default: all
include toc2.make

package.dist_files += $(wildcard *.cpp *.hpp *.js *.cc *.h)
SOURCES = demo.cc

c-bins.list := BoundNative

BoundNative.BIN.OBJECTS := demo.o MyNative.o
#$(error x=$(V8_LDFLAGS))
BoundNative.BIN.LDADD = $(LIBV8JUICE_CLIENT_INTREE_LDADD) $(V8_LDFLAGS)
#$(error BoundNative.BIN.LDADD=$(BoundNative.BIN.LDADD))
# package.install.bins := $(BoundNative.BIN)
include $(toc2.dirs.makefiles)/c-bins.make
all: $(BoundNative.BIN)

#package.install.man1 = BoundNative.1
#subdirs: subdir-js
#all: subdirs

define RUN_TEST_BIN
# $1 = run-name (must be unique)
# $2 = Binary name
# $3 = optional arg to binary
run-$(1):
	LD_LIBRARY_PATH="$(v8juice.builds.libv8juice):$${LD_LIBRARY_PATH}"; \
	PATH="$(v8juice.builds.shell):$${PATH}"; \
	echo ./$(2) $(3); \
	rc=$$$$?; echo "[run-$(1) RC==$$$$rc]"; exit $$$$rc
run: run-$(1)
endef

$(eval $(call RUN_TEST_BIN,BoundNative1,BoundNative,my.js))
