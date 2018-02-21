#! /usr/bin/perl

# subroutine
sub add_one {
    my ($n) = @_[0]; # Copy first argument
    return ($n + 1);
}

my ($a, $b) = (10, 0);
add_one($a); # Return value is lost
$b = add_one($a); # $a is 10, $b is 11

sub add_two {
    my ($n) = @_[0];
    my ($m) = @_[1];
    return ($m + 2);
}
my ($a, $b) = (10, 0);
add_one($a);
$c = add_one($a);
$d = add_two($a, $b);
print $a, "\n";
print $b, "\n";
print $c, "\n";
print $d, "\n";

sub add {
    @_[0] = @_[0]+1;
}
my $a = 10; add($a);
print $a, "\n"; # 11, call_by_reference
