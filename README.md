# perl-v8

This is a [Perl5](http://www.perlfoundation.org/perl5/index.cgi) extension
module that lets you interpret
[JavaScript](http://en.wikipedia.org/wiki/JavaScript) by way of [Google's V8
ECMAScript/JavaScript interpreter](http://code.google.com/p/v8/).

The original code for this was lifted from a [Japanese message board of some
sort](http://d.hatena.ne.jp/dayflower/20080905/1220592409).  

I am not the original author of this code!  I just fixed one bug, added a test
for `make test`, and put it up on GitHub for others to find and improve upon.
When I found this code, it was (and is, as of July 12, 2009) the only perl
binding for V8.

This code works fine for me but I would really be happy to turn this over to
someone who is more of an expert in [XS](http://perldoc.perl.org/perlxs.html).

## Installation

Download, build, and install v8.

    svn checkout http://v8.googlecode.com/svn/trunk/ v8

    cd v8

    scons 

    sudo mv include/v8.h /usr/local/include/

    sudo mv libv8.a /usr/local/lib/

Install prerequisite modules

    sudo cpan Module::Install

Build the v8 "bridge"

    make -f bridge.mk

Build the perl extension module.

    perl Makefile.PL

    make

    make test

    sudo make install

Try it out.

    perl test.pl

## Dependencies

This module requires these other modules and libraries:

    libv8

    Module::Install

## Copyright and Licence

Copyright (C) 2009 by [Fictorial LLC](http://fictorial.com).

This library is free software; you can redistribute it and/or modify
it under the same terms as Perl itself, either Perl version 5.10.0 or,
at your option, any later version of Perl 5 you may have available.


