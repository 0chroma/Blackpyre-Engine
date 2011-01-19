#ifndef WANDERINGHORSE_NET_GOOGLE_V8_P3_PLUGIN_H_INCLUDED_
#define WANDERINGHORSE_NET_GOOGLE_V8_P3_PLUGIN_H_INCLUDED_ 1

#include <string>
#include <v8.h>
#include <v8/juice/plugin-config.h>

namespace v8 {
namespace juice {
    class PathFinder; // declared in PathFinder.h
/**
   The plugin namespace encapsulates an API for dynamically loading
   JS functionality via plugins (DLLs/shared libraries).

   On Linux (and maybe other Unix) platforms it is important to link
   any application using this API with the -export-dynamic (or
   -rdyanamic) flag, or else DLL loading will likely fail (the DLLs
   won't be able to see the callback function they need!).

   TODO:

   - Add path accessors/mutators to the public API (without exposing
   the underlying/internal PathFinder class, if we can do that without
   too much work).
*/
namespace plugin {

    using ::v8::Handle;
    using ::v8::Value;
    using ::v8::Arguments;
    using ::v8::Object;
    /**
       Tries to dynamically load a DLL using the given dll name. The
       name need not have a file extension (a platform-specific
       extension will be used if needed) or directory element(s) (or
       it may have a relative path). It will be sought using the lookup
       path defined by the PluginsPath() object.

       The library search path can be inspected and modified using
       the PluginsPath() function.

       If a DLL is found but opening fails for some reason,
       this routine throws a JS exception with platform-specific
       error message.

       It is (theoretically) safe for plugins to load other plugins
       during their loading process, as long as they fetch (and copy)
       the LoadPluginScope::Current() pointer before loading additional
       plugins. See LoadPluginScope for details.

       Thread safety notes:

       As of v8-juice version 20091114, this function locks a global
       mutex so that multiple threads may load plugins safely.

       For versions older than 20091114:
       
       The process which enables plugins to "back-feed" information
       into the running JS engine is not strictly thread-safe. That
       is, if multiple threads call LoadPlugin() at once, the plugins
       might feed their data into the wrong target object. That said:
       v8 explicitly disallows multiple threads from using the engine
       at one time, so it is theoretically (let's stress the word
       "theoretically") impossible that multiple v8 client threads
       could be loading DLLs this way at the same time. It would be
       unusual, to say the least.
    */
    Handle< Value > LoadPlugin( std::string const & dllname, Handle< Object > target );

    /**
       A script-side equivalent of the "native" LoadPlugin(). This can
       be added directly as a function in a JS object.

       JS signature:

       Mixed load_plugin( String pluginname [, Object target] )

       This function throws if:

       - No arguments, or more than two arguments.

       - Target object is-not-a Object

       - No DLL can be found for the given name. (The PluginsPath()
       object is used to do the lookups.)

       - A DLL is found, but the native DLL opening routine fails
       (often a result of missing symbols or binary incompatibility).

       The exception string will tell the caller what exactly the
       problem was.

       What actually happens:

       The plugin "should" (if it is well behaved) install its
       contents in the given object (which defaults args.Holder(),
       which is normally the Global object of the current context).

       The exact semantics of the return value are, in the general
       case, undefined. In fact, in some tests, any access to the
       return value (even "if(val){...}") causes a segfault (for
       unknown reasons).  When calling from script code, it is best to
       ignore the return value, as this function will throw if it
       cannot find a plugin DLL or if opening the DLL fails at the
       level of the platform-dependent DLL opener (e.g. dlopen()).
       When calling from native code, one can use the normal v8
       conventions for TryCatch
    */
    Handle<Value> LoadPlugin(const Arguments& args);

    /**
       LoadPluginScope is a helper to allow plugins to feed back data
       into a JS engine without having to fish out in-DLL symbols and
       convert them to functions. They cannot be instantiated from
       client code. Instead, they are used like this...

       First we need an initializtion routine to initialize
       our add-on using some client-specified target object
       (typically the global object). Assume we have:

       \code
       Handle<Value> SetupMyAddon( Handle<Object> );    
       \endcode

       The semantics are that the plugin should put its content into
       the object passed to that function. It should return some
       arbitrary value, typically a true value on success and an
       exception on error.

       To call that function automatically when a DLL is opend (via
       LoadPlugin()), add code similar to the following in your DLL:

       \code
       static void InitPlugin()
       {
           using v8::juice::plugin::LoadPluginScope;
           LoadPluginScope * sc = LoadPluginScope::Current();
           if( ! sc ) {
	       // this means that this call to InitPlugin()
	       // did not happen as a result of LoadPlugin()
	       return;
	   }
           sc->SetReturnValue( SetupMyAddon( sc->Target() ) );
       }
       static bool dll_initializer = (InitPlugin(),true);
       \endcode

       Or use the V8_JUICE_PLUGIN_STATIC_INIT() macro in your source file
       somewhere, as it does all of that work for you.

       Here's how it works:

       The dll_initializer variable will get initialized when the DLL
       is opened, which in turn will call InitPlugin(). The code may
       be in a namespace (including an anonymous namespace) or may be
       global - it doesn't matter for our purposes.

       The return value from the initialization is set in the
       LoadPluginScope object, and LoadPlugin() will then pass that
       back to its caller.

       Some notable properties of this plugin model are:

       - Any number of init routines, from any number of source/object
       files, can be stored in a given DLL. They will all be called
       (in an unspecified order!) as part of the static initialization
       phase when the DLL is opened (before the call to dlopen() or
       ::LoadModule() ever returns!). This means plugins don't have to
       be designed with a limitation of one plugin per DLL.

       - 100% type-safe. We do no casting at all.

       - Uses no dlsym() (or similar) hackery to fish out a function
       name from the DLL (which, contrary to popular belief,
       technically provides undefined behaviour).

       - On Linux (and maybe other Unix platforms), the application
       must be linked with the -export-dynamic (or -rdynamic) option,
       or DLL loading will likely fail.
    */
    class LoadPluginScope
    {
    private:
	/** Target of the initialization. */
	Handle<Object> target;
	/** Return value from initialization. */
	Handle<Value> returnVal;
	/**
	   Previous scope in the chain. When we create a new
	   LoadPluginScope(), it's prev member is set to
	   LoadPluginScope::current and LoadPluginScope::current is
	   set to the new object. That is then undone in the dtor.
	*/
	LoadPluginScope * prev;
	/**
	   Marks the current scope. If a LoadPlugin() triggers another
	   LoadPlugin(), the second will get a different LoadPluginScope
	   than the first one.

	   This value is only non-0 when LoadPlugin() is running.
	*/
	static LoadPluginScope * current;
    public:
	/**
	   Returns the current module loading scope. If it is null,
	   the DLL init routine "should" not do anything, as the
	   routine was not called in response to a DLL-open request.
	   Alternately, they "may" decide to populate the current
	   global JS object with their content.
	*/
	static LoadPluginScope * Current();

	/**
	   Returns the target of the current LoadPlugin()
	   request. Normally this corresponds to a Global object, but
	   it need not. The plugin init routine should put all new
	   content (e.g. new functions) in this object, rather than
	   explicitly fishing out the official Global Object from the
	   current Context.
	*/
	Handle<Object> Target() const;

	/**
	   The init routine "should" call this function to set a return
	   value for the module load operation. It may be any arbitrary
	   value. In theory it is safe to pass a value returned from
	   ThrowException(), but this is currently untested (and requires
	   the caller to pay particular attention!).
	*/
	void SetReturnValue( Handle<Value> v );
    private:
	/** Internally used by LoadPlugin(). */
	explicit LoadPluginScope( Handle<Object> target );
	/**
	   Sets LoadPluginScope::current = this->prev.
	*/
	~LoadPluginScope();
	/**
	   Value set via SetReturnValue(), this gets returned by
	   LoadPlugin().
	*/
	Handle<Value> ReturnValue() const;
	// LoadPlugin() is the only place we can instantiate these objects.
	friend Handle< Value > LoadPlugin( std::string const &, Handle< Object > );
    };

    /**
       Returns the shared object used for finding plugins based on
       partial names and lookup paths. See PluginsPath.h for the full
       details.
    */
    PathFinder & PluginsPath();

    /** @typedef Handle<Value> (*PluginInitFunction)( Handle<Object> target )
       Callback type for plugins initialized via
       V8_JUICE_PLUGIN_STATIC_INIT().

       This routine should treat the given target as the logical
       global object, install its new content there, and return a
       non-exception on success.
    */
    typedef Handle<Value> (*PluginInitFunction)( Handle<Object> target );

#if !defined(DOXYGEN)
    namespace Detail
    {
	/**
	   Intended to be called only via the static initialization
	   phase of app/DLL startup in order to register a plugin.
	   
	   Normally this is not called directly, but via
	   V8_JUICE_PLUGIN_STATIC_INIT().

	   This function returns true if it was able to pass on the call
	   to f(). It does not analyze that return value, but passes it
	   back to the LoadPlugin() caller who triggered the plugin
	   load.
	*/
	bool PluginStaticInit( PluginInitFunction f );
    }
#endif // !DOXYGEN

    /** \def V8_JUICE_PLUGIN_STATIC_INIT

        V8_JUICE_PLUGIN_STATIC_INIT is a convenience macro to set up
        the skeleton code needed for initializing a plugin using this
        framework. It is not required - it is simply convenient in
        some cases.

	To use it, simply call it from somewhere in your
	implementation code and pass it the name of a function, which
	must have the same signature as the PluginInitFunction()
	typedef:

	\code
	Handle<Value> (*)( Handle<Object> target )
	\endcode

	The function name may be namespace-qualified.

	Example:

	\code
	V8_JUICE_PLUGIN_STATIC_INIT(SetupMyPlugin);
	\endcode

	This macro may be used multiple times in a single
	implementation file as long as it is passed a different
	function name on each call.

    */
#define V8_JUICE_PLUGIN_STATIC_INIT(INIT_FUNC) \
    static const bool INIT_FUNC ## _v8_plugin_static_initializer  = (::v8::juice::plugin::Detail::PluginStaticInit(INIT_FUNC),true)


}}} // namespaces

#endif /* WANDERINGHORSE_NET_GOOGLE_V8_P3_PLUGIN_H_INCLUDED_ */
