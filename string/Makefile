PWD=$(shell pwd)
cppFlags=-Wall -g -c -fPIC -I../../corelibs++-api/include
libName=libnaeem++-string
majorVersion=1
minorVersion=0

all: compile static dynamic copy_to_api_dir

compile:
	mkdir -p .libs
	g++ $(cppFlags) helper.cc -o .libs/helper.o

static:
	rm -rf .libs/$(libName).a.$(majorVersion).$(minorVersion)
	ar -cq .libs/$(libName).a.$(majorVersion).$(minorVersion) \
	       .libs/helper.o
	rm -rf .libs/$(libName).a.$(majorVersion)
	rm -rf .libs/$(libName).a 
	ln -s $(PWD)/.libs/$(libName).a.$(majorVersion).$(minorVersion) .libs/$(libName).a.$(majorVersion)
	ln -s $(PWD)/.libs/$(libName).a.$(majorVersion).$(minorVersion) .libs/$(libName).a

dynamic:
	g++ -shared -Wl,-soname,$(libName).so.$(majorVersion) -o .libs/$(libName).so.$(majorVersion).$(minorVersion) \
	    .libs/helper.o
	rm -rf .libs/$(libName).so.$(majorVersion)
	rm -rf .libs/$(libName).so
	ln -s $(PWD)/.libs/$(libName).so.$(majorVersion).$(minorVersion) .libs/$(libName).so.$(majorVersion)
	ln -s $(PWD)/.libs/$(libName).so.$(majorVersion).$(minorVersion) .libs/$(libName).so

copy_to_api_dir:
	cp .libs/$(libName).so.$(majorVersion).$(minorVersion) ../../corelibs++-api/lib
	cp .libs/$(libName).a.$(majorVersion).$(minorVersion) ../../corelibs++-api/lib
	rm -rf ../../corelibs++-api/lib/$(libName).so.$(majorVersion)
	rm -rf ../../corelibs++-api/lib/$(libName).so
	rm -rf ../../corelibs++-api/lib/$(libName).a.$(majorVersion)
	rm -rf ../../corelibs++-api/lib/$(libName).a
	ln -s $(PWD)/../../corelibs++-api/lib/$(libName).so.$(majorVersion).$(minorVersion) ../../corelibs++-api/lib/$(libName).so.$(majorVersion)
	ln -s $(PWD)/../../corelibs++-api/lib/$(libName).so.$(majorVersion).$(minorVersion) ../../corelibs++-api/lib/$(libName).so
	ln -s $(PWD)/../../corelibs++-api/lib/$(libName).a.$(majorVersion).$(minorVersion) ../../corelibs++-api/lib/$(libName).a.$(majorVersion)
	ln -s $(PWD)/../../corelibs++-api/lib/$(libName).a.$(majorVersion).$(minorVersion) ../../corelibs++-api/lib/$(libName).a