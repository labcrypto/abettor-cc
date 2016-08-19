#  The MIT License (MIT)
#
#  Copyright (c) 2015 LabCrypto Org.
#
#  Permission is hereby granted, free of charge, to any person obtaining a copy
#  of this software and associated documentation files (the "Software"), to deal
#  in the Software without restriction, including without limitation the rights
#  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#  copies of the Software, and to permit persons to whom the Software is
#  furnished to do so, subject to the following conditions:
#  
#  The above copyright notice and this permission notice shall be included in all
#  copies or substantial portions of the Software.
#  
#  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
#  SOFTWARE.
#

PWD=$(shell pwd)
cppFlags=-Wall -g -c -fPIC -I../../LabCryptoOrg-abettor-cc-api/include `pkg-config --cflags libpq`
libName=libabettor++-db
majorVersion=1
minorVersion=0

all: compile static dynamic copy_to_api_dir

compile:
	mkdir -p .libs
	g++ $(cppFlags) pgsql/driver.cc -o .libs/pgsql_driver.o

static:
	rm -rf .libs/$(libName).a.$(majorVersion).$(minorVersion)
	ar -cq .libs/$(libName).a.$(majorVersion).$(minorVersion) \
	       .libs/pgsql_driver.o
	rm -rf .libs/$(libName).a.$(majorVersion)
	rm -rf .libs/$(libName).a 
	ln -s $(PWD)/.libs/$(libName).a.$(majorVersion).$(minorVersion) .libs/$(libName).a.$(majorVersion)
	ln -s $(PWD)/.libs/$(libName).a.$(majorVersion).$(minorVersion) .libs/$(libName).a

dynamic:
	g++ -shared -Wl,-soname,$(libName).so.$(majorVersion) -o .libs/$(libName).so.$(majorVersion).$(minorVersion) \
	    .libs/pgsql_driver.o
	rm -rf .libs/$(libName).so.$(majorVersion)
	rm -rf .libs/$(libName).so
	ln -s $(PWD)/.libs/$(libName).so.$(majorVersion).$(minorVersion) .libs/$(libName).so.$(majorVersion)
	ln -s $(PWD)/.libs/$(libName).so.$(majorVersion).$(minorVersion) .libs/$(libName).so

copy_to_api_dir:
	cp .libs/$(libName).so.$(majorVersion).$(minorVersion) ../../LabCryptoOrg-abettor-cc-api/lib/gcc-amd64
	cp .libs/$(libName).a.$(majorVersion).$(minorVersion) ../../LabCryptoOrg-abettor-cc-api/lib/gcc-amd64
	rm -rf ../../LabCryptoOrg-abettor-cc-api/lib/gcc-amd64/$(libName).so.$(majorVersion)
	rm -rf ../../LabCryptoOrg-abettor-cc-api/lib/gcc-amd64/$(libName).so
	rm -rf ../../LabCryptoOrg-abettor-cc-api/lib/gcc-amd64/$(libName).a.$(majorVersion)
	rm -rf ../../LabCryptoOrg-abettor-cc-api/lib/gcc-amd64/$(libName).a
	ln -s $(PWD)/../../LabCryptoOrg-abettor-cc-api/lib/gcc-amd64/$(libName).so.$(majorVersion).$(minorVersion) ../../LabCryptoOrg-abettor-cc-api/lib/gcc-amd64/$(libName).so.$(majorVersion)
	ln -s $(PWD)/../../LabCryptoOrg-abettor-cc-api/lib/gcc-amd64/$(libName).so.$(majorVersion).$(minorVersion) ../../LabCryptoOrg-abettor-cc-api/lib/gcc-amd64/$(libName).so
	ln -s $(PWD)/../../LabCryptoOrg-abettor-cc-api/lib/gcc-amd64/$(libName).a.$(majorVersion).$(minorVersion) ../../LabCryptoOrg-abettor-cc-api/lib/gcc-amd64/$(libName).a.$(majorVersion)
	ln -s $(PWD)/../../LabCryptoOrg-abettor-cc-api/lib/gcc-amd64/$(libName).a.$(majorVersion).$(minorVersion) ../../LabCryptoOrg-abettor-cc-api/lib/gcc-amd64/$(libName).a