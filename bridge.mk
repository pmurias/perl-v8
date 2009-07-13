# bridge.mk

PERL_INC=$(shell perl -MConfig -e 'print $$Config{archlib}')/CORE

CFLAGS+=-Wall -fPIC -fno-rtti -I$(PERL_INC)

all:    build

build:  bridge.o

clean:
	rm -f bridge.o

bridge.o: bridge.cc bridge.h
	g++ $(CFLAGS) -c -o $@ $<

bridge.o: bridge.mk

.PHONY:	all build clean
