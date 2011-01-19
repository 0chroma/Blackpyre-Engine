#ifndef V8_JUICE_PATHFINDER_H_INCLUDED
#define V8_JUICE_PATHFINDER_H_INCLUDED
// Author: stephan beal <stephan@s11n.net>
// License: Public Domain

#include <string>
#include <list>
#include <map>
#include <v8.h>
namespace v8 { namespace juice {

    /**
       PathFinder searches for files using a set of prefixes
       (paths) and suffixes (file extensions).
           
       Example:

       <pre>
       PathFinder p;
       p.Path( "/lib:/usr/lib" );
       p.Extensions( ".a:.so" );
       std::cout << p.Find( "libz" ) << std::endl;
       </pre>

       That would print an empty string if it finds nothing, or a
       string if it finds any of the following:

       - libz (that is, if the value passed is an existing file,
       it is returned as-is).
       - /lib/libz
       - /lib/libz.a
       - /lib/libz.so
       - /usr/lib/libz
       - /usr/lib/libz.a
       - /usr/lib/libz.so


       Maintainer's note:

       This code was one of my very first STL-based classes, and the
       implementation probably shows that very clearly. That said, it
       has worked well for me for many years now without any
       appeciable maintenance. :)
    */
    class PathFinder
    {
    public:

	/**
	   A list type returned by some functions.

	   TODO: consider using a std::set instead of a std::list.
	*/
	typedef std::list<std::string> StringList;

	/**
	   Creates object with the given path/extension/separator list.
	*/
	explicit PathFinder( const std::string & path = std::string(), const std::string & ext = std::string(), const std::string & pathsep = ":" );

	virtual ~PathFinder();

	/**
	   Returns a PathSeparator()-separated string of all paths
	   added via add/Path().
	*/
	std::string PathString() const;

	/**
	   Sets the string used as a separator for the
	   string-based variants of Path(), extentions(), etc.
	   If sep.empty() then a default of ":" is set instead
	   (we cannot tokenize paths based on an empty separator).
	*/
	void PathSeparator( const std::string & sep );

	/**
	   Returns the path separator string. Default is ":";
	*/
	std::string PathSeparator() const;

	/**
	   Sets the path to p, which should be a PathSeparator()-delimited string.
	   Returns the number of path elements parsed from p.
	*/
	virtual std::size_t Path( const std::string & p );

	/**
	   Sets the path to the given list of directories.
	   Returns the number of elements in the list.
	*/
	virtual std::size_t Path( const StringList & p );

	/**
	   Adds p to the path. May be path_separtor()-delimited.
	*/
	virtual void AddPath( const std::string & p );

	/**
	   Adds a "search extension." Sample:
	   finder.extension( ".txt:.TXT" ); Will now try all
	   path combinations with the rightmost characters
	   matching ".txt" or ".TXT" (in that order). Be sure
	   to include a period if you want that searched -
	   that is so this class can be used to find non-files
	   and those with non-traditional extensions, like
	   "foo_EXT".
	*/
	virtual void AddExtension( const std::string & ext );
	/**
	   like AddExtension(), but overwrites extension list.
	   Returns the number of entries parsed from the string.
	*/
	virtual std::size_t Extensions( const std::string & ext );
	/**
	   Sets the extensions list to the given list.
	   Returns the number of entries in p.
	*/
	virtual std::size_t Extensions( const StringList & p );

	/**
	   Returns the PathSeparator()-delimited listed of file
	   suffixes to use when searching for a path.
	*/
	std::string ExtensionsString() const;
	/**
	   Returns this object's extensions list.
	*/
	StringList Extensions() const;

	/** Non-const overload, intended for serialization. */
	StringList & Extensions();

	/**
	   Helper function to collapse a list into a string.

	   This function was changed from a normal member to
	   static member in s11n version 1.1.3.
	*/
	static std::string JoinList( const StringList & list, const std::string & separator );

	/**
	   Returns true if path is readable.
	*/
	static bool IsAccessible( const std::string & path );

	/**
	   Returns the "base name" of the given string: any part
	   following the final directory separator character.
	*/
	static std::string BaseName( const std::string & );

	/**
	   Returns a platform-dependent directory separator. This
	   is set when the class is compiled:

	   Windows: '\\'
	   Everyone else: '/'
	*/
	static std::string DirSeparator();

	/**
	   Returns the full path of the given resource,
	   provided it could be found using the available
	   lookup paths/extensions and is readable.  Note that
	   this might return a relative path, especially if
	   the resourcename passed to it immediately resolves
	   to an existing resource.  It returns an empty
	   string if the resourcename cannot be found in the
	   filesystem tree (or is otherwise unaccessible).

	   If check_cache is false then this function ignores
	   its lookup cache and searches again, otherwise it
	   uses a cache. When caching it will always return
	   the same result for any given resourcename.
	*/
	std::string Find( const std::string & resourcename, bool check_cache ) const;
	/** Equivalent to Find(resourcename,true). */
	std::string Find( const std::string & resourcename ) const { return this->Find(resourcename,true); }

	/**
	   Empties the hit-cache used by Find().
	*/
	void ClearCache();

	/**
	   Returns a list of all items added via AddPath() and path().
	*/
	StringList Path() const;

	/** Non-const overload, intended mainly for serialization
	    purposes. */
	StringList & Path();

	/** Returns true if this object has no paths or extensions. */
	bool IsEmpty() const;

    private:
	StringList paths;
	StringList exts;
	std::string pathseparator;
	typedef std::map < std::string, std::string > StringStringMap;
	typedef StringStringMap::iterator StringStringIterator;
	mutable StringStringMap hitcache;
    };

    /**
       Shared instance of PathFinder used for searching for scripts.
    */
    PathFinder & ScriptsPath();

    /**

    Sets up script-side access to the PathFinder class and to the
    shared PathFinder instance available via
    v8::juice::plugin::PluginsPath().

    After calling this, the shared plugin path is available script-side
    as the object 'PathFinder.shared.plugins'. Modifying that object
    will modify the search path for plugin loading.

    The returned object has the following functions
    and functions:

    - String pathString()
    - int setPathString( String ) 
    - Array pathArray()
    - int setPathArray( Array ) 
    - String pathSeparator()
    - void setPathSeparator( String ) 
    - Array extensionsArray()
    - int setExtensionsArray( Array ) 
    - String extensionsString()
    - int setExtensionsString( String ) 
    - void addPathString( String ) 
    - void addExtensionString( String ) 
    - String find( String ) 
    - void clearCache()
    - bool isEmpty()

    For the full JS-side API docs see:

    http://code.google.com/p/v8-juice/wiki/PathFinderClass
    */
    v8::Handle< ::v8::Value > SetupPathFinderClass(const ::v8::Handle< ::v8::Object > target );

}} // namespaces

#endif // V8_JUICE_PATHFINDER_H_INCLUDED
