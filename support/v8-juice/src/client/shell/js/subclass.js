/**
   Causes ChildClass to inherit from ParentClass, in the conventional
   OO sense of the word inherit.

   Unlike real-world inheritance, ParentClass must outlive ChildClass.

   Derived from code posted here:

   http://groups.google.com/group/v8-users/browse_thread/thread/adfc2978ee519b42

   Author: Stephan Beal (http://wanderinghorse.net/home/stephan/)
   License: Public Domain

*/
if(0) Object.prototype._extends_ = function( ChildClass, ParentClass )
{
    if( 1 == arguments.length )
    {
	//ParentClass = ChildClass;
	//ChildClass = this;
	return this._extends_( this, ChildClass );
    }
    function TempClass() {}
    TempClass.prototype = ParentClass.prototype;

    ChildClass.prototype = new TempClass();
    ChildClass.prototype.constructor = ChildClass;
    ChildClass.prototype._superConstructor_ = ParentClass;
    ChildClass.prototype._superClass_ = ParentClass.prototype;
};
if(1) Object.prototype._extends_ = function( ChildClass, ParentClass )
{
    if( 1 == arguments.length )
    {
	//ParentClass = ChildClass;
	//ChildClass = this;
	return this._extends_( this, ChildClass );
    }
    function TempClass() {};
    TempClass.prototype = ParentClass.prototype;

    ChildClass.prototype = new TempClass();
    ChildClass.prototype.constructor = ChildClass;
    ChildClass._superConstructor_ = ParentClass;
    ChildClass._superClass_ = ParentClass.prototype;
};
var MyType = function()
{
    var av = Array.prototype.slice.apply(arguments,[0]);
    print("new MyType(",av.join(','),')');
  this.prop1 = 1;
};

var MySubType = function()
{
  var av = Array.prototype.slice.apply(arguments,[0]);
  MySubType._superConstructor_.call( this, av );
  print("new MySubType(",av.join(','),')');
  this.prop2 = 2;
};


//Object._extends_( MySubType, MyType );
MySubType._extends_( MyType );

var x = new MySubType(7,3,11);

print( x.prop1 + ":" + x.prop2 );
print( x instanceof MyType );

