# Makefile.PL

use inc::Module::Install;

name 'V8';
all_from 'lib/V8.pm';

makemaker_args(
    LDFROM => join(q{ }, '$(OBJECT)', 'bridge.o'),
    LIBS   => join(q{ }, makemaker_args()->{LIBS}, '-lv8', '-lstdc++'),
);

build_requires 'Test::More';

auto_include;
WriteAll;
