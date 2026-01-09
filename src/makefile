# all:
# 	cd greeklib; $(MAKE) greeklib.a
# 	cd morphlib; $(MAKE) morphlib.a
# 	cd gkends; $(MAKE) all
# 	cd gkdict; $(MAKE) all
# 	cd gener; $(MAKE) all
# 	cd anal; $(MAKE) all

# install:
# 	[ -d ../bin ] || mkdir ../bin
# 	cd gkdict; $(MAKE) install
# 	cd gkends; $(MAKE) install
# 	cd gener; $(MAKE) install
# 	cd anal; $(MAKE) install

# clean:
# 	cd anal; $(MAKE) clean
# 	cd gener; $(MAKE) clean
# 	cd gkdict; $(MAKE) clean
# 	cd gkends; $(MAKE) clean
# 	cd greeklib; $(MAKE) clean
# 	cd morphlib; $(MAKE) clean

# libs:
# 	cd gener; $(MAKE) gener.a
# 	cd gkdict; $(MAKE) gkdict.a
# 	cd gkends; $(MAKE) gkends.a
# 	cd greeklib; $(MAKE) greeklib.a
# 	cd morphlib; $(MAKE) morphlib.a



UNAME_S := $(shell uname -s)

.PHONY: dependencies
dependencies:
ifeq ($(UNAME_S),Darwin)
	@if ! which brew > /dev/null; then \
		echo "Error: Homebrew is not installed. Please visit https://brew.sh/ to install it."; \
		exit 1; \
	fi
	@if ! brew list flex > /dev/null 2>&1; then \
		echo "flex is not installed. Installing with brew..."; \
		brew install flex; \
	fi
else ifeq ($(UNAME_S),Linux)
	@if ! which flex > /dev/null; then \
		echo "Error: flex is not found."; \
		echo "Please install it using your distribution's package manager."; \
		echo "For Debian/Ubuntu: sudo apt-get install flex"; \
		echo "For Fedora/CentOS: sudo yum install flex"; \
		exit 1; \
	fi
endif

ifeq ($(UNAME_S),Darwin)
    FLEX_PREFIX := $(shell brew --prefix flex)
    ifneq ($(FLEX_PREFIX),)
        export LDFLAGS += -L$(FLEX_PREFIX)/lib
    endif
endif

all: dependencies
	cd greeklib; $(MAKE) greeklib.a
	cd morphlib; $(MAKE) morphlib.a
	cd gkends; $(MAKE) all
	cd gkdict; $(MAKE) all
	cd gener; $(MAKE) all
	cd anal; $(MAKE) all

install: all
	[ -d ../bin ] || mkdir ../bin
	cd gkdict; $(MAKE) install
	cd gkends; $(MAKE) install
	cd gener; $(MAKE) install
	cd anal; $(MAKE) install

clean:
	cd anal; $(MAKE) clean
	cd gener; $(MAKE) clean
	cd gkdict; $(MAKE) clean
	cd gkends; $(MAKE) clean
	cd greeklib; $(MAKE) clean
	cd morphlib; $(MAKE) clean

libs:
	cd gener; $(MAKE) gener.a
	cd gkdict; $(MAKE) gkdict.a
	cd gkends; $(MAKE) gkends.a
	cd greeklib; $(MAKE) greeklib.a
	cd morphlib; $(MAKE) morphlib.a
