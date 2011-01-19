#ifndef V8_JUICE_PATHFINDER_CW_H_INCLUDED
#define V8_JUICE_PATHFINDER_CW_H_INCLUDED
/************************************************************************
This file contains the declarations (and some template
implementations) of the v8::juice::cw::ClassWrap-related
specializations used for binding the v8::juice::PathFinder class to
JS.

This file is intended to be used by client code which wants to get
C++ access to JS-side PathFinder objects. To do so, the following
operations are made available.

- convert::CastFromJS<PathFinder>( jsPathFinderObject )
- cw::Installer<PathFinder>::SetupBindings()


- convert::CastToJS(PathFinder) MIGHT work, depending on which
ClassWrap policy set is defined (see the header file).
************************************************************************/
// Author: stephan beal <stephan@s11n.net>
// License: Public Domain

#include <string>
#include <list>
#include <map>
#include <v8.h>
#include "PathFinder.h"

#include <v8/juice/ClassWrap.h>
////////////////////////////////////////////////////////////////////////
// Select a ClassWrap policy set...
#define CLASSWRAP_BOUND_TYPE v8::juice::PathFinder
#if 0
   // Default ClassWrap policy set.
#  include <v8/juice/ClassWrap-JSToNative.h>
#else
#  if 0
// #  warning "JuiceBind policy set"
#    include <v8/juice/ClassWrap_JuiceBind.h>
#  else
// #  warning "TwoWay policy set"
#    include <v8/juice/ClassWrap_TwoWay.h>
#  endif
#endif

namespace v8 { namespace juice {  namespace cw {
    /**
       ClassWrap ClassName policy specialization for
       v8::juice::PathFinder.
    */
    template <>
    struct ClassName<PathFinder>
    {
        static char const * Value();
    };
    /**
       ClassWrap Factory policy specialization for
       v8::juice::PathFinder.

       Maintenance note: they are implemented in PathFinder-cw.cc.
    */
    template <>
    struct Factory<PathFinder>
    {
        //! Required by Factory interface.
        static size_t const AllocatedMemoryCost = sizeof(PathFinder);
        //! Required by Factory interface.
        typedef PathFinder Type;
        //! Required by Factory interface.
        typedef PathFinder * NativeHandle;
        /**
           Required by Factory interface.

           Accepts 0 to 3 arguments, just like the native ctor.
        */
        static NativeHandle Instantiate( Arguments const & argv,
                                         std::ostream & exceptionText);
        /**
           Required by Factory interface.

           Destroys obj unless it refers to one of the internal/shared
           PathFinder instances.
        */
        static void Destruct( v8::Handle<v8::Object>, NativeHandle obj );
    };
    /**
       ClassWrap Installer policy specialization for v8::juice::PathFinder.
    */
    template <>
    struct Installer<PathFinder>
    {
        /** Installs the PathFinder class into the given object. */
        static void SetupBindings( ::v8::Handle< ::v8::Object> target );
    };

} } } // v8::juice::cw

#endif // V8_JUICE_PATHFINDER_CW_H_INCLUDED
