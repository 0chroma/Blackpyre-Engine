#!/bin/bash
########################################################################
# Generates code for some ClassWrap parts of the v8::juice API.
count=${1-0}

defaultCommand=CtorForwarder
test "$count" -gt 0 || {
    echo "Usage: $0 NUMBER (>=1) [COMMAND=${defaultCommand}]"
    echo "Commands: CtorForwarder"
    echo "Generates specializations for operations taking exactly NUMBER argumnents."
    exit 1
}

command=${2-${defaultCommand}}

aTDecl="" # typename A0, typename A1,...
aTParam="" # A0, A1 ...
castCalls="" # CastFromJS<A0>(argv[0), ...
at=0

########################################################
# must be called first to populate the shared vars
function makeLists()
{
    for (( at = 0; at < count; at = at + 1)); do
    #echo "at=$at"
	local AT="A${at}"
	aTDecl="${aTDecl} typename ${AT}"
	aTParam="${aTParam} ${AT}"
	castCalls="${castCalls} CastFromJS< ${AT} >(argv[${at}])"
	test $at -ne $((count-1)) && {
	    aTDecl="${aTDecl}, "
	    aTParam="${aTParam},"
	    castCalls="${castCalls},"
	}
    done
    #tmplsig="${tmplsig} RV (WrappedType::*Func)(${aTParam})";
}


#######################################################
# Creates Factory_CtorForwarder${count} specializations.
function makeCtorForwarder()
{
    local class=Factory_CtorForwarder${count}
    local base="Detail::Factory_CtorForwarder_Base<T>"
    local err_native_is_null="${callBase}::Call(): Native object is null!"
    local err_too_few_args="${callBase}::Call(): wrong argument count!"
cat <<EOF
/**
A concrete Factory implementation which creates objects by calling
the ${count}-argument ctor and destroys them with 'delete'.

A0 is the first argument type of the ctor. A1 is the second...
*/
template <typename T, ${aTDecl} >
struct ${class} : public ${base}
{
    typedef typename convert::TypeInfo<T>::Type Type;
    typedef typename convert::TypeInfo<T>::NativeHandle NativeHandle;
    static NativeHandle Instantiate( Arguments const &  argv, std::ostream & errmsg )
    {
        CtorForwarder_ArgvCheck_Prep(${count});
        return CF::template Ctor<${aTParam} >(argv);
    }
};
EOF
} # makeMemFuncForwarder()


##########################################################
# here we go...
makeLists

case $command in
    'CtorForwarder')
	makeCtorForwarder
	;;
    *)
	echo "Unhandled command: ${command}"
	exit 2
    ;;
esac
