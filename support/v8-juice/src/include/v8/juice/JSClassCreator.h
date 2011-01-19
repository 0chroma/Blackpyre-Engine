#if !defined(CODE_GOOGLE_COM_P_V8_V8_CLASSWRAP_H_INCLUDED)
#define CODE_GOOGLE_COM_P_V8_V8_CLASSWRAP_H_INCLUDED 1
/*
   Author: Stephan Beal (http://wanderinghorse.net/home/stephan/)

   License: same as v8 (see below)
*/
// Copyright 2009 Stephan Beal. All rights reserved.  Redistribution
// and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
//       copyright notice, this list of conditions and the following
//       disclaimer in the documentation and/or other materials provided
//       with the distribution.
//     * Neither the name of Google Inc. nor the names of its
//       contributors may be used to endorse or promote products derived
//       from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include <v8.h>
namespace v8 {
namespace juice {

    /**
       JSClassCreator is a tool to simplify the creation of new
       JS-side classes. It does not have any features for automatic
       conversions between the native and JS object, for purposes of,
       e.g., forwarding JS funcs to member functions. See the
       WeakJSClassCreator and ClassBinder subclasses for those
       features.

       Example usage:

       \code
       JSClassCreator binder( "MyClass", targetObject, myCtor, 1 );
       binder
           .Inherit( otherBinder )
	   .Set( "funcOne", my_callback_func )
	   .Set( "valOne", String::New("hi there!") )
	   .Seal(); // Seal() MUST come last!
       \endcode

       Seal() MUST be the last function called and no setters should
       be called after calling Seal() (it might work, it might not,
       but in my experimentation v8 is very sensitive to certain
       orders of operations).
    */
    class JSClassCreator
    {
    private:
	char const * className;
	Handle<Object> target;
	Persistent<FunctionTemplate> ctorTmpl;
	Persistent<ObjectTemplate> proto;
 	JSClassCreator( JSClassCreator const & ); // not implemented
 	JSClassCreator & operator=( JSClassCreator const & ); // not implemented
	bool hasTarget;
        bool wasSealed;
    public:
	/**
	   Begins setting up a new JS class, as a member of the given target object,
	   with the given class name and constructor function. The optionan internalFieldCount
	   can be set here or by calling SetINternalFieldCount().

           This class does NOT copy className - it is assumed to be a
           constant/static string.
	*/
	JSClassCreator( char const * className,
			Handle<Object> target,
			v8::InvocationCallback ctor,
			int internalFieldCount = 0 );
	/**
	   Identical to the 4-arg ctor except that it does not take a target
	   object. The implications of this are:

	   - The Target() member will return an empty handle.
	   - The caller must add this class to his chosen target manually,
	   as demonstrated here:

	   \code
	   target->Set( String::New("ClassName"), myCreator.Seal() );
           // or:
           myCreator.Seal();
           myCreator.AddClassTo( target );
	   \endcode
	*/
	JSClassCreator( char const * className,
			v8::InvocationCallback ctor,
			int internalFieldCount = 0 );
	/**
	   Does nothing.
	 */
	virtual ~JSClassCreator();

	/**
	   Sets the number of internal fields for this JS class (also
	   setable via the constructor).

	   Returns this object.
	*/
	virtual JSClassCreator & SetInternalFieldCount( int n );

	/**
	   Returns the constructor template.
	*/
	Handle<FunctionTemplate> CtorTemplate() const;

	/**
	   Returns this object's JS class name.
	*/
	char const * ClassName() const;

	/**
	   Returns the prototype object.
	*/
	Handle<ObjectTemplate> Prototype() const;

	/**
	   Returns the target set in the constructor. If no target was
	   set in the ctor, the returned handle will be
	   default-constructed (empty).
	*/
	Handle<Object> Target() const;

	/**
	   Adds the generated JS class to the given target object,
	   using ClassName() as the property name.

	   This should not be called before Seal() is called.

	   If a target object was set in the ctor, this need not be
	   called - it will be called by Seal(). It may, however, be
	   called to add the class to other objects.

	   Returns the JS constructor function object (the same as
	   Seal()).
	*/
	Handle<Function> AddClassTo( Handle<Object> target );

	/**
	   Finalizes the class creation process and adds the
	   construtor to this->Target() (if it was set in the
	   ctor). No setter methods should be called after this (well,
	   go ahead - maybe it'll work for you).

	   It returns the result of CtorTemplate()->GetFunction(), for
	   reasons too deep and dark to shed light on at the moment.

           If no target object was set in the ctor, call AddClassTo()
           (*after* calling Seal()) to add the generated class to the
           a target object (e.g. your global object).
	*/
	Handle<Function> Seal();
        /** Returns true if Seal() has been called on this object. */
        bool IsSealed() const;
	/**
	   Creates a new instance of this class' represented type,
	   using the constructor function set in the ctor.  This must
	   not be called before Seal() is called (results are
	   undefined). The returned object is owned by the JS engine,
	   and it may be Empty() (v8's way of signaling an exception).
	*/
	virtual Handle<Object> NewInstance( int argc, Handle<Value> argv[] );

	/**
	   Sets a property with the given name and value.

	   Returns this object.
	*/
	JSClassCreator & Set( char const * name, Handle< Data > const & value , PropertyAttribute attributes = v8::None );

	/**
	   Sets a function property with the given name and callback function.

	   Returns this object.
	*/
	JSClassCreator & Set( char const * name, InvocationCallback func, PropertyAttribute attributes = v8::None );

	/**
	   Adds a property accessor to the prototype object.

	   Returns this object.
	*/
	JSClassCreator & Set( char const * name,
			      AccessorGetter  	getter,
			      AccessorSetter  	setter = 0,
			      Handle< Value >  	data = Handle< Value >(),
			      AccessControl  	settings = v8::DEFAULT,
			      PropertyAttribute attribute = v8::None
			      );
	/**
	   Sets this JS class to inherit the given parent.

	   Returns this object.

	   Note that this has NOTHING to do with any inhertance which
	   may or may not apply to any native objects attached to
	   JS instances created via this interface.
	*/
	JSClassCreator & Inherit( Handle< FunctionTemplate > parent );

	/**
	   Convenience form of Inherit( parent.CtorTemplate() ).

	   Returns this object.
	*/
	virtual JSClassCreator & Inherit( JSClassCreator const & parent );

    };

}} /* namespaces */

#endif /* CODE_GOOGLE_COM_P_V8_V8_CLASSWRAP_H_INCLUDED */
