########################################################################
# This is my first scons and first python, so this code is as ugly as
# can be. scons hackers are welcomed to improve upon it! :)

import platform
import re
import sys
import os
#from types import DictType, StringTypes
#root_dir = os.path.dirname(File('SConstruct').rfile().abspath)

print("********************************************************************************")
print("BIG FAT HAIRY WARNING:");
print("\ni am no scons expert and i hate python, so this build doesn't do very much!")
print("\nThis file assumes you have (and need) -ldl, and needs to be hacked to work on non-*nix.")
print("\nEdit this and set v8_home to the installation prefix of your libv8!")
print("\nFixes and additions from scons hackers are welcomed!")
print("********************************************************************************")
v8_home = os.path.abspath('/home/stephan')
v8_incdir = os.path.join(v8_home,'include')
v8_libdir = os.path.join(v8_home,'lib')
v8_libname = 'v8' #or use 'v8_g'
env = Environment(
    CPPPATH = ['#/src/include',v8_incdir],
    LIBPATH = ['.',v8_libdir]
    )


libjuice_libname = 'v8-juice'
if( True ):
    my_src = [os.path.join('#/src/lib/juice/', x) for x in [
        'cleanup.cc',
        'JSClassCreator.cc',
        'jssprintf.cc',
        'juice.cc',
        'JuiceShell.cc',
        'PathFinder.cc',
        'PathFinder-cw.cc',
        'plugin.cc',
        'time.cc',
        'mutex.cpp',
        'whprintf.c',
        'StringTokenizer.cc'
        ]]
    print("Creating static juice lib...");
    env.StaticLibrary(libjuice_libname,my_src)
    print("Creating shared juice lib...");
    env.SharedLibrary(libjuice_libname,my_src ,
                      LIBS = ['dl',v8_libname,'pthread'],
                      )


if( True ):
    my_src = [os.path.join('#/src/client/shell/', x) for x in [
        'shell.cc'
        ]]
    print("Creating shell...")
    env.Program( target = 'v8-juice-shell',
                 source = my_src,
                 LDFLAGS = "-L. -export-dynamic",
                 LIBS = [libjuice_libname,v8_libname]
                 )
