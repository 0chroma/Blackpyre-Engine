//    Author: stephan beal <stephan@s11n.net>
//    License: Public Domain

#include <iostream>

#include <v8/juice/PathFinder.h>

#ifndef WIN32
#  define WIN32 0
#endif

#if WIN32
#  include  <io.h>
#  include  <stdio.h>
#else
#  include <unistd.h>
#endif

namespace v8 { namespace juice {


    PathFinder::~PathFinder()
    {
	// DTOROUT(PathFinder) << this->PathString() << std::endl;
    }

    PathFinder::PathFinder( const std::string & p, const std::string & e, const std::string & pathsep )
    {
	this->PathSeparator( pathsep );
	this->Path( p );
	this->Extensions( e );
    }


    bool PathFinder::IsEmpty() const
    {
	return this->paths.empty() && this->exts.empty();
    }

    std::string PathFinder::PathSeparator() const
    {
	return this->pathseparator;
    }

    void PathFinder::PathSeparator( const std::string & sep )
    {
	this->pathseparator = sep.empty() ? ":" : sep;
    }

    std::string PathFinder::JoinList( const StringList & list, const std::string & separator )
    {
	std::string ret;
	unsigned long count = list.size();
	unsigned long at = 0;
	StringList::const_iterator it = list.begin();
	StringList::const_iterator et = list.end();
	for(; it != et; ++it )
	{

	    ret += (*it);
	    if( ++at != count ) ret += separator;
	}
	return ret;
    }
    std::string PathFinder::PathString() const
    {
	return this->JoinList( this->paths, this->pathseparator );
    }

    PathFinder::StringList PathFinder::Path() const
    {
	return this->paths;
    }

    PathFinder::StringList & PathFinder::Path()
    {
	return this->paths;
    }

    std::string PathFinder::ExtensionsString() const
    {
	return this->JoinList( this->exts, this->pathseparator );
    }

    PathFinder::StringList PathFinder::Extensions() const
    {
	return this->exts;
    }

    PathFinder::StringList & PathFinder::Extensions()
    {
	return this->exts;
    }


    std::size_t tokenize_to_list( const std::string & str, std::list<std::string> & li, const std::string & sep )
    { // internal helper function
	if( str.empty() ) return 0;

	std::size_t c = 0;

	std::string token;
	std::string::size_type sz = str.size();
	for( std::string::size_type i = 0; i < sz; i++ )
	{
	    if( sz-1 == i ) token += str[i];
	    if( str.find( sep, i ) == i || (sz-1 == i) )
	    {
		//CERR << "token="<<token<<std::endl;
		li.push_back( token );
		token = "";
		i += sep.size() - 1;
		continue;
	    }
	    token += str[i];
	}
	return c;
    }

    std::size_t PathFinder::Path( const std::string & p )
    {
	this->paths.erase( this->paths.begin(), this->paths.end() );
	return tokenize_to_list( p, this->paths, this->pathseparator );
    }

    std::size_t PathFinder::Path( const PathFinder::StringList & p )
    {
	this->paths = p;
	return this->paths.size();
    }

    void PathFinder::AddPath( const std::string & p )
    {
	tokenize_to_list( p, this->paths, this->pathseparator );
    }


    std::size_t PathFinder::Extensions( const std::string & p )
    {
	this->exts.erase( this->exts.begin(), this->exts.end() );
	return tokenize_to_list( p, this->exts, this->pathseparator );
    }

    std::size_t PathFinder::Extensions( const PathFinder::StringList & e )
    {
	this->exts = e;
	return this->exts.size();
    }

    void PathFinder::AddExtension( const std::string & p )
    {
	tokenize_to_list( p, this->exts, this->pathseparator );
    }

    // static
    bool PathFinder::IsAccessible( const std::string & path )
    {
#if WIN32
#  define CHECKACCESS _access
#  define CHECKRIGHTS 0
#else
#  define CHECKACCESS access
#  define CHECKRIGHTS F_OK
#endif

	return 0 == CHECKACCESS( path.c_str(), CHECKRIGHTS );
#undef CHECKACCESS
#undef CHECKRIGHTS
    }

    std::string PathFinder::BaseName( const std::string & name )
    {
	std::string::size_type slashat = name.find_last_of( PathFinder::DirSeparator() );
	if ( slashat == std::string::npos )
	    return name;
	return name.substr( slashat + 1 );
    }


    std::string PathFinder::DirSeparator()
    {
#if WIN32
	return std::string( "\\" );
#else
	return std::string( "/" );
#endif
    }


    std::string PathFinder::Find( const std::string & resource, bool check_cache ) const
    {
	//static const std::string NOT_FOUND = "PathFinder::Find() : no findie";
	if( resource.empty() ) return resource;

#define CHECKPATH(CHECKAT)						\
        if( ! CHECKAT.empty() && PathFinder::IsAccessible( CHECKAT ) ) \
        { this->hitcache[resource] = CHECKAT; return CHECKAT; }

	//CERR << "Find( " << resource << " )" << std::endl;
	if( check_cache )
	{
	    std::map <std::string,std::string>::iterator mapiter;
	    mapiter = this->hitcache.find( resource );
	    if( this->hitcache.end() != mapiter ) return (*mapiter).second;
	}

	CHECKPATH( resource );

	StringList::const_iterator piter = this->paths.begin();
	StringList::const_iterator eiter = this->exts.begin();

	std::string path;
	std::string ext;

	if ( PathFinder::IsAccessible( resource ) )
	    return resource;

	piter = this->paths.begin();
	std::string checkhere;
	while ( piter != this->paths.end() )
	{
	    path = ( *piter );
	    if ( !path.empty() )
	    {
		path += PathFinder::DirSeparator();
	    }
	    ++piter;
	    checkhere = path + resource;
	    //CERR << "Find( " << resource << " ) checking " << checkhere << std::endl;
	    CHECKPATH( checkhere );
	    eiter = this->exts.begin();
	    while ( eiter != this->exts.end() )
	    {
		ext = ( *eiter );
		++eiter;
		checkhere = path + resource + ext;
		//CERR << "Find( " << resource << " ) checking " << checkhere << std::endl;
		CHECKPATH( checkhere );
	    }
	}
	//CERR << "Find( "<<resource<<" ): not found :(" << std::endl;
	// so arguable:
	// this->hitcache[resource] = "";
	return std::string();
    }
#undef CHECKPATH
    void PathFinder::ClearCache()
    {
	this->hitcache.clear();
    }

}} // namespaces

