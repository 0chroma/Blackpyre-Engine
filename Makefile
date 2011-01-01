SUPPORT_DIRS	=	 \
			./support/glpng/src

V8_DIRS = ./support/v8

BLACKPYRE_DIRS	=	\
			./src

LBITS := $(shell getconf LONG_BIT)
ifeq ($(LBITS),64)
    V8_EXTRA_ARGS = arch=x64
else
    V8_EXTRA_ARGS = 
endif

all: $(SUPPORT_DIRS) $(V8_DIRS) blackpyre

blackpyre: $(BLACKPYRE_DIRS) finish

v8: $(V8_DIRS) finish

support: $(SUPPORT_DIRS)

$(BLACKPYRE_DIRS): FORCE
	cd $@; $(MAKE)

$(SUPPORT_DIRS): FORCE
	cd $@; $(MAKE)

$(V8_DIRS): FORCE
	cd $@;  scons mode=release library=static snapshot=off $(V8_EXTRA_ARGS)

finish: 
	@echo ""
	@mv -vf ./src/blackpyre ./bin 
	@chmod +x ./bin/blackpyre
	@echo ""
	-ls --color ./bin/*
	@echo ""
	@echo "Now cd to ./bin and run blackpyre!"
	@echo ""

clean:
	for i in $(SUPPORT_DIRS); do ( cd $$i ; $(MAKE) clean ) ; done
	for i in $(BLACKPYRE_DIRS); do ( cd $$i ; $(MAKE) clean ) ; done
	for i in $(V8_DIRS); do ( cd $$i ; scons -c ) ; done
	
FORCE:
