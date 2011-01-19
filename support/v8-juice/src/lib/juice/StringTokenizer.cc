////////////////////////////////////////////////////////////////////////
//   This file was part of the KDE libraries
//    Copyright (C) 1997 Martin Jones (mjones@kde.org)
//              (C) 1997 Torben Weis (weis@kde.org)
//              (C) 1998 Waldo Bastian (bastian@kde.org)
//
//    This copy is mainained by stephan@s11n.net
//    i have written permission from the three original authors
//    to release this code into the Public Domain, and this copy 
//    falls under that "license."
////////////////////////////////////////////////////////////////////////


#include <v8/juice/StringTokenizer.h>

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>
//-----------------------------------------------------------------------------

namespace v8 { namespace juice {

        enum quoteEnum { NO_QUOTE=0, SINGLE_QUOTE, DOUBLE_QUOTE };


        StringTokenizer::StringTokenizer()
        {
                buffer = 0;
                pos    = 0;
                end    = 0;
                bufLen = 0;
        }

        void StringTokenizer::Tokenize( const char *str, const char *_separators )
        {
                if ( *str == '\0' )
                {
                        pos = 0;
                        return;
                }

                int strLength = strlen( str ) + 1;
                if ( bufLen < strLength )
                {
                        delete [] buffer;
                        buffer = new char[ strLength ];
                        bufLen = strLength;
                }

                const char *src = str;
                end = buffer;
                int quoted = NO_QUOTE;
    
                for ( ; *src != '\0'; src++ )
                {
                        char const *x = strchr( _separators, *src );
                        if (( *src == '\"' ) && !quoted)
                                quoted = DOUBLE_QUOTE;
                        else if (( *src == '\'') && !quoted)
                                quoted = SINGLE_QUOTE;
                        else if ( (( *src == '\"') && (quoted == DOUBLE_QUOTE)) ||
                                  (( *src == '\'') && (quoted == SINGLE_QUOTE)))
                                quoted = NO_QUOTE;
                        else if ( x && !quoted )
                                *end++ = 0;
                        else
                                *end++ = *src;
                }

                *end = 0;

                if ( end - buffer < 1 )
                {
                        // that check used to be <=1, but changed by stephan
                        // because this thing failes to tokenize 1-char strings :/
                        // i /hope/ it doesn't have evil side-effects!!!
                        // Been using it 3 years with this bug and never noticed it. :/
                        pos = 0;	// no tokens
                }
                else
                        pos = buffer;
        }

        const char* StringTokenizer::NextToken()
        {
                if ( pos == 0 )
                        return 0;

                char *ret = pos;
                pos += strlen( ret ) + 1;
                if ( pos >= end )
                        pos = 0;

                return ret;
        }

        StringTokenizer::~StringTokenizer()
        {
                if ( buffer != 0 )
                        delete [] buffer;
        }

        bool StringTokenizer::HasTokens() { return ( pos != 0 ); }
} } // namespaces
