////////////////////////////////////////////////////////////////////////
// platform-specific parts of plugin.{c,h}pp: for libltdl and libdl
////////////////////////////////////////////////////////////////////////
#if v8_juice_plugin_CONFIG_HAVE_LIBLTDL // prefer libltdl, but if it's not available...
#  include <ltdl.h>
#else           // assume libdl is.
#  include <dlfcn.h> // this actually has a different name on some platforms!
#endif // v8_juice_plugin_CONFIG_HAVE_LIBLTDL

namespace v8 { namespace juice { namespace plugin {

    std::string open( const std::string & basename, std::string & errmsg )
    {
	std::string where = FindPlugin( basename );
	if( where.empty() )
	{
	    errmsg = std::string("v8::juice::plugin::open(")
		+ basename
		+ std::string( "): No DLL found.")
		;
	    return std::string();
	}

	static bool donethat = false;
	if( !donethat && (donethat=true) )
	{
	    // About these dlopen(0) calls:
	    // They open the main() app and are
	    // required. If they are not called at some
	    // point then loading DLLs will not work.
#if v8_juice_plugin_CONFIG_HAVE_LIBLTDL
	    lt_dlinit();
	    lt_dlopen( 0 );
#else
	    dlopen( 0, RTLD_NOW | RTLD_GLOBAL );
#endif
	}

	void * soh = 0; // DLL handle

	//CERR << "s11n::plugin::open("<<basename<<"): trying to open: " << where << "\n";

#if v8_juice_plugin_CONFIG_HAVE_LIBLTDL // libltdl:
	soh = lt_dlopen( where.c_str() );
#else // libdl:
	soh = dlopen( where.c_str(), RTLD_NOW | RTLD_GLOBAL );
#endif
	if( 0 == soh )
	{
	    const char * err = 0;
#if v8_juice_plugin_CONFIG_HAVE_LIBLTDL // libltdl:
	    err = lt_dlerror();
#else // libdl:
	    err = dlerror();
#endif
	    errmsg = err ? err : "unknown error";
	}
	else
	{
	    errmsg.clear();
	}
	return where;
    }

}}} // namespaces

