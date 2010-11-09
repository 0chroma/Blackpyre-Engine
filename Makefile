SUPPORT_DIRS	=	 \
			./support/glpng/src

V8_DIRS = ./support/v8

BLACKPYRE_DIRS	=	\
			./src

all: $(SUPPORT_DIRS) $(V8_DIRS) blackpyre

blackpyre: $(BLACKPYRE_DIRS) finish

v8: $(V8_DIRS) finish

support: $(SUPPORT_DIRS)

$(BLACKPYRE_DIRS): FORCE
	cd $@; $(MAKE)

$(SUPPORT_DIRS): FORCE
	cd $@; $(MAKE)

$(V8_DIRS): FORCE
	cd $@;  scons mode=release library=shared snapshot=off

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
