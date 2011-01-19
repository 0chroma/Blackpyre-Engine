#!/bin/bash
########################################################################
# Generates code for the ClassBinder API (and friends).
count=${1-0}

test "$count" -gt 0 || {
    echo "Usage: $0 NUMBER (>=1) [COMMAND=BindMemFunc]"
    echo "Commands: MemFuncCallOps, BindMemFunc, MemFuncCaller"
    exit 1
}

command=${2-BindMemFunc}

tmplsig="typename WrappedType, typename RV, "
ttlist="WrappedType, RV,"
tmplsigV="typename WrappedType, void, "
aTDecl="" # typename A0, typename A1,...
aTParam="" # A0, A1 ...
castCalls="" # CastFromJS<A0>(argv[0), ...
at=0
callop=MemFuncCallOp${count}
MemFuncCaller=MemFuncForwarder
#callBase="${MemFuncCaller}<${count}>"
callBase="v8::juice::convert::${MemFuncCaller}<${count}>"
callBaseWeak="WeakMemFuncCaller<${count}>"

########################################################
# must be called first to populate the shared vars
function makeLists()
{
    for (( at = 0; at < count; at = at + 1)); do
    #echo "at=$at"
	local AT="A${at}"
	tmplsig="${tmplsig} typename ${AT},"
	ttlist="${ttlist} ${AT},"
	tmplsigV="${tmplsigV} ${AT},"
	aTDecl="${aTDecl} typename ${AT}"
	aTParam="${aTParam} ${AT}"
	castCalls="${castCalls} convert::CastFromJS< ${AT} >(argv[${at}])"
	test $at -ne $((count-1)) && {
	    aTDecl="${aTDecl}, "
	    aTParam="${aTParam},"
	    castCalls="${castCalls},"
	}
    done
    #tmplsig="${tmplsig} RV (WrappedType::*Func)(${aTParam})";
    funcSig="(WrappedType::*Func)(${aTParam}) "
    tmplsig="typename WrappedType, typename RV, ${aTDecl}, RV ${funcSig}";
    tmplsigV="typename WrappedType, ${aTDecl}, void ${funcSig}";
    tmplspecV="WrappedType, void, ${aTParam}, void ${funcSig}"
}


#######################################################
# Creates ${callBaseWeak} implementations.
function makeCallBase()
{
cat <<EOF
template <>
struct ${callBaseWeak} : ${callBase}
{
    enum { Arity = ${count} };

    template <typename WeakWrappedType, typename RV, ${aTDecl} >
    static Handle<Value> CallOnWeakSelf( RV (WeakWrappedType::*func)(${aTParam}), Arguments const & argv )
    {
	typedef WeakJSClassCreator<WeakWrappedType> Wrapper;
	//typename Wrapper::WrappedType * obj = Wrapper::GetSelf( argv.This() );
        typedef typename Wrapper::WrappedType WT;
        WT * obj = CastFromJS<WT>( argv.This() );
	if( ! obj ) return ThrowException(String::New("${callBaseWeak}::Call() could not find native 'this' object!"));
	return Call( obj, func, argv );
    }
    
    template <typename WeakWrappedType, typename RV, ${aTDecl} >
    static Handle<Value> CallOnWeakSelf( const RV (WeakWrappedType::*func)(${aTParam}) const, Arguments const & argv )
    {
	typedef WeakJSClassCreator<WeakWrappedType> Wrapper;
	//typename Wrapper::WrappedType const * obj = Wrapper::GetSelf( argv.This() );
        typedef typename Wrapper::WrappedType WT;
        WT * obj = CastFromJS<WT>( argv.This() );
	if( ! obj ) return ThrowException(String::New("${callBaseWeak}::Call() could not find native 'this' object!"));
	return Call( obj, func, argv );
    }
    
    template <typename WeakWrappedType, ${aTDecl} >
    static Handle<Value> CallOnWeakSelf( void (WeakWrappedType::*func)(${aTParam}), Arguments const & argv )
    {
	typedef WeakJSClassCreator<WeakWrappedType> Wrapper;
	//typename Wrapper::WrappedType * obj = Wrapper::GetSelf( argv.This() );
        typedef typename Wrapper::WrappedType WT;
        WT * obj = CastFromJS<WT>( argv.This() );
	if( ! obj ) return ThrowException(String::New("${callBaseWeak}::Call() could not find native 'this' object!"));
	return Call( obj, func, argv );
    }
    
    template <typename WeakWrappedType, ${aTDecl} >
    static Handle<Value> CallOnWeakSelf( const void (WeakWrappedType::*func)(${aTParam}) const, Arguments const & argv )
    {
	typedef WeakJSClassCreator<WeakWrappedType> Wrapper;
	//typename Wrapper::WrappedType const * obj = Wrapper::GetSelf( argv.This() );
        typedef typename Wrapper::WrappedType WT;
        WT * obj = CastFromJS<WT>( argv.This() );
	if( ! obj ) return ThrowException(String::New("${callBaseWeak}::Call() could not find native 'this' object!"));
        return Call( obj, func, argv );
    }

};
EOF
} # makeCallBase()


#######################################################
# Creates ${callop} specializations.
function makeMemFuncCallOps()
{
    cat <<EOF
/**
    Member function call forwarder for member functions taking ${count} arguments.
*/
template < ${tmplsig} >
struct ${callop}
{
    enum { Arity = $count };
    typedef WrappedType Type;
    typedef ${callBaseWeak} OpBase;
    static Handle<Value> Call( Type * obj, Arguments const & argv )
    {
	return OpBase::Call( obj, Func, argv );
    }
    static Handle<Value> CallOnWeakSelf( Arguments const & argv )
    {
	return OpBase::CallOnWeakSelf<Type>( Func, argv );
    }
};

/**
    Specialization for member functions taking ${count} args and returning void.
*/
template < ${tmplsigV} >
struct ${callop}< WrappedType,void,${aTParam}, Func >
{
    enum { Arity = $count };
    typedef WrappedType Type;
    typedef ${callBaseWeak} OpBase;
    static Handle<Value> Call( Type * obj, Arguments const & argv )
    {
	return OpBase::Call( obj, Func, argv );
    }
    static Handle<Value> CallOnWeakSelf( Arguments const & argv )
    {
	return OpBase::CallOnWeakSelf<Type>( Func, argv );
    }
};
EOF
echo
return
}
#######################################################
# Creates ${callop} specializations for const members.
function makeMemFuncCallOpsConst()
{
    cat <<EOF
/**
    Member function call forwarder for const member functions taking ${count} arguments
    and returning RV.
*/
template < typename WrappedType, typename RV, ${aTDecl}, RV ${funcSig} const >
struct ${callop}< const WrappedType, RV,${aTParam}, Func>
{
    enum { Arity = $count };
    typedef WrappedType Type;
    typedef ${callBaseWeak} OpBase;
    static Handle<Value> Call( Type const * obj, Arguments const & argv )
    {
	return OpBase::Call( obj, Func, argv );
    }
    static Handle<Value> CallOnWeakSelf( Arguments const & argv )
    {
	return OpBase::CallOnWeakSelf<const Type>( Func, argv );
    }
};

/**
    Specialization for const member functions taking ${count} args and returning void.
*/
template < typename WrappedType, ${aTDecl}, void ${funcSig} const >
struct ${callop}< const WrappedType,void,${aTParam}, Func >
{
    enum { Arity = $count };
    typedef WrappedType Type;
    static Handle<Value> Call( Type const * obj, Arguments const & argv )
    {
	return OpBase::Call( obj, Func, argv );
    }
    static Handle<Value> CallOnWeakSelf( Arguments const & argv )
    {
	return OpBase::CallOnWeakSelf<const Type>( Func, argv );
    }
};
EOF
}
###############################################
# Creates ClassBinder::BindMemFunc() overloads
function makeBindFunc()
{
cat <<EOF
/**
   Overload requiring a WrappedType CONSTNESS member function
   taking ${count} args and returning RV.
*/
template < typename RV, ${aTDecl}, RV ${funcSig} CONSTNESS >
ClassBinder & BindMemFunc( char const * name )
{
    typedef Detail::${callop}< CONSTNESS WrappedType, RV, ${aTParam}, Func > Caller;
    this->Set(name, Detail::MemFuncCallOp< Caller >::Call );
    return *this;
}
EOF

}

##########################################################
# here we go...
makeLists
false && {
    echo funcSig=${funcSig}
    echo tmplsig=${tmplsig}
    echo tmplsigV=${tmplsigV}
    echo tmplspecV=${tmplspecV}
}


case $command in
    'BindMemFunc')
        makeBindFunc | sed -e 's/CONSTNESS //g'
	makeBindFunc | sed -e 's/CONSTNESS /const /g'
	;;
    'MemFuncCallOps')
	    makeMemFuncCallOps
	    ;;
    'MemFuncCaller')
	makeCallBase
	;;
    *)
	echo "Unhandled command: ${command}"
	exit 2
    ;;
esac
