var m = new MyNative();
MyNative.prototype.toString = function()
{
    return '{MyNative str:'+this.str+'}';
}

print('void returns:',m.avoid(),m.avoid1(32),m.avoid2(17,11));
print(m.hi());
print('m.func1() ==',m.func1());
print('m.func2(...) ==',m.func2(m.func1()));
print('m.func3(...) ==',m.func3(m.func1(),m.func2(m.func1())));
 print('m.him(m) ==',m.him(m));
print('m.me() ==',m.me());
print('m.takes3(...) ==',m.takes3(2,2,3));
print('m.str =',(m.str='bye, world!'));
print('m.other =',m.other);
m.otherProxy = new MyNative();
print("m.other ==",m.other);
print("m.otherProxy ==",m.otherProxy);
m.other.str = "i am the other!";
print('m.other.str =',m.other.str,m.other.me());
print('forwarder() =',m.other.forwarder(12,-13,8));
print('someref1() =',m.someref1(m.other));
print('proxiedProp =', m.proxiedProp );
m.proxiedProp += 23;
print('proxiedProp =', m.proxiedProp );

//throw new Error("Testing return from JuiceShell::Include()");

var ex = null;
try
{
    print('m.someref1(non-MyNative) =',m.someref1(undefined));
}catch(e)
{
    ex = e;
    print("Caught expected exception:",e);
}
if( null === ex ) throw("The last test should have thrown but didn't!");

ex = null;
print("my.other.destroy() ==",m.other.destroy());
try
{
    print('undefined.someref1(non-MyNative) =',m.other.str);
}catch(e)
{
    ex = e;
    print("Caught expected exception:",e);
}
if( null === ex ) throw("The last test should have thrown but didn't!");

print("Done!");

if(1)
{
    function SubType()
    {
        this.prototype = this.__proto__ =
            new MyNative();
            //MyNative.call( this, Array.prototype.slice( arguments, [0] ) );//.call(this);
        this.prototype.constructor = arguments.callee;
        print('proto =',this.prototype,'str=',this.str);
        return this;
    }
    
    var sub = new SubType();
    sub.str = "sub.str";
    var sub2 = new SubType();
    sub2.str = "sub2.str";
    print(sub.str,sub2.str,sub.me(),sub2.me());
    print(sub.hi());
    print( 'sub2 instanceof MyNative ==',sub2 instanceof MyNative );
    print("Done again!");
}

m;
