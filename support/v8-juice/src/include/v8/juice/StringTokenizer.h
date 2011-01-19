#ifndef CODE_GOOGLE_COM_V8_JUICE_STRINGTOKENIZER_H
#define CODE_GOOGLE_COM_V8_JUICE_STRINGTOKENIZER_H

namespace v8 { namespace juice {


        /**
           StringTokenizer is a... well, a string tokenizer, modelled after
           Java's java.util.StringTokenizer class.

           This code used to be part of the KDE 1.x libraries: (named StringTokenizer)

           Copyright (C) 1997 Martin Jones (mjones@kde.org),
           (C) 1997 Torben Weis (weis@kde.org), and
           (C) 1998 Waldo Bastian (bastian@kde.org)
           
           Then this code was part of the QUB project:

           Copyright (C) 2000-2003 stephan beal (sgbeal@users.sourceforge.net)
           and Rusty Ballinger (bozo@users.sourceforge.net)
           
           THIS code is part of the s11n project, and is maintained by
           stephan@s11n.net. i have been graciously granted explicit
           permission from the three original authors to release this
           code into the Public Domain, and this copy falls under that
           "license." (The original license was GNU GPL.)
        */

        class StringTokenizer
        {
        public:
                StringTokenizer();
                ~StringTokenizer();

                /**
                   Sets the token list and separator to be used by
                   subsequent NextToken() calls.

                   It is important that the strings not be
                   destroyed/freed by the client before this object is
                   done with them. That is, do not call Tokenize(),
                   then free the strings, then call HasTokens() or
                   NextToken(). (In practice, this has never happened.)
                 */
                void Tokenize( const char * sequence, const char * separator );

                /**
                   Returns the next token in the list. Results are
                   undefined if this method is called when
                   HasTokens() returns false.
                */
                const char* NextToken();

                /**
                   Returns true if this object has another token to
                   return via NextToken().
                 */
                bool HasTokens();

        private:
                char *pos;
                char *end;
                char *buffer;
                int  bufLen;
        };

} } // namespaces
#endif // CODE_GOOGLE_COM_V8_JUICE_STRINGTOKENIZER_H
