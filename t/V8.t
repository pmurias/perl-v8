use Test::More tests => 4;
BEGIN { use_ok('V8') };

my $ctx = V8::Context->new();

my $r = $ctx->execute(<<'END_JS');
a = 1;
b = 2;
a + b;
END_JS

is($r, 3, 'simple');

sub foo {
  is_deeply(\@_, [1,2,"baz"], 'pass args to sub');

  return "hello from foo!";
}

$ctx->register_method_by_name("foo");

$r = $ctx->execute(<<'END_JS');
foo(a, b, "baz");   /* => foo called: 1, 2, baz */
END_JS

is($r, "hello from foo!", 'simple');
