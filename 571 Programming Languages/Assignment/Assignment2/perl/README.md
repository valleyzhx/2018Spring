# request
(1) strings that contain the text “or”,
(2) strings that contain at least two vowel characters (i.e. a, e, i, o, u),
(3) strings that do not start with “h”,
(4) strings that have “e” as the second symbol, and end with the letter “y”,
(5) strings that contain both letters and digits.

```bash
➜  perl git:(master) ✗ grep -rn '$_' .
./hello.pl:63:for (keys %data) {print $_; print "$data{$_} \n"};
./hello.pl:67:    if ($s eq $_) {
./file.pl:18:    print ": $_";
./match.pl:7:    print ": $_";
```
