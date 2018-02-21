#! /usr/bin/perl
#
#rules of RE, you know that pretty much

$word = "what do you wanting?";
if($word =~ m/^ing/) { print "$word\n";}

$word = "going home";
print $word, "\n";
if ($word=~m/ing\b/) { print "match 1\n";}
if ($word=~m/\bing/) { print "match 2\n";}

$word = "ing home";
print $word, "\n";
if ($word=~m/ing\b/) { print "match 3\n";}
if ($word=~m/\bing/) { print "match 4\n";}

# replace the first occurrence of abc with cba
$var1 = "abced abcde";
$var1 =~ s/abc/cba/;
print $var1;

# replace all occurrence of abc with cba
$var2 = "abced abcde";
$var2 =~ s/abc/cba/g;
print $var2;

# $&: contains the string matched
# $`: the text until the first match
# $': the text after the last match
# $1, $2: the text matched in the first, second parenthesis

$target = "I have 25 apples";
print "\n", $target, "\n";
if ($target =~ /(\d+)/) {
    print "match\n";
}
print("$&\n");
print("$'\n");
print("$`\n");
print("$1\n");

$exp = "I crave to rule the world!";
if ( $exp =~ /^([A-Za-z+\s]*)\bcrave\b([\sA-Za-z]+)/){
    print "$1\n";
    print "$2\n";
}
