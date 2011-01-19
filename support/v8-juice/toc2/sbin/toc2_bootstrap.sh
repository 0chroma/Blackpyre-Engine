#!/do/not/bash
# ^^^^ This file should be sourced (not run directly) from a toc2-style
# configure script.
#
# Source tree configure script, toc-style.
# The latest code is at http://toc.sourceforge.net/
#
# Do not run this directly: wrap it up in a script called 'configure', 
# stick it into your top-level build tree, set some environment vars,
# and source it. See the configure from the toc distribution for a
# quick starting point.
#
# Requires the the Bourne Again SHell, GNU Make, plus a skew of other open-source utilities
# which are typically installed on any Unix-type system.
#
# This whole thing is subject to change at any minute.
#
# Notes about this configure process:
# Project-wide vars are currently defined in:
# - this file
# - toc2.${PACKAGE_NAME}.make.at
# - And check the top-level Makefile, to be certain :/
#
#
# Any options you pass on the command line, like:
#  ./configure --prefix=/opt
# will be filtered through the shared makefile and config.h.
#
# This tool still requires quite a few things, but it will not aim to be all things
# to all projects. Customize as you see fit.
#
# Note: there are no guarantees that any exit codes mean anything specific!

test -z "${PACKAGE_VERSION}" -a -z "${PACKAGE_NAME}" && {
    echo "toc2_bootstrap.sh: environment vars PACKAGE_NAME and PACKAGE_VERSION must be set."
    exit 1
}
configure=${TOC2_CONFIGURE_SCRIPT-./configure}
test -f "$configure" || {
    echo "toc2_bootstrap.sh: could not find [$configure]!"
    exit 2
}

grep -i "toc" $configure > /dev/null || {
    # this is kind of a callback, actually, since we should only be
    # sourced from configure.
    echo "Your configure script does not appear to be toc-aware. It shouldn't be sourcing this file."
    exit 3
}

TOC2_TOP_SRCDIR=${PWD}
TOC2_HOME=${TOC2_HOME-"${TOC2_TOP_SRCDIR}/toc"}

test -d "${TOC2_HOME}" || {
    echo "The toc home directory, TOC2_HOME, not found. Set that variable to the top-most path to your toc installation, or unset it to use the default of ./toc"
    exit 4
}
export TOC2_TOP_SRCDIR
export TOC2_HOME
export PATH=${TOC2_HOME}/bin:${PATH}

{ # set up the core
    CORE_SH=${TOC2_HOME}/sbin/toc2_core.sh
    . ${CORE_SH} "$@" || { # core toc functions and initial sanity test
        echo "toc2_bootstrap.sh: Pain! Suffering! Loading ${CORE_SH} failed!"
        exit 5
    }
}

test x1 = "x${new_project}" && {
# ./configure --new-project
cat <<EOF
**********************************************************************

Creating Makefile stubs for new project!

This process will create a file called Makefile.suggestion in each
subdirectory.  These files may be renamed to Makefile and tweaked to
suit the needs of your project.

**********************************************************************
EOF
    echo "Press ENTER to continue or Ctrl-C to quit."
    read
    ${TOC2_HOME}/bin/create_makefile_stubs.sh
    return
}


toc2_export PACKAGE_NAME="${PACKAGE_NAME}"
toc2_export PACKAGE_VERSION="${PACKAGE_VERSION}"
toc2_export TOC2_HOME="${TOC2_HOME}"
toc2_export TOC2_EMOTICON_OKAY=${TOC2_EMOTICON_OKAY}
toc2_export TOC2_EMOTICON_ERROR=${TOC2_EMOTICON_ERROR}
toc2_export TOC2_EMOTICON_WARNING=${TOC2_EMOTICON_WARNING}

# include package-specific configure script. This eases upgrading a project's toc:
pkgconfig=${PACKAGE_CONFIGURE_SCRIPT-configure.${PACKAGE_NAME}}
test -f $pkgconfig && {
    . $pkgconfig
    err=$?
    test $err -eq 0 || {
        echo "toc2_bootstrap.sh: error: $pkgconfig returned [non-zero] error code $err."
        exit $err
    }
}
# toc2_test toc_project_makefile "Looking for toc.${PACKAGE_NAME}.make"
toc2_add_config SHELL=$(which bash)

# toc2_test_require toc2_configure_finalcheck
# toc2_configre_finalcheck is arguable :/



##### end the configuration process and write out our files...
toc2_endconfigure


# if $POSTCONFIG exists it is run as our final step:
POSTCONFIG=${TOC2_TOP_SRCDIR}/postconfig.${PACKAGE_NAME}
test -f ${POSTCONFIG} && {
    . ${POSTCONFIG} || {
        err=$?
        echo "${POSTCONFIG} returned non-zero exit status: $?"
        return $err
    }
}

package_configure=${TOC2_TOP_SRCDIR}/toc2.${PACKAGE_NAME}.configure.make
toc2_dump_make_properties | perl -pe 's|^(\w+)=|$1 ?= |' > ${package_configure}

find . -type f -name '.toc.*' | xargs rm -f &>/dev/null # these sometimes cause weird behaviour after a reconfigure

cat <<-EOF
	=========================================================================
	${TOC2_EMOTICON_OKAY}  Build configuration complete. You may now run make (or gmake).
	Be sure to read any messages from the tests run by configure.
	=========================================================================
EOF
# ^^^^ note the intentional use of hard tabs in the cat <<-EOF, above.

