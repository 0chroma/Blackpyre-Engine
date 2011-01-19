#!/usr/bin/make -f

include toc2.make

#ifneq (,$(strip $(filter dist testdist clean distclean uninstall install,$(MAKECMDGOALS))))
# only build these package.subdirs when running certain targets
#      package.subdirs_FIRST += include
#endif

package.subdirs_FIRST += include lib
package.subdirs_SECOND = client


package.subdirs = $(package.subdirs_FIRST) $(package.subdirs_SECOND)
subdirs: $(addprefix subdir-,$(package.subdirs))
all: subdirs
#$(package.subdirs_SECOND): |$(package.subdirs_FIRST)
subdir-lib: |subdir-include
subdir-client: |subdir-lib

#package.dist_files += $(wildcard in.*) test.cpp
# Makefile.for.generated.src.tree

