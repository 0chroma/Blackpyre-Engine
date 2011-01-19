var foo = {_a:"this is a"};
foo.__defineGetter__("a", function() { return this._a; } );

foo.__defineSetter__("a", function() { this._a = arguments[0]; } );

print(foo.a);
foo.a = "bye, world";
print( foo._a );
