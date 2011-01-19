/************************************************************************
Demonstration of C++-like signals/slots.

These classes are redundant as of 2006.03.28: the Signal and Slot
classes were implemented in native code, and can be installed
by calling ape::init_sigslot_classes() before creating
MonkeyWrapper objects.
************************************************************************/

function DefaultSlotImplementation() {
	throw new Error( "Slot.implementation() was not redefined." );
}

/************************************************************************
Constructor for slots. If you pass it an argument, it must be
a function or string source code which can be used as a function body.
If you do not pass an argument then you must re-assign the 'implementation'
property of this object to a function which implements your slot's logic.

Methods:

.connect( Signal ): connects this slot to the given Signal object.

The .id member is assigned at construction time to uniquely identify
slots. This is used to assist in the connect/disconnect operations
of Signal and may be of use during debugging. Under NO CIRCUMSTANCES
should client code change this member's value!
************************************************************************/
function Slot()
{
	var self = this;
	self.id = Slot.id++;
	if( arguments.length ) {
	    var a0 = arguments[0];
	    var f = (a0 instanceof Function)
		? a0
		: Function(a0.toString());
		this.implementation = f;
	}
	else {
		// client must add implementation() impl
		this.implementation = DefaultSlotImplementation;
	}
	this.connect = function( signal ) {
		signal.connect( this );
	};
	this.disconnect = function( signal ) {
		signal.disconnect( this );
	};

	return self;
}
Slot.id = 1000000;
/************************************************************************
Constructor for signals. To use a Signal object, do the following:

myslot1 = new Slot( "print('This is my slot.')" );
mysignal.connect( myslot1 );
...
mysignal.connect( myslotN );
...
mysignal.fire();


The .connect(Slot) member connects a slot to this signal.

The .disconnect(Slot) member disconnects a connected slot.

The .fire(...) method passes on all arguments to all connected
slots. Returns the number of slots called.

The .count() member returns the number of connected slots.

Set the .silent member to true to disable all signal firing. When
silent.true, fire() will always return 0. Set it to true to enable
firing.

The .slots member is an Array holding all connected slots. Note that
.slots.length does not return an accurate number, because of the way
we index slots.

Set the .debug member to true to enable extra debug output, and to
false to disable debug output.

All other members are for internal use only.
************************************************************************/
function Signal() {
	var self = this;
	this.slots = new Array();
	this.debug = false;
	this.silent = false;
	this.connect = function( slot ) {
		this.slots[slot.id] = slot;
		if( this.debug ) {
			print("Connecting slot #"+slot.id);
		}
		return true;
	};

	this.count = function() {
	    var i = 0;
	    for( var k in this.slots ) {
		++i;
	    }
	    return i;
	};

	this.disconnect = function( slot ) {
		delete this.slots[slot.id];
		if( this.debug ) {
			print("Disconnecting slot #"+slot.id);
		}
		return true;
	};

	this.fire = function() {
		if( this.silent ) { return 0; }
		var i = 0;
		for( var k in self.slots )
		{
			++i;
			var slot = self.slots[k];
			if( this.debug ) {
			    print("Firing to slot #"+k+" (slot.id=="+slot.id+") typeof implementation ==",typeof slot.implementation);//,'slot.implementation=',slot.implementation);
			}
			slot.implementation.apply( slot, Array.prototype.slice.apply( arguments, [0] ) );
		}
		return i;
	};
}


if( 1 ) { // demonstrate how to use it...
	var obj = new Object();
	var s = obj.slotOne = new Slot();
	s.implementation = function() {
		print( "obj.slotOne.implementation() argc ==",arguments.length );
		for( var i = 0; i < arguments.length; ++i ) {
			print( "arguments["+i+"] ==",arguments[i] );
		}
	};

	s = obj.signalOne = new Signal();
	s.connect( obj.slotOne );
	s.connect( obj.slotTwo = new Slot("print('obj.slotTwo.implementation() argc ==',arguments.length)") );
	print("Firing... slot count =",s.count());
	//s.debug = true;
	s.fire(1,4,6);

	s.disconnect( obj.slotTwo );
	//obj.slotTwo.implementation(1,2,3,4,5,6,7,8,9,0);
        function foogle() {
		print( "foogle()" );
	}
	s.connect( obj.slotThree = new Slot(foogle) );
	print("Firing again... slot count =",s.count());
	s.fire( new Date() );
}

1;
