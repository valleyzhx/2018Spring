#! /usr/bin/perl

open FILE, "input.txt" or die $!;
my $lineno = 1;
while (<FILE>) {
    # print $lineno++; # do we have #if debug mechnism
    # print ": $_";
    chomp $_;  # remove new line
    if($_ =~ m/or/) { print "$_ contains or\n"; }
    if($_ =~ m/[aeiou]\w*[aeiou]/) {
        print "$_ contains at least two vowel letters\n";
    }
    if($_ =~ m/^[^h]/) {print "$_ does not start with h\n";}
    if($_ =~ m/^.e\w*y$/) {
        print "$_ has e as the second symbol and ends with y\n";
    }
    if($_ =~ m/[a-zA-Z]/ and $_ =~ m/[0-9]/) {
        print "$_ contains both letters and digits\n";
    }
}
