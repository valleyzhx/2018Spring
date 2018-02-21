#! /usr/bin/perl

print "Hello World!\n";

$first_name = "Tom";
$last_name = "Smolka";
$full_name = $first_name." ".$last_name;
print $full_name."\n";

$language = "Perl";
if($language eq "Perl") {print "Correct\n";}

$name1 = "abc"; $name2 = "bca";
if ($name1 gt $name2) {print "greater\n";}
if ($name1 lt $name2) {print "smaller\n";}

@array = (1..5);
print "$array[0]\n";
print "$array[8]\n"; # print out nothing
print "$array[-1]\n";

@array = (1..20);
print @array;
print "\n";

# the find the index of the last element in an array
@numbers = ();
print $#numbers;

#
@array = qw(red blue green);
unshift(@array, "black");
$element = shift @array;
print $element; # black


# splice(@ARRAY, INDEX, LENGTH, @REPLACE_WITH);
@fruits = qw(Banana Orange Apple Mango);
@removed = splice(@fruits, 1, 2);
print @fruits, "\n"; # BananaMango
print @removed, "\n"; # OrangeApple

@array = (1..5);
foreach $element (@array)
{ print "$element\n"; }

# adding to an array
@array1 = (1, 2, 3);
@array2 = (@array1, 4, 5, 6);
print @array2;
print "\n";

# types of data
%data = ('John' => 45, 'Lisa'=> 30, 'Tom' => 40);
print "$data{'John'}\n";
print "$data{'Lisa'}\n";
print "$data{'Tom'}\n";

print keys %data;
print values %data;
print "\n";

for (keys %data) {print $_; print "$data{$_} \n"};

$s = "John";
for (keys %data) {
    if ($s eq $_) {
        print "match\n";
    };
};

# scope
$record = 4;
print "record is ", $record, "\n";
{
    my $record;
    $record = 7;
    print "inside the block, record is ", $record, "\n";
}
print "exit the block, record is ", $record, "\n";
