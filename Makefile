SUPPORT_DIRS	=	 \
			./support/glpng/src

V8_DIRS = \
            ./support/v8

JUICE_DIRS = \
            ./support/v8-juice

BLACKPYRE_DIRS	=	\
			./src

LBITS := $(shell getconf LONG_BIT)
ifeq ($(LBITS),64)
    V8_EXTRA_ARGS = arch=x64
else
    V8_EXTRA_ARGS = 
endif

all: $(SUPPORT_DIRS) $(V8_DIRS) $(JUICE_DIRS) blackpyre

blackpyre: $(BLACKPYRE_DIRS) finish

v8: $(V8_DIRS)

juice: $(JUICE_DIRS)

support: $(SUPPORT_DIRS)


$(BLACKPYRE_DIRS): FORCE
	cd $@; $(MAKE)

$(SUPPORT_DIRS): FORCE
	cd $@; $(MAKE)

$(V8_DIRS): FORCE
	cd $@;  scons mode=release library=shared snapshot=off $(V8_EXTRA_ARGS); echo libv8.so|cpio -pd ./lib/

$(JUICE_DIRS): FORCE
	cd $@; ./configure --disable-plugins --v8-prefix=`pwd`/../v8; $(MAKE)

finish: 
	@echo ""
	@cp -vf ./src/blackpyre .
	@cp -vf ./support/v8-juice/src/lib/juice/libv8-juice.so ./lib
	@cp -vf ./support/v8/libv8.so ./lib
	@chmod +x ./blackpyre
	@echo ""
	-ls --color ./blackpyre ./lib
	@echo ""
	@echo "Now run blackpyre!"
	@echo ""

clean:
	for i in $(SUPPORT_DIRS); do ( cd $$i ; $(MAKE) clean ) ; done
	for i in $(BLACKPYRE_DIRS); do ( cd $$i ; $(MAKE) clean ) ; done
	for i in $(JUICE_DIRS); do ( cd $$i ; $(MAKE) distclean ) ; done
	for i in $(V8_DIRS); do ( cd $$i ; scons -c ; rm -R ./lib ) ; done
	
FORCE:
