/************************************************************************
A JS/Native binding of the v8::juice::PathFinder class, using the
v8::juice::cw binding mechanism.
************************************************************************/
//    Author: stephan beal <stephan@s11n.net>
//    License: Public Domain

#include <iostream>
#include <set>

#include <v8.h>
#include <v8/juice/PathFinder-cw.h>
#include <v8/juice/bind.h>
#include <v8/juice/plugin.h>


#if !defined(CERR)
#    include <iostream> /* only for debuggering */
#    define CERR std::cerr << __FILE__ << ":" << std::dec << __LINE__ << " : "
#endif

namespace {
    enum Internal { MagicExternalArgc = 1 /*must be 1 or else crash*/ };
    //! PathFinder.toString() impl.
    static v8::Handle<v8::Value> pf_toString( v8::Arguments const & argv )
    {
        using namespace v8::juice;
        typedef PathFinder T;
        T * p = convert::CastFromJS<T>( argv.This() );
        convert::StringBuffer sb;
        sb << "[object "<<cw::ClassName<T>::Value()<<"@"<<p<<"]";
        return sb;
    }

} // anon namespace

namespace v8 { namespace juice { namespace cw {
    using namespace ::v8::juice;

#define JSTR(X) v8::String::New(X)

    
    //! internal
    typedef std::set<Factory<PathFinder>::NativeHandle> PFSet;
    /**
       All PathFinders which should be deleted by
       this type (that depends on how the ctor is called)
       are added here. Only dtors called for these objects
       will trigger a delete.
    */
    static PFSet & pfset()
    {
        static PFSet pf;
        return pf;
    }


    char const * ClassName<PathFinder>::Value()
    {
        return "PathFinder";
    }

    /**
       ClassWrap Factory<PathFinder> policy implementation.

       Reminder to self: we implement a custom factory instead of
       using the constructor-forwarding factory so that we can do some
       internal trickery to bind in some shared instances of the
       class.
    */
    Factory<PathFinder>::NativeHandle
    Factory<PathFinder>::Instantiate( Arguments const & argv,
                                      std::ostream & exceptionText)
    {
        const int argc = argv.Length();
        if( (MagicExternalArgc == argc) && argv[0]->IsExternal() )
        { // assume arg is an externally-owned/shared PathFinder instance
            Local<External> ex( External::Cast( *argv[0] ) );
            NativeHandle xp = bind::GetBoundNative<PathFinder>( ex->Value() );
            if( xp )
            {
                bind::UnbindNative( xp ); // we don't need this anymore, but cw::WeakWrap policy might re-bind it.
                return xp;
            }
            else
            {
                exceptionText << "First argument to "
                              << ClassName<PathFinder>::Value()
                              << " ctor failed type check!";
                return 0;
            }
        }
        // TODO: add array arg support.
        std::string a0 = (argc>0) ? convert::JSToStdString(argv[0]) : "";
        std::string a1 = (argc>1) ? convert::JSToStdString(argv[1]) : "";
        std::string a2 = (argc>2) ? convert::JSToStdString(argv[2]) : ":";
        //CERR << ClassName<PathFinder>::Value()<< "(["<<a0<<"], ["<<a1<<"], ["<<a2<<"])\n";
        NativeHandle pf = new PathFinder( a0, a1, a2 );
        if( pf )
        {
            pfset().insert( pf );
        }
        return pf;
    }

    void Factory<PathFinder>::Destruct( v8::Handle<v8::Object>, NativeHandle obj )
    {
        if( obj )
        {
            PFSet::iterator it = pfset().find(obj);
            if( it != pfset().end() )
            {
                //CERR << ClassName<PathFinder>::Value() << " dtor deleting on @"<<obj<<'\n';
                pfset().erase(it);
                delete obj;
            }
        }
    }

    void Installer<PathFinder>::SetupBindings( ::v8::Handle< ::v8::Object> target )
    {
        v8::juice::SetupPathFinderClass(target);
    }
    
}}} // namespaces


namespace v8 { namespace juice {

    ::v8::Handle< ::v8::Value> SetupPathFinderClass( ::v8::Handle< ::v8::Object> target )
    {
        using namespace v8;
        using namespace v8::juice;
        v8::HandleScope scope;
        typedef PathFinder N;
        typedef cw::ClassWrap<N> CW;
        typedef convert::MemFuncInvocationCallbackCreator<N> MF;
        CW & cw( CW::Instance() );
        if( cw.IsSealed() )
        {
            /**
               ASSUME that it was us who did the sealing. We return
               here because changes made to the prototype after the
               first time GetFunction() is called on the prototype
               template appear to have no effect.
            */
            cw.AddClassTo(target);
            return target;
        }
        typedef convert::InvocationCallbackCreator ICC;
        v8::InvocationCallback isAccessible = ICC::F1::Invocable<bool,std::string const &,N::IsAccessible>;
        v8::InvocationCallback baseName = ICC::F1::Invocable<std::string,std::string const &,N::BaseName>;
        
        typedef N::StringList SL;
        typedef SL const & SLCR;
        struct FuncInfo
        {
            char const * name;
            v8::InvocationCallback func;
        }  FuncList[] =
        {
        { "addExtensionString", MF::M1::Invocable<void,std::string const &,&N::AddExtension> },
        { "addPathString", MF::M1::Invocable<void,std::string const &,&N::AddPath> },
        { "baseName", baseName },
        { "clearCache", MF::M0::Invocable<void, &N::ClearCache> },
        { "find", MF::M1::Invocable<std::string,std::string const &,&N::Find> },
        { "isAccessible", isAccessible },
        { "isEmpty", MF::M0::Invocable<bool, &N::IsEmpty> },
        { "getPathSeparator", MF::M0::Invocable<std::string,&N::PathSeparator> },
        { "setPathSeparator", MF::M1::Invocable<void,std::string const &,&N::PathSeparator> },
        { "getPathString", MF::M0::Invocable<std::string,&N::PathString> },
        { "setPathString", MF::M1::Invocable<size_t,std::string const &,&N::Path> },
        { "getPathArray", MF::M0::Invocable<SL,&N::Path> },
        { "setPathArray", MF::M1::Invocable<size_t,SLCR,&N::Path> },
        { "getExtensionsArray", MF::M0::Invocable<SL,&N::Extensions> },
        { "setExtensionsArray", MF::M1::Invocable<size_t,SLCR,&N::Extensions> },
        { "getExtensionsString", MF::M0::Invocable<std::string,&N::ExtensionsString> },
        { "setExtensionsString", MF::M1::Invocable<size_t,std::string const &,&N::Extensions> },
        { "toString", pf_toString},
        {0,0}
        };
        ////////////////////////////////////////////////////////////////////////
        // Bind instance functions:
        for( FuncInfo * f = FuncList; f->name; ++f )
        {
            cw.Set( f->name, f->func );
        }
        ////////////////////////////////////////////////////////////////////////
        // Bind instance properties:
        cw.BindGetterSetter< std::string, &N::PathSeparator, void, std::string const &,&N::PathSeparator>( "pathSeparator" );
        cw.BindGetterSetter< std::string, &N::PathString, size_t, std::string const &,&N::Path>( "pathString" );
        cw.BindGetterSetter< SL, &N::Path, size_t, SLCR,&N::Path>( "pathArray" );
        cw.BindGetterSetter< SL, &N::Extensions, size_t, SLCR,&N::Extensions>( "extensionsArray" );
        cw.BindGetterSetter< std::string, &N::ExtensionsString, size_t, std::string const &,&N::Extensions>( "extensionsString" );
        cw.Set( "dirSeparator", convert::CastToJS( N::DirSeparator() ), v8::ReadOnly );

        //////////////////////////////////////////////////////////////
        // Seal the class:
        Handle<Function> ctor( cw.Seal() );
        // ^^^^^^^ reminder: starting now, changes made to the prototype will have no effect.
        // At least, v8 seems to work that way.
        cw.AddClassTo(target);

        //////////////////////////////////////////////////////////////
        // Bind class ("static") properties/funcs:
        ctor->Set( JSTR("dirSeparator"), convert::CastToJS( N::DirSeparator() ), v8::ReadOnly );
        ctor->Set( JSTR("isAccessible"), convert::CastToJS( isAccessible ) );
        ctor->Set( JSTR("baseName"), convert::CastToJS( baseName ) );

        //////////////////////////////////////////////////////////////
        // Set up some shared instances:
        {
            Handle<Object> shared = Object::New();
            ctor->Set(JSTR("shared"),shared);

            if(1)
            {
                // Install an instance wrapping the v8::juice::plugin::PluginsPath() shared object:
                PathFinder * pf = &::v8::juice::plugin::PluginsPath();
                Handle<Value> pfex( External::New( pf ) );
                bind::BindNative( pf, pf );
                Handle<Object> pfobj = cw.NewInstance( MagicExternalArgc, &pfex );
                shared->Set(String::New("plugins"), pfobj );
            }

            if(1)
            {
                // Includes includes path:
                PathFinder * pf = &::v8::juice::ScriptsPath();
                Handle<Value> pfex( External::New( pf ) );
                bind::BindNative( pf, pf );
                Handle<Object> pfobj = cw.NewInstance( MagicExternalArgc, &pfex );
                shared->Set(String::New("include"), pfobj );
            }
        }

        if(0)
        { // some basic sanity checks...
            typedef cw::Extract<N> XT;
            v8::HandleScope hscope;
            v8::Handle<v8::Object> jobj =
                cw.NewInstance(0,0)
                //ctor->NewInstance(0,0)
                ;
            N const * bound = CW::ToNative::Value(jobj);
            CERR << "bound (void *) == @"<<(void const *)bound<<'\n';
            CERR << "bound (CastFromJS<N*>(jsObj)) == @"<<convert::CastFromJS<N*>( jobj )<<'\n';
            CERR << "bound (JSToNative<N>(jsObj)) == @"<<convert::JSToNative<N>()( jobj )<<'\n';
            CERR << "bound (JSToNative<N*>(jsObj)) == @"<<convert::JSToNative<N*>()( jobj )<<'\n';
            CERR << "bound (cw::JSToNativeImpl<N>()(jsObj)) == @"<<cw::JSToNativeImpl<N>()( jobj )<<'\n';
            CERR << "bound (cw::JSToNativeImpl<N*>()(jsObj)) == @"<<cw::JSToNativeImpl<N*>()( jobj )<<'\n';
            CERR << "Extract: @"<<(void const *)XT::ExtractVoid(jobj,false)<<"\n";
            N const * np = convert::CastFromJS<N>( jobj );
            CERR << "bound (CastFromJS<N>(jsObj)) == @"<<np<<'\n';
            if( bound )
            {
                void * exh = jobj->GetPointerFromInternalField(CW::InternalFields::NativeIndex);
                CERR << "fetched void* == "<<(const void *)exh<<'\n';
            }
#if 0 // only if using the TwoWay policy set
            {
                v8::Handle<v8::Value> check = convert::CastToJS(bound);
            }
#endif       
            cw.DestroyObject( jobj );
        }
        
	return target;
    }
#undef JSTR
}} // namespaces
