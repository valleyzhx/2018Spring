#! /usr/bin/perl

$weather = "Sun";
# braces are required
if ( $weather eq "Rain" ) {
    print "Umbrella!\n";
}
elsif ( $weather eq "Sun" ) {
    print "Sunglasses!\n";
}
else {
    print "Anti Radiation Armor!\n";
}

# eq, gt, ge, lt, le
# but do not find not equel operator

$weather = "Rain";
unless ($weather eq "Rain") {
    print "Dress as you wish!\n";
} else {
    print "Umbrella!\n";
}

$i = 0;
while ( $i <= 3) {
    print "$i\n";
    $i++;
}
$i = 0;
until ($i == 3) {
    print "$i\n"; $i++;
}

for ( $i = 0; $i <= 3; $i=$i+1 ) {
    print "$i\n";
}

for ( $i = 0; $i < 10; $i++) {
    if ($i == 1 || $i == 3) { next; }
    elsif($i == 5) { last; }
    else { print "$i\n";}
}
