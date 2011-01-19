#include <v8/juice/plugin.h>
#include <v8/juice/PathFinder.h>
#include <v8/juice/Phoenix.h>
#include <sstream>
#include "mutex.hpp"
/**
   Set to 1 to use a no-op plugin (non-)loader (just for testing
   purposes, or when no plugin loader is implemented for this platform).
*/
#if v8_juice_CONFIG_ENABLE_PLUGINS
#  define PLUGIN_USE_NOOP 0
#else
#  define PLUGIN_USE_NOOP 1
#endif

/* only for debuggering */
#if 0
#  ifndef CERR
#    include <iostream>
#    define CERR std::cerr << __FILE__ << ":" << std::dec << __LINE__ << " : "
#  endif
#endif
namespace v8 {
namespace juice {
namespace plugin {

    std::string open( const std::string & basename, std::string & errmsg ); // defined in one of the platform-specific files

    using namespace ::v8;
    using ::v8::juice::PathFinder;

    struct PathFinder_plugins_context {};
    struct PathFinder_phoenix_initializer
    {
	void operator()( PathFinder & t ) const
	{
	    t.Path(v8_juice_plugin_CONFIG_PLUGINS_PATH);
	    t.Extensions(v8_juice_plugin_CONFIG_DLL_EXTENSIONS);
	    t.PathSeparator(v8_juice_plugin_CONFIG_PATH_SEPARATOR);
	}
    };

    PathFinder & PluginsPath()
    {
	typedef ::v8::juice::Detail::phoenix<PathFinder,
	    PathFinder_plugins_context,
	    PathFinder_phoenix_initializer> PHX;
	return PHX::instance();
    }

    LoadPluginScope * LoadPluginScope::current = 0;
    LoadPluginScope::LoadPluginScope( Handle<Object> target )
	: target(target),
	  returnVal(target),
	  prev(LoadPluginScope::current)
    {
	LoadPluginScope::current = this;
    }

    LoadPluginScope::~LoadPluginScope()
    {
	LoadPluginScope::current = this->prev;
    }

    LoadPluginScope * LoadPluginScope::Current()
    {
	return LoadPluginScope::current;
    }

    Handle<Object> LoadPluginScope::Target() const
    {
	return this->target;
    }

    void LoadPluginScope::SetReturnValue( Handle<Value> v )
    {
	this->returnVal = v;
    }

    Handle<Value> LoadPluginScope::ReturnValue() const
    {
	return this->returnVal;
    }

    Handle< Value > LoadPlugin( std::string const & modname,
				Handle< Object > target )
    {
        static v8::juice::mutex Mu;
        v8::juice::mutex_sentry locker(Mu);
	LoadPluginScope sentry(target);
	std::string errmsg;
	std::string fn( open( modname, errmsg ) );
	if( ! errmsg.empty() )
	{
	    std::ostringstream os;
	    os << "LoadPlugin(\""<<modname<<"\") DLL error message: dll=["<<fn<<"]: "
	       << errmsg
	       << "\nPluginPath()=["<<PluginsPath().PathString()<<']';
	    errmsg = os.str();
	    return ThrowException( String::New(errmsg.c_str(),
					       static_cast<int>(errmsg.size())) );
	}
	else if( fn.empty() )
	{
	    std::ostringstream os;
	    os << "LoadPlugin(\""<<modname<<"\"): No DLL found in path "
	       << '['<<PluginsPath().PathString()<<']';
	    errmsg = os.str();
	    return ThrowException( String::New(errmsg.c_str(),
					       static_cast<int>(errmsg.size())) );
	}
	return sentry.ReturnValue();
    }

    Handle<Value> LoadPlugin(const Arguments& argv)
    {
	const int argc = argv.Length();
	if(  !argc || (argc>2) )
	{
	    return ThrowException(String::New("Invalid usage: LoadPlugin(String[,Object])"));
	}
	Handle<Object> tgt = argv.Holder();
	if( argc == 2 )
	{
	    if( ! argv[1]->IsObject() )
	    {
		return ThrowException(String::New("LoadPlugin() Second argument is-not-a Object!"));
	    }
	    tgt = Handle<Object>( Object::Cast( *argv[1] ) );
	}
	String::AsciiValue av( argv[0] );
	std::string dllname = *av ? *av : "";
	return LoadPlugin( dllname, tgt );
    }


    /** Used by the platform-specific open() implementations. */
    static std::string FindPlugin( const std::string & basename )
    {
	// CERR << "find("<<basename<<")... path="<<Path().PathString()<<"\nextensions="<<Path().extensions_string()<<"\n";
	return PluginsPath().Find( basename );
    }


    bool Detail::PluginStaticInit( PluginInitFunction f )
    {
	LoadPluginScope * sc = f ? LoadPluginScope::Current() : 0;
	if( ! sc ) return false;
	try
	{
	    sc->SetReturnValue( f( sc->Target() ) );
	}
	catch(...)
	{}
	return true;
    }

#if PLUGIN_USE_NOOP
    std::string open( const std::string & basename, std::string & errmsg )
    {
	if(0)
	{ // only here to avoid a "static function defined but not used" warning
	    FindPlugin( basename );
	}
	errmsg = std::string("v8::juice::plugin::open(")
	    + basename
	    + std::string( "): not implemented for this build of v8-juice." )
	    ;
	return std::string();
    }
#endif // PLUGIN_USE_NOOP


}}} // namespaces

#if ! PLUGIN_USE_NOOP
#    if v8_juice_plugin_CONFIG_HAVE_LIBLTDL || v8_juice_plugin_CONFIG_HAVE_LIBDL
#      include "plugin.dl.cpp"
#    elif defined(WIN32)
#      include "plugin.win32.cpp"
#    endif
#endif // WIN32?

#undef PLUGIN_USE_NOOP
