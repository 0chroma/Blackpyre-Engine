
#include <ostream>
#include <sstream>
#include <v8/juice/JSClassCreator.h>
namespace v8 { namespace juice {

    using namespace v8;

    JSClassCreator::JSClassCreator( char const * className,
				    Handle<Object> target,
				    v8::InvocationCallback ctor,
				    int internalFieldCount )
	: className(className ? className : "UnnamedClass"),
	  target(target),
	  ctorTmpl( Persistent<FunctionTemplate>::New( FunctionTemplate::New(ctor) ) ),
	  proto( Persistent<ObjectTemplate>::New( ctorTmpl->PrototypeTemplate() ) ),
	  hasTarget(true),
          wasSealed(false)
    {
	if( internalFieldCount > 0 )
	{
	    ctorTmpl->InstanceTemplate()->SetInternalFieldCount(internalFieldCount);
	}
    }

    JSClassCreator::JSClassCreator( char const * className,
				    v8::InvocationCallback ctor,
				    int internalFieldCount )
	: className(className),
	  target(),
	  ctorTmpl( Persistent<FunctionTemplate>::New( FunctionTemplate::New(ctor) ) ),
	  proto( Persistent<ObjectTemplate>::New( ctorTmpl->PrototypeTemplate() ) ),
	  hasTarget(false)
    {
	if( internalFieldCount > 0 )
	{
	    ctorTmpl->InstanceTemplate()->SetInternalFieldCount(internalFieldCount);
	}
    }

    JSClassCreator::~JSClassCreator()
    {
    }

    JSClassCreator & JSClassCreator::SetInternalFieldCount( int n )
    {
	this->ctorTmpl->InstanceTemplate()->SetInternalFieldCount( n );
	return *this;
    }

    Handle<FunctionTemplate> JSClassCreator::CtorTemplate() const
    {
	return this->ctorTmpl;
    }
    
    char const * JSClassCreator::ClassName() const
    {
	return this->className;
    }

    Handle<ObjectTemplate> JSClassCreator::Prototype() const
    {
	return this->proto;
    }

    Handle<Object> JSClassCreator::Target() const
    {
	return this->target;
    }

    Handle<Function> JSClassCreator::AddClassTo( Handle<Object> tgt )
    {
	Handle<Function> func( ctorTmpl->GetFunction() );
	tgt->Set( ::v8::String::New(this->className), func );
        //if( this->target.IsEmpty() ) this->target = tgt;
//         if( ! this->hasTarget )
//         {
//             this->target = tgt;
//             this->hasTarget;
//         }
	return func;
    }

    bool JSClassCreator::IsSealed() const
    {
        return this->wasSealed;
    }

    Handle<Function> JSClassCreator::Seal()
    {
        this->wasSealed = true;
	// In my experience, if GetFunction() is called BEFORE setting up
	// the Prototype object, v8 gets very unhappy (class member lookups don't work?).
	if( this->hasTarget )
	{
	    return this->AddClassTo( this->target );
	}
	else return ctorTmpl->GetFunction();
    }

    Handle<Object> JSClassCreator::NewInstance( int argc, Handle<Value> argv[] )
    {
	return this->CtorTemplate()->GetFunction()->NewInstance( argc, argv );
    }

    JSClassCreator & JSClassCreator::Set( char const * name, Handle< Data > const & value , PropertyAttribute attributes )
    {
	proto->Set( String::New(name), value, attributes );
	return *this;
    }

    JSClassCreator & JSClassCreator::Set( char const * name, InvocationCallback func, PropertyAttribute attributes )
    {
	proto->Set( String::New(name), FunctionTemplate::New(func), attributes );
	return *this;
    }

    JSClassCreator & JSClassCreator::Inherit( Handle< FunctionTemplate > parent )
    {
	ctorTmpl->Inherit( parent );
	return *this;
    }

    JSClassCreator & JSClassCreator::Inherit( JSClassCreator const & parent )
    {
	return this->Inherit( parent.CtorTemplate() );
    }

    JSClassCreator & JSClassCreator::Set( char const * name,
					  AccessorGetter  	getter,
					  AccessorSetter  	setter,
					  Handle< Value >  	data,
					  AccessControl  	settings,
					  PropertyAttribute attribute
					  )
    {
	this->proto->SetAccessor( String::New(name), getter, setter, data, settings, attribute );
	return *this;
    }

}}
