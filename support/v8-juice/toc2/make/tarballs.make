#!/do/not/make
#
# a toc snippet to help provide support for creating tarballs.
# It expects $(toc2.bins.tar) to be set via the configure process (e.g., via the
# gnu_tar test).
#
# Define:
#
# tarballs.list := target1 [...targetN]
# optional: tarballs.flags := flags to pass to tar (e.g., -z for gzip)
# optional: tarballs.chdir := [path to cd to before starting]
#
# For each target in tarballs.list you must define the following:
#
# target1.tarball.files := list of files/dirs to tar
# target1.tarball := destination filename
# optional: target1.tarball.flags := takes precedence over tarballs.flags
# optional: target1.tarball.chdir := [path to cd to before starting]
#
# xxx.tarballs.chdir is an odd-case var, and is not required (it defaults
# to .)
#
# To run all tarball targets run one of:
#   make tarballs
#
# To run one of them:
#   make tarball-targetname

toc2.tarballs.makefile := $(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST))
ifeq (,$(toc2.bins.tar))
$(warning you must define toc2.bins.tar before using the tarballs targets. Try running the gnu_tar toc test.)
tarballs:
$(patsubst %,tar-%,$(tarballs.list)):
else


toc2.tarballs.rules-generator = $(toc2.dirs.makefiles)/makerules.tarballs
$(toc2.tarballs.rules-generator):
$(toc2.tarballs.makefile):

toc2.tarballs.incfile = .toc2.tarballs.make
toc2.tarballs.clean_files += $(toc2.tarballs.incfile)
$(call toc2.call.define-cleanup-set,toc2.tarballs)

$(toc2.tarballs.rules-generator):
$(toc2.tarballs.incfile): $(toc2.tarballs.rules-generator) $(toc2.tarballs.makefile) $(toc2.files.makefile)
ifeq (1,$(toc2.flags.making_clean))
	@echo "$(MAKECMDGOALS): skipping tarballs rules generation."
else
	@echo "Generating tarballs rules: $(tarballs.list)"; \
	$(call toc2.call.generate-rules,tarballs,$(tarballs.list)) > $@
endif
-include $(toc2.tarballs.incfile)

.PHONY: tarballs
tarballs:

endif
# ^^^ end no-tar guard
