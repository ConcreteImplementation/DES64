all: tests/makefile demo/makefile
	cd tests/; make;
	cd demo/; make;
	mkdir -p build
	cp des64.h build/
	cp demo/libdes64.a build/