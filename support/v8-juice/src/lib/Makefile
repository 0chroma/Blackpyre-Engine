#!/usr/bin/make -f

include toc2.make

########################################################################
# Reminder: we set package.subdirs so that cleanup rules will work:
package.subdirs = juice
ifeq (1,$(v8_juice_CONFIG_ENABLE_PLUGINS))
package.subdirs += plugins
endif

subdirs: $(addprefix subdir-,$(package.subdirs))
subdir-plugins: |subdir-juice
all: subdirs
