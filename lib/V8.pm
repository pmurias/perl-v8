package V8;

use strict;
use warnings;

our $VERSION = '0.01';

require XSLoader;
XSLoader::load(__PACKAGE__, $VERSION);

package V8::Context;

sub new {
    my $class = shift;
    my $self = bless {}, $class;

    _bind_new_v8context($self);

    return $self;
}

sub DESTROY {
    my $self = shift;
    _destroy_v8context($self);
}

1;
__END__
