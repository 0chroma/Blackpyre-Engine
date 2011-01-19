/************************************************************************
 ************************************************************************/

#include "MyNative.h"
#include <v8/juice/forwarding.h>
#include <v8/juice/ClassBinder.h>


int my_forwarded_func()
{
    CERR << "my_forwarded_func()!\n";
    return 42;
}
int my_forwarded_func3(int x,int y,int z)
{
    CERR << "my_forwarded_func3()!\n";
    return x + y + z;
}
void my_void_forwarded_func(int x)
{
    CERR << "my_void_forwarded_func("<<x<<")!\n";
}

v8::Handle<v8::Value> MyNative::forwarder( v8::Arguments const & argv )
{
    return v8::juice::convert::FwdToFunc( my_forwarded_func3, argv );
    //return v8::juice::convert::FwdToFunc3<int,int,int,int>( my_forwarded_func3, argv );
}

/**
   Demonstration of adding a close() or destroy() member to
   a bound class.
*/
v8::Handle<v8::Value> MyNative_destroy( v8::Arguments const & argv )
{
    if(1)
    { // informational only: has no real effect:
        MyNative * N = v8::juice::convert::CastFromJS<MyNative>( argv.This() );
        if( ! N ) return v8::ThrowException(v8::String::New("This object is not (or is no longer) a MyNative!"));
        CERR << "MyNative_destroy( @"<<(void const *)N<<" )\n";
    }
    typedef v8::juice::ClassBinder<MyNative> BinderType;
    BinderType::DestroyObject(argv.This());
    return v8::Undefined();
}

bool MyNative::SetupClass( v8::Handle<v8::Context> cx )
{
    typedef v8::juice::ClassBinder<MyNative> WT;
    WT & w = WT::Instance();
    //WT w;
    WT::SearchPrototypesForNative(true); // allows JS classes to subclass MyNative
    WT::AllowCtorWithoutNew(true);
    //BindMemFunc( w, "func1", &MyNative::func1 );
    typedef MyNative MY;
    w
        .BindMemFunc< int, &MY::func1>( "func1" )
        .BindMemFunc< int, int, &MY::func2 >( "func2" )
        .BindMemFunc< std::string,&MY::hi >( "hi" )
        .BindMemFunc< MY *,&MY::me >( "me" )
        .BindMemFunc< bool,MY *,&MY::him >( "him" )
        .BindMemFunc< double,int,int,&MY::func3 >( "func3" )
        .BindMemFunc< void,&MY::avoid >( "avoid" )
        .BindMemFunc< void,int,&MY::avoid1 >( "avoid1" )
        .BindMemFunc< void,int,double, &MY::avoid2 >( "avoid2" )
        .BindMemFunc< double,int,int,int, &MY::takes3 >( "takes3" )
        .BindMemVar<std::string, &MY::str>( "str" )
        .BindMemFunc< &MY::forwarder >( "forwarder" )
        .BindMemFunc< void, MY &, &MY::someref1 >( "someref1" )
        .BindPropToAccessors< int, &MY::propGetter, int, int, &MY::propSetter >( "proxiedProp" )
        .BindMemVar<MyNative *, &MY::other>("other")
        .BindPropToAccessors< MY *, &MY::getOther, void, MY *, &MY::setOther >( "otherProxy" )
        //.BindPropToAccessors< int, &MY::propGetter, void, int, &MY::propSetterVoid >( "proxiedProp" )
        //.BindPropToGetter< int, &MY::propGetter >( "proxiedProp" )
        //.BindPropToSetter< void, int, &MY::propSetterVoid >( "proxiedProp" )
        V8_JUICE_BUG_NUMBER(11)
        //.BindMemFunc< MY &, MY &, &MY::someref2 >( "someref2" )
        //.BindMemFunc< MY const &, MY const &, &MY::someref3 >( "someref3" )
        .Set( "destroy", MyNative_destroy )
        ;
#if 0
    if( WT::OptShallowBind )
    { // these should cause a compile-time error:
        w.Inherit( w );
        w.InheritNative<MY>();
    }
#endif
    w.Seal();
    w.AddClassTo( cx->Global() );
    return true;
}

