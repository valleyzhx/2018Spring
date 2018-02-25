#! /usr/bin/perl

$word1 = "ab";
$word2 = "abab";
$word3 = "abbb";
$word4 = "ababb";
$word5 = "abbab";

# if($word1 =~ m/(a(bb)*b)+/) { print "pass1\n"; }

@words = qw(ab abab abbb ababb abbab);

foreach $word (@words){
    if($word =~ m/(a(bb)*b)+/){
        print $word, " passed\n";
    } else{
        print $word, " not passed\n";
    }
}
