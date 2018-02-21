#! /usr/bin/perl

open FH, 'output.log' or die $!;

open FH, "> writetest.txt" or die $!; print FH "abc";
open FH, ">> writetest.txt" or die $!; print FH "def";

print "What type of pet do you have?";
my $pet = <STDIN>;
chomp $pet;  # remove new line
print "You have pet $pet";

print "\n";
open FILE, "readtest.txt" or die $!;
my $lineno = 1;
while (<FILE>) {
    print $lineno++;
    print ": $_";
}

open FILE, "readtest.txt" or die $!;
my ($data, $n);
while (($n = read FILE, $data, 4) != 0) {
    print "$n bytes read\n";
    print $data, "\n";
}
close(FILE);
