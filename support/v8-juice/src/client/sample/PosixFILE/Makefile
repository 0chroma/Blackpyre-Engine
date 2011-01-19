#package.subdirs := js
default: all
include toc2.make

package.dist_files += $(wildcard *.cpp *.hpp *.js *.cc *.h)
SOURCES = demo.cc

c-bins.list := PosixFILE

PosixFILE.BIN.OBJECTS := demo.o
PosixFILE.BIN.LDADD = $(LIBV8JUICE_CLIENT_INTREE_LDADD) $(V8_LDFLAGS)
include $(toc2.dirs.makefiles)/c-bins.make
all: $(PosixFILE.BIN)

c-dlls.list := posix.FILE
posix.FILE.DLL.OBJECTS := PosixFILE.o
include $(toc2.dirs.makefiles)/c-dlls.make
all: $(posix.FILE.DLL)

define RUN_TEST_BIN
# $1 = run-name (must be unique)
# $2 = Binary name
# $3 = optional arg to binary
run-$(1):
	@LD_LIBRARY_PATH="$(v8juice.builds.libv8juice):$${LD_LIBRARY_PATH}"; \
	PATH="$(v8juice.builds.shell):$${PATH}"; \
	./$(2) $(3); \
	rc=$$$$?; echo "[run-$(1) RC==$$$$rc]"; exit $$$$rc
run: run-$(1)
endef

$(eval $(call RUN_TEST_BIN,PosixFILE1,PosixFILE,test.js))
