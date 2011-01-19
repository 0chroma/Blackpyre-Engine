package.subdirs := js
default: all
include toc2.make

package.dist_files += $(wildcard *.cpp *.hpp *.js *.cc *.h)
SOURCES = shell.cc

c-bins.list := v8-juice-shell
v8-juice-shell.BIN.OBJECTS := shell.o
#$(error x=$(V8_LDFLAGS))
v8-juice-shell.BIN.LDADD = $(LIBV8JUICE_CLIENT_INTREE_LDADD) $(V8_LDFLAGS)
#$(error v8-juice-shell.BIN.LDADD=$(v8-juice-shell.BIN.LDADD))
package.install.bins := $(v8-juice-shell.BIN)
include $(toc2.dirs.makefiles)/c-bins.make
all: $(v8-juice-shell.BIN)

package.install.bins := $(v8-juice-shell.BIN)
#package.install.man1 = v8-juice-shell.1
subdirs: subdir-js
all: subdirs
