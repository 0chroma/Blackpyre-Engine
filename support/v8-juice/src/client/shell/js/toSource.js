var o1 = {a:13,
          b:"hi, world"
};


var o2 = {x:o1,y:3,ar:[17,0,1,3,2],z1:o1,z2:o1,aFunc:print,bFunc:function(){print("hi, world");}};
//o2.ar['hi'] = 'does this work with toSource?';
o2.ar.push( 'does THIS work with toSource?');
o2.ar.push(13,42,32);
print(toSource(o2));
print(toSource(NaN));
print(toSource(Infinity));

//print( toSource(PathFinder.shared.plugins) );
