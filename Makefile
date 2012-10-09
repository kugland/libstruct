ifndef DESTDIR
	DESTDIR := /usr/local
endif

all: build

build: FORCE
	$(MAKE) $(MFLAGS) -C src

dep: FORCE
	$(MAKE) $(MFLAGS) -C src dep

install: FORCE
	$(MAKE) $(MFLAGS) -C src -e DESTDIR="$(DESTDIR)" install

uninstall: FORCE
	$(MAKE) $(MFLAGS) -C src -e DESTDIR="$(DESTDIR)" uninstall

doc: FORCE
	doxygen doxygen.cfg

clean: FORCE
	$(MAKE) $(MFLAGS) -C src clean
	$(RM) -rv doc/html doc/latex
	$(RM) -v libstruct-*.zip

dist: clean
	 zip -9 -r libstruct-`date +"%Y%m%d%H%M"`.zip *

FORCE:
