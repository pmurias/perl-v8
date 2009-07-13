use strict;
use warnings;

use V8;

my $ctx = V8::Context->new();

my $r = $ctx->execute(<<'END_JS');
a = 1;
b = 2;
a + b;
END_JS

print $r, "\n";     # => 3

sub foo {
	print "foo called: ", join(q{, }, @_), "\n";
	return "hello from foo!";
}

$ctx->register_method_by_name("foo");

$r = $ctx->execute(<<'END_JS');
foo(a, b, "baz");   /* => foo called: 1, 2, baz */
END_JS

print $r, "\n";     # => bar
